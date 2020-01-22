// Author: Muhammed Emin ÖMÜR
#include <stdio.h>
#include <stdbool.h>

bool
for_int(void *l, void *r)
{
    return (((*(int *) l) == (*(int *) r)) ? true : false);
}

bool
lsearch(void *key, void *base,
        int num_of_elems, int elem_size,
        bool (*cmp_func)(void *, void*))
{
    for (int i = 0; i < num_of_elems; ++i) {
        if (cmp_func(key, (void *) ((char *) base + i * elem_size))) {
            return (true);
        }
    }
    return (false);
}

int
main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 11, 22, 12, 342};
    int key = 342;
    
    printf("%s\n", ((lsearch((void *) &key, (void *) arr, sizeof (arr) / sizeof (int), sizeof (int), for_int)) ? "Exist" : "Nope"));
    
    return (0);
}
