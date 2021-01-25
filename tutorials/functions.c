#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Function types are derived types. In this case, the type is derived from the
return type and the number and types of its parameters. The return type of
a function cannot be an array type.

The function definition provides the actual implementation of the
function.
*/

// You should never declare functions with an empty parameter list in C. //

// DECLARATIONS
int max(int a, int b);
int f(void);
int *fip();
void f2(int i, int j);
void h(int, int);

// DEFINITION
int max(int a, int b) { 
    return a > b ? a : b; 
}

// some other examples
char* revString(char* str, char* res) {
    int len = strlen(str);
    for (int i = len - 1; i >= 0; i--) {
        res[i] = str[(len - 1) - i];
    }
    res[len+1] = '\0';
    return res;
}

void swap(int* p_a, int* p_b) {
    int tmp = *p_a;
    *p_b = *p_a;
    *p_a = tmp;
}


/* 
A function invocation, like max(a, b), is converted to a pointer-to-function at 
compile time, the number and type (excluding coercion) of arguments must be the 
same of the function declaration (but variadic function exists).

We can also pass one function to another.
*/
int ff(void) {
    return 0;
}

void g(int (*func)(void)) {
    if (func() != 0) {
        printf("g failed\n");
    } else {
        printf("g successeded\n");
    }
}

// different syntax, same result
void g2(int func(void)) {
    if (func() != 0) {
        printf("g failed\n");
    } else {
        printf("g successeded\n");
    }
}

void funcPtrEx(void) {
    g(ff); // call g with function-pointer argument
    g2(ff);
}

