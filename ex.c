// example on inheritance

#include <stdlib.h>
#include <stdio.h>

typedef struct foo_s
{
    int a;
} foo;

typedef struct bar_s
{
    foo *super;
    int b;
} bar;

int getA(foo *x)
{
    return x->a;
}

int getB(bar *x)
{
    return x->b;
}

foo *newA()
{
    foo *new = malloc(sizeof(foo));
    new->a = 10;
    return new;
}

bar *newB()
{
    bar *new = (void *)newA();
    printf("A: %d\n", getA((void *)new));
    printf("B: %d\n", getB((void *)new));
    new->b = 3;
    return new;
}

int main()
{
    bar *derived = newB();
    printf("A: %d\n", getA((void *)derived));
    printf("B: %d\n", getB((void *)derived));
    return 0;
}