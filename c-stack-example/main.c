#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

// String free function definition given here
void
string_free(void *elem)
{
    free(*(char **) elem);
}
//

void
string_example(void)
{
    stack s;
    char *strs[] = {"He", "asd", "gel", "de", "bir", "buna", "babababak", "hadi", "git"};
    int string_array_size = sizeof (strs) / sizeof (char *);
    
    stack_new(&s, sizeof (char *), string_free);
    
    for (int i = 0; i < string_array_size; ++i) {
        char *ptr = strdup(strs[i]);
        stack_push(&s, &ptr);
    }
    
    printf("Five elements of stack:\n");
    for (int i = 0; i < 5; ++i) {
        char *arr;
        stack_pop(&s, &arr);
        printf("%s\n", arr);
        free(arr);
    }
    
    stack_dispose(&s);
}

void
int_example(void)
{
    stack s;
    
    stack_new(&s, sizeof (int), NULL);
    
    for (int i = 1; i <= 100; ++i) {
        stack_push(&s, &i);
    }
    
    while (s.num_of_elems) {
        int popped_value;
        stack_pop(&s, &popped_value);
        printf("%d\n", popped_value);
    }
    
    stack_dispose(&s);
}

int
main(void)
{
    string_example();
    int_example();
    
    return (0);
}
