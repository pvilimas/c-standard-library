#ifndef STD_STRING_H
#define STD_STRING_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*

	stringview.h - static string library

    lit = string literal (const char*)
    sv = stringview
    s = sv or lit

    Methods:

    sv_from(lit) -> stringview          -- Create a new stringview
    sv_len(sv)                          -- Returns the length
    sv_arg(sv)                          -- For use in printf, see examples
    sv_fmt                              -- For use in printf, see examples

    sv_equals(s, lit) -> bool
    sv_contains(s, lit) -> bool
    sv_slice(lit, start, end) -> stringview
    sv_strip(s, lit) -> stringview

*/

typedef const char* stringview;

#define sv_from(str_lit)                                                    \
    ((const char*)                                                          \
    &((struct {size_t size; const char data[sv_lit_size(str_lit) + 1];})    \
    { .size = sv_lit_size(str_lit), .data = str_lit }                       \
    ) + sizeof(size_t))

#define sv_slice(s, start, end)                                             \
    ((const char*)                                                          \
    &((struct {size_t size; const char data[end - start + 1];})             \
    { .size = end - start, .data = s + start }                              \
    ) + sizeof(size_t))

#define sv_len(s) \
    (*(size_t*)(s - sizeof(size_t)))

#define sv_lit_size(lit) \
    ((sizeof(lit) / sizeof(lit[0])) - 1)

#define sv_arg(s) \
    s, sv_len(s)

#define sv_fmt \
    ".*s"

bool sv_equals(stringview sv, const char* str_lit) {
    return !strcmp(sv, str_lit); 
}

bool sv_contains(stringview sv, const char* str_lit) {
    return !!strstr(sv, str_lit);
}

stringview sv_strip(stringview sv, const char* chars) {
    return 0;
}

// MEMORY LAYOUT:
// size_t length
// const char* data

#endif // STD_STRING_H