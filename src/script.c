#include "common.h"

static BOOL write_code_and_constant_to_file(sByteCode* code, sConst* constant, int var_num, char* fname)
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

    xstrncat(output_fname, ".clo", PATH_MAX);

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

BOOL compile_script(char* fname, char* source)
{
    sParserInfo info;

    memset(&info, 0, sizeof(sParserInfo));

    info.p = source;
    info.sname = fname;
    info.sline = 1;
    info.lv_table = init_var_table();

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

    while(*info.p) {
        unsigned int node = 0;
        if(!expression(&node, &info)) {
            return FALSE;
        }

#ifdef VM_DEBUG
show_node(node);
#endif

        if(info.err_num == 0) {
            if(!compile(node, &cinfo)) {
                sByteCode_free(&code);
                sConst_free(&constant);
                return FALSE;
            }

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

    if(!write_code_and_constant_to_file(&code, &constant, var_num, fname)) {
        sByteCode_free(&code);
        sConst_free(&constant);
        return FALSE;
    }

    sByteCode_free(&code);
    sConst_free(&constant);

    return TRUE;
}
