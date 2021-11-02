#include <stdio.h>

typedef struct {
    int  x;
    int z;
} base;

typedef struct {
    struct base;
    int y;
    int x;
} derived;

void function_on_base( base * a) // here I can pass both pointers to derived and to base
{
    printf("Class base [%d]\n", a -> x);
    printf("Class base [%d]\n", a -> z);
}
void function_on_derived( derived * b) // here I must pass a pointer to the derived class
{
    printf("Class derived [%d]\n", b -> y);
    printf("Class derived [%d]\n", b -> x);
}

int main()
{
    derived d;
    base b;
    printf("Teste de poliformismo\n");

    b.x = 2;
    d.y = 1;
    b.z = 3;
    d.x = 7;
    printf("class b\n");
    function_on_base(&b);
    printf("class d\n");
    function_on_base(&d);
    //function_on_derived(&b);
    function_on_derived(&d);
    return 0;
}
