#include "common.h"

#define BYTE_CODE_INIT_SIZE 128

void sByteCode_init(sByteCode* code)
{
    code->mCodes = MCALLOC(1, sizeof(char)*BYTE_CODE_INIT_SIZE);
    code->mLen = 0;
    code->mSize = BYTE_CODE_INIT_SIZE;
}

void sByteCode_init_with_size(sByteCode* code, int size)
{
    code->mCodes = MCALLOC(1, sizeof(char)*size);
    code->mLen = 0;
    code->mSize = size;
}

void sByteCode_free(sByteCode* code)
{
    MFREE(code->mCodes);
}

static void arrange_alignment(sByteCode* code)
{
    alignment(&code->mLen);
}

void append_value_to_code(sByteCode* code, void* data, size_t size, BOOL no_output)
{
    if(!no_output) {
        arrange_alignment(code);

        if(code->mSize <= code->mLen + size) {
            size_t new_size = (code->mSize + size) * 2;
            code->mCodes = MREALLOC(code->mCodes, new_size);
            memset(code->mCodes + code->mSize, 0, sizeof(char)*(new_size - code->mSize));

            code->mSize = new_size;
        }

        memcpy(code->mCodes + code->mLen, data, size);
        code->mLen += size;
    }
}

void append_opecode_to_code(sByteCode* code, unsigned int op, BOOL no_output)
{
    append_value_to_code(code, &op, sizeof(int), no_output);
}

void append_int_value_to_code(sByteCode* code, int value, BOOL no_output)
{
    append_value_to_code(code, &value, sizeof(int), no_output);
}

void append_long_value_to_code(sByteCode* code, long value, BOOL no_output)
{
    int n1, n2;

    memcpy(&n1, &value, sizeof(int));
    memcpy(&n2, (char*)&value + sizeof(int), sizeof(int));

    append_value_to_code(code, &n1, sizeof(int), no_output);
    append_value_to_code(code, &n2, sizeof(int), no_output);
}
