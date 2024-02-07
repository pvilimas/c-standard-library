#ifndef STD_OTHER_H
#define STD_OTHER_H

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define assert_true(condition, errmsg) \
    do {
        if (!(condition)) {
            const char* file_name = strrchr(__FILE__, '/');
            file_name = (!!file_name)
                ? file_name + 1
                : __FILE__;
            printf("assertion '%s' failed @ %s:%d\n",
                #condition,
                file_name,
                __LINE__);
            printf("\terrmsg: '%s'\n", (errmsg));
            exit(1);
        }
    } while(0)

#define breakpoint                  \
    printf("breakpoint @ %s:%d\n",  \
    (strrchr((__FILE__), '/')       \
    ? strrchr((__FILE__), '/') + 1  \
    : (__FILE__)), __LINE__)

#endif // STD_OTHER_H