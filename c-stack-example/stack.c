#include "stack.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

void
stack_new(stack *s, int size, void (*freefn)(void *elem))
{
    s->elem_size = size;
    s->num_of_elems = 0;
    s->max_size = 4;
    s->elems = malloc(s->elem_size * s->max_size);
    s->function_to_free_elems = freefn;
    assert(s->elems != NULL);
}

void
stack_dispose(stack *s)
{
    if (s->function_to_free_elems) {
        for (int i = 0; i < s->num_of_elems; ++i) {
            s->function_to_free_elems((char *) s->elems + i * s->elem_size);
        }
    }
    
    free(s->elems);
}

void
stack_push(stack *s, void *new_elem)
{
    if (s->num_of_elems == s->max_size) {
        s->max_size *= 2;
        s->elems = realloc(s->elems, s->max_size * s->elem_size);
        assert(s->elems != NULL);
    }
    memcpy((char *) s->elems + (s->elem_size * s->num_of_elems), new_elem, s->elem_size);
    s->num_of_elems++;
}

void
stack_pop(stack *s, void *popped_elem)
{
    if (s->num_of_elems > 0) {
        s->num_of_elems--;
        memcpy(popped_elem, (char *) s->elems + (s->elem_size * s->num_of_elems), s->elem_size);
    }
}
