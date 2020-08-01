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

void func1(int *a)
{
    printf("%d\n", a);
}

void func2(int *a)
{
    printf("%d\n", *a);
    func1(*a);
}

int main()
{
    // int b[5] = {[0] = {1}, [4] = {2}};

    // int *ptr = func();
    int a[1];
    *a = 3;
    func2(a);

    return 0;
}
