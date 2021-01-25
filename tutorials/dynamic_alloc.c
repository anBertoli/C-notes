#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
Every object has a storage duration that determines its lifetime, and 
that C defines four storage durations: static, thread, automatic, and
allocated.

The dynamically allocated memory (or simply allocated memory) is allocated
from the heap at runtime. Dynamically allocated memory is useful when the
exact storage requirements for a program are unknown before runtime.
*/

/* AUTOMATIC
Objects of automatic storage duration are declared within a block or as
a function parameter. The lifetime of these objects begins when the block
in which they’re declared begins execution, and ends when execution of the
block ends. If the block is entered recursively, a new object is created each
time, each with its own storage.
*/

/* STATIC
Objects declared in the file scope have static storage duration. The
lifetime of these objects is the entire execution of the program, and their
stored value is initialized prior to program startup. You can also declare a
variable within a block scope to have static storage duration by using the
storage-class specifier static.
*/

/* ALLOCATED
Dynamically allocated memory has allocated storage duration. The lifetime
of an allocated object extends from the allocation until the deallocation.
Dynamically allocated memory is allocated from the heap, which is simply
one or more large, subdividable blocks of memory that are managed by the
memory manager.

Memory managers are libraries that manage the heap for you by pro-
viding implementations of the standard memory management functions
described in the following sections.

Memory managers manage unallocated and deallocated memory only.
Once memory has been allocated, the caller manages the memory until it’s
returned. It’s the caller’s responsibility to ensure that the memory is deal-
located, although most implementations will reclaim dynamically allocated
memory when the program terminates.

NB: memory allocated for the client process and memory allocated for internal
use within the memory manager is all within the addressable memory space of 
the client process.

Dynamically allocated memory is used when the exact storage requirements
for a program are unknown before runtime. Dynamically allocated mem-
ory is less efficient than statically allocated memory, because the memory
manager needs to find appropriately sized blocks of memory in the runtime
heap, and then the caller must explicitly free those blocks when no longer
needed, all of which requires additional processing. By default, you should
declare objects with either automatic or static storage duration for objects
whose sizes are known at compilation time.

*/


///////////////////// MEMORY MANAGEMENT FUNCTIONS /////////////////////
/*
The C Standard Library defines memory management functions for allo-
cating and deallocating dynamic memory. These functions include malloc,
aligned_alloc, calloc, and realloc. You can call the free function to deal-
locate memory.
*/

///////////////////// MALLOC /////////////////////
/* 
The malloc function allocates space for an object of a specified size whose
initial value is indeterminate.

All memory allocation functions accept an argument of type size_t
that specifies the number of bytes of memory to be allocated. For por-
tability, we use the sizeof operator when calculating the size of objects, as
the size of objects of various types, such as int and long, may differ among
implementations.

The malloc function returns either a null pointer to indicate an error,
or a pointer to the allocated space. Therefore, we check whether malloc
returns a null pointer and appropriately handle the error.
*/ 

typedef struct {
    char c[10];
    int i;
    double d;
} widget;

void mallocEx(void) {
    widget *p = malloc(sizeof(widget)); // implicit conversion from void* to widget*
    if (p == NULL) {
        // handle allocation error
        printf("cannot allocate memory for p\n");
        return;
    }
    // memory succesfully allocated
    p->i = 24;
    p->d = 300;
    strcpy(p->c, "ciao");
    printf("p: %p\n", p);
    printf("p->c = %s\n", p->c);
    printf("p->i = %d\n", p->i);
    printf("p->d = %lf\n", p->d);
    free(p);
}


/*
*/
void mallocNoType(void) {
    void *p = malloc(sizeof(widget));
    if (p == NULL) {
        // handle allocation error
        printf("cannot allocate memory for p\n");
        return;
    }
    // memory succesfully allocated
    widget w = {
        .c = "abc", 
        .i = 9, 
        .d = 3.2
    };
    // copy memory directly without 
    // using the struct type "facility" 
    memcpy(p, &w, sizeof(widget)); // w is coerced to void * pointers
    printf("p->i = %d\n", ((widget*)p)->i);
}

/*
The contents of memory returned from malloc are uninitialized, which
means it contains indeterminate values. Reading uninitialized memory is
never a good idea, and you should think of it as undefined behavior.

The malloc function does not initialize the returned memory, because
the expectation is that you will overwrite this memory anyway. The following
program could have been this error, if str[15] = '\0'; was not added assuming
zero-valued allocatd memory by default.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strAlloc(void) {
    char *str = (char *)malloc(16);
    if (str) {
        strncpy(str, "123456789abcdef", 15);
        str[15] = '\0'; // without this -> last byte is random -> printf goes ahead (undefined) 
        printf("str = %s.\n", str);
        free(str);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}


///////////////////// CALLOC /////////////////////
/*
// void *calloc(size_t nmemb, size_t size);

The calloc function allocates storage for an array of nmemb objects, each of
whose size is size bytes. This function initializes the storage to all zero-valued 
bytes. This zero value might not be the same one used to represent floating-point 
zero or null-pointer constants.
*/


