#include "common.h"

//////////////////////////////////////////////////
// Constant Pool operation. Make it resizable and get alignment
//////////////////////////////////////////////////
void sConst_init(sConst* self)
{
    self->mSize = 1024;
    self->mLen = 0;
    self->mConst = MCALLOC(1, sizeof(char)*self->mSize);
}

void sConst_init_with_size(sConst* self, int size)
{
    self->mSize = size;
    self->mLen = 0;
    self->mConst = MCALLOC(1, sizeof(char)*self->mSize);
}

void sConst_free(sConst* self)
{
    MFREE(self->mConst);
}

static void arrange_alignment(sConst* self)
{
    alignment((unsigned int*)&self->mLen);
}

int sConst_append(sConst* self, void* data, size_t size, BOOL no_output)
{
    if(!no_output) {
        arrange_alignment(self);

        void* data2;

        data2 = MCALLOC(1, size);        // prevent deleting from bellow REALLOC
        memcpy(data2, data, size);

        if(self->mSize <= self->mLen + size + 1) {
            int new_size = (self->mLen + size + 1) * 2;
            char* new_constant = MCALLOC(1, new_size);

            memcpy(new_constant, self->mConst, self->mLen);
            MFREE(self->mConst);

            self->mConst = new_constant;
            self->mSize = new_size;
        }

        int result = self->mLen;

        memcpy(self->mConst + self->mLen, data2, size);
        self->mLen += size;

        MFREE(data2);

        return result;
    }
    else {
        return 0;
    }
}

int append_int_value_to_constant_pool(sConst* constant, int n, BOOL no_output)
{
    return sConst_append(constant, &n, sizeof(int), no_output);
}

int append_float_value_to_constant_pool(sConst* constant, float n, BOOL no_output)
{
    return sConst_append(constant, &n, sizeof(float), no_output);
}

int append_double_value_to_constant_pool(sConst* constant, double n, BOOL no_output)
{
    return sConst_append(constant, &n, sizeof(double), no_output);
}

int append_str_to_constant_pool(sConst* constant, char* str, BOOL no_output)
{
    size_t len = strlen(str);
    int result = sConst_append(constant, str, len+1, no_output);

    return result;
}

int append_wstr_to_constant_pool(sConst* constant, char* str, BOOL no_output)
{
    int len;
    wchar_t* wcs;
    int result;

    len = strlen(str);
    wcs = MMALLOC(sizeof(wchar_t)*(len+1));
    (void)mbstowcs(wcs, str, len+1);

    result = sConst_append(constant, wcs, sizeof(wchar_t)*(len+1), no_output);

    MFREE(wcs);

    return result;
}

void append_str_to_constant_pool_and_code(sConst* constant, sByteCode* code, char* str, BOOL no_output)
{
    int offset = append_str_to_constant_pool(constant, str, no_output);
    append_int_value_to_code(code, offset, no_output);
}

void append_buffer_to_constant_pool_and_code(sConst* constant, sByteCode* code, char* buf, int size, BOOL no_output)
{
    int offset = sConst_append(constant, buf, size, no_output);
    append_int_value_to_code(code, offset, no_output);
}

