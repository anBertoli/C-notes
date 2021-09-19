#include <stdio.h>
#include <stdbool.h>

/*
 * Objects declared as _Bool can store only the values 0 and 1. This Boolean type
 * was introduced in C99, and starts with an underscore to differentiate it in
 * existing programs that had already declared their own identifiers named
 * bool or boolean.
 *
 * If you include the header <stdbool.h>, you can also spell this type as
 * bool and assign it the values true (which expands to the integer constant 1)
 * and false (which expands to the integer constant 0).
 */

void bool_type(void) {
    bool a = true;
    bool b = false;
}

/*
 * The C language defines three character types: char, signed char, and unsigned
 * char. The char type is commonly used to represent character data in C language
 * programs.
 */

void char_types(void) {
    char a = 'a';
    signed char b = 110;
    unsigned char c = 111;

    printf("'%c' as number: '%d'\n", a, a);
    printf("'%c' as number: '%d'\n", b, b);
    printf("'%c' as number: '%d'\n", c, c);
}

/*
 * Signed integer types can be used to represent negative numbers, positive numbers, and zero.
 * The signed integer types include signed char, short int, int, long int, and long long int.
 * For each signed integer type, there is a corresponding unsigned integer type that uses the
 * same amount of storage: unsigned char, unsigned short int, unsigned int, unsigned long int,
 * and unsigned long long int. The unsigned types can be used to represent only positive numbers
 * and zero.
 *
 * The signed and unsigned integer types are used to represent integers of various sizes. Each
 * platform (current or historical) determines the size for each of these types. You can specify
 * actual width integers by using type definitions from the <stdint.h> or <inttypes.h> headers,
 * like uint32_t.
 */

void integer_types(void) {
    // The 'int' keyword can be omitted
    // if it isn't the only type keyword.
    signed short int a = 1;
    signed int b = 1;
    signed long int c = 1;
    signed long long int d = 1;

    unsigned short int aa = 1;
    unsigned int bb = 1;
    unsigned long int cc = 1;
    unsigned long long int dd = 2;
}

/*
 * The C language supports three floating-point types: float, double, and long double.
 * Floating-point arithmetic is similar to, and often used as a model for, the
 * arithmetic of real numbers
 */

void floating_point_types(void) {
    // The 'float' keyword can be omitted
    // if it isn't the only type keyword.
    float a = 1.0;
    double b = 2.0;
    long double c = 3.0;
}

/*
 * An enumeration, or enum, allows you to define a type that assigns names (enumerators) to
 * integer values in cases with an enumerable set of constant values. If you don’t specify a
 * value to the first enumerator with the = operator, the value of its enumeration constant
 * is 0, and each subsequent enumerator without an = adds 1 to the value of the previous
 * enumeration constant.
 */
enum colors {
    yellow = 0,
    green,
    blu
};

// starting from 0 and adding 1
enum day {
    sun,
    mon,
    tue,
    wed,
    thu,
    fri,
    sat
};

// specific values to each enumerator
enum foods {
    meat = 34,
    salad = 12,
    bread = 76
};

/*
 * The void type is a rather strange type. The keyword void (by itself) means
 * “cannot hold any value.” For example, you can use it to indicate that a
 * function doesn’t return a value, or as the sole parameter of a function to
 * indicate that the function takes no arguments. On the other hand, the
 * derived type void * means that the pointer can reference any object
 */

void void_return(int a) {
    printf("number is: %d\n", a);
}

int void_params(void) {
    return 1;
}

/*
 * Function types are derived types. In this case, the type is derived from the
 * return type and the number and types of its parameters. The return type of a
 * function cannot be an array type.
 *
 * You should never declare functions with an empty parameter list in C. First,
 * this is a deprecated feature of the language that may be removed in the future.
 * Second, the code could be ported to C++, so explicitly list parameter types
 * and use void when there are no parameters
 */

int add_nums(int a, int b) {
    return a + b;
}