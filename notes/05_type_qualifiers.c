#include <stdio.h>

/*
 * Types can be qualified by using one or more of the following qualifiers:
 * const, volatile, and restrict. Each of these qualifiers changes behaviors
 * when accessing objects of the qualified type. The qualified and unqualified
 * versions of types can be used interchangeably as arguments to functions,
 * return values from functions, and members of unions.
 */

/*
 * Objects declared with the const qualifier (const-qualified types) are not
 * modifiable. In particular, they’re not assignable but can have constant
 * initializers. This means objects with const-qualified types can be placed
 * in read-only memory by the compiler, and any attempt to write to them will
 * result in a runtime error.
 */

// Const keyword can be used in return types,
// parameters local variables and so on.
const int const_qualifier(const int a) {
    const int b = 3;
    // a = 4;  ---> error

    // The object of const-qualified type sis coerced to a pointer to
    // a non const type, but actually the object is still const.
    // Undefined behaviour arise here.
    const int i = 1;
    int *ip = (int *)&i;
    *ip = 2;  // ---> undefined behavior

    return a + b;
}

/*
 * C allows you to modify an object that is pointed to by a const-qualified pointer
 * by casting the const away, provided that the original object was not declared const.
 */

void const_pointers(void) {
    int i = 12;
    const int j = 12;
    const int *ip = &i;
    const int *jp = &j;
    *(int *)ip = 42; // ok
    *(int *)jp = 42; // undefined behavior
}

/*
 * Objects of volatile-qualified types serve a special purpose. Static volatile-qualified
 * objects are used to model memory-mapped input/output (I/O) ports, and static constant
 * volatile-qualified objects model memory-mapped input ports such as a real-time clock.
 *
 * The values stored in these objects may change without the knowledge of the compiler.
 * Using a volatile-qualified type lets the compiler know that the value may change, and
 * ensures that every access to the real-time clock occurs, without the compiler optimizing
 * or caching the value.
 */

void volatile_qualifier(volatile int a) {
    // Here each iteration is done, the val
    // 'a' evaluated and printed.
    for (int i = 0; i < 10; i++) {
        int tmp = a;
        printf("%d read: %d\n",i, tmp);
    }
}

/*
 * A restrict-qualified pointer is used to promote optimization. Objects indirectly accessed
 * through a pointer frequently cannot be fully optimized because of potential aliasing, which
 * occurs when more than one pointer refers to the same object. The 'restrict' keyword applies to
 * pointers.
 *
 * Because both p and q are restrict-qualified pointers, the compiler can assume that an object
 * accessed through one of the pointer parameters is not also accessed through other pointers.
 */

void copy(int n, int * restrict p, int * restrict q) {
    while (n-- > 0) {
        *p++ = *q++;
    }
}