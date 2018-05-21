#ifndef BUFFER_H
#define BUFFER_H

#include <unistd.h>

/// resizable buffer
struct sBufStruct {
    char* mBuf;
    int mSize;
    int mLen;
};

typedef struct sBufStruct sBuf;

void sBuf_init(sBuf* self);
void sBuf_append(sBuf* self, void* str, size_t size);
void sBuf_append_char(sBuf* self, char c);
void sBuf_append_str(sBuf* self, char* str);
void sBuf_append_int(sBuf* self, int value);
void sBuf_append_long(sBuf* self, long long value);
void sBuf_clone(sBuf* self, sBuf* buf);

#endif
