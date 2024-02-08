#include "../std/stringview.h"
// #include "../std/other.h"

#include <stdio.h>

int main() {
    stringview s = sv_from("abcde");

    s = sv_slice("abcde", 0, 3);
    printf("%s\n", s);

    // for (int i = 0; i < sv_len(s); i++) {
    //     printf("%c", s[i]);
    // }
    // printf("\n");

    return 0;
}