#include "common.h"

BOOL read_source(char* fname, sBuf* source)
{
    int f = open(fname, O_RDONLY);

    if(f < 0) {
        fprintf(stderr, "%s doesn't exist(2)\n", fname);
        return FALSE;
    }

    while(1) {
        char buf[BUFSIZ+1];
        int size = read(f, buf, BUFSIZ);

        if(size == 0) {
            break;
        }
        else if(size < 0) {
            fprintf(stderr, "unexpected error\n");
            close(f);
            return FALSE;
        }

        buf[size] = 0;
        sBuf_append_str(source, buf);

        if(size < BUFSIZ) {
            break;
        }
    }

    close(f);

    return TRUE;
}

BOOL delete_comment(sBuf* source, sBuf* source2)
{
    char* p = source->mBuf;

    BOOL in_string = FALSE;
    BOOL in_char = FALSE;

    while(*p) {
        if((in_string || in_char) && *p == '\\') {
            sBuf_append_char(source2, *p);
            p++;
            sBuf_append_char(source2, *p);
            p++;
        }
        /// comment1 ///
        else if(!in_string && !in_char && *p == '/' && *(p+1) == '*') {
            p+=2;
            int nest = 0;
            while(1) {
                if((in_string || in_char) && *p == '\\') {
                    p++;
                    p++;
                }
                else if(!in_char && *p == '"') {
                    p++;
                    in_string = !in_string;
                }
                else if(!in_string && *p == '\'') {
                    p++;
                    in_char = !in_char;
                }
                else if(*p == 0) {
                    fprintf(stderr, "there is not a comment end until source end\n");
                    return FALSE;
                }
                else if(!in_string && !in_char && *p == '/' && *(p+1) == '*') {
                    p+=2;
                    nest++;
                }
                else if(!in_string && !in_char && *p == '*' && *(p+1) == '/') {
                    p+=2;
                    if(nest == 0) {
                        break;
                    }

                    nest--;
                }
                else if(*p == '\n') {
                    sBuf_append_char(source2, *p);   // no delete line field for error message
                    p++;
                }
                else {
                    p++;
                }
            }
        }
        /// comment2 ///
        else if(!in_char && !in_string && *p == '#') {
            p++;

            while(1) {
                if(*p == 0) {
                    break;
                }
                else if(*p == '\n') {
                    //p++;      // no delete line field for error message
                    break;
                }
                else {
                    p++;
                }
            }
        }
        else if(!in_char && *p == '"') {
            in_string = !in_string;
            sBuf_append_char(source2, *p);
            p++;
        }
        else if(!in_string && *p == '\'') {
            in_char = !in_char;
            sBuf_append_char(source2, *p);
            p++;
        }
        else if(*p == '\\' && *(p+1) == '/' && *(p+2) == '*') {
            sBuf_append_char(source2, *p);
            p++;
            sBuf_append_char(source2, *p);
            p++;
            sBuf_append_char(source2, *p);
            p++;
        }
        else if(*p == '\\' && *(p+1) == '#') {
            sBuf_append_char(source2, *p);
            p++;
            sBuf_append_char(source2, *p);
            p++;
        }
        else {
            sBuf_append_char(source2, *p);
            p++;
        }
    }

    return TRUE;
}

static BOOL write_code_and_constant_to_file(sByteCode* code, sConst* constant, int var_num, char* fname, BOOL js)
{
    sBuf buf;
    sBuf_init(&buf);

    sBuf_append_str(&buf, "CLOVER SCRIPT FILE");

    sBuf_append(&buf, &var_num, sizeof(int));

    sBuf_append(&buf, &code->mLen, sizeof(int));
    sBuf_append(&buf, code->mCodes, code->mLen);

    sBuf_append(&buf, &constant->mLen, sizeof(int));
    sBuf_append(&buf, constant->mConst, constant->mLen);

    char output_fname[PATH_MAX];

    char* p = fname;
    char* p2 = output_fname;
    while(*p) {
        if(*p == '.') {
            break;
        }
        else {
            *p2++ = *p++;
        }
    }

    if(p2 - output_fname > PATH_MAX-5) {
        fprintf(stderr, "too long file name\n");
        MFREE(buf.mBuf);
        return FALSE;
    }

    *p2 = 0;

    if(js) {
        xstrncat(output_fname, ".ojscl", PATH_MAX);
    }
    else {
        xstrncat(output_fname, ".ocl", PATH_MAX);
    }

    FILE* f = fopen(output_fname, "w");
    if(f == NULL) {
        fprintf(stderr, "can't open %s\n", output_fname);
        MFREE(buf.mBuf);
        return FALSE;
    }
    fwrite(buf.mBuf, 1, buf.mLen, f);
    fclose(f);

    MFREE(buf.mBuf);

    return TRUE;
}

BOOL compile_script(char* fname, char* source, BOOL js)
{
    sParserInfo info;
    memset(&info, 0, sizeof(sParserInfo));

    info.p = source;
    info.source = source;
    info.sname = fname;
    info.sline = 1;
    info.lv_table = init_var_table();
    info.parse_phase = 0;
    info.mJS = js;

    sCompileInfo cinfo;
    memset(&cinfo, 0, sizeof(sCompileInfo));

    sByteCode code;
    sByteCode_init(&code);
    cinfo.code = &code;

    sConst constant;
    sConst_init(&constant);
    cinfo.constant = &constant;

    cinfo.lv_table = info.lv_table;
    cinfo.no_output = FALSE;
    cinfo.pinfo = &info;

    info.cinfo = &cinfo;

    while(*info.p) {
        info.exist_block_object_err = FALSE;
        info.next_command_is_to_bool = FALSE;
        unsigned int node = 0;
        if(!expression(&node, &info)) {
            return FALSE;
        }

#ifdef VM_LOG
    //show_node(node);
#endif

        cinfo.sname = gNodes[node].mSName;
        cinfo.sline = gNodes[node].mLine;

        if(info.err_num == 0 && node != 0) {
            append_opecode_to_code(cinfo.code, OP_HEAD_OF_EXPRESSION, cinfo.no_output);

            append_opecode_to_code(cinfo.code, OP_MARK_SOURCE_CODE_POSITION, cinfo.no_output);
            append_str_to_constant_pool_and_code(cinfo.constant, cinfo.code, cinfo.sname, cinfo.no_output);
            append_int_value_to_code(cinfo.code, cinfo.sline, cinfo.no_output);

            if(!compile(node, &cinfo)) {
                sByteCode_free(&code);
                sConst_free(&constant);
                return FALSE;
            }

            append_opecode_to_code(cinfo.code, OP_SIGINT, cinfo.no_output);

            arrange_stack(&cinfo);
        }

        if(*info.p == ';') {
            info.p++;
            skip_spaces_and_lf(&info);
        }
    }

    if(info.err_num > 0 || cinfo.err_num > 0) {
        fprintf(stderr, "Parser error number is %d. Compile error number is %d\n", info.err_num, cinfo.err_num);
        sByteCode_free(&code);
        sConst_free(&constant);
        return FALSE;
    }

    int var_num = get_var_num(info.lv_table);

    if(!write_code_and_constant_to_file(&code, &constant, var_num, fname,js)) {
        sByteCode_free(&code);
        sConst_free(&constant);
        return FALSE;
    }

    sByteCode_free(&code);
    sConst_free(&constant);

    return TRUE;
}

