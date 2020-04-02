#ifndef STACK_H
#define STACK_H

typedef struct {
    int elem_size;
    int num_of_elems;
    int max_size;
    void *elems;
    void (*function_to_free_elems)(void *elem);  // This function is used to clean up remaining elements in stack, if required
} stack;

extern void stack_new(stack *s, int size, void (*freefn)(void *elem));
extern void stack_dispose(stack *s);
extern void stack_push(stack *s, void *new_elem);
extern void stack_pop(stack *s, void *popped_elem);

#endif
