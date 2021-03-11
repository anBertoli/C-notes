#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "tutorials/declarations.h"

// choose the test
int i = 1;

int main(void) {
    if (i == 0) {
        for (int i = 0; i < 10; i++) {
            printf("Max of %d and %d is: %d.\n", i, 5, max(i, 5));
            printf("Is %d divisible by %d? %s.\n", 10, i, isDivisibleBy(10, i) ? "Yes" : "No");
        }
    }
    if (i == 1) {
        char str[30], rev[30];
        for (int i = 0; i < 10; i++) {
            sprintf(str, "This is the attempt %d", i);
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