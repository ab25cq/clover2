#include "common.h"

int utf8_index_to_utf32_index(char* str, int utf8_index)
{
    unsigned char* str2 = (unsigned char*)str;
    unsigned char* p = str2;

    int utf32_index = 0;

    if(utf8_index == 0) {
        return 0;
    }

    while(*p) {
        /// utf8 character ///
        if(*p > 127) {
            int size;

            size = ((*p & 0x80) >> 7) + ((*p & 0x40) >> 6) + ((*p & 0x20) >> 5) + ((*p & 0x10) >> 4);

            if(size > MB_LEN_MAX) {
                return -1;
            }
            else {
                p+=size;
            }

            utf32_index++;
        }
        /// ascii ///
        else {
            p++;
            utf32_index++;
        }

        if(p - str2 == utf8_index) {
            break;
        }
    }

    return utf32_index;
}

int utf32_index_to_utf8_index(char* str, int utf32_index)
{
    unsigned char* str2 = (unsigned char*)str;
    unsigned char* p = str2;

    int utf32_index2 = 0;

    if(utf32_index == 0) {
        return 0;
    }

    while(*p) {
        /// utf8 character ///
        if(*p > 127) {
            int size;

            size = ((*p & 0x80) >> 7) + ((*p & 0x40) >> 6) + ((*p & 0x20) >> 5) + ((*p & 0x10) >> 4);

            if(size > MB_LEN_MAX) {
                return -1;
            }
            else {
                p+=size;
            }

            utf32_index2++;
        }
        /// ascii ///
        else {
            p++;
            utf32_index2++;
        }

        if(utf32_index2 == utf32_index) {
            break;
        }
    }

    return p - str2;
}
