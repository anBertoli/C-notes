#include <string.h>
#include <stdio.h>

/*
Derived types are types that are constructed from other types. These include
pointers, arrays, type definitions, structures, and unions.
*/


// POINTERS
// If the pointer is not pointing to a valid
// object or function, bad things may happen.
void pointers(void) {
    int *ip;
    char *cp;
    void *vp;

    *ip = 4; // indirection

    int a = 4;
    int *ap = &a; // dereference
}

/*
Pointers arithmetic exists. 

Adding or subtracting an expression that has integer type to or from
a pointer returns a value with the type of the pointer operand. If the
pointer operand points to an element of an array, then the result points
to an element offset from the original element. If the resulting pointer is
outside the bounds of the array, undefined behavior occurs.

When we subtract one pointer from another, both must point to elements
of the same array object or the too-far element. This operation returns the
difference of the subscripts of the two array elements. The type of the result
is ptrdiff_t (a signed integer type).

Pointer arithmetic is automatically scaled to work with array element sizes, 
rather than individual bytes.
*/


// ARRAYS
// An array is a contiguously allocated sequence of objects that all have the
// same element type. Array types are characterized by their element types
// and the number of elements in the array.
void arrays(void) {
    int ia[11];
    float *afp[17];

    // create the "0123456789" string
    char str[11];
    for (unsigned int i = 0; i < 10; ++i) {
        str[i] = '0' + i; // str[i] is identical to *(str + i)
    }
    str[10] = '\0'; 

    // multidimensional
    int arr[3][5];
    int x = arr[2][3];
}


// STRUCTs
// contains sequentially allocated member objects. Each object has its own name
// and may have a distinct type—unlike arrays, which must all be of the same type.

// an object identified by 'sigline' that has a type of struct 'sigrecord'
// and sigline_p which is a pointer to a sigrecord struct
struct sigrecord {
    int signum;
    char signame[20];
    char sigdesc[100];
};

void structs(void) {
    struct sigrecord sigline, *sigline_p;

    // assign individual members
    sigline.signum = 5;
    strcpy(sigline.signame, "SIGINT");
    strcpy(sigline.sigdesc, "Interrupt from keyboard");
    
    // access members like:
    char *desc = sigline.sigdesc;

    printf("%s\n", sigline.sigdesc);

    // with pointers
    sigline_p = &sigline;
    sigline_p->signum = 5;
    strcpy(sigline_p->signame, "SIGINT");
    strcpy(sigline_p->sigdesc, "Interrupt from keyboard");
}

// UNIONs
// Union types are similar to structures, except that the memory used by the
// member objects overlaps. Unions can contain an object of one type at
// one time, and an object of a different type at a different time, but never
// both objects at the same time, and are primarily used to save memory.

// an union type that contains exclusivally one of the following structs
union {
    struct {
        int type;
    } n;
    struct {
        int type;
        int intnode;
    } ni;
    struct {
        int type;
        double doublenode;
    } nf;
} u;

void unions(void) {
    u.nf.type = 1;
    u.nf.doublenode = 3.14;
}

// TAGs
// Tags are a special naming mechanism for structs, unions, and enumerations.

// s is the tag
struct s {
    int a;
    char b;
    unsigned int c;
};

void tags(void) {
    struct s v;     // instance of struct s
    struct s *p;    // pointer to struct s
}

// The names of unions and enumerations are also tags and not types,
// meaning that they cannot be used alone to declare a variable. For example:
enum day { sun, mon, tue, wed, thu, fri, sat };
// day today; // error
enum day tomorrow = sun; // OK

// You can think of struct tags as type names and define an alias 
// for the tag by using a typedef. Here’s an example:
typedef struct user { 
    int age;
    char name[30]; 
} user_type;
// or simply (tag name in struct, union, and enum is optional)
typedef struct { 
    int age;
    char name[30]; 
} user_type2;



// TYPEDEFs
// You use a typedef to declare an alias for an existing type; it never creates a
// new type. For example, each of the following declarations creates a new type alias:
typedef unsigned int uint_type;
typedef signed char schar_type, *schar_p, (*fp)(void);
// On the first line, we declare uint_type as an alias for the type unsigned
// int. On the second line, we declare schar_type as an alias for signed char,
// schar_p as an alias for signed char *, and fp as an alias for signed char(*)
// (void). Identifiers that end in _t in the standard headers are type definitions
// (aliases for existing types). Don't use this pattern, it is reserved.

