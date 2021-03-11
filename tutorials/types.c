#include <stdbool.h>
#include <stdio.h>

////////////////////////////////// BOOLEAN TYPE //////////////////////////////////
// to use bool: #include <stdbool.h>
bool isDivisibleBy(int a, int b) {
    if (!b) { return false; }
    if (!(a % b)) {
        return true;
    }
    return false;
}

////////////////////////////////// CHAR TYPE //////////////////////////////////
// they are numbers at the end
void chars(void) {
    char a = 'a';
    signed char b = 110;
    unsigned char c = 111;
    printf("%c %d\n", a, a);
    printf("%c %d\n", b, b);
    printf("%c %d\n", c, c);
}

////////////////////////////////// INT TYPE //////////////////////////////////
// they are integer numbers, the word 'int' can be omitted if itsn't the only one they 
// are signed by default if not specified, excluding char which is implementation dependent
// overflow is well defined and it "wraps around"
// #include <limits.h> has limits for each of these types
void integer(void) {
    short int a = 1;
    int b = 1;
    long int c = 1;
    long long int d = 1;

    unsigned short int aa = 1;
    unsigned int bb = 1;
    unsigned long int cc = 1;
    unsigned long long int dd = 2;

    // #include <stdint.h> has platform indepenendent int types
    u_int16_t aaa = 1;
    u_int64_t bbb = 1;

    int32_t ccc = 1;
    int64_t ddd = 1;

    int dec = 10;
    int oct = 013;
    int hex = 0xA; 
}

/* UNSIGNED INTs REPRESENTATION
Decimal     Binary      Hexadecimal
0           0000 0000   0x00
1           0000 0001   0x01
17          0001 0001   0x11
255         1111 1111   0xFF
*/


/* SIGNED INTs REPRESENTATION
Range from –2^(N–1) to 2^(N–1)–1, usually two complements (but not always).
For example, that an 8-bit value of type signed char has a range of –128 to 127.

The two’s complement representation for negative signed values includes a sign
bit and other value bits. The sign bit is given the weight –(2N – 1). To negate 
a value in two’s-complement representation, simply toggle each non-padding bit 
and then add 1.

Signed integer overflow is undefined behavior in C, allowing implementations to
silently wrap (the most common behavior), trap, or both.

Binary      Decimal     Weighting   
00000000    0           0
00000001    1           20
01111110    126         2^6+2^5+2^4+2^3+2^2+2^1
01111111    127         2^(N−1)− 1 
10000000    −128        −(2^(N−1)) + 0 
10000001    −127        −(2^(N−1)) + 1
11111110    −2          −(2^(N−1)) + 126
11111111    −1          −(2^(N−1)) + 127
*/

////////////////////////////////// FLOATING POINT TYPE //////////////////////////////////
// they are fractional numbers

// default types: double, float if F at the end, long double if L at the end
void floatNums(void) {
    float a = 1.0;
    double b = 2.0;
    long double c = 3.0;
}

/*
SIGN, EXPONENT, AND SIGNIFICAND

As with integers, the sign bit represents whether the number is positive or nega-
tive: 0 denotes a positive number, and 1 denotes a negative number.

The exponent field needs to represent both positive and negative expo-
nents. To avoid storing the exponent as a signed number, a bias is implicitly
added to the actual exponent to get the stored exponent. For the float type,
the bias is 127. Consequently, to express an exponent of 0, we would store
127 in the exponent field. A stored value of 200 indicates an exponent of
200 – 127, or 73. Exponents of –127 (where every exponent bit is 0) and +128
(where every exponent bit is 1) are reserved for special numbers. Similarly, the
bias for double-precision numbers is 1023. This means that the value stored
will range from 0 to 255 for a float, and 0 to 2047 for a double.

The significand bits represent the precision bits of the number. For example,
if you were to represent the value 1.0100110 × 24 as a floating-point value, the
significand refers to the precision bits 1.0100110, and the exponent refers to the
power of 2, which is 4 in this example (Hollasch 2019).


Floating-point numbers are bounded in magnitude and have finite precision.

Floating-point types cannot represent all real numbers exactly, even
when they can be represented in a small number of decimal digits. For
example, common decimal constants such as 0.1 can’t be represented
exactly as binary floating-point numbers.
*/

////////////////////////////////// ENUMS types //////////////////////////////////
enum day { sun, mon, tue, wed, thu, fri, sat };
enum cardinal_points { north = 0, east = 90, south = 180, west = 270 };
enum months { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };