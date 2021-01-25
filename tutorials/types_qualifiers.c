#include <stdbool.h>
#include <stdio.h>

/*
Types can be qualified by using one or more of the
following qualifiers: const, volatile, and restrict. 

The _Atomic type qualifier, available since C11, supports concurrent programs.
*/

// CONST
// Objects declared with the const qualifier (const-qualified types) are not modifiable.
void consts(void) {
    const int a = 1;
    // a = 3;  error

    int i = 12;
    const int j = 12;
    const int *ip = &i;
    const int *jp = &j;
    *(int *)ip = 42; // ok
    *(int *)jp = 42; // undefined behavior
}


// VOLATILE
/*
The values stored in these objects may change without the knowledge
of the compiler. For example, every time the value from a real-time clock
is read, it may change, even if the value has not been written to by the
C program. Using a volatile-qualified type lets the compiler know that
the value may change, and ensures that every access to the real-time clock
occurs (otherwise, an access to the real-time clock may be optimized away
or replaced by a previously read and cached value).
*/

// Without the volatile qualification, the compiler would see this as a
// no-op (a programming statement that does nothing) and potentially elimi-
// nate both the read and the write.
void volat(void) {
    volatile int port;
    port = port;
}



// RESTRICT
/*
A restrict-qualified pointer is used to promote optimization. Objects indirectly
accessed through a pointer frequently cannot be fully optimized because of
potential aliasing, which occurs when more than one pointer refers to the
same object. Aliasing can inhibit optimizations, because the compiler can’t
tell if portions of an object can change values when another apparently
unrelated object is modified, for example.
*/

/*
Because both p and q are restrict-qualified pointers, the compiler
can assume that an object accessed through one of the pointer param-
eters is not also accessed through the other.
*/
void copy(unsigned int n, int * restrict p, int * restrict q) {
    while (n-- > 0) {
        *p++ = *q++;
    }
}


