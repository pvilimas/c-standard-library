#ifndef STD_ARRAY_H
#define STD_ARRAY_H

#include <stdint.h>
#include <stdlib.h>

/*

	array.h - static array

	The type array(T) is defined as T* so you can read and write elements
	directly, see array_example.c. Just like with pointers, there is no bounds
	checking.

	Methods:

	array_size(a) -> size_t             -- Returns the size of the array

	array_new(T, s) -> array<T>         -- Creates a new array with size s
	array_free(a)                       -- Frees all memory in the array

*/

#define array(T) T*

#define array_elemsize(dptr) \
	(*(((size_t*) (dptr)) - 2))

#define array_size(dptr) \
	(*(((size_t*) (dptr)) - 1))

#define array_new(T, sz) \
	((T*) f_array_new(sizeof(T), (sz)))

#define array_free(a) \
	f_array_free((void*)(a))

// MEMORY LAYOUT:
// size_t elemsize  <-- hptr points here
// size_t size
// T*	  dptr		<-- the pointer given to the user

// internal macros for converting between dptr and hptr
// dptr - data pointer, only contains the data
// hptr - header pointer, contains header and data

#define i_array_d2h(dptr) \
	(((size_t*) (dptr)) - 2)

#define i_array_h2d(hptr) \
	((void*)(((size_t*) (hptr)) + 2))

// internal helper functions

static inline void* f_array_new(size_t esz, size_t sz) {
	// allocate header + data
	size_t total_size = (sizeof(size_t) * 2) + (esz * sz);
	size_t* hptr = malloc(total_size);
    hptr[0] = esz;
    hptr[1] = sz;
    return i_array_h2d(hptr); // return dptr
}

static inline void* f_array_from(size_t esz, size_t sz) {
	// allocate header + data
	size_t total_size = (sizeof(size_t) * 2) + (esz * sz);
	size_t* hptr = malloc(total_size);
    hptr[0] = esz;
    hptr[1] = sz;
    return i_array_h2d(hptr); // return dptr
}

static inline void f_array_free(void* dptr) {
	free(i_array_d2h(dptr));
}

#endif // STD_ARRAY_H
