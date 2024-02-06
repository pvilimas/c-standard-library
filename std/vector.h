#ifndef STD_VECTOR_H
#define STD_VECTOR_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*

	vector.h - dynamic array

	Only the basic functions are provided and there is no error checking or
	bounds checking (for example if you call vector_pop or access v[5] when the
	vector is empty). There are no iterator functions or anything like that,
	just use a loop with vector_size().

	The type vector(T) is defined as T* so you can read and write elements
	directly, see vector_example.c.

	Methods:

	vector_size(v) -> size_t            -- Returns the size of the vector
	vector_cap(v) -> size_t             -- Returns the capacity of the vector
	vector_is_empty(v) -> bool          -- Is the size equal to zero?

	vector_new(T) -> vector<T>          -- Creates a new vector
	vector_free(v)                      -- Frees all memory in the vector
	vector_push(v, T) -> T              -- Push a value and return it
	vector_pop(v) -> T                  -- Pop a value and return it
	vector_insert(v, i, T)              -- Insert a value at index i
	vector_remove(v, i)                 -- Remove value at index i
	
*/

#define VECTOR_INITIAL_CAP 10
#define VECTOR_RESIZE_FACTOR 2

#define vector(T) T*

#define vector_elemsize(dptr) \
	(*(((size_t*) (dptr)) - 3))

#define vector_size(dptr) \
	(*(((size_t*) (dptr)) - 2))

#define vector_cap(dptr) \
	(*(((size_t*) (dptr)) - 1))

#define vector_new(T) \
	((T*) f_vector_new(sizeof(T), 0, VECTOR_INITIAL_CAP))

#define vector_free(v) \
	f_vector_free((void*)(v))

// using __VA_ARGS__ here allows compound initializer to be used
#define vector_push(v, ...) 		\
	(vector_size((v))++, 			\
	(v) = f_vector_try_resize((v)), \
	(v)[vector_size((v))-1] = (__VA_ARGS__))

#define vector_pop(v) \
	(vector_size((v))--, (v)[vector_size((v))])

#define vector_insert(v, i, ...)                        \
	(vector_size((v))++,                                \
	(v) = f_vector_try_resize((v)),                     \
	memmove((void*)(v + i + 1), (void*)(v + i),         \
	vector_elemsize(v) * (vector_size(v) - i - 1)),     \
	(v)[(i)] = (__VA_ARGS__))

#define vector_remove(v, i)                             \
	(vector_size(v) != 0) && (vector_size((v))--,       \
	memmove((void*)(v + i), (void*)(v + i + 1),         \
	vector_elemsize(v) * (vector_size(v) - i)))

#define vector_is_empty(v) \
	(vector_size((v)) == 0)

// MEMORY LAYOUT:
// size_t elemsize  <-- hptr points here
// size_t size
// size_t cap
// T*	  dptr		<-- the pointer given to the user

// internal macros for converting between dptr and hptr
// dptr - data pointer, only contains the data
// hptr - header pointer, contains header and data

#define i_vector_d2h(dptr) \
	(((size_t*) (dptr)) - 3)

#define i_vector_h2d(hptr) \
	((void*)(((size_t*) (hptr)) + 3))

// internal helper functions

static inline void* f_vector_new(size_t esz, size_t sz, size_t cap) {
	// allocate header + data
	size_t total_size = (sizeof(size_t) * 3) + (esz * cap);
	size_t* hptr = malloc(total_size);
    hptr[0] = esz;
    hptr[1] = sz;
    hptr[2] = cap;
    return i_vector_h2d(hptr); // return dptr
}

static inline void f_vector_free(void* dptr) {
	free(i_vector_d2h(dptr)); 
}

// double capacity if size = capacity
static inline void* f_vector_try_resize(void* dptr) {
	if (vector_size(dptr) == vector_cap(dptr)) {
		vector_cap(dptr) *= VECTOR_RESIZE_FACTOR;
		void* hptr = i_vector_d2h(dptr);
		size_t total_size = (sizeof(size_t) * 3) + 
			vector_elemsize(dptr) * vector_cap(dptr);
		hptr = realloc(hptr, total_size);
		return i_vector_h2d(hptr);
	}
	return dptr;
}

#endif // STD_VECTOR_H
