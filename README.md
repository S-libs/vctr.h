# Minimalist C Dynamic Vector

A header-only, type-safe dynamic array implementation for C. It uses a "hidden header" approach, allowing you to treat the vector as a standard C array while storing metadata (size and capacity) just before the data pointer.
## How it Works

The implementation stores a VectorHeader struct in memory immediately preceding the array data.
<code>[ Capacity | Size ] [ Element 0 | Element 1 | Element 2 | ... ] 
^ Header ^ Your pointer (v) points here </code>

## API Reference

<code>vec_header(v)</code>

Internal Helper. Returns a pointer to the VectorHeader by shifting the user pointer v backwards. This is used by other macros to access metadata.

<code>vec_size(v)</code>

Returns the current element count.
If the vector is NULL, it returns 0.
Otherwise, it reads the size field from the header.

<code>vec_capacity(v)</code>

Returns the allocated capacity.
Shows how many elements the vector can hold before the next reallocation.

<code>vec_push(v, val)</code>

Adds an element to the end.
Automatic Scaling: If the vector is full or NULL, it doubles the capacity (starting at 2).
Memory Management: Uses realloc to adjust the buffer size (Header + Data).
Pointer Update: Since realloc might move the buffer, it updates your pointer v to the new data location.

<code>vec_remove(v, idx)</code>

Removes an element at a specific index.
Bounds Checking: Ensures the index is valid.
Shift: Uses memmove to shift subsequent elements one position to the left, maintaining order.
Update: Decrements the size in the header.

<code>vec_free(v)</code>

Deallocates the vector.
Frees the memory starting from the header (the true start of the block).
Sets your pointer v to NULL to prevent "use-after-free" bugs.

## Quick Example

``` c
int *my_vec = NULL;
vec_push(my_vec, 10);
vec_push(my_vec, 20);

printf("Size: %zu\n", vec_size(my_vec)); // Output: 2
vec_remove(my_vec, 0); // Removes 10
vec_free(my_vec);
```
