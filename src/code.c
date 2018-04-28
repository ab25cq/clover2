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
    code->mSize = size;
    code->mCodes = MCALLOC(1, sizeof(char)*code->mSize);
    code->mLen = 0;
}

void sByteCode_free(sByteCode* code)
{
    MFREE(code->mCodes);
}

void sByteCode_clone(sByteCode* self, sByteCode* code)
{
    if(code->mLen > 0) {
        self->mSize = code->mLen;
        self->mCodes = MCALLOC(1, sizeof(char)*code->mLen);
        self->mLen = code->mLen;

        memcpy(self->mCodes, code->mCodes, code->mLen);
    }
    else {
        self->mSize = 64;
        self->mCodes = MCALLOC(1, sizeof(char)*self->mSize);
        self->mLen = 0;
    }
}

static void arrange_alignment(sByteCode* code)
{
    alignment(&code->mLen);
}

void append_value_to_code(sByteCode* code, void* data, size_t size, BOOL no_output)
{
    if(!no_output) {
        arrange_alignment(code);

        if(code->mLen + size + 1 >= code->mSize) {
            size_t new_size = (code->mLen + size + 1) * 2;
            char* new_code = MCALLOC(1, new_size);
            
            memcpy(new_code, code->mCodes, code->mLen);
            MFREE(code->mCodes);

            code->mCodes = new_code;
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

void append_float_value_to_code(sByteCode* code, float value, BOOL no_output)
{
    append_value_to_code(code, &value, sizeof(float), no_output);
}

void append_long_value_to_code(sByteCode* code, clint64 value, BOOL no_output)
{
    int n1, n2;

    memcpy(&n1, &value, sizeof(int));
    memcpy(&n2, (char*)&value + sizeof(int), sizeof(int));

    append_value_to_code(code, &n1, sizeof(int), no_output);
    append_value_to_code(code, &n2, sizeof(int), no_output);
}

void append_double_value_to_code(sByteCode* code, double value, BOOL no_output)
{
    int n1, n2;

    memcpy(&n1, &value, sizeof(int));
    memcpy(&n2, (char*)&value + sizeof(int), sizeof(int));

    append_value_to_code(code, &n1, sizeof(int), no_output);
    append_value_to_code(code, &n2, sizeof(int), no_output);
}