///////////////////// REALLOC /////////////////////
/*
The realloc function increases or decreases the size of previously allocated
storage. It takes a pointer to some memory allocated by an earlier call to
aligned_alloc, malloc, calloc, or realloc (or a null pointer) and a size, and has
the following signature:

void *realloc(void *ptr, size_t size);

You can use the realloc function to grow or (less commonly) shrink the
size of an array. 

IMPORTANT
If the newly allocated storage is larger than the old contents, realloc leaves 
the additional storage uninitialized. If realloc succeeds in allocating the new 
object, it calls free to deallocate the old object. If the allocation fails, the
realloc function retains the old object data at the same address and returns a 
null pointer.

This code also includes a test for a zero-byte allocation. You should
avoid passing the realloc function a value of 0 as the size argument, as
this is effectively undefined behavior (and is actually undefined behavior
in C2x).

NOTE
Calling realloc with a null pointer is equivalent to calling malloc.
*/

void *resizeExample(size_t size) {
    if (size == 0) {
        return NULL;
    }
    void *p1 = malloc(100); // alloc 100 bytes
    void *p2; 
    p2 = realloc(p1, size);
    if (p2 == NULL) {
        // realloc failed, p still valid
        return NULL;
    }
    // realloc successeded, 
    // p isn't valid anymore
    return p2;
}

void* growArrayTo(void* ptrArray, size_t size) {
    if (size == 0) return NULL;
    void *ptr = realloc(ptrArray, size);
    if (ptr == NULL) {
        return NULL;
    }
    return ptr;
}

void growString(void) {
    char *str = malloc(sizeof(char[10])); // or calloc
    strcpy(str, "Hello world!");
    char *p = realloc(str, 20);
    if (p == NULL) {
        printf("error\n");
        return;
    }
    printf("success\n");
    // print values in memory
    for (int i = 0; i < 20; i++) {
        printf("Char at %p \t%d\t'%c'\n", p + i, p[i], p[i]);
    }
    for (int i = 0; i < 20; i++) {
        printf("Char at %p \t%d\t'%c'\n", p + i, p[i], p[i]);
    }
    printf("\n");
}



///////////////////// FREE /////////////////////
/*
You should deallocate dynamically allocated memory when it’s no longer
needed by calling the free function. Deallocating memory is important
because it allows that memory to be reused, reducing the chances that
you’ll exhaust the available memory, and often providing more efficient
use of the heap.
We deallocate memory by passing a pointer to that memory to the free
function, which has the following signature:

void free(void *ptr);

The ptr value must have been returned by a previous call to aligned_alloc,
malloc, calloc, or realloc.
*/



/* DANGLING POINTERS
If you call the free function on the same pointer more than once, undefined
behavior occurs. These defects can result in a security flaw known as
a double-free vulnerability.

Another common error is to access memory that has already been
freed. This type of error frequently goes undiagnosed, because the code
might appear to work, but fails in unexpected ways away from the actual
error.

We refer to pointers to already freed memory as dangling pointers.

To limit the opportunity for defects involving dangling pointers, set the
pointer to NULL after completing a call to free.
*/

///////////////////// FLEXIBLE ARRAY MEMBERS ////////////////////
/*
Flexible array members let you declare and allocate storage for a struc-
ture with any number of fixed members, where the last member is an array of

unknown size. Starting with C99, the last member of a struct with more than
one member can have incomplete array type, which means that the array has an
unknown size.

Example:
*/

typedef struct {
    size_t num;
    int data[];
} widget2;

void *func(size_t array_size) {
    widget2 *p = (widget2 *)malloc(sizeof(widget2) + sizeof(int) * array_size);
    if (p == NULL) {
        return NULL;
    }
    p->num = array_size;
    for (size_t i = 0; i < p->num; ++i) {
        p->data[i] = 17;
    }
    return p;
}

/*
When computing the size of a struct containing a flex-
ible array member using the sizeof operator, the flexible array member is
ignored. Therefore, we must explicitly include an appropriate size for the
flexible array member when allocating storage.
*/




///////////////////// VARIABLE-LENGTH ARRAYS (VLAs) /////////////////////
/*
Variable-length arrays (VLAs), introduced in C99, are arrays that you can
declare by using a variable to specify the array dimensions, allowing you
to specify their size at runtime. The size of the array cannot be modified
after you create it. VLAs are useful when you don’t know the number of
elements in the array until runtime.
*/

void func2(size_t size) {
    int vla[size]; // dimension known only at runtime
    
    // ---snip---
}

/*
You can also declare VLAs as function parameters. Remember from
Chapter 2 that, when used in an expression, an array is converted to a
pointer to the first element of the array. This means that we must add
an explicit parameter to specify the size of the array.
*/

void *func3(void *s, int c, size_t n);

/*
When declaring a function to take a VLA as an argument that specifies
a size, we must declare the size of the array before referencing the size in
the array declaration.
*/

void *func4(size_t n, char s[n], int c);