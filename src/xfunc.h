#ifndef XFUNC_H
#define XFUNC_H

extern char* xstrncpy(char* des, char* src, int size);
extern char* xstrncat(char* des, char* str, int size);
ALLOC char* xwcstombs(wchar_t* wstr, int len);

#endif
