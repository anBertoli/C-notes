#include <stddef.h>
#include <stdio.h>

// SIZEOF operator
/*
You can use the sizeof operator to find the size in bytes of its operand; spe-
cifically, it returns an unsigned integer of size_t type that represents the
size. The size_t type is defined in <stddef.h>

You can pass the sizeof operator an unevaluated expression of a com-
plete object type or a parenthesized name of such a type:
*/


int i;
size_t i_size = sizeof i; // the size of the object i
size_t int_size = sizeof(int); // the size of the type int

struct test {
    int i;
    char a;
};


void printSizes(void) {
    printf("char bytes: %lu\n", sizeof(char));
    printf("int bytes: %lu\n", sizeof(int));
    printf("long int bytes: %lu\n", sizeof(long int));
    printf("long long int bytes: %lu\n", sizeof(long long int));

    printf("int[4] bytes: %lu\n", sizeof(int[4]));
    printf("struct test bytes: %lu\n", sizeof(struct test));
}
