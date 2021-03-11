#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int age;
    char name[50]; 
} user;

struct filt_params {
    int age;
    char *name;
    bool case_sens;
};

int compareStrings(char *s1, char *s2, bool case_sens) {
    if (!case_sens) {
        char s1l[strlen(s1)];
        char s2l[strlen(s2)];
        for (int i=0; s1[i]; i++) s1l[i] = tolower(s1[i]);
        for (int i=0; s2[i]; i++) s2l[i] = tolower(s2[i]);
        return strcmp(s1l, s2l) == 0;
    } else {
        return strcmp(s1, s2) == 0;
    }
}

int filter(user input[], user filtered[], unsigned int input_len,  struct filt_params filt) {
    int j = 0;
    int i = 0;
    for (i = 0;  i < input_len; i++) {
        bool in = false;
        if (filt.age <= input[i].age) {
            if (filt.name == NULL) {
                in = true;
            } else {
                in = compareStrings(input[i].name, filt.name, filt.case_sens);
            }
        }
        if (in) {
            filtered[j] = input[i];
            j++;
        }
    }
    // return number of resulting items
    return j;
}



int main(void) {
    user res[5];
    user users[] = {
        {.age = 26, .name = "Andrea"},
        {.age = 23, .name = "Luca"},
        {.age = 43, .name = "Matteo"},
        {.age = 35, .name = "Giovanni"},
        {.age = 67, .name = "Bruno"},
    };

    int n = filter(users, res, 5, (struct filt_params){
        .age = 60,
        .case_sens = false,
        .name = ""
    });

    printf("Obtained %d elements.\n", n);
    for (int i = 0; i < n; i++) {
        printf("\t%d --> name: %s, age: %d\n", i, res[i].name, res[i].age);
    }
    return 0;
}
