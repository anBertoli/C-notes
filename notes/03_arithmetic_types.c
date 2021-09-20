#include <stdio.h>
#include <limits.h>
#include <math.h>

/*
 * Each integer type represents a finite range of integers. Signed integer
 * types represent values that can be negative, zero, or positive; unsigned
 * integers represent values that can be only zero or positive. The range that
 * each type of integer can represent depends on your implementation. Unless
 * explicitly declared as unsigned, integer types are assumed to be signed,
 * while with char it is implementation dependent by default (we need to
 * specify).
 *
 * The <limits.h> header file provides the minimum and maximum representable
 * values for the various integer types. A representable value is one that can
 * be represented in the number of bits available to an object of a particular
 * type. Values that cannot be represented will be diagnosed by the compiler
 * or converted to a representable but different (incorrect) value.
 */


/*
 * Unsigned integers have ranges that start at 0, and their upper bound is
 * greater than that of the corresponding signed integer type.
*/

void uint_types(void) {
    unsigned int u1 = 1;
    unsigned u2 = 2;            // int can be omitted
    unsigned long u3 = 3;       // int can be omitted
    unsigned long long u4 = 4;  // int can be omitted

    // With chars we must specify
    // if it's signed or unsigned.
    unsigned char u5 = 5;
}

/*
 * They represent values using a pure binary system with no offset: the least
 * significant bit has the weight 20, the next least significant has the weight
 * 21, and so forth. The value of the binary number is the sum of all the weights
 * for the set bits. This maximum value is 2^N – 1, where N is the width.
 * Here's some examples:
 *
 * Decimal     Binary      Hexadecimal
 * 0           0000 0000   0x00
 * 1           0000 0001   0x01
 * 17          0001 0001   0x11
 * 255         1111 1111   0xFF
 *
 */

void print_uint(unsigned int a) {
    printf("num: '%d' ---> ",a );
    for (int i = 31; i >= 0; i--) {
        int buf = a & (1 << i);
        printf("%c", buf == 0 ? '0' : '1');
    }
    printf("\n");
}

void print_uint_representation(void) {
    print_uint(1);
    print_uint(17);
    print_uint(255);
    print_uint(UINT_MAX);
};



/*
 * The limits.h file contains constant values for upper limits of the
 * current implementation. They are typically the ones printed by the
 * following example. Note that the standard ANSI imposes some min-max
 * ranges for both unsigned and signed, but actual implementations
 * usually extend these ranges.
 */

void uint_limits(void) {
    printf("%u\n", UCHAR_MAX);      // --> unsigned char, 255 (8 bits), 255 min from standard (8 bits)
    printf("%u\n", USHRT_MAX);      // --> unsigned short, 65.535 (16 bits), 65.535 min from standard (16 bits)
    printf("%u\n", UINT_MAX);       // --> unsigned int, 4.294.967.295 (32 bits), 65.535 min from standard (16 bits)
    printf("%lu\n", ULONG_MAX);     // --> unsigned long, 18.446.744.073.709.551.615 (64 bits), 4.294.967.295 min from standard (32 bits)
    printf("%llu\n", ULLONG_MAX);   // --> unsigned long long, 18.446.744.073.709.551.615 (64 bits), 18.446.744.073.709.551.615 min from standard (64 bits)
}

/*
 * Wraparound occurs when you perform arithmetic operations that result
 * in values too small (less than 0) or too large (greater than 2^N – 1)
 * to be represented as a particular unsigned integer type. In this case,
 * the value is reduced modulo the number that is one greater than the
 * largest value that can be represented in the resulting type. To avoid
 * unplanned behavior (such as having your airplane fall from the sky),
 * it’s important to check for wraparound by using the limits from <limits.h>
 */

void uint_wraparound(int a, int b, int j, int i) {
    // Perform checks to control the wraparound behavior,
    // both with the upper and the lower limit (0).
    int sum;
    if (a > UINT_MAX - b)
        printf("too big");
    else
        sum = b + a;

    int diff;
    if (j > i)
        printf("negative");
    else
        diff = i - j;
}


