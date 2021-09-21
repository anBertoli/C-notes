#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Objects are dynamically allocated with functions like malloc, calloc, realloc. The
 * lifetime of these objects begins when the allocation occurs and ends when the
 * objects are manually deallocated (with the free function). Dynamically allocated
 * memory is allocated from the heap, which is simply one or more large, subdividable
 * blocks of memory that are managed by the memory manager.
 *
 * A memory manager runs as part of the client process. The memory manager will request
 * one or more blocks of memory from the operating system and then allocate this memory
 * to the client process when it invokes a memory allocation function. Once memory has
 * been allocated, the caller manages the memory until it’s returned. It’s the caller’s
 * responsibility to ensure that the memory is deallocated.
 *
 * Dynamically allocated memory is used when the exact storage requirements for a program
 * are unknown before runtime. Dynamically allocated memory is less efficient than
 * statically allocated memory, because the memory manager needs to find appropriately
 * sized blocks of memory in the runtime heap, and then the caller must explicitly free
 * those blocks when no longer needed, all of which requires additional processing. By
 * default, you should declare objects with either automatic or static storage duration
 * for objects whose sizes are known at compilation time.
 *
 * Memory leaks occur when dynamically allocated memory that’s no longer needed isn’t
 * returned to the memory manager. If these memory leaks are severe, the memory manager
 * will eventually be unable to satisfy new requests for storage.
 */

/*
 * The malloc function allocates space for an object of a specified size whose initial
 * value is indeterminate. All memory allocation functions accept an argument of type
 * size_t that specifies the number of bytes of memory to be allocated. For portability,
 * we use the sizeof operator when calculating the size of objects, as the size of
 * objects of various types, such as int and long, may differ among implementations.
 * The malloc function returns either a null pointer to indicate an error, or a
 * pointer to the allocated space.
 */

typedef struct {
    char name[10];
    int quantity;
} widget;

void malloc_func(void) {
    // Allocate space to contain a widget struct.
    widget *w = malloc(sizeof(widget));
    if (w == NULL) {
        return;
    }
    strcpy(w->name, "John");
    w->quantity = 10;

    // Allocate space to contain an array of 10 widgets.
    widget *w_arr = malloc(sizeof(widget) * 10);
    if (w_arr == NULL) {
        return;
    }
    for (int i = 0; i < 10; i++) {
        w_arr[i] = (widget){
            .name = "widget",
            .quantity = i
        };
    }


    // At some point, in this function or in an upper one
    // in the call stack, we must release the memory.
    free(w_arr);
    free(w);
}

/*
 * The calloc function allocates storage for an array of n objects, each of whose size
 * is m bytes. This function initializes the storage to all zero-valued bytes. This zero
 * value might not be the same one used to represent floating-point zero or null-pointer
 * constants (malloc doesn't zeroes the allocated bytes).
 */

void calloc_func(void) {
    // Allocate space to contain a widget struct.
    widget *w = calloc(1, sizeof(widget));
    if (w == NULL) {
        return;
    }
    strcpy(w->name, "John");
    w->quantity = 10;

    // Allocate space to contain an array of 10 widgets.
    widget *w_arr = calloc(10, sizeof(widget));
    if (w_arr == NULL) {
        return;
    }
    for (int i = 0; i < 10; i++) {
        w_arr[i] = (widget){
            .name = "widget",
            .quantity = i
        };
    }


    // At some point, in this function or in an upper one
    // in the call stack, we must release the memory.
    free(w_arr);
    free(w);
}

/*
 * The realloc function increases or decreases the size of previously allocated storage.
 * It takes a pointer to some memory allocated by an earlier call to aligned_alloc,
 * malloc, calloc, or realloc (or a null pointer) and the new desired size. You can
 * use the realloc function to grow or (less commonly) shrink the size of an array.
 *
 * The realloc function typically calls the malloc function to allocate new storage,
 * and then copies the contents of the old storage to the new storage up to the
 * minimum of the old and new sizes. If the newly allocated storage is larger than
 * the old contents, realloc leaves the additional storage uninitialized. If realloc
 * succeeds in allocating the new object, it calls free to deallocate the old object.
 * If the allocation fails, the realloc function retains the old object data at the
 * same address and returns a null pointer, but DOESN'T DEALLOCATE the old pointer.
 * In this case we must handle the error and deallocate the memory using
 * the old pointer.
 */

