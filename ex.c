// example on comparator arguments

#include <stdlib.h>
#include <stdio.h>

typedef struct BA
{
    int a;
} BA;

int funct(int a)
{
    printf("a = %d\n", a);
}

int bar(BA *structure, void *lambda(const void *))
{
    if (lambda == NULL)
        printf("lambda is null\n");
    else if (lambda(3))
        printf("wow lambda said something\n");

    return 0;
}

int main()
{
    BA *derived = &(BA){.a = 200};

    printf("%d\n", bar(derived, NULL));
    // printf("%d\n", bar(derived, funct));

    return 0;
}