/*
 * Each unsigned integer type has a corresponding signed integer type that
 * occupies the same amount of storage. The two’s complement is the system
 * usually used in most implementations. With this system the sign bit is
 * given the weight −(2^n − 1), and the other value bits have the same
 * weights as for unsigned.
 *
 * Signed integer types with a width of N can represent any integer value
 * in the range of –2^n – 1 to 2^(n–1) – 1.
 *
 * binary       decimal     weighting
 * 01111110     126         2^6 + 2^5 + 2^4 + 2^3 + 2^2 + 2^1
 * 10000000     −128        −(2^n − 1) + 0
 * 11111110     −2          −(2^n − 1) + 126
 *
 * The limits.h file contains constant values for upper limits of the
 * current implementation. They are typically the ones printed by the
 * following example.
 */

void int_types(void) {
    signed char a = 1;
    signed short b = 2;
    signed int c = 3;
    signed long d = 4;
    signed long long e = 5;
}

void int_limits(void) {
    printf("%d\n", SCHAR_MIN);      // --> signed char, –128 (8 bits), –127 min from standard (8 bits)
    printf("%d\n", SCHAR_MAX);      // --> signed char, 127 (8 bits), 127 min from standard (8 bits)

    printf("%d\n", SHRT_MIN);       // --> signed short int, -32768 (16 bits), -32767 min from standard (16 bits)
    printf("%d\n", SHRT_MAX);       // --> signed short int, 32767 (16 bits), 32767 min from standard, (16 bits)

    printf("%d\n", INT_MIN);        // --> signed int, -2147483648 (32 bits), -32767 min from standard (16 bits)
    printf("%d\n", INT_MAX);        // --> signed int, 2147483647 (32 bits), 32767 min from standard (16 bits)

    printf("%ld\n", LONG_MIN);      // --> long signed int, -9223372036854775808 (64 bits), -2147483647 min from standard (32 bits)
    printf("%ld\n", LONG_MAX);      // --> long signed int, 9223372036854775807 (64 bits),  2147483647 min from standard (32 bits)

    printf("%lld\n", LLONG_MIN);    // --> long long signed int, -9223372036854775808 (64 bits), -9223372036854775807 min from standard 64 bits
    printf("%lld\n", LLONG_MAX);    // --> long long signed int, 9223372036854775807 (64 bits), 9223372036854775807 min from standard 64 bits
}

/*
 * Overflow occurs when a signed integer operation results in a value
 * that cannot be represented in the resulting type. Signed integer
 * overflow is undefined behavior in C, allowing implementations to
 * silently wrap (the most common behavior), trap, or both. Traps
 * interrupt execution of the program so that no further operations
 * are performed. Common architectures like x86 do a combination of both.
 *
 * Unsigned integers have well-defined wraparound behavior. Signed integer
 * overflow, or the possibility of it, should always be considered a defect.
 */

void int_overflow(void) {
    print_uint(INT_MAX);           // --> num: '2147483647'  ---> 01111111111111111111111111111111
    print_uint(INT_MAX + 1);    // --> num: '-2147483648' ---> 10000000000000000000000000000000
}

/*
 * Integer literals. C has three kinds of integer constants that use
 * different number systems: decimal constants, octal constants, and
 * hexadecimal constants.
 *
 * Decimal constants always begin with a nonzero digit. If a constant
 * starts with a 0, optionally followed by digits 0 through 7, it is
 * an octal constant. You can also create a hexadecimal constant by
 * prefixing a sequence of decimal digits and the letters a (or A)
 * through f (or F) with 0x or 0X.
 */

void int_literals(void) {
    int a = 123;
    int b = 0777;
    int c = 0x4c3;
}


