// If you compile and run this program, it is likely to crash

#include <stdio.h>

// This function accesses function main using its adress
void first_function(void);

// This function accesses all the paramters provided function
void second_function(char a, char b, char c, char d);

// This function accesses variable 'c' in function main through pointer
void third_function(void);

int
main(void)
{
    char c = 'x';
    
    printf("%p\n\n", &c);
    
    printf("First function is called here:\n");
    first_function();
    
    printf("\n\nSecond function is called here:\n");
    second_function('A', 'B', 'C', 'D');
    
    printf("\n\nThird function is called here:\n");
    third_function();
    
    return (0);
}

void
first_function(void)
{
    printf("%p\t\t%p\n", main, first_function);
    
    typedef int (*main_function_type)(void);
    int (*ptr)(void) = (main_function_type)first_function - 149; // OR int (*ptr)(void) = (int (*)(void))first_function - 149;
    
    printf("%p\n", first_function - 149);
    printf("%p\t\t%p\n", ptr, ptr + 1);

    // If you call this function, program will end with stack overflow
//     ptr();
}

void
second_function(char a, char b, char c, char d)
{
    char *ptr;
    ptr = (char *)&ptr - 16;
    
    printf("%c\t%c\t%c\t%c\n", *(ptr + 12), *(ptr + 8), *(ptr + 4), *(ptr));
    
    printf("\n%p\n%p\n%p\n%p\n%p\n", &ptr, &a, &b, &c, &d);
    
    printf("\n%p\t\t", ptr);
    printf("%p\n", ++ptr);
}

void
third_function(void)
{
    char *ptr;
    
    ptr = (char *)&ptr;
    
    printf("%p\n", &ptr);
    printf("%p\t\t%p\n", ptr, ptr + 39);
    printf("%c\n", *(ptr + 39));
}
