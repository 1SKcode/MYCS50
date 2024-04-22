//Свап двух переменных через указатели
#include <stdio.h>

void swap(int* a, int* b);

int main(void)
{
    int a = 50;
    int b = 100;

    printf("a: %d b: %d\n", a, b);
    swap(&a, &b);
    printf("a: %d b: %d\n", a, b);
}

void swap(int* a, int* b)
{
    int temp = 0;
    temp = *a;
    *a = *b;
    *b = temp;
}
