// Author: Muhammed Emin ÖMÜR

#include <stdio.h>
#include <string.h>

int
for_int(const void *left, const void *right)
{
    const int *left_int_ptr = (int *) left;
    const int *right_int_ptr = (int *) right;
    
    if (*left_int_ptr < *right_int_ptr) {
        return (1);
    } else if (*left_int_ptr > *right_int_ptr) {
        return (-1);
    } else {
        return (0);
    }
}

int
for_string(const void *left, const void *right)
{
    int result = strcmp(*(char **) right, *(char **) left);
    
    if (result > 0) {
        return (1);
    } else if (result == 0) {
        return (0);
    } else {
        return (-1);
    }
}

const void *
bsearch(const void *key, const void *base,
    size_t num_of_elems, size_t elem_size,
    int (*comparison_function)(const void *, const void *))
{
    int begin = 0;
    int middle = 0;
    int end = num_of_elems - 1;
    int equality;
    
    while (begin <= end) {
        middle = begin + (end - begin) / 2;
        equality = comparison_function(key, base + (middle * elem_size));
        
        if (equality == 0) {
            return (base + (middle * elem_size));
        } else if (equality == 1) {
            end = middle - 1;
        } else {
            begin = middle + 1;
        }
    }
    
    return (NULL);
}

int
main(void)
{
    int arr[] = {-4, 1, 2, 3, 4, 5, 11, 122, 123, 124, 125, 888, 23333, 99999};
    const char *str_arr[] = {"A", "Ali", "Ata", "Bak", "Git"};
    int key = 99999;
    const char *str_key = "Git";
    
    const void *result = bsearch(&str_key, str_arr, sizeof (str_arr) / sizeof (char *), sizeof (char *), for_string);
    
    if (result) {
        printf("Value exist\n");
    } else {
        printf("Value does not exist\n");
    }
    
    return (0);
}
