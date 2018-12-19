#include "common.h"

BOOL compile_method(sCLMethod* method, sParserParam* params, int num_params, sParserInfo* info, sCompileInfo* cinfo)
{
    info->lv_table = init_var_table();

    /// self ///
    if(!(method->mFlags & METHOD_FLAGS_CLASS_METHOD)) {
        sNodeType* node_type = alloc_node_type();
        node_type->mClass = info->klass;
        node_type->mNumGenericsTypes = info->generics_info.mNumParams;

        int i;
        for(i=0; i<info->generics_info.mNumParams; i++) {
            char class_name[CLASS_NAME_MAX+1];
            snprintf(class_name, CLASS_NAME_MAX, "GenericsParametorClass%d", i);

            node_type->mGenericsTypes[i] = create_node_type_with_class_name(class_name);
        }

        if(!add_variable_to_table(info->lv_table, "self", node_type, TRUE)) {
            parser_err_msg(info, "overflow the table or a variable which has the same name exists");
            return FALSE;
        }
    }

    /// add params to lv_table ///
    int i;
    BOOL including_pointer_param = FALSE;
    for(i=0; i<num_params; i++) {
        sParserParam* param = params + i;
        if(!add_variable_to_table(info->lv_table, param->mName, param->mType, FALSE)) {
            parser_err_msg(info, "overflow the table or a variable which has the same name exists");
            return FALSE;
        }

        if(type_identify_with_class_name(param->mType, "pointer")) {
            including_pointer_param = TRUE;
        }
    }

    if(including_pointer_param) {
        method->mFlags |= METHOD_FLAGS_NON_NATIVE_CODE;
    }

    sCompileInfo cinfo2;

    memset(&cinfo2, 0, sizeof(sCompileInfo));

    sByteCode code;
    sByteCode_init(&code);

    cinfo2.code = &code;
    cinfo2.constant = &info->klass->mConst;
    cinfo2.stack_num = 0;
    cinfo2.lv_table = info->lv_table;
    cinfo2.no_output = FALSE;
    cinfo2.err_num = 0;
    cinfo2.pinfo = info;
    cinfo2.type = NULL;
    cinfo2.num_break_points = NULL;
    cinfo2.break_points = NULL;
    cinfo2.method = method;

    sNodeType* last_result_type = NULL;

    unsigned int node = 0;

    while(1) {
        if(*info->p == '}') {
            info->p++;
            skip_spaces_and_lf(info);
            break;
        }
        else if(*info->p == '\0') {
            parser_err_msg(info, "The block requires } character for closing block");
            info->err_num++;
            sByteCode_free(cinfo2.code);
            return TRUE;
        }
        else {
            node = 0;
            if(!expression(&node, info)) {
                sByteCode_free(cinfo2.code);
                return FALSE;
            }

            cinfo2.sname = gNodes[node].mSName;
            cinfo2.sline = gNodes[node].mLine;

            if(info->err_num == 0) {
                append_opecode_to_code(cinfo2.code, OP_HEAD_OF_EXPRESSION, cinfo2.no_output);

/*
                append_opecode_to_code(cinfo2.code, OP_MARK_SOURCE_CODE_POSITION, cinfo2.no_output);
                append_str_to_constant_pool_and_code(cinfo2.constant, cinfo2.code, cinfo2.sname, cinfo2.no_output);
                append_int_value_to_code(cinfo2.code, cinfo2.sline, cinfo2.no_output);
*/

                if(!compile(node, &cinfo2)) {
                    sByteCode_free(cinfo2.code);
                    return FALSE;
                }

                last_result_type = cinfo2.type;

                if(*info->p == ';') {
                    info->p++;
                    skip_spaces_and_lf(info);
                }

                if(*info->p == '}') {
                    info->p++;
                    skip_spaces_and_lf(info);
                    break;
                }
                else if(gNodes[node].mNodeType != kNodeTypeReturn) {
                    arrange_stack(&cinfo2);
#ifdef ENABLE_INTERPRETER
                append_opecode_to_code(cinfo2.code, OP_SIGINT, cinfo2.no_output);
#endif
                }
            }

            if(*info->p == ';') {
                info->p++;
                skip_spaces_and_lf(info);
            }
        }
    }

    /// set result value on the stack ///
    sNodeType* result_type = create_node_type_from_cl_type(method->mResultType, info->klass);
    if(!(method->mFlags & METHOD_FLAGS_CLASS_METHOD) && strcmp(CONS_str(&info->klass->mConst, method->mNameOffset), "initialize") == 0) 
    {
        arrange_stack(&cinfo2);

        append_opecode_to_code(cinfo2.code, OP_LOAD, FALSE);
        append_int_value_to_code(cinfo2.code, 0, FALSE);
        append_int_value_to_code(cinfo2.code, 4, FALSE);
        append_opecode_to_code(cinfo2.code, OP_RETURN, FALSE);
    }
    else if(type_identify_with_class_name(result_type, "Null")) {
        arrange_stack(&cinfo2);

        append_opecode_to_code(cinfo2.code, OP_LDCNULL, FALSE);
        append_opecode_to_code(cinfo2.code, OP_RETURN, FALSE);
    }
    else if(gNodes[node].mNodeType == kNodeTypeReturn) {
    }
    else {
        if(cinfo2.stack_num != 1) {
            parser_err_msg(info, "Require return value. Stack num is %d", cinfo2.stack_num);
            cinfo2.err_num++;
        }

        sNodeType* result_type2 = NULL;
        solve_generics_for_variable(result_type, &result_type2, info);

        if(cast_posibility(result_type2, last_result_type)) {
            cast_right_type_to_left_type(result_type2, &last_result_type, &cinfo2);
        }

/*
        if(!substitution_posibility(result_type2, last_result_type, NULL, NULL, NULL, NULL)) {
            compile_err_msg(&cinfo2, "Invalid type of return value. Left type is %s. Left generics number %d. Right type is %s. right generics number %d.", CLASS_NAME(result_type2->mClass), result_type2->mNumGenericsTypes, CLASS_NAME(last_result_type->mClass), last_result_type->mNumGenericsTypes);

            return FALSE;
        }
*/

        append_opecode_to_code(cinfo2.code, OP_RETURN, FALSE);
    }

    int var_num = get_var_num(cinfo2.lv_table);
    add_code_to_method(method, cinfo2.code, var_num);
    cinfo->err_num += cinfo2.err_num;

    return TRUE;
}
