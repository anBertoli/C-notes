#include <stddef.h>
#include <stdio.h>
#include <limits.h>
#include <stdalign.h>

/*
 * You can use the sizeof operator to find the size in bytes of its operand;
 * specifically, it returns an unsigned long integer of size_t type that
 * represents the size. The size_t type is defined in <stddef.h>. You can
 * pass the sizeof operator an unevaluated expression of a complete object
 * type or a parenthesized name of such a type. If you need to determine the
 * number of bits of storage available, you can multiply the size of an
 * object by CHAR_BIT, which gives the number of bits contained in a byte.
 *
 * Object types other than character types can include padding as well
 * as value representation bits.
 */

void size_of_operator(void) {
    int i = 654;
    size_t i_size = sizeof i;      // the size of the object i
    size_t int_size = sizeof(int); // the size of the type int
    printf("%lu %lu\n", i_size, int_size); // -> 4 4

    size_t i_size_bits = sizeof(i) * CHAR_BIT;
    size_t int_size_bits = sizeof(int) * CHAR_BIT;
    printf("%lu %lu\n", i_size_bits, int_size_bits); // -> 32 32
}

/*
 * Casts (also known as type casts) explicitly convert a value of one type to
 * a value of another type. To perform a cast, we precede an expression by a
 * parenthesized type name, which converts the value of the expression to the
 * unqualified version of the named type. Casts are extremely powerful and
 * must be used carefully.
 *
 * Casts may reinterpret the existing bits as a value of the specified type
 * without changing the bits, or they may also change these bits into whatever
 * bits are needed to represent the original value in the resulting type.
 */

void cast_operator(int a) {
    // Doesn't change bits.
    int *some_pointer = &a;
    intptr_t i = (intptr_t)some_pointer;

    // Change bits.
    float f = 34.34;
    int j = (int)f;
}

/*
 * The _Alignof operator yields an integer constant representing the alignment
 * requirement of its operand’s declared complete object type. It does not
 * evaluate the operand. When applied to an array type, it returns the alignment
 * requirement of the element type.
 */

void alignof_operator(void) {
    int arr[4];
    long int arr2[4];
    printf("Alignment of arr = %zu\n", alignof(arr));
    printf("Alignment of arr2 = %zu\n", alignof(arr2));
    printf("Alignment of long long int = %zu\n", alignof(long long int));
    printf("Alignment of char = %zu\n", alignof(char));
    printf("Alignment of int = %zu\n", alignof(int));
    printf("Alignment of struct {int c; char v} = %zu\n", alignof(struct {
        int c;
        char v;
    }));
    printf("Alignment of struct {char v; int c} = %zu\n", alignof(struct {
        char v;
        int c;
    }));
}

/*
 * It’s possible to use the additive operators (addition and subtraction) on
 * either arithmetic values or object pointers. Adding or subtracting an
 * expression that has integer type to or from a pointer returns a value with
 * the type of the pointer operand.
 *
 * If the pointer operand points to an element of an array, then the result
 * points to an element offset from the original element. If the resulting
 * pointer is outside the bounds of the array, undefined behavior occurs.
 *
 * When we subtract one pointer from another, both must point to elements
 * of the same array object or the too-far element. The type of the result
 * is ptrdiff_t (a signed integer type).
 *
 * ---> Pointer arithmetic is automatically scaled to work with array
 * ---> element sizes, rather than individual bytes.
 */

void pointer_arithmetics(void) {
    int arr[10];
    for (int i = 0; i < 10; i++) {
        arr[i] = i * 2;
        printf("%p --> %d\n", &arr[i], arr[i]);
    };

    int *arr_ptr_1 = &arr[4];
    int *arr_ptr_2 = arr_ptr_1 + 2;      // arr_ptr_2 points to arr[6]

    printf("ptr_1 = %p, ptr_2 = %p\n", arr_ptr_1, arr_ptr_2);
    printf("*ptr_1 = %d, *ptr_2 = %d\n", *arr_ptr_1, *arr_ptr_2);
    printf("diff: %td\n", arr_ptr_2 - arr_ptr_1);

    /* OUTPUT
     * 0x7ffee3d55a60 --> 0
     * 0x7ffee3d55a64 --> 2
     * 0x7ffee3d55a68 --> 4
     * 0x7ffee3d55a6c --> 6
     * 0x7ffee3d55a70 --> 8
     * 0x7ffee3d55a74 --> 10
     * 0x7ffee3d55a78 --> 12
     * 0x7ffee3d55a7c --> 14
     * 0x7ffee3d55a80 --> 16
     * 0x7ffee3d55a84 --> 18
     *
     * ptr_1 = 0x7ffee3d55a70, ptr_2 = 0x7ffee3d55a78
     * *ptr_1 = 8, *ptr_2 = 12
     * diff: 2
     */
}