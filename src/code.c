#include "common.h"

#define BYTE_CODE_INIT_SIZE 128

void sByteCode_init(sByteCode* code)
{
    code->mCodes = MCALLOC(1, sizeof(char)*BYTE_CODE_INIT_SIZE);
    code->mLen = 0;
    code->mSize = BYTE_CODE_INIT_SIZE;
}

void sByteCode_free(sByteCode* code)
{
    MFREE(code->mCodes);
}

static void arrange_alignment(sByteCode* code)
{
    code->mLen = (code->mLen + 3) & ~3;
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
