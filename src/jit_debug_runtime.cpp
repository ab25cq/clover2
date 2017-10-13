#include "jit_common.hpp"

extern "C"
{

void show_number_in_jit(clint64 number)
{
    printf("%ld(%p)\n", number, number);
}

void show_number_in_jit2(int number)
{
    printf("%d\n", number);
}

void show_inst_in_jit(int opecode)
{
    switch(opecode) {
        case OP_BYTE_TO_CULONG_CAST:
            puts("OP_BYTE_TO_CULONG_CAST");
            break;

        case OP_UBYTE_TO_CULONG_CAST:
            puts("OP_UBYTE_TO_CULONG_CAST");
            break;

        case OP_SHORT_TO_CULONG_CAST :
            puts("OP_SHORT_TO_CULONG_CAST ");
            break;

        case OP_USHORT_TO_CULONG_CAST :
            puts("OP_USHORT_TO_CULONG_CAST ");
            break;

        case OP_INT_TO_CULONG_CAST :
            puts("OP_INT_TO_CULONG_CAST ");
            break;

        case OP_UINT_TO_CULONG_CAST :
            puts("OP_UINT_TO_CULONG_CAST ");
            break;

        case OP_LONG_TO_CULONG_CAST :
            puts("OP_LONG_TO_CULONG_CAST ");
            break;

        case OP_ULONG_TO_CULONG_CAST :
            puts("OP_ULONG_TO_CULONG_CAST ");
            break;

        case OP_FLOAT_TO_CULONG_CAST :
            puts("OP_FLOAT_TO_CULONG_CAST ");
            break;

        case OP_DOUBLE_TO_CULONG_CAST :
            puts("OP_DOUBLE_TO_CULONG_CAST ");
            break;

        case OP_CHAR_TO_CULONG_CAST :
            puts("OP_CHAR_TO_CULONG_CAST ");
            break;

        case OP_POINTER_TO_CULONG_CAST :
            puts("OP_POINTER_TO_CULONG_CAST ");
            break;

        case OP_LONG_TO_ULONG_CAST:
            puts("OP_LONG_TO_ULONG_CAST");
            break;

        case OP_BOOL_TO_CULONG_CAST :
            puts("OP_BOOL_TO_CULONG_CAST ");
            break;

        case OP_INT_TO_ULONG_CAST:
            puts("OP_INT_TO_ULONG_CAST");
            break;

        case OP_CREATE_BUFFER :
            puts("OP_CREATE_BUFFER");
            break;

        case OP_CREATE_PATH :
            puts("OP_CREATE_PATH");
            break;

        case OP_CREATE_ARRAY :
            puts("OP_CREATE_ARRAY");
            break;

        case OP_CREATE_CARRAY :
            puts("OP_CREATE_CARRAY");
            break;

        case OP_CREATE_SORTABLE_CARRAY :
            puts("OP_CREATE_SORTABLE_CARRAY");
            break;

        case OP_CREATE_EQUALABLE_CARRAY :
            puts("OP_CREATE_EQUALABLE_CARRAY");
            break;

        case OP_CREATE_LIST :
            puts("OP_CREATE_LIST");
            break;

        case OP_CREATE_SORTALBE_LIST :
            puts("OP_CREATE_SORTALBE_LIST");
            break;

        case OP_CREATE_EQUALABLE_LIST :
            puts("OP_CREATE_EQUALABLE_LIST");
            break;

        case OP_CREATE_TUPLE :
            puts("OP_CREATE_TUPLE");
            break;

        case OP_CREATE_HASH :
            puts("OP_CREATE_HASH");
            break;

        case OP_CREATE_BLOCK_OBJECT :
            puts("OP_CREATE_BLOCK_OBJECT");
            break;

        case OP_BYTE_TO_STRING_CAST :
            puts("OP_BYTE_TO_STRING_CAST");
            break;

        case OP_SHORT_TO_STRING_CAST :
            puts("OP_SHORT_TO_STRING_CAST");
            break;

        case OP_INT_TO_STRING_CAST :
            puts("OP_INT_TO_STRING_CAST");
            break;

        case OP_LONG_TO_STRING_CAST :
            puts("OP_LONG_TO_STRING_CAST");
            break;

        case OP_UBYTE_TO_STRING_CAST :
            puts("OP_UBYTE_TO_STRING_CAST");
            break;

        case OP_USHORT_TO_STRING_CAST :
            puts("OP_USHORT_TO_STRING_CAST");
            break;

        case OP_UINT_TO_STRING_CAST :
            puts("OP_UINT_TO_STRING_CAST");
            break;

        case OP_ULONG_TO_STRING_CAST :
            puts("OP_ULONG_TO_STRING_CAST");
            break;

        case OP_FLOAT_TO_STRING_CAST :
            puts("OP_FLOAT_TO_STRING_CAST");
            break;

        case OP_DOUBLE_TO_STRING_CAST :
            puts("OP_DOUBLE_TO_STRING_CAST");
            break;

        case OP_BOOL_TO_STRING_CAST :
            puts("OP_BOOL_TO_STRING_CAST");
            break;

        case OP_REGEX_TO_STRING_CAST :
            puts("OP_REGEX_TO_STRING_CAST");
            break;

        case OP_POINTER_TO_STRING_CAST :
            puts("OP_POINTER_TO_STRING_CAST");
            break;

        case OP_BYTE_TO_INTEGER_CAST :
            puts("OP_BYTE_TO_INTEGER_CAST");
            break;

        case OP_UBYTE_TO_INTEGER_CAST :
            puts("OP_UBYTE_TO_INTEGER_CAST");
            break;

        case OP_SHORT_TO_INTEGER_CAST :
            puts("OP_SHORT_TO_INTEGER_CAST");
            break;

        case OP_USHORT_TO_INTEGER_CAST :
            puts("OP_USHORT_TO_INTEGER_CAST");
            break;

        case OP_INT_TO_INTEGER_CAST :
            puts("OP_INT_TO_INTEGER_CAST");
            break;

        case OP_UINT_TO_INTEGER_CAST :
            puts("OP_UINT_TO_INTEGER_CAST");
            break;

        case OP_LONG_TO_INTEGER_CAST :
            puts("OP_LONG_TO_INTEGER_CAST");
            break;

        case OP_ULONG_TO_INTEGER_CAST :
            puts("OP_ULONG_TO_INTEGER_CAST");
            break;

        case OP_FLOAT_TO_INTEGER_CAST :
            puts("OP_FLOAT_TO_INTEGER_CAST");
            break;

        case OP_DOUBLE_TO_INTEGER_CAST :
            puts("OP_DOUBLE_TO_INTEGER_CAST");
            break;

        case OP_CHAR_TO_INTEGER_CAST :
            puts("OP_CHAR_TO_INTEGER_CAST");
            break;

        case OP_POINTER_TO_INTEGER_CAST :
            puts("OP_POINTER_TO_INTEGER_CAST");
            break;

        case OP_BOOL_TO_INTEGER_CAST :
            puts("OP_BOOL_TO_INTEGER_CAST");
            break;

        case OP_CHAR_TO_STRING_CAST :
            puts("OP_CHAR_TO_STRING_CAST");
            break;

        case OP_STORE_FIELD:
            puts("OP_STORE_FIELD");
            break;

        case OP_POP:
            puts("OP_POP");
            break;

        case OP_DUPE:
            puts("OP_DUPE");
            break;

        case OP_COND_JUMP :
            puts("OP_COND_JUMP");
            break;

        case OP_COND_NOT_JUMP:
            puts("OP_COND_NOT_JUMP");
            break;

        case OP_GOTO:
            puts("OP_GOTO");
            break;

        case OP_LABEL:
            puts("OP_LABEL");
            break;

        case OP_LOAD:
            puts("OP_LOAD");
            break;

        case OP_STORE:
            puts("OP_STORE");
            break;

        case OP_LDCBYTE: 
            puts("OP_LDCBYTE");
            break;

        case OP_LDCINT: 
            puts("OP_LDCINT");
            break;

        case OP_LDCNULL:
            puts("OP_LDCNULL");
            break;

        case OP_BADD:
            puts("OP_BAND");
            break;

        case OP_BSUB:
            puts("OP_BSUB");
            break;

        case OP_BMULT:
            puts("OP_BMULT");
            break;

        case OP_BDIV:
            puts("OP_BDIV");
            break;

        case OP_BMOD:
            puts("OP_BMOD");
            break;

        case OP_BLSHIFT:
            puts("OP_BLSHIFT");
            break;

        case OP_BRSHIFT:
            puts("OP_BRSHIFT");
            break;

        case OP_BAND:
            puts("OP_BAND");
            break;

        case OP_BXOR:
            puts("OP_BXOR");
            break;

        case OP_BOR:
            puts("OP_BOR");
            break;

        case OP_UBADD:
            puts("OP_UBAND");
            break;

        case OP_UBSUB:
            puts("OP_UBSUB");
            break;

        case OP_UBMULT:
            puts("OP_UBMULT");
            break;

        case OP_UBDIV:
            puts("OP_UBDIV");
            break;

        case OP_UBMOD:
            puts("OP_UBMOD");
            break;

        case OP_UBLSHIFT:
            puts("OP_UBLSHIFT");
            break;

        case OP_UBRSHIFT:
            puts("OP_UBRSHIFT");
            break;

        case OP_UBAND:
            puts("OP_UBAND");
            break;

        case OP_UBXOR:
            puts("OP_UBXOR");
            break;

        case OP_UBOR:
            puts("OP_BOR");
            break;

        case OP_SADD:
            puts("OP_SADD");
            break;

        case OP_SSUB:
            puts("OP_SSUB");
            break;

        case OP_SMULT: 
            puts("OP_SMULT");
            break;

        case OP_SDIV: 
            puts("OP_SDIV");
            break;

        case OP_SMOD: 
            puts("OP_SMOD");
            break;

        case OP_SLSHIFT: 
            puts("OP_SLSHIFT");
            break;

        case OP_SRSHIFT: 
            puts("OP_SRSHIFT");
            break;

        case OP_SAND: 
            puts("OP_SAND");
            break;

        case OP_SXOR: 
            puts("OP_SXOR");
            break;

        case OP_SOR: 
            puts("OP_SOR");
            break;

        case OP_USADD: 
            puts("OP_USADD");
            break;

        case OP_USSUB: 
            puts("OP_USSUB");
            break;

        case OP_USMULT: 
            puts("OP_USMULT");
            break;

        case OP_USDIV: 
            puts("OP_USDIV");
            break;

        case OP_USMOD: 
            puts("OP_USMOD");
            break;

        case OP_USLSHIFT: 
            puts("OP_USLSHIFT");
            break;

        case OP_USRSHIFT: 
            puts("OP_USRSHIFT");
            break;

        case OP_USAND: 
            puts("OP_USAND");
            break;

        case OP_USXOR: 
            puts("OP_USXOR");
            break;

        case OP_USOR: 
            puts("OP_USOR");
            break;

        case OP_IADD: 
            puts("OP_IADD");
            break;

        case OP_ISUB: 
            puts("OP_ISUB");
            break;

        case OP_IMULT: 
            puts("OP_IMULT");
            break;

        case OP_IDIV: 
            puts("OP_IDIV");
            break;

        case OP_IMOD: 
            puts("OP_IMOD");
            break;

        case OP_ILSHIFT: 
            puts("OP_ILSHIFT");
            break;

        case OP_IRSHIFT: 
            puts("OP_IRSHIFT");
            break;

        case OP_IAND: 
            puts("OP_IAND");
            break;

        case OP_IXOR: 
            puts("OP_IXOR");
            break;

        case OP_IOR: 
            puts("OP_IOR");
            break;

        case OP_UIADD: 
            puts("OP_UIADD");
            break;

        case OP_UISUB: 
            puts("OP_UISUB");
            break;

        case OP_UIMULT: 
            puts("OP_UIMULT");
            break;

        case OP_UIDIV: 
            puts("OP_UIDIV");
            break;

        case OP_UIMOD: 
            puts("OP_UIMOD");
            break;

        case OP_UILSHIFT: 
            puts("OP_UILSHIFT");
            break;

        case OP_UIRSHIFT: 
            puts("OP_UIRSHIFT");
            break;

        case OP_UIAND: 
            puts("OP_UIAND");
            break;

        case OP_UIXOR: 
            puts("OP_UIXOR");
            break;

        case OP_UIOR: 
            puts("OP_UIOR");
            break;

        case OP_LADD: 
            puts("OP_LADD");
            break;

        case OP_LSUB: 
            puts("OP_LSUB");
            break;

        case OP_LMULT: 
            puts("OP_LMULT");
            break;

        case OP_LDIV: 
            puts("OP_LDIV");
            break;

        case OP_LMOD: 
            puts("OP_LMOD");
            break;

        case OP_LLSHIFT: 
            puts("OP_LLSHIFT");
            break;

        case OP_LRSHIFT: 
            puts("OP_LRSHIFT");
            break;

        case OP_INVOKE_BLOCK:
            puts("OP_INVOKE_BLOCK");
            break;

        case OP_LAND: 
            puts("OP_LAND");
            break;

        case OP_LXOR: 
            puts("OP_LXOR");
            break;

        case OP_LOR: 
            puts("OP_LOR");
            break;

        case OP_ULADD: 
            puts("OP_ULADD");
            break;

        case OP_ULSUB: 
            puts("OP_ULSUB");
            break;

        case OP_ULMULT: 
            puts("OP_ULMULT");
            break;

        case OP_ULDIV: 
            puts("OP_ULDIV");
            break;

        case OP_ULMOD: 
            puts("OP_ULMOD");
            break;

        case OP_ULLSHIFT: 
            puts("OP_ULLSHIFT");
            break;

        case OP_ULRSHIFT: 
            puts("OP_ULRSHIFT");
            break;

        case OP_ULAND: 
            puts("OP_ULAND");
            break;

        case OP_ULXOR: 
            puts("OP_ULXOR");
            break;

        case OP_UBCOMPLEMENT:
            puts("OP_UBCOMPLEMENT");
            break;

        case OP_SCOMPLEMENT:
            puts("OP_SCOMPLEMENT");
            break;

        case OP_USCOMPLEMENT:
            puts("OP_USCOMPLEMENT");
            break;

        case OP_ICOMPLEMENT:
            puts("OP_ICOMPLEMENT");
            break;

        case OP_UICOMPLEMENT:
            puts("OP_UICOMPLEMENT");
            break;

        case OP_LCOMPLEMENT:
            puts("OP_LCOMPLEMENT");
            break;

        case OP_ULCOMPLEMENT:
            puts("OP_ULCOMPLEMENT");
            break;


        case OP_FADD:
            puts("OP_FADD");
            break;

        case OP_FSUB:
            puts("OP_FSUB");
            break;

        case OP_FMULT:
            puts("OP_FMULT");
            break;

        case OP_FDIV:
            puts("OP_FDIV");
            break;


        case OP_DADD:
            puts("OP_DADD");
            break;

        case OP_DSUB:
            puts("OP_DSUB");
            break;

        case OP_DMULT:
            puts("OP_DMULT");
            break;

        case OP_DDIV:
            puts("OP_DDIV");
            break;


        case OP_PADD:
            puts("OP_PADD");
            break;

        case OP_PSUB:
            puts("OP_PSUB");
            break;

        case OP_PPSUB:
            puts("OP_PPSUB");
            break;


        case OP_CADD:
            puts("OP_CADD");
            break;

        case OP_CSUB:
            puts("OP_CSUB");
            break;


        case OP_BEQ :
            puts("OP_BEQ ");
            break;

        case OP_BNOTEQ :
            puts("OP_BNOTEQ ");
            break;

        case OP_BGT :
            puts("OP_BGT ");
            break;

        case OP_BLE :
            puts("OP_BLE ");
            break;

        case OP_BGTEQ :
            puts("OP_BGTEQ ");
            break;

        case OP_BLEEQ :
            puts("OP_BLEEQ ");
            break;


        case OP_UBEQ :
            puts("OP_UBEQ ");
            break;

        case OP_UBNOTEQ :
            puts("OP_UBNOTEQ ");
            break;

        case OP_UBGT :
            puts("OP_UBGT ");
            break;

        case OP_UBLE :
            puts("OP_UBLE ");
            break;

        case OP_UBGTEQ :
            puts("OP_UBGTEQ ");
            break;

        case OP_UBLEEQ :
            puts("OP_UBLEEQ ");
            break;


        case OP_SEQ :
            puts("OP_SEQ ");
            break;

        case OP_SNOTEQ :
            puts("OP_SNOTEQ ");
            break;

        case OP_SGT :
            puts("OP_SGT ");
            break;

        case OP_SLE :
            puts("OP_SLE ");
            break;

        case OP_SGTEQ :
            puts("OP_SGTEQ ");
            break;

        case OP_SLEEQ :
            puts("OP_SLEEQ ");
            break;


        case OP_USEQ :
            puts("OP_USEQ ");
            break;

        case OP_USNOTEQ :
            puts("OP_USNOTEQ ");
            break;

        case OP_USGT :
            puts("OP_USGT ");
            break;

        case OP_USLE :
            puts("OP_USLE ");
            break;

        case OP_USGTEQ :
            puts("OP_USGTEQ ");
            break;

        case OP_USLEEQ :
            puts("OP_USLEEQ ");
            break;

        case OP_INOTEQ :
            puts("OP_INOTEQ ");
            break;

        case OP_IGT :
            puts("OP_IGT ");
            break;

        case OP_UIEQ :
            puts("OP_UIEQ ");
            break;

        case OP_UINOTEQ :
            puts("OP_UINOTEQ ");
            break;

        case OP_UIGT :
            puts("OP_UIGT ");
            break;

        case OP_UILE :
            puts("OP_UILE ");
            break;

        case OP_UIGTEQ :
            puts("OP_UIGTEQ ");
            break;

        case OP_UILEEQ :
            puts("OP_UILEEQ ");
            break;



        case OP_LEQ :
            puts("OP_LEQ ");
            break;

        case OP_LNOTEQ :
            puts("OP_LNOTEQ ");
            break;

        case OP_LGT :
            puts("OP_LGT ");
            break;

        case OP_LLE :
            puts("OP_LLE ");
            break;

        case OP_LGTEQ :
            puts("OP_LGTEQ ");
            break;

        case OP_LLEEQ :
            puts("OP_LLEEQ ");
            break;


        case OP_ULEQ :
            puts("OP_ULEQ ");
            break;

        case OP_ULNOTEQ :
            puts("OP_ULNOTEQ ");
            break;

        case OP_ULGT :
            puts("OP_ULGT ");
            break;

        case OP_ULLE :
            puts("OP_ULLE ");
            break;

        case OP_ULGTEQ :
            puts("OP_ULGTEQ ");
            break;

        case OP_ULLEEQ :
            puts("OP_ULLEEQ ");
            break;



        case OP_FEQ :
            puts("OP_FEQ ");
            break;

        case OP_FNOTEQ :
            puts("OP_FNOTEQ ");
            break;

        case OP_FGT :
            puts("OP_FGT ");
            break;

        case OP_FLE :
            puts("OP_FLE ");
            break;

        case OP_FGTEQ :
            puts("OP_FGTEQ ");
            break;

        case OP_FLEEQ :
            puts("OP_FLEEQ ");
            break;



        case OP_DEQ :
            puts("OP_DEQ ");
            break;

        case OP_DNOTEQ :
            puts("OP_DNOTEQ ");
            break;

        case OP_DGT :
            puts("OP_DGT ");
            break;

        case OP_DLE :
            puts("OP_DLE ");
            break;

        case OP_DGTEQ :
            puts("OP_DGTEQ ");
            break;

        case OP_DLEEQ :
            puts("OP_DLEEQ ");
            break;



        case OP_PEQ :
            puts("OP_PEQ ");
            break;

        case OP_PNOTEQ :
            puts("OP_PNOTEQ ");
            break;

        case OP_PGT :
            puts("OP_PGT ");
            break;

        case OP_PLE :
            puts("OP_PLE ");
            break;

        case OP_PGTEQ :
            puts("OP_PGTEQ ");
            break;

        case OP_PLEEQ :
            puts("OP_PLEEQ ");
            break;


        case OP_CEQ :
            puts("OP_CEQ ");
            break;

        case OP_CNOTEQ :
            puts("OP_CNOTEQ ");
            break;

        case OP_CGT :
            puts("OP_CGT ");
            break;

        case OP_CLE :
            puts("OP_CLE ");
            break;

        case OP_CGTEQ :
            puts("OP_CGTEQ ");
            break;

        case OP_CLEEQ :
            puts("OP_CLEEQ ");
            break;

        case OP_REGEQ :
            puts("OP_REGEQ ");
            break;

        case OP_REGNOTEQ :
            puts("OP_REGNOTEQ ");
            break;

        case OP_ULOR: 
            puts("OP_ULOR");
            break;

        case OP_RETURN: 
            puts("OP_RETURN");
            break;

        case OP_TRY:
            puts("OP_TRY");
            break;

        case OP_INVOKE_METHOD:
            puts("OP_INVOKE_METHOD");
            break;

        case OP_THROW:
            puts("OP_THROW");
            break;

        case OP_CREATE_STRING:
            puts("OP_CREATE_STRING");
            break;

        case OP_CREATE_REGEX:
            puts("OP_CREATE_REGEX");
            break;

        case OP_HEAD_OF_EXPRESSION: 
            puts("OP_HEAD_OF_EXPRESSION");
            break;

        case OP_SIGINT:
            puts("OP_SIGINT");
            break;

        case OP_NEW:
            puts("OP_NEW");
            break;

        case OP_BCOMPLEMENT:
            puts("OP_BCOMPLEMENT");
            break;

        case OP_IEQ:
            puts("OP_IEQ");
            break;

        case OP_ILE:
            puts("OP_ILE");
            break;

        case OP_IGTEQ:
            puts("OP_IGTEQ");
            break;

        case OP_ANDAND:
            puts("OP_ANDAND");
            break;

        case OP_LOAD_FIELD:
            puts("OP_LOAD_FIELD");
            break;

        case OP_BYTE_TO_INT_CAST:
            puts("OP_BYTE_TO_INT_CAST");
            break;

        case OP_LOAD_ELEMENT :
            puts("OP_LOAD_ELEMENT");
            break;

        case OP_STORE_ELEMENT:
            puts("OP_STORE_ELEMENT");
            break;

/*
        case OP_INT_TO_BYTE_CAST:
            puts("OP_INT_TO_BYTE_CAST");
            break;
*/

        default:
            printf("opecode %d\n", opecode);
            break;
    }
}

void show_stack_stat(CLVALUE** stack_ptr, CLVALUE* stack)
{
    printf("stack_ptr %p\n", *stack_ptr);
    printf("stack %p\n", *stack);
    printf("stack_ptr - stack %d\n", (int)((*stack_ptr) - stack));
}

void show_str_in_jit(char* str)
{
    printf("%s\n", str);
}

}