void realloc_func(void) {
    // Allocate space to contain a widget struct,
    // note that it works as malloc if the passed
    // pointer is null.
    widget *w = realloc(NULL, sizeof(widget));
    if (w == NULL) {
        return;
    }
    strcpy(w->name, "John");
    w->quantity = 10;

    // Expand the previous allocated memory from one
    // element to ten elements.
    widget *w_al = w;
    w = realloc(w, 10 * sizeof(widget));
    if (w == NULL) {
        // If realloc fails we should free
        // the old pointer, and we saved
        // the alias for this.
        free(w_al);
        return;
    }
    // From here, the value of the old pointer (w_al)
    // is invalid since that memory was freed.
    for (int i = 0; i < 10; i++) {
        w[i] = (widget){
            .name = "widget",
            .quantity = i
        };
    }


    // At some point, in this function or in an upper one
    // in the call stack, we must release the memory.
    free(w_al);
}

/*
 * You should deallocate dynamically allocated memory when it’s no longer needed by
 * calling the free function. Deallocating memory is important because it allows
 * that memory to be reused, reducing the chances that you’ll exhaust the available
 * memory, and often providing more efficient use of the heap.
 *
 * If we call free with a null-pointer argument, nothing happens, and the free
 * function simply returns. If you call the free function on the same pointer
 * more than once, undefined behavior occurs. These defects can result in a
 * security flaw known as a double-free vulnerability. Another common error is
 * to access memory that has already been freed (dangling pointers).
 *
 * ---> To limit the opportunity for defects involving dangling pointers, set the
 * ---> pointer to NULL after completing a call to free.
 *
 * Any future attempt to dereference the pointer will usually result in a crash
 * (increasing the likelihood that the error is detected during implementation
 * and testing).
 */


void free_func(void) {
    widget *w = malloc(sizeof(widget));
    if (w == NULL) {
        return;
    }

    // Release resources and set w to NULL
    // to avoid double frees and writing
    // to freed memory.
    free(w);
    w = NULL;
}

// Interesting utility.
void safe_free(void **ptr) {
    free(*ptr);
    *ptr = NULL;
}

/*
 * Flexible array members let you declare and allocate storage for a structure with
 * any number of fixed members, where the last member is an array of unknown size.
 * Starting with C99, the last member of a struct with more than one member can have
 * incomplete array type, which means that the array has an unknown size.
 *
 * When computing the size of a struct containing a flexible array member using the
 * sizeof operator, the flexible array member is ignored. Therefore, we must
 * explicitly include an appropriate size for the flexible array member when
 * allocating storage.
 */

typedef struct {
    int num;
    int data[]; // <- no fixed length
} tool;

void flexible_array_members(int array_size) {
    tool *p = (tool *)malloc(sizeof(tool) + sizeof(int) * array_size);
    if (p == NULL) {
        return;
    }
    p->num = array_size;
    for (int i = 0; i < p->num; ++i) {
        p->data[i] = 17;
    }
}

/*
 * Variable-length arrays (VLAs), introduced in C99, are arrays that you can declare
 * by using a variable to specify the array dimensions, allowing you to specify
 * their size at runtime. VLAs are useful when you don’t know the number of elements
 * in the array until runtime. All VLA declarations must be at either block scope
 * or function prototype scope.
 *
 * The array is allocated in the stack frame and freed when the current frame exits,
 * similar to the alloca function (a dynamic allocated memory handled in the stack).
 * The main advantage of using VLAs instead of the alloca function is that the syntax
 * matches the programmer’s model of how arrays with automatic storage duration work
 * —that is, there’s no need to explicitly free the storage.
 *
 * VLAs share some of the problems of the alloca function, in that they can attempt
 * to make allocations that exceed the bounds of the stack. Unfortunately, there’s no
 * portable way to determine the remaining stack space to detect such an error.
 * You should determine whether you have sufficient stack space in the worst-case
 * scenario (maximum-sized allocations with deep recursions). Finally, another
 * interesting and possibly unexpected behavior occurs when calling sizeof on a VLA.
 * The compiler usually performs the sizeof operation at compile time. However, if
 * the expression changes the size of the array, it will be evaluated at runtime
 * including side effects.
 */

void variable_length_arrays(unsigned int size) {
    int vla[size];
    for (int i = 0; i < size; i++) {
        vla[i] = 13;
    }
}

/*
 * Remember that, when used in an expression, an array is converted to a pointer to
 * the first element of the array. This means that we must add an explicit parameter
 * to specify the size of the array usually. When declaring a function to take a VLA
 * as an argument that specifies a size, we must declare the size of the array before
 * referencing the size in the array declaration. No storage is allocated by either
 * the function declaration or the function definition.
 */

void vla_in_parameters(unsigned int size, char vla[size], char c) {
    for (int i = 0; i < size; i++) {
        vla[i] = c;
    }
}

int vla_matrix_sum(size_t rows, size_t cols, int m[rows][cols]) {
    int total = 0;
    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < cols; c++) total += m[r][c];
    }
    return total;
}