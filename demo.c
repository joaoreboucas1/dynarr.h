#include <stdio.h>
#include "dynarr.h"

DEFINE_DYN_ARRAY(int)           // Creates a new type called DA_int and many functions
DEFINE_DYN_ARRAY(float)         // Creates a new type called DA_float and many functions
DEFINE_PRINT_DEBUG(int, "%d")   // Creates a da_int_print function that dumps the array info
DEFINE_PRINT_DEBUG(float, "%f") // Creates a da_float_print function that dumps the array info
typedef DA_int ArrayInt;        // You can create aliases if you don't like the syntax
#define ArrayInt_from(arr, size) da_int_from(arr, size)


// Dynamic array of struct
// This creates the type DA_Point
typedef struct {
    int x;
    int y;
} Point;
DEFINE_DYN_ARRAY(Point)

// Nested dynamic array of int
DEFINE_DYN_ARRAY(DA_int)

int main()
{
    // Create dynamic array from static array
    int nums[5] = {1, 2, 3};
    DA_int a = da_int_from(nums, 3);
    printf("Dynamic array of `int` from static array [1, 2, 3]:\n");
    da_int_print(a);
    printf("----------------------------\n");
    // Append element to array
    printf("After appending 4:\n");
    da_int_append(&a, 4);
    da_int_print(a);
    printf("----------------------------\n");
    // Zero-initialized array
    printf("Dynamic array of `int` initialized with zeros:\n");
    DA_int b = da_int_zeros(2);
    da_int_print(b);
    printf("----------------------------\n");
    // Array filled with value
    printf("Dynamic array of `int` initialized with the value 13:\n");
    DA_int c = da_int_fill(3, 13);
    da_int_print(c);
    printf("----------------------------\n");
    // DA of DA
    printf("Dynamic array of dynamic array of `int`:\n");
    DA_DA_int nested = da_DA_int_fill(2, a);
    nested.items[0] = b;
    for (size_t i = 0; i < nested.len; i++) {
        printf("%zu: \n", i);
        da_int_print(nested.items[i]);
    }
    printf("---------------------------\n");
    // Float arrays
    printf("Dynamic array of `float`:\n");
    float v[3] = {1.0f, 3.14f, -1.5f};
    DA_float d = da_float_from(v, 3);
    da_float_append(&d, 4.20f);
    da_float_print(d);
    printf("----------------------------\n");
    // Struct arrays
    printf("Dynamic array of `struct Point {int x; int y;}`:\n");
    DA_Point e = da_Point_zeros(2);
    da_Point_append(&e, (Point) {.x = 1, .y = 3});
    printf("e elements:\n");
    for (size_t i = 0; i < e.len; i++) {
        printf("  %zu: (%d, %d)\n", i, e.items[i].x, e.items[i].y);
    }

    // User must deallocate the dynamic arrays when they are not needed
    da_free(a);
    da_free(b);
    da_free(c);
    da_free(d);
    da_free(e);
    return 0;
}