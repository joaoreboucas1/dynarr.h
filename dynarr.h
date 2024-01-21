#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXPAND_SIZE 30

#define DEFINE_PRINT_DEBUG(type, fmt)\
    void da_##type##_print(DA_##type array) \
    { \
        printf("len: %zu\n", array.len); \
        printf("cap: %zu\n", array.cap); \
        printf("elements:\n"); \
        for (size_t i = 0; i < array.len; i++) { \
            printf("  %zu: "fmt"\n", i, array.items[i]); \
        } \
    }

/*
    #define DEFINE_PRINT_DEBUG(type, fmt, ...)\
        void da_##type##_print(DA_##type array) \
        { \
            printf("len: %zu\n", array.len); \
            printf("cap: %zu\n", array.cap); \
            printf("elements:\n"); \
            for (size_t i = 0; i < array.len; i++) { \
                printf("  %zu: "fmt"\n", i, array.items[i]); \
            } \
        }
*/

#define da_free(array)\
{\
    free(array.items);\
}\

#define DEFINE_DYN_ARRAY(type) \
    typedef struct { \
        type *items; \
        size_t len; \
        size_t cap; \
    } DA_##type; \
    DA_##type da_##type##_from(type *array, size_t array_size) \
    { \
        size_t bytes = (array_size + EXPAND_SIZE)*sizeof(type); \
        type *p = malloc(bytes); \
        if (p == NULL) { \
            printf("ERROR: could not allocate %zu bytes", bytes); \
            exit(1); \
        } \
        memcpy(p, array, bytes); \
        DA_##type a = { \
            .items = p, \
            .len = array_size, \
            .cap = (array_size + EXPAND_SIZE), \
        }; \
        return a; \
    } \
    DA_##type da_##type##_zeros(size_t size) \
    { \
        size_t bytes = (size + EXPAND_SIZE)*sizeof(type); \
        type *p = malloc(bytes); \
        if (p == NULL) { \
            printf("ERROR: could not allocate %zu bytes", bytes); \
            exit(1); \
        } \
        memset(p, 0, bytes); \
        DA_##type array = { \
            .items = p, \
            .len = size, \
            .cap = (size + EXPAND_SIZE) \
        }; \
        return array; \
    } \
\
    DA_##type da_##type##_fill(size_t size, type n)\
    {\
        size_t cap = (size + EXPAND_SIZE);\
        size_t bytes = cap*sizeof(type);\
        type *p = malloc(bytes);\
        if (p == NULL) {\
            printf("ERROR: could not allocate %zu bytes", bytes);\
            exit(1);\
        }\
        DA_##type array = {\
            .items = p,\
            .len = size,\
            .cap = cap\
        };\
        for (size_t i = 0; i < size; i++) {\
            array.items[i] = n;\
        }\
        return array;\
    }\
\
    void da_##type##_expand(DA_##type *array)\
    {\
        const size_t new_cap = array->cap + EXPAND_SIZE;\
        const size_t bytes = new_cap * sizeof(type);\
        \
        type *new_storage = malloc(bytes);\
        if (new_storage == NULL) {\
            printf("ERROR: could not allocate %zu bytes", bytes);\
            exit(1);\
        }\
        \
        memcpy(new_storage, array->items, array->cap*sizeof(type));\
\
        free(array->items);\
        array->items = new_storage;\
        array->cap = new_cap;\
    }\
    void da_##type##_append(DA_##type *array, type n)\
    {\
        if (array->len == array->cap) da_##type##_expand(array);\
        array->items[array->len] = n;\
        array->len += 1;\
    }\
