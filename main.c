#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "tutorials/declarations.h"

int main(void) {
    int i = 9;
    if (!i) {
        for (int i = 0; i < 10; i++) {
            printf("Sum of %d and %d is: %d.\n", i, i*2, sum(i, i*2));
            printf("Divison of %d and %d is: %d.\n", 10, i, divide(10, i));
            printf("Is %d divisible by %d? %s.\n", 10, i, isDivisibleBy(10, i) ? "Yes" : "No");
        }
    }
    if (i == 1) {
        for (int i = 0; i < 10; i++) {
            char str[30], rev[30];
            sprintf(str, "this is the attempt %d", i);
            revString(str, rev);
            printf("Reverse of string '%s' is '%s'\n", str, rev);
        }
    }
    if (i == 2) {
        chars();
    }
    if (i == 4) {
        printSizes();
    }
    if (i == 5) {
        mallocEx();
        mallocNoType();
    }
    if (i == 6) {
        growString();
    }
    if (i == 7) {
        ex35();
    }
    if (i == 8) {
        createFileGeneral();
        createFilePosix();
        rwExamples();
        tellSeekExample();
    }
    if (i == 9) {
        fscanfEx();
    }
    return 0;
}