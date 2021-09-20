
/*
 * Tags are a special naming mechanism for structs, unions, and enumerations.
 * The identifier s appearing in the following structure is a tag. By itself,
 * a tag is not a type name and cannot be used to declare a variable. The tags
 * of structures, unions, and enumerations are defined in a separate namespace
 * from ordinary identifiers. This allows a C program to have both a tag and
 * another identifier with the same spelling in the same scope.
 */

void tags(void) {
    struct s {
        int age;
    };

    struct s val;
    struct s *ptr;
}

/*
 * The names of unions and enumerations are also tags and not types, meaning
 * that they cannot be used alone to declare a variable.
 */

void enum_tags(void) {
    enum day { sun, mon, tue, wed, thu, fri, sat };
    // day today;  ---> error
    enum day tomorrow = sun;
}

/*
 * You can think of struct/enum/union tags as type names and define an alias
 * for the tag by using a typedef. Since the tag name in struct, union, and
 * enum is optional, you can just dispense with it entirely.
 */

void type_def(void) {
    // We can use the type definition instead of
    // all the 'struct tag' definition.
    typedef struct s {
        int age;
    } sx;

    sx val;
    sx *ptr;

    // We can remove entirely the struct tag and a new
    // type is declared anyway.
    typedef struct {
        int age;
    } sy;

    sy val_2;
    sy *ptr_2;
}

/*
 * You can also define this type before the structure.
 */

void type_def_2(void) {
    typedef struct t_node node;

    struct t_node {
        int count;
        node *left;
        node *right;
    };

    node n1;
    node *n2;
}