/*
 * Floating-point is the most common representation for real numbers
 * in computers. Floating-point representation is a technique that
 * uses scientific notation to encode numbers with a base number and
 * an exponent. C has three floating-point types: float, double, and
 * long double.
 *
 * - float: 1 sign bit, 8 exponent bits and 23 significand bits
 * - double: 1 sign bit, 11 exponent bits, and 52 significand bits
 * - long double: variable
 *
 * As with integers, the sign bit represents whether the number is positive
 * or negative: 0 denotes a positive number, and 1 denotes a negative number.
 *
 * The exponent field needs to represent both positive and negative exponents.
 * To avoid storing the exponent as a signed number, a bias is implicitly
 * added to the actual exponent to get the stored exponent. For the float
 * type, the bias is 127. Consequently, to express an exponent of 0, we would
 * store 127 in the exponent field. A stored value of 200 indicates an exponent
 * of 200 – 127, or 73. Exponents of –127 (where every exponent bit is 0) and
 * +128 (where every exponent bit is 1) are reserved for special numbers.
 *
 * The significand bits represent the precision bits of the number. For example,
 * if you were to represent the value 1.0100110 × 24 as a floating-point value,
 * the significand refers to the precision bits 1.0100110, and the exponent
 * refers to the power of 2, which is 4 in this example. Since the significand
 * refers to the precision bits, the leading 1 is stripped and must be accounted
 * when performing calculations (significand of 1001 bits = 1.1001).
 *
 * Floating-point types cannot represent all real numbers exactly, even
 * when they can be represented in a small number of decimal digits. For
 * example, common decimal constants such as 0.1 can’t be represented
 * exactly as binary floating-point numbers.
 *
 * Floating-point types can also represent values that are not floating-point
 * numbers, such as negative and positive infinity and not-a-number (NaN) values.
 * Here's some examples.
 *
 * decimal                    approx                sign    exponent (-127)     significand
 * 0                          0                     0       00000000            00000000000000000000000
 * -0                         -0                    1       00000000            00000000000000000000000
 * 0.125                      0.125                 0       01111100            00000000000000000000000
 * 1                          1                     0       01111111            00000000000000000000000
 * 2                          2                     0       10000000            00000000000000000000000  --> 1 * 2^1
 * 4                          4                     0       10000001            00000000000000000000000
 * 8                          8                     0       10000010            00000000000000000000000  --> 1 * 2^3
 * 0.2                        0.20000000298023224   0       01111100            10011001100110011001101
 */

void print_float_bits(const float a) {
    // Cast the float to an int of the same size
    // this will retain the same bits, but will
    // change the interpretation of it.
    unsigned int *b = (unsigned int *)&a;

    for (int i = 31; i >= 0; i--) {
        // Generate a bitmask for the i-th bit (1 << i)
        // and use it against the numeric value to select
        // the i-th bit only.
        int buf = *b & (1 << i);

        // If the selected bit is zero, all bits are zero
        // and buf == 0, else the selected bit is one and
        // buf != 0.
        printf("%c", buf == 0 ? '0' : '1');
    }
    printf("\n");
}

void float_representation(void) {
    print_float_bits(0);
    print_float_bits(0.125);
    print_float_bits(8);
    print_float_bits(0.2);
}


/*
 * Values can be implicitly or explicitly converted from one arithmetic type
 * to another. You can use the cast operator to perform explicit conversions.
 * To perform a cast, place a type name in parentheses just before the
 * expression. The cast converts the expression to the unqualified version
 * of the type name in parentheses.
 *
 * Casting to wider types always works with no loss of precision. When casting
 * to a type with less precision the result of the conversion might not be
 * equal to the original value.
 *
 * There are 3 concepts important that determine if the conversion happens and
 * in which direction: Integer Conversion Rank, Integer Promotions, Usual
 * Arithmetic Conversions. Then depending on the implementation, the conversion
 * is done following specific rules (e.g. uint to int reinterprets the same bits
 * as the new type).
 */

void explicit_cast(void) {
    // No information loss.
    int a = 5;
    long b = (long)a;

    // Potential information loss.
    int c = 14;
    short d = (short)c;
}

/*
 * Implicit conversion, also known as coercion, occurs automatically in
 * expressions as required. This happens, for example, when operations
 * are performed on mixed types.
 *
 * The same rules are applied: Integer Conversion Rank, Integer Promotions,
 * Usual Arithmetic Conversions. The following example demonstrates an
 * implicit conversion. The variable c is of type signed char. Because signed
 * char has a lower integer conversion rank than int or unsigned int, the
 * value stored in c is promoted to an object of type signed int when used
 * in the comparison. This is accomplished by sign-extending the original
 * value of 0xFF to 0xFFFFFFFF.
 *
 * ext, the usual arithmetic conversions are applied. Because the operands to
 * the equal (==) operator have different signedness and equal rank, the
 * operand with the signed integer type is converted to the type of the
 * operand with the unsigned integer type. Because UINT_MAX has the same
 * values as the promoted and converted value of c, the result is true.
 */

void implicit_coercion(void) {
    unsigned int ui = UINT_MAX;
    signed char c = -1;
    if (c == ui) {
        puts("-1 equals 4,294,967,295");
    }
}


