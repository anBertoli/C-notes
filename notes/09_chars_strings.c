#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void print_bits(void *ptr, int len_bytes);

// CHARS TODO

void string_type(void) {
    // char string literal type
    print_bits("ABC", sizeof("ABC"));
    // 01000001 01000010 01000011 00000000

    // wchar_t string literal type with L prefix
    print_bits(L"ABC", sizeof(L"ABC"));
    // 01000001 00000000 00000000 00000000
    // 01000010 00000000 00000000 00000000
    // 01000011 00000000 00000000 00000000
    // 00000000 00000000 00000000 00000000

    // UTF-8 string literal type
    print_bits(u8"ABC", sizeof(u8"ABC"));
    // 01000001 01000010 01000011 00000000

    // char16_t string literal type
    print_bits(u"ABC", sizeof(u"ABC"));
    // 01000001 00000000 01000010 00000000
    // 01000011 00000000 00000000 00000000

    // char32_t string literal type
    print_bits(U"ABC", sizeof(U"ABC"));
    // 01000001 00000000 00000000 00000000
    // 01000010 00000000 00000000 00000000
    // 01000011 00000000 00000000 00000000
    // 00000000 00000000 00000000 00000000

    // 11110000 10011111 10001101 10001100
    printf("\n");
    print_bits("🍌", sizeof("🍌"));
    print_bits(L"🍌", sizeof(L"🍌"));
    print_bits(u8"🍌", sizeof(u8"🍌"));
    print_bits(u"🍌", sizeof(u"🍌"));
    print_bits(U"🍌", sizeof(U"🍌"));
}



// Utility
void print_bits(void *ptr, int len_bytes) {

    for (int i = 0; i < len_bytes; i++) {
        unsigned char byte = *(unsigned char *)(ptr + i);
        for (int j = 7; j >= 0; j--) {
            unsigned char buf = byte & ((unsigned char)1 << j);
            printf("%c", buf == 0 ? '0' : '1');
        }
        printf(" ");
    }
    printf("\n");
}






