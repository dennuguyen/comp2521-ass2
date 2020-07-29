// example on comparator arguments

#include <stdlib.h>
#include <stdio.h>

// typedef struct BA
// {
//     int a;
// } BA;

// int funct(int a)
// {
//     printf("a = %d\n", a);
// }

// int bar(BA *structure, void *lambda(const void *))
// {
//     if (lambda == NULL)
//         printf("lambda is null\n");
//     else if (lambda(3))
//         printf("wow lambda said something\n");

//     return 0;
// }

// int main()
// {
//     BA *derived = &(BA){.a = 200};

//     printf("%d\n", bar(derived, NULL));
//     // printf("%d\n", bar(derived, funct));

//     return 0;
// }

// multidimensional arrays
int a[3][3] = {{0, 1, 2}, {7, 4, 5}, {6, 3, 8}};

int *func()
{
    return &a[2][0];
}

int main()
{
    int b[5] = {[0] = {1}, [4] = {2}};

    // int *ptr = func();

    for (int i = 0; i < 5; i++)
        printf("%d\n", b[i]);

    return 0;
}
