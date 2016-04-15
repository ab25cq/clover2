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

#endif
