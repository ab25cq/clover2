#include "common.h"

void cast_right_type_to_byte(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte"))
    {
        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte"))
    {
        append_opecode_to_code(info->code, OP_UBYTE_TO_BYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short"))
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_BYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_BYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_BYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint"))
    {
        append_opecode_to_code(info->code, OP_UINT_TO_BYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_BYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong"))
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_BYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_BYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_BYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_BYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_BYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_BYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Byte"))
    {
        append_opecode_to_code(info->code, OP_CBYTE_TO_BYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UByte"))
    {
        append_opecode_to_code(info->code, OP_CUBYTE_TO_BYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Short"))
    {
        append_opecode_to_code(info->code, OP_CSHORT_TO_BYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UShort"))
    {
        append_opecode_to_code(info->code, OP_CUSHORT_TO_BYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Integer"))
    {
        append_opecode_to_code(info->code, OP_INTEGER_TO_BYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UInteger"))
    {
        append_opecode_to_code(info->code, OP_UINTEGER_TO_BYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Long"))
    {
        append_opecode_to_code(info->code, OP_CLONG_TO_BYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ULong"))
    {
        append_opecode_to_code(info->code, OP_CULONG_TO_BYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Float"))
    {
        append_opecode_to_code(info->code, OP_CFLOAT_TO_BYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Double"))
    {
        append_opecode_to_code(info->code, OP_CDOUBLE_TO_BYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Pointer"))
    {
        append_opecode_to_code(info->code, OP_CPOINTER_TO_BYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Char"))
    {
        append_opecode_to_code(info->code, OP_CCHAR_TO_BYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Bool"))
    {
        append_opecode_to_code(info->code, OP_CBOOL_TO_BYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous")) {
        //append_opecode_to_code(info->code, OP_CBYTE_TO_BYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("byte", info->pinfo->mJS);
    }
}

void cast_right_type_to_short(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte"))
    {
        append_opecode_to_code(info->code, OP_BYTE_TO_SHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) 
    {
        append_opecode_to_code(info->code, OP_UBYTE_TO_SHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short")) 
    {
        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_SHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_SHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_UINT_TO_SHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_SHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_SHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_SHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_SHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_SHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_SHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_SHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Byte"))
    {
        append_opecode_to_code(info->code, OP_CBYTE_TO_SHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UByte"))
    {
        append_opecode_to_code(info->code, OP_CUBYTE_TO_SHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Short"))
    {
        append_opecode_to_code(info->code, OP_CSHORT_TO_SHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UShort"))
    {
        append_opecode_to_code(info->code, OP_CUSHORT_TO_SHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Integer"))
    {
        append_opecode_to_code(info->code, OP_INTEGER_TO_SHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UInteger"))
    {
        append_opecode_to_code(info->code, OP_UINTEGER_TO_SHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Long"))
    {
        append_opecode_to_code(info->code, OP_CLONG_TO_SHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ULong"))
    {
        append_opecode_to_code(info->code, OP_CULONG_TO_SHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Float"))
    {
        append_opecode_to_code(info->code, OP_CFLOAT_TO_SHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Double"))
    {
        append_opecode_to_code(info->code, OP_CDOUBLE_TO_SHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Pointer"))
    {
        append_opecode_to_code(info->code, OP_CPOINTER_TO_SHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Char"))
    {
        append_opecode_to_code(info->code, OP_CCHAR_TO_SHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Bool"))
    {
        append_opecode_to_code(info->code, OP_CBOOL_TO_SHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous")) {
        //append_opecode_to_code(info->code, OP_CSHORT_TO_SHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("short", info->pinfo->mJS);
    }
}

void cast_right_type_to_int(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte"))
    {
        append_opecode_to_code(info->code, OP_BYTE_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) 
    {
        append_opecode_to_code(info->code, OP_UBYTE_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short"))
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int")) 
    {
        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_UINT_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Byte"))
    {
        append_opecode_to_code(info->code, OP_CBYTE_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UByte"))
    {
        append_opecode_to_code(info->code, OP_CUBYTE_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Short"))
    {
        append_opecode_to_code(info->code, OP_CSHORT_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UShort"))
    {
        append_opecode_to_code(info->code, OP_CUSHORT_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Integer"))
    {
        append_opecode_to_code(info->code, OP_INTEGER_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UInteger"))
    {
        append_opecode_to_code(info->code, OP_UINTEGER_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Long"))
    {
        append_opecode_to_code(info->code, OP_CLONG_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ULong"))
    {
        append_opecode_to_code(info->code, OP_CULONG_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Float"))
    {
        append_opecode_to_code(info->code, OP_CFLOAT_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Double"))
    {
        append_opecode_to_code(info->code, OP_CDOUBLE_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Pointer"))
    {
        append_opecode_to_code(info->code, OP_CPOINTER_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Char"))
    {
        append_opecode_to_code(info->code, OP_CCHAR_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Bool"))
    {
        append_opecode_to_code(info->code, OP_CBOOL_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous")) {
        //append_opecode_to_code(info->code, OP_INTEGER_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("int", info->pinfo->mJS);
    }
}

void cast_right_type_to_long(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte"))
    {
        append_opecode_to_code(info->code, OP_BYTE_TO_LONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) 
    {
        append_opecode_to_code(info->code, OP_UBYTE_TO_LONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short"))
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_LONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_LONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_LONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_UINT_TO_LONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long")) 
    {
        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_LONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_LONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_LONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_LONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_LONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_LONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Byte"))
    {
        append_opecode_to_code(info->code, OP_CBYTE_TO_LONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UByte"))
    {
        append_opecode_to_code(info->code, OP_CUBYTE_TO_LONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Short"))
    {
        append_opecode_to_code(info->code, OP_CSHORT_TO_LONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UShort"))
    {
        append_opecode_to_code(info->code, OP_CUSHORT_TO_LONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Integer"))
    {
        append_opecode_to_code(info->code, OP_INTEGER_TO_LONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UInteger"))
    {
        append_opecode_to_code(info->code, OP_UINTEGER_TO_LONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Long"))
    {
        append_opecode_to_code(info->code, OP_CLONG_TO_LONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ULong"))
    {
        append_opecode_to_code(info->code, OP_CULONG_TO_LONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Float"))
    {
        append_opecode_to_code(info->code, OP_CFLOAT_TO_LONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Double"))
    {
        append_opecode_to_code(info->code, OP_CDOUBLE_TO_LONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Pointer"))
    {
        append_opecode_to_code(info->code, OP_CPOINTER_TO_LONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Char"))
    {
        append_opecode_to_code(info->code, OP_CCHAR_TO_LONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Bool"))
    {
        append_opecode_to_code(info->code, OP_CBOOL_TO_LONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous")) {
        //append_opecode_to_code(info->code, OP_CLONG_TO_LONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("long", info->pinfo->mJS);
    }
}


void cast_right_type_to_ubyte(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte"))
    {
        append_opecode_to_code(info->code, OP_BYTE_TO_UBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte"))
    {
        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short"))
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_UBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_UBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_UBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint"))
    {
        append_opecode_to_code(info->code, OP_UINT_TO_UBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_UBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong"))
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_UBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_UBYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_UBYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_UBYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_UBYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_UBYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Byte"))
    {
        append_opecode_to_code(info->code, OP_CBYTE_TO_UBYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UByte"))
    {
        append_opecode_to_code(info->code, OP_CUBYTE_TO_UBYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Short"))
    {
        append_opecode_to_code(info->code, OP_CSHORT_TO_UBYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UShort"))
    {
        append_opecode_to_code(info->code, OP_CUSHORT_TO_UBYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Integer"))
    {
        append_opecode_to_code(info->code, OP_INTEGER_TO_UBYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UInteger"))
    {
        append_opecode_to_code(info->code, OP_UINTEGER_TO_UBYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Long"))
    {
        append_opecode_to_code(info->code, OP_CLONG_TO_UBYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ULong"))
    {
        append_opecode_to_code(info->code, OP_CULONG_TO_UBYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Float"))
    {
        append_opecode_to_code(info->code, OP_CFLOAT_TO_UBYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Double"))
    {
        append_opecode_to_code(info->code, OP_CDOUBLE_TO_UBYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Pointer"))
    {
        append_opecode_to_code(info->code, OP_CPOINTER_TO_UBYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Char"))
    {
        append_opecode_to_code(info->code, OP_CCHAR_TO_UBYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Bool"))
    {
        append_opecode_to_code(info->code, OP_CBOOL_TO_UBYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous")) {
        //append_opecode_to_code(info->code, OP_CUBYTE_TO_UBYTE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ubyte", info->pinfo->mJS);
    }
}

void cast_right_type_to_ushort(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte"))
    {
        append_opecode_to_code(info->code, OP_BYTE_TO_USHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) 
    {
        append_opecode_to_code(info->code, OP_UBYTE_TO_USHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short")) 
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_USHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_USHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_UINT_TO_USHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_USHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_USHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_USHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_USHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_USHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_USHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_USHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Byte"))
    {
        append_opecode_to_code(info->code, OP_CBYTE_TO_USHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UByte"))
    {
        append_opecode_to_code(info->code, OP_CUBYTE_TO_USHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Short"))
    {
        append_opecode_to_code(info->code, OP_CSHORT_TO_USHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UShort"))
    {
        append_opecode_to_code(info->code, OP_CUSHORT_TO_USHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Integer"))
    {
        append_opecode_to_code(info->code, OP_INTEGER_TO_USHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UInteger"))
    {
        append_opecode_to_code(info->code, OP_UINTEGER_TO_USHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Long"))
    {
        append_opecode_to_code(info->code, OP_CLONG_TO_USHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ULong"))
    {
        append_opecode_to_code(info->code, OP_CULONG_TO_USHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Float"))
    {
        append_opecode_to_code(info->code, OP_CFLOAT_TO_USHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Double"))
    {
        append_opecode_to_code(info->code, OP_CDOUBLE_TO_USHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Pointer"))
    {
        append_opecode_to_code(info->code, OP_CPOINTER_TO_USHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Char"))
    {
        append_opecode_to_code(info->code, OP_CCHAR_TO_USHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Bool"))
    {
        append_opecode_to_code(info->code, OP_CBOOL_TO_USHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous")) {
        //append_opecode_to_code(info->code, OP_CUSHORT_TO_USHORT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ushort", info->pinfo->mJS);
    }
}

void cast_right_type_to_uint(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte"))
    {
        append_opecode_to_code(info->code, OP_BYTE_TO_UINT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) 
    {
        append_opecode_to_code(info->code, OP_UBYTE_TO_UINT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short"))
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_UINT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_UINT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int")) 
    {
        append_opecode_to_code(info->code, OP_INT_TO_UINT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_UINT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_UINT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_UINT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_UINT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_UINT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_UINT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Byte"))
    {
        append_opecode_to_code(info->code, OP_CBYTE_TO_UINT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UByte"))
    {
        append_opecode_to_code(info->code, OP_CUBYTE_TO_UINT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Short"))
    {
        append_opecode_to_code(info->code, OP_CSHORT_TO_UINT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UShort"))
    {
        append_opecode_to_code(info->code, OP_CUSHORT_TO_UINT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Integer"))
    {
        append_opecode_to_code(info->code, OP_INTEGER_TO_UINT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UInteger"))
    {
        append_opecode_to_code(info->code, OP_UINTEGER_TO_UINT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Long"))
    {
        append_opecode_to_code(info->code, OP_CLONG_TO_UINT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ULong"))
    {
        append_opecode_to_code(info->code, OP_CULONG_TO_UINT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Float"))
    {
        append_opecode_to_code(info->code, OP_CFLOAT_TO_UINT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Double"))
    {
        append_opecode_to_code(info->code, OP_CDOUBLE_TO_UINT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Pointer"))
    {
        append_opecode_to_code(info->code, OP_CPOINTER_TO_UINT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Char"))
    {
        append_opecode_to_code(info->code, OP_CCHAR_TO_UINT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Bool"))
    {
        append_opecode_to_code(info->code, OP_CBOOL_TO_UINT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous")) {
        //append_opecode_to_code(info->code, OP_UINTEGER_TO_UINT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("uint", info->pinfo->mJS);
    }
}

void cast_right_type_to_ulong(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte"))
    {
        append_opecode_to_code(info->code, OP_BYTE_TO_ULONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) 
    {
        append_opecode_to_code(info->code, OP_UBYTE_TO_ULONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short"))
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_ULONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_ULONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_ULONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_UINT_TO_ULONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long")) 
    {
        append_opecode_to_code(info->code, OP_LONG_TO_ULONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_ULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_ULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_ULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_ULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_ULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Byte"))
    {
        append_opecode_to_code(info->code, OP_CBYTE_TO_ULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UByte"))
    {
        append_opecode_to_code(info->code, OP_CUBYTE_TO_ULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Short"))
    {
        append_opecode_to_code(info->code, OP_CSHORT_TO_ULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UShort"))
    {
        append_opecode_to_code(info->code, OP_CUSHORT_TO_ULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Integer"))
    {
        append_opecode_to_code(info->code, OP_INTEGER_TO_ULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UInteger"))
    {
        append_opecode_to_code(info->code, OP_UINTEGER_TO_ULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Long"))
    {
        append_opecode_to_code(info->code, OP_CLONG_TO_ULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ULong"))
    {
        append_opecode_to_code(info->code, OP_CULONG_TO_ULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Float"))
    {
        append_opecode_to_code(info->code, OP_CFLOAT_TO_ULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Double"))
    {
        append_opecode_to_code(info->code, OP_CDOUBLE_TO_ULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Pointer"))
    {
        append_opecode_to_code(info->code, OP_CPOINTER_TO_ULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Char"))
    {
        append_opecode_to_code(info->code, OP_CCHAR_TO_ULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Bool"))
    {
        append_opecode_to_code(info->code, OP_CBOOL_TO_ULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous")) {
        //append_opecode_to_code(info->code, OP_CULONG_TO_ULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ulong", info->pinfo->mJS);
    }
}

void cast_right_type_to_float(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte"))
    {
        append_opecode_to_code(info->code, OP_BYTE_TO_FLOAT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte"))
    {
        append_opecode_to_code(info->code, OP_UBYTE_TO_FLOAT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short"))
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_FLOAT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort"))
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_FLOAT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_FLOAT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint"))
    {
        append_opecode_to_code(info->code, OP_UINT_TO_FLOAT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_FLOAT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong"))
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_FLOAT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_FLOAT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_FLOAT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_FLOAT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Byte"))
    {
        append_opecode_to_code(info->code, OP_CBYTE_TO_FLOAT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UByte"))
    {
        append_opecode_to_code(info->code, OP_CUBYTE_TO_FLOAT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Short"))
    {
        append_opecode_to_code(info->code, OP_CSHORT_TO_FLOAT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UShort"))
    {
        append_opecode_to_code(info->code, OP_CUSHORT_TO_FLOAT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Integer"))
    {
        append_opecode_to_code(info->code, OP_INTEGER_TO_FLOAT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UInteger"))
    {
        append_opecode_to_code(info->code, OP_UINTEGER_TO_FLOAT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Long"))
    {
        append_opecode_to_code(info->code, OP_CLONG_TO_FLOAT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ULong"))
    {
        append_opecode_to_code(info->code, OP_CULONG_TO_FLOAT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Float"))
    {
        append_opecode_to_code(info->code, OP_CFLOAT_TO_FLOAT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Double"))
    {
        append_opecode_to_code(info->code, OP_CDOUBLE_TO_FLOAT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Char"))
    {
        append_opecode_to_code(info->code, OP_CCHAR_TO_FLOAT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Bool"))
    {
        append_opecode_to_code(info->code, OP_CBOOL_TO_FLOAT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous")) {
        //append_opecode_to_code(info->code, OP_CFLOAT_TO_FLOAT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("float", info->pinfo->mJS);
    }
}

void cast_right_type_to_double(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte"))
    {
        append_opecode_to_code(info->code, OP_BYTE_TO_DOUBLE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) 
    {
        append_opecode_to_code(info->code, OP_UBYTE_TO_DOUBLE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short"))
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_DOUBLE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_DOUBLE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_DOUBLE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint"))
    {
        append_opecode_to_code(info->code, OP_UINT_TO_DOUBLE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_DOUBLE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong"))
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_DOUBLE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_DOUBLE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_DOUBLE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_DOUBLE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Byte"))
    {
        append_opecode_to_code(info->code, OP_CBYTE_TO_DOUBLE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UByte"))
    {
        append_opecode_to_code(info->code, OP_CUBYTE_TO_DOUBLE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Short"))
    {
        append_opecode_to_code(info->code, OP_CSHORT_TO_DOUBLE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UShort"))
    {
        append_opecode_to_code(info->code, OP_CUSHORT_TO_DOUBLE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Integer"))
    {
        append_opecode_to_code(info->code, OP_INTEGER_TO_DOUBLE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UInteger"))
    {
        append_opecode_to_code(info->code, OP_UINTEGER_TO_DOUBLE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Long"))
    {
        append_opecode_to_code(info->code, OP_CLONG_TO_DOUBLE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ULong"))
    {
        append_opecode_to_code(info->code, OP_CULONG_TO_DOUBLE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Float"))
    {
        append_opecode_to_code(info->code, OP_CFLOAT_TO_DOUBLE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Double"))
    {
        append_opecode_to_code(info->code, OP_CDOUBLE_TO_DOUBLE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Char"))
    {
        append_opecode_to_code(info->code, OP_CCHAR_TO_DOUBLE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Bool"))
    {
        append_opecode_to_code(info->code, OP_CBOOL_TO_DOUBLE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous")) {
        //append_opecode_to_code(info->code, OP_CDOUBLE_TO_DOUBLE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("double", info->pinfo->mJS);
    }
}

void cast_right_type_to_char(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte"))
    {
        append_opecode_to_code(info->code, OP_BYTE_TO_CHAR_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) 
    {
        append_opecode_to_code(info->code, OP_UBYTE_TO_CHAR_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short"))
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_CHAR_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_CHAR_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_CHAR_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint"))
    {
        append_opecode_to_code(info->code, OP_UINT_TO_CHAR_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_CHAR_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_CHAR_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_CHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_CHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_CHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_CHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Byte"))
    {
        append_opecode_to_code(info->code, OP_CBYTE_TO_CHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UByte"))
    {
        append_opecode_to_code(info->code, OP_CUBYTE_TO_CHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Short"))
    {
        append_opecode_to_code(info->code, OP_CSHORT_TO_CHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UShort"))
    {
        append_opecode_to_code(info->code, OP_CUSHORT_TO_CHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Integer"))
    {
        append_opecode_to_code(info->code, OP_INTEGER_TO_CHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UInteger"))
    {
        append_opecode_to_code(info->code, OP_UINTEGER_TO_CHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Long"))
    {
        append_opecode_to_code(info->code, OP_CLONG_TO_CHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ULong"))
    {
        append_opecode_to_code(info->code, OP_CULONG_TO_CHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Float"))
    {
        append_opecode_to_code(info->code, OP_CFLOAT_TO_CHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Double"))
    {
        append_opecode_to_code(info->code, OP_CDOUBLE_TO_CHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Pointer"))
    {
        append_opecode_to_code(info->code, OP_CPOINTER_TO_CHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Char"))
    {
        append_opecode_to_code(info->code, OP_CCHAR_TO_CHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Bool"))
    {
        append_opecode_to_code(info->code, OP_CBOOL_TO_CHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous")) {
        //append_opecode_to_code(info->code, OP_CCHAR_TO_CHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("char", info->pinfo->mJS);
    }
}

void cast_right_type_to_pointer(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte"))
    {
        append_opecode_to_code(info->code, OP_BYTE_TO_POINTER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) 
    {
        append_opecode_to_code(info->code, OP_UBYTE_TO_POINTER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short"))
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_POINTER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_POINTER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_POINTER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint"))
    {
        append_opecode_to_code(info->code, OP_UINT_TO_POINTER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_POINTER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong"))
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_POINTER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_POINTER_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_POINTER_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Buffer"))
    {
        append_opecode_to_code(info->code, OP_BUFFER_TO_POINTER_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("pointer", info->pinfo->mJS);
    }
}

void cast_right_type_to_bool(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte"))
    {
        append_opecode_to_code(info->code, OP_BYTE_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) 
    {
        append_opecode_to_code(info->code, OP_UBYTE_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short"))
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_UINT_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Byte"))
    {
        append_opecode_to_code(info->code, OP_CBYTE_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UByte"))
    {
        append_opecode_to_code(info->code, OP_CUBYTE_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Short"))
    {
        append_opecode_to_code(info->code, OP_CSHORT_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UShort"))
    {
        append_opecode_to_code(info->code, OP_CUSHORT_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Integer"))
    {
        append_opecode_to_code(info->code, OP_INTEGER_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "UInteger"))
    {
        append_opecode_to_code(info->code, OP_UINTEGER_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Long"))
    {
        append_opecode_to_code(info->code, OP_CLONG_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ULong"))
    {
        append_opecode_to_code(info->code, OP_CULONG_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Float"))
    {
        append_opecode_to_code(info->code, OP_CFLOAT_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Double"))
    {
        append_opecode_to_code(info->code, OP_CDOUBLE_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Pointer"))
    {
        append_opecode_to_code(info->code, OP_CPOINTER_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Char"))
    {
        append_opecode_to_code(info->code, OP_CCHAR_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Bool"))
    {
        append_opecode_to_code(info->code, OP_CBOOL_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous"))
    {
        //append_opecode_to_code(info->code, OP_CBOOL_TO_INT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("bool", info->pinfo->mJS);
    }
}

void cast_right_type_to_String(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte")) {
        append_opecode_to_code(info->code, OP_BYTE_TO_STRING_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("String", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) {
        append_opecode_to_code(info->code, OP_UBYTE_TO_STRING_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("String", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short")) 
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_STRING_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("String", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_STRING_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("String", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_STRING_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("String", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_UINT_TO_STRING_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("String", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_STRING_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("String", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_STRING_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("String", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_STRING_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("String", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_STRING_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("String", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_STRING_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("String", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_STRING_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("String", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_BOOL_TO_STRING_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("String", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "regex"))
    {
        append_opecode_to_code(info->code, OP_REGEX_TO_STRING_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("String", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous"))
    {
        *right_type = create_node_type_with_class_name("String", info->pinfo->mJS);
    }
}

void cast_right_type_to_Byte(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte")) {
        append_opecode_to_code(info->code, OP_BYTE_TO_CBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) {
        append_opecode_to_code(info->code, OP_UBYTE_TO_CBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short")) 
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_CBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_CBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_CBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_UINT_TO_CBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_CBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_CBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_CBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_CBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_CBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_CBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_BOOL_TO_CBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Byte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous"))
    {
        *right_type = create_node_type_with_class_name("Byte", info->pinfo->mJS);
    }
}

void cast_right_type_to_UByte(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte")) {
        append_opecode_to_code(info->code, OP_BYTE_TO_CUBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UByte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) {
        append_opecode_to_code(info->code, OP_UBYTE_TO_CUBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UByte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short")) 
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_CUBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UByte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_CUBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UByte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_CUBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UByte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_UINT_TO_CUBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UByte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_CUBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UByte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_CUBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UByte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_CUBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UByte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_CUBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UByte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_CUBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UByte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_CUBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UByte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_BOOL_TO_CUBYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UByte", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous"))
    {
        *right_type = create_node_type_with_class_name("UByte", info->pinfo->mJS);
    }
}

void cast_right_type_to_Short(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte")) {
        append_opecode_to_code(info->code, OP_BYTE_TO_CSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) {
        append_opecode_to_code(info->code, OP_UBYTE_TO_CSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short")) 
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_CSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_CSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_CSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_UINT_TO_CSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_CSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_CSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_CSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_CSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_CSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_CSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_BOOL_TO_CSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Short", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous"))
    {
        *right_type = create_node_type_with_class_name("Short", info->pinfo->mJS);
    }
}

void cast_right_type_to_UShort(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte")) {
        append_opecode_to_code(info->code, OP_BYTE_TO_CUSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UShort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) {
        append_opecode_to_code(info->code, OP_UBYTE_TO_CUSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UShort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short")) 
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_CUSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UShort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_CUSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UShort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_CUSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UShort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_UINT_TO_CUSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UShort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_CUSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UShort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_CUSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UShort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_CUSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UShort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_CUSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UShort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_CUSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UShort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_CUSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UShort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_BOOL_TO_CUSHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UShort", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous"))
    {
        *right_type = create_node_type_with_class_name("UShort", info->pinfo->mJS);
    }
}

void cast_right_type_to_Integer(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte")) {
        append_opecode_to_code(info->code, OP_BYTE_TO_INTEGER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Integer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) {
        append_opecode_to_code(info->code, OP_UBYTE_TO_INTEGER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Integer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short")) 
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_INTEGER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Integer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_INTEGER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Integer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_INTEGER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Integer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_UINT_TO_INTEGER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Integer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_INTEGER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Integer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_INTEGER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Integer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_INTEGER_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Integer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_INTEGER_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Integer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_INTEGER_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Integer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_INTEGER_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Integer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_BOOL_TO_INTEGER_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Integer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous"))
    {
        *right_type = create_node_type_with_class_name("Integer", info->pinfo->mJS);
    }
}

void cast_right_type_to_UInteger(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte")) {
        append_opecode_to_code(info->code, OP_BYTE_TO_UINTEGER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UInteger", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) {
        append_opecode_to_code(info->code, OP_UBYTE_TO_UINTEGER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UInteger", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short")) 
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_UINTEGER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UInteger", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_UINTEGER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UInteger", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_UINTEGER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UInteger", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_UINT_TO_UINTEGER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UInteger", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_UINTEGER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UInteger", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_UINTEGER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("UInteger", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_UINTEGER_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("UInteger", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_UINTEGER_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("UInteger", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_UINTEGER_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("UInteger", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_UINTEGER_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("UInteger", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_BOOL_TO_UINTEGER_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("UInteger", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous"))
    {
        *right_type = create_node_type_with_class_name("UInteger", info->pinfo->mJS);
    }
}

void cast_right_type_to_Long(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte")) {
        append_opecode_to_code(info->code, OP_BYTE_TO_CLONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) {
        append_opecode_to_code(info->code, OP_UBYTE_TO_CLONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short")) 
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_CLONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_CLONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_CLONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_UINT_TO_CLONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_CLONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_CLONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_CLONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_CLONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_CLONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_CLONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_BOOL_TO_CLONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Long", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous"))
    {
        *right_type = create_node_type_with_class_name("Long", info->pinfo->mJS);
    }
}

void cast_right_type_to_ULong(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte")) {
        append_opecode_to_code(info->code, OP_BYTE_TO_CULONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ULong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) {
        append_opecode_to_code(info->code, OP_UBYTE_TO_CULONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ULong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short")) 
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_CULONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ULong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_CULONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ULong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_CULONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ULong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_UINT_TO_CULONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ULong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_CULONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ULong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_CULONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("ULong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_CULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ULong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_CULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ULong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_CULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ULong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_CULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ULong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_BOOL_TO_CULONG_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("ULong", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous"))
    {
        *right_type = create_node_type_with_class_name("ULong", info->pinfo->mJS);
    }
}

void cast_right_type_to_Float(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte")) {
        append_opecode_to_code(info->code, OP_BYTE_TO_CFLOAT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) {
        append_opecode_to_code(info->code, OP_UBYTE_TO_CFLOAT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short")) 
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_CFLOAT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_CFLOAT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_CFLOAT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_UINT_TO_CFLOAT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_CFLOAT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_CFLOAT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_CFLOAT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_CFLOAT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_CFLOAT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_BOOL_TO_CFLOAT_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Float", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous"))
    {
        *right_type = create_node_type_with_class_name("Float", info->pinfo->mJS);
    }
}

void cast_right_type_to_Double(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte")) {
        append_opecode_to_code(info->code, OP_BYTE_TO_CDOUBLE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) {
        append_opecode_to_code(info->code, OP_UBYTE_TO_CDOUBLE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short")) 
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_CDOUBLE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_CDOUBLE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_CDOUBLE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_UINT_TO_CDOUBLE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_CDOUBLE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_CDOUBLE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_CDOUBLE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_CDOUBLE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_CDOUBLE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_BOOL_TO_CDOUBLE_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Double", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous"))
    {
        *right_type = create_node_type_with_class_name("Double", info->pinfo->mJS);
    }
}

void cast_right_type_to_Pointer(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte")) {
        append_opecode_to_code(info->code, OP_BYTE_TO_CPOINTER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) {
        append_opecode_to_code(info->code, OP_UBYTE_TO_CPOINTER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short")) 
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_CPOINTER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_CPOINTER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_CPOINTER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_UINT_TO_CPOINTER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_CPOINTER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_CPOINTER_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_CPOINTER_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_CPOINTER_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_BOOL_TO_CPOINTER_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Pointer", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous"))
    {
        *right_type = create_node_type_with_class_name("Pointer", info->pinfo->mJS);
    }
}

void cast_right_type_to_Char(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte")) {
        append_opecode_to_code(info->code, OP_BYTE_TO_CCHAR_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) {
        append_opecode_to_code(info->code, OP_UBYTE_TO_CCHAR_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short")) 
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_CCHAR_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_CCHAR_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_CCHAR_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_UINT_TO_CCHAR_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_CCHAR_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_CCHAR_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_CCHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_CCHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_CCHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_CCHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_BOOL_TO_CCHAR_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Char", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous"))
    {
        *right_type = create_node_type_with_class_name("Char", info->pinfo->mJS);
    }
}

void cast_right_type_to_Bool(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte")) {
        append_opecode_to_code(info->code, OP_BYTE_TO_CBOOL_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ubyte")) {
        append_opecode_to_code(info->code, OP_UBYTE_TO_CBOOL_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "short")) 
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_CBOOL_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_USHORT_TO_CBOOL_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "int"))
    {
        append_opecode_to_code(info->code, OP_INT_TO_CBOOL_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_UINT_TO_CBOOL_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "long"))
    {
        append_opecode_to_code(info->code, OP_LONG_TO_CBOOL_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_ULONG_TO_CBOOL_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("Bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "float"))
    {
        append_opecode_to_code(info->code, OP_FLOAT_TO_CBOOL_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "double"))
    {
        append_opecode_to_code(info->code, OP_DOUBLE_TO_CBOOL_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "char"))
    {
        append_opecode_to_code(info->code, OP_CHAR_TO_CBOOL_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "pointer"))
    {
        append_opecode_to_code(info->code, OP_POINTER_TO_CBOOL_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "bool"))
    {
        append_opecode_to_code(info->code, OP_BOOL_TO_CBOOL_CAST, info->no_output);
        *right_type = create_node_type_with_class_name("Bool", info->pinfo->mJS);
    }
    else if(type_identify_with_class_name(*right_type, "Anonymous"))
    {
        *right_type = create_node_type_with_class_name("Bool", info->pinfo->mJS);
    }
}

void cast_right_type_to_Array(sNodeType** right_type, sCompileInfo* info)
{
    if((*right_type)->mArray) {
        sCLClass* klass = (*right_type)->mClass;

        append_opecode_to_code(info->code, OP_ARRAY_TO_CARRAY_CAST, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, CLASS_NAME(klass), info->no_output);

        sNodeType* node_type = clone_node_type(*right_type);
        make_boxing_type(node_type, right_type);
    }
}

void cast_right_type_to_left_type(sNodeType* left_type, sNodeType** right_type, sCompileInfo* info)
{
    if(left_type->mArray) {
    }
    else if((*right_type)->mArray) {
        if(type_identify_with_class_name(left_type, "Array")) {
            cast_right_type_to_Array(right_type, info);
        }
    }
    else {
        if(type_identify_with_class_name(left_type, "byte"))
        {
            cast_right_type_to_byte(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "ubyte")) 
        {
            cast_right_type_to_ubyte(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "short"))
        {
            cast_right_type_to_short(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "ushort"))
        {
            cast_right_type_to_ushort(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "int"))
        {
            cast_right_type_to_int(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "uint"))
        {
            cast_right_type_to_uint(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "long"))
        {
            cast_right_type_to_long(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "ulong"))
        {
            cast_right_type_to_ulong(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "float"))
        {
            cast_right_type_to_float(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "double"))
        {
            cast_right_type_to_double(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "pointer"))
        {
            cast_right_type_to_pointer(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "char"))
        {
            cast_right_type_to_char(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "bool"))
        {
            cast_right_type_to_bool(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "String"))
        {
            cast_right_type_to_String(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "Byte"))
        {
            cast_right_type_to_Byte(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "UByte"))
        {
            cast_right_type_to_UByte(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "Short"))
        {
            cast_right_type_to_Short(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "UShort"))
        {
            cast_right_type_to_UShort(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "Integer"))
        {
            cast_right_type_to_Integer(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "UInteger"))
        {
            cast_right_type_to_UInteger(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "Long"))
        {
            cast_right_type_to_Long(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "ULong"))
        {
            cast_right_type_to_ULong(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "Float"))
        {
            cast_right_type_to_Float(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "Double"))
        {
            cast_right_type_to_Double(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "Pointer"))
        {
            cast_right_type_to_Pointer(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "Char"))
        {
            cast_right_type_to_Char(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "Bool"))
        {
            cast_right_type_to_Bool(right_type, info);
        }
        else if(type_identify_with_class_name(left_type, "Anonymous") && ((*right_type)->mClass->mFlags & CLASS_FLAGS_PRIMITIVE)) 
        {
            boxing_to_lapper_class(right_type, info);
        }
    }
}
