
/*
 * Each object has a storage duration that determines its lifetime, which is the
 * time during program execution for which the object exists, has storage, has
 * a constant address, and retains its last-stored value. Objects must not be
 * referenced outside their lifetime.
 */

void variables(void) {
    int a = 21;
    long b = 17;
    char c = 'a';
}

/*
 * The C language also has pointers, which can be thought of as an address
 * a location in memory where an object or function is stored. A pointer type
 * is derived from a function or object type called the referenced type.
 */

void pointers(int *ptr_a, int *ptr_b) {
    int tmp = *ptr_a;
    *ptr_a = *ptr_b;
    *ptr_b = tmp;
}

void use_pointers(void) {
    int a = 1;
    int b = 2;
    pointers(&a, &b);
}

/*
 * Objects have a storage duration that determines their lifetime. Altogether,
 * four storage durations are available: automatic, static, thread, and allocated.
 *
 * - AUTOMATIC: objects declared within a block or as a function parameter, the
 *              lifetime of these objects begins when the block in which they’re declared begins execution,
 *              and ends when execution of the block ends
 *
 * - STATIC:    objects declared in file scope have static storage duration. The lifetime of these
 *              objects is the entire execution of the program, and their stored value is initialized
 *              prior to program startup. You can also declare a variable within a block scope to have
 *              static storage duration by using the storage class specifier static.
 *
 * - ALLOCATED: objects dynamically allocated using functions like malloc, calloc, realloc. The lifetime
 *              of these objects begins when the allocation occurs and ends when the objects are manually
 *              freed (with the free function).
 *
 * - THREAD:    storage duration is used in concurrent programming.
 *
 * Scope and lifetime are entirely different concepts. Scope applies to identifiers,
 * whereas lifetime applies to objects. The scope of an identifier is the code region
 * where the object denoted by the identifier can be accessed by its name. The lifetime
 * of an object is the time period for which the object exists.
 */
