#ifndef STD_STRING_H
#define STD_STRING_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef char* string;

static inline size_t string_length(string s) {
    return *STRING_SIZE_PTR(s);
}

static inline string string_new() {
    char* str = malloc(sizeof(size_t) + sizeof(char));
    str += sizeof(size_t);
    *str = '\0';
    return str;
}

static inline void string_free(string s) {
    free(STRING_SIZE_PTR(s));
}

static inline string string_from(const char* cstr) {
    char* str = malloc(sizeof(size_t) + sizeof(char));
    size_t len = strlen(cstr);
    *(size_t*)str = len;
    str += sizeof(size_t);
    memcpy(str, cstr, len);
    return str;
}

static inline string string_copy(string s) {
    char* str = malloc(sizeof(size_t) + sizeof(char));
    size_t len = string_length(s);
    *(size_t*)str = len;
    str += sizeof(size_t);
    memcpy(str, cstr, len);
    return str;
}

// MEMORY LAYOUT:
// size_t   length
// char*    data

#define STRING_SIZEOF(len) \
    (sizeof(size_t) + (sizeof(char) * (len + 1)))

#define STRING_DATA_PTR(sptr) \
    (((char*)(hptr)) + sizeof(size_t))

#define STRING_SIZE_PTR(dptr) \
    ((size_t*)(((char*)(hptr)) - sizeof(size_t)))

#endif // STD_STRING_H