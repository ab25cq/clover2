#include "buffer.h"
#include "debug.h"
#include <wchar.h>
#include <string.h>
#include <ctype.h>

//////////////////////////////////////////////////
// resizable buf
//////////////////////////////////////////////////
void sBuf_init(sBuf* self)
{
    self->mBuf = (char*)MMALLOC(sizeof(char)*64);
    self->mSize = 64;
    self->mLen = 0;
    *(self->mBuf) = 0;
}

void sBuf_append(sBuf* self, void* str, size_t size)
{
    void* str2 = (char*)MCALLOC(1, size);        // prevent deleting from bellow MREALLOC
    memcpy(str2, str, size);

    if(self->mSize <= self->mLen + size + 1) {
        self->mSize = (self->mSize + size + 1) * 2;
        self->mBuf = (char*)MREALLOC(self->mBuf, sizeof(char)*self->mSize);
    }

    memcpy(self->mBuf + self->mLen, str2, size);

    self->mLen += size;
    self->mBuf[self->mLen] = 0;

    MFREE(str2);
}

void sBuf_append_char(sBuf* self, char c)
{
    if(self->mSize <= self->mLen + 1 + 1) {
        self->mSize = (self->mSize + 1 + 1) * 2;
        self->mBuf = (char*)MREALLOC(self->mBuf, sizeof(char)*self->mSize);
    }

    self->mBuf[self->mLen] = c;
    self->mLen++;
    self->mBuf[self->mLen] = 0;
}

void sBuf_append_str(sBuf* self, char* str)
{
    sBuf_append(self, str, strlen(str));
}
