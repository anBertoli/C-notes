#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// TODO: understand something
//////////////////////////// CHARS ////////////////////////////
/*
C offers the unadorned char type to represent narrow characters (those 
that can be represented in as few as 8 bits), and the wchar_t type to 
represent wide characters (those that may require more than 8 bits).

As we have already seen, char is an integer type, but each implementation
defines whether it is signed or unsigned—meaning that in portable code,
you cannot assume either. The char type can be safely used to represent 
7-bit character encodings, such as US-ASCII. Upper byte is always 0.

The char type can also be used to represent 8-bit character encodings
such as Extended ASCII, ISO/IEC 8859, EBCDIC, and UTF-8. These 8-bit
character encodings can be problematic on implementations that define
char as an 8-bit signed type.

Example:
*/
void x(void) {
    // char c = 'ÿ'; 
    char c = 'c'; 
    // 'ÿ' is an extended character = in ISO/IEC 8859-1 this value is 255
    // if the C implementation has signed chars, this will overflow to -1
    // so c == EOF (note: in the current IDE the encoding is UTF-8 so the
    // value is not 255)
    if (c == EOF) {
        puts("end of file");
    }
}

void testUTF(void) {
    char *s = "\u00A3";
    printf("%s\n", s);
    printf("len %lu\n", sizeof(s)); // for me 8 bytes
}


/*
The wchar_t type is an integer type added to C to process the characters of a
large character set. It can be a signed or unsigned integer type, depending
on the implementation, and has an implementation-defined inclusive range
of WCHAR_MIN to WCHAR_MAX.

C11 introduced the 16- and 32-bit character data types char16_t and char32_t, 
declared in <uchar.h>, to provide data types for UTF-16 and UTF-32 encodings, 
respectively. Without library functions, these types have limited usefulness.

C allows you to specify character constants, also known as character literals,
which are sequences of one or more characters enclosed in single quotes,
such as 'd'.

Types of Charachter Constants
==============================
Prefix      Type
===============================
None        int
L'a'        The unsigned type corresponding to wchar_t
u'a'        char16_t
U'a'        char32_t
*/

void s1(void) {
    char a = 'a';
    char nl = '\n';
}


// TODO: understand something
//////////////////////////// STRINGs ////////////////////////////
/*
C doesn’t support a primitive string type and probably never will. Instead,
it implements strings as arrays of characters. C has two types of strings: nar-
row and wide.

A narrow string has the type array of char. It consists of a contigu-
ous sequence of characters that include a terminating null character. A
pointer to a string points to its initial character. The size of a string is the
number of bytes allocated to the backing array storage. The length of a
string is the number of code units (bytes) preceding the first null char-
acter.

The following string the size of the string is 7, and the length of the string
is 5. Elements of the backing array beyond the last element must not be
accessed. Elements of the array that haven’t been initialized must not
be read.

0 1 2 3 4 5  6 7
h e l l o \0 ? ?
================ size 7
=========        length 5


A wide string has the type array of wchar_t. It’s a contiguous sequence of
wide characters that include a terminating null wide character. A pointer
to a wide string points to its initial wide character. The length of a wide
string is the number of code units preceding the first null wide character.
*/



////////// STRING LITERALS
/*
A character string literal is a string constant represented by a sequence of zero
or more multibyte characters enclosed in double quotes; for example, "ABC".

You can use various prefixes to declare string literals of different character
types:
• char string literal type, such as "ABC"
• wchar_t string literal type with L prefix, such as L"ABC"
• UTF-8 string literal type with u8 prefix, such as u8"ABC"
• char16_t string literal type with u prefix, such as u"ABC"
• char32_t string literal type with U prefix, such as U"ABC"

A string literal has a non-const array type. Modifying a string literal is
undefined behavior and prohibited.
*/

void strTest(void) {
    char c1[4] = "ABC"; // 3 for chars + null terminator
    char c2[] = "ABC"; // same but automatic
    wchar_t *ct = L"ABC";
    char uc[3] = u8"ABC"; 
}



//////////////////// STRING FUNC UTILITIES
/*
Narrow string-handling functions are defined in the <string.h> header file, 
and wide string-handling functions in <wchar.h>.

As mentioned earlier in this chapter, strings have both a size (which is the
number of bytes allocated to the backing array storage) and a length. You
can determine the size of a statically allocated backing array at compile
time by using the sizeof operator.
*/

void ex3(void) {
    char str[100] = "Here comes the sun";
    size_t str_size = sizeof(str); // str_size is 100
    printf("%lu\n", str_size);
}

void ex35(void) {
    char *str = "Hello";
    size_t str_len = strlen(str);
    printf("str_len 1: %lu\n", str_len);
    printf("%s\n", str);

    for (int i = 0;; i++) {
        if (!str[i]) {
            break;
        }
        printf("byte: %c\n", str[i]);
    }

    char *str2 = u8"Hello 円!";
    size_t str_len2 = strlen(str2);
    printf("str_len 2: %lu\n", str_len2);
    printf("%s\n", str2);

    for (int i = 0;; i++) {
        if (!str2[i]) {
            break;
        }
        printf("byte: %c\n", str2[i]);
    }
}

/* STRLEN
You can compute the length of a string by using the strlen function.
The strlen function has no way of knowing the size of the object refer-
enced by str. If you call strlen with an invalid string that lacks a null char-
acter before the bound, the function will access the array beyond its end,
resulting in undefined behavior. Passing a null pointer to strlen will also
result in undefined behavior (a null-pointer dereference).
*/

void ex4(void) {
    char str[100] = "Here comes the sun";
    size_t str_len = strlen(str); // str_len is 18
    printf("%lu\n", str_len);
}

/* STRCPY
strcpy function to make a copy of str by determining the length and then adding
1 to accommodate the terminating null character. A proper null termination must
be present at the source.
*/

void ex5(void) {
    char str1[] = "Here comes the sun";
    char *str2 = malloc(strlen(str1) + 1);
    strcpy(str2, str1);
    printf("%s\n", str2);
}

/*
The strcpy_s function copies characters from a source string to a destination 
character array up to and including the terminating null character. Here’s the
strcpy_s signature:

errno_t strcpy_s(
    char *restrict s1, rsize_t s1max, const char * restrict s2
);

The strcpy_s function succeeds only when it can fully copy the source string to
the destination without overflowing the destination buffer.
*/

/* MEMCPY
The memcpy function copies a specified number of characters, size, from the
object referenced by src into the object referenced by dest. The best advice 
is to use strcpy when copying a string, and memcpy when copying only raw, 
untyped memory.

void *memcpy(void * restrict dest, const void * restrict src, size_t size);
*/


/* GETS, GETS_S & PUTS
The gets function is a flawed input function that accepts input without
providing any way to specify the size of the destination array. For that rea-
son, it cannot prevent buffer overflows. As a result, the gets function was
deprecated in C99 and eliminated from C11.

You should never use this function, and you should replace any use of the gets
function you find in any code you are maintaining.
*/

// BAD CODE
bool get_y_or_n(void) {
    char response[8];
    puts("Continue? [y] n: ");
    gets(response); // will fill response[8] but continues beyond the end
    if (response[0] == 'n') {
        return false;
    }
    return true;
}

/*
gets_s vs gets: the two functions are similar, except that the gets_s
function checks the array bounds.
*/ 

bool get_y_or_n2(void) {
    char response[8];
    size_t len = sizeof(response);
    puts("Continue? [y] n: ");
    // gets_s(response, len);       TODO: what's the header for this??
    return !(response[0] == 'n');
}