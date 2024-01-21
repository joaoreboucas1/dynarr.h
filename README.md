# Dynamic Array in C

`dynarr.h` is a header-only library that dispatches dynamic array definitions for any given type, including primitives and structs. So far, we only provide routines for initialization and appending single elements. Check `demo.c` for the basic functionality.

# Basic usage
```c
#include "dynarr.h"
DEFINE_DYN_ARRAY(int)

int main()
{
    int nums[] = {1, 2, 3, 4};
    DA_int a = da_int_from(nums);  // Creates a dynamic array from fixed size array
    DA_int b = da_int_fill(10, 3); // Creates a dynamic array of size 10 filled with 3
    da_int_append(&a, 4); // Appends an element to the array
    da_free(a);
    da_free(b);
}
```

# TODO:
- I would like to define `da_print` macro for a struct with many fields, something like `SV_Arg`