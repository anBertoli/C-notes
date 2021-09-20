#include <string.h>
#include <stdio.h>

/*
 * A pointer type is derived from the function or object type that it points to,
 * called the referenced type. A pointer provides a reference to an entity of the
 * referenced type.
 *
 * You use the & operator to take the address of an object or function. The
 * unary * operator converts a pointer to a type into a value of that type. It
 * denotes indirection and operates only on pointers. If the operand points to
 * a function, the result of using the * operator is the function designator,
 * and if it points to an object, the result is a value of the designated object.
 */

void pointer_types(void) {
    // pointer to int
    int *int_ptr;

    // pointer to char
    int *char_ptr;

    // int_ptr will point to the value
    // linked to the variable num
    int num = 1;
    int_ptr = &num;

    // num_2 will be assigned a value equal to the
    // value pointed by the int_ptr pointer
    int num_2 = *int_ptr;
}

/*
 * An array is a contiguously allocated sequence of objects that all have the same
 * element type. Array types are characterized by their element types and the number
 * of elements in the array. Arrays variables are pointers to the first element of
 * the stored array.
 */

void array_types(void) {
    // an array of 10 int
    int int_array[10];

    // an array of 10 pointers to char
    char *char_array[10];
}

/*
 * Arrays can be indexed with the [] operator. The square bracket operator ([]) is
 * equivalent to adding a value to the array pointer and dereferencing the obtained
 * pointer. The operand i of the [] operator (e.g. [i]) is converted to i * sizeof(type)
 * so the expression int_array[2] yields a pointer to the third element of the array.
 */

void array_indexing(void) {
    int int_array[10] = { 0,1,2,3,4,5,6,7,8,9 };

    // If int_array = 0X00 and ints are 4 bytes long
    // int_array[2] = *(0X00 + 2 * (4 bytes)) = *0x08,
    // namely a pointer yielding the int value of the
    // third value in the array.
    int third_elem = int_array[2];

    // If the operand of the unary & operator is the
    // result of a [] operator, the result is as if the
    // & operator were removed and the [] operator were
    // changed to a + operator.
    //
    // The following two are the same.
    int *ptr_to_third_elem = &int_array[2];
    int *ptr_to_third_elem_2 = int_array + (2 * sizeof(int));
}

/*
 * A structure type (also known as a struct) contains sequentially allocated member
 * objects. Each object has its own name and may have a distinct type. You reference
 * members of an object of the structure type by using the structure member (.)
 * operator. If you have a pointer to a structure, you can reference its members
 * with the structure pointer (->) operator.
 */

void struct_types(void) {
    // Define a variable sig_line that is a struct named
    // sig_record and modify some fields.
    struct sig_record {
        int sig_num;
        char sig_name[20];
        char sig_desc[100];
    } sig_line;

    sig_line.sig_num = 5;
    strcpy(sig_line.sig_name, "SIGINT");
    strcpy(sig_line.sig_desc, "Interrupt from keyboard");

    // Take a pointer to the struct variable
    // and modify some fields.
    struct sig_record *sig_line_ptr = &sig_line;

    sig_line_ptr->sig_num = 5;
    strcpy(sig_line_ptr->sig_name, "SIGINT");
    strcpy(sig_line_ptr->sig_desc, "Interrupt from keyboard");
}

/*
 * The name associated with the struct is a tag. Each time a struct is declared
 * with a tag, a new type is created and the type can be used in the next variables
 * declaration. A struct without a tag is an "anonymous struct type" and no more
 * variables with that type could be declared (we cannot reference an anonymous
 * type). Note that the type name is the entire "struct user" and not only the
 * word "user".
 */

void struct_types_declarations(void) {

    // Define a struct user type and declare a variable of
    // that type (u1) and a pointer to that type (u2).
    struct user {
        int age;
        char first_name[30];
        char second_name[30];
    };

    struct user u1;
    struct user *u2;

    // Struct without tags doesn't declare any type, no new
    // variables of that type can be declared.
    struct {
        char first_name[30];
    } user_2;

    struct {
        char first_name[30];
    } user_3;

    // user_2 = user_3; --> not allowed by the compiler

    // Note however that anonymous struct "saved" with typedefs
    // can be used in multiple variables as a properly declared
    // type.
    typedef struct {
        char first_name[30];
    } user_4;

    user_4 a;
    user_4 b;
    a = b;
}

/*
 * Union types are similar to structures, except that the memory used by the
 * member objects overlaps. Unions can contain an object of one type at one
 * time, and an object of a different type at a different time, but never both
 * objects at the same time, and are primarily used to save memory.
 */

void union_types(void) {
    union un {
        int a;
        char b;
        float c;
    };

    union un u;

    // This assigment gives to binary representation of int 1 to the
    // union type, reading using the other union fields will lead to
    // incorrect interpretation.
    u.a = 65;
    printf("%d\n", u.a); // ---> 65
    printf("%c\n", u.b); // ---> A
    printf("%f\n", u.c); // ---> 0.0000

    u.b = 'C';
    printf("%d\n", u.a); // ---> 67
    printf("%c\n", u.b); // ---> C
    printf("%f\n", u.c); // ---> 0.0000

}








