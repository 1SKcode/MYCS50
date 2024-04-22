#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
//---------------ВЫДЕЛЕНИЕ ПЕРЕМЕННОЙ------------------
    //Обычное выделение целочисленной переменной на стеке
    int a = 0;

    // malloc выделение целочисленного указателя на КУЧЕ
    int *ap = NULL;
    ap = malloc(sizeof(int));
    if (ap == NULL) // ОБЯЗАТЕЛЬНО ПРОВЕРЯЕМ НА НУЛЕВОЙ УКАЗАТЕЛЬ
        exit(1);
    *ap = 5;
    printf("%d\n", *ap);
    free(ap); // ОБЯЗАТЕЛЬНО ОЧИАЩАЕМ

//--------------ВЫДЕЛЕНИЕ МАССИВА INT-------------------
    int *int_arr_p = NULL;
    if ((int_arr_p = malloc(10 * sizeof(int))) == NULL)
        exit(2);
    for (int i = 0; i < 10; i++)
    {
        int_arr_p[i] = 10 + i;
        printf("%d\n", int_arr_p[i]);
    }
    free(int_arr_p);

//---------------ВЫДЕЛЕНИЕ МАССИВА СТРОК И КОПИРОВАНИЕ----------------
    char *str1 = "str1HIHI";
    // Задача: скопировать эту строку в новую

    char *str2 = malloc(strlen(str1) + 1); // +1 для \0 символа, означающий конец строки
    if (!str2)
        exit(3); // Проверка на нулевой указатель
    for (int i = 0, l = strlen(str1); i <= l; i++)
    {
        str2[i] = str1[i];
    }
    str2[3] = '2';
    printf("%s\n", str2);
    free(str2);

    char *str3 = NULL;
    str3 = "qwe";
    printf("%s\n", str3);
//--------------------------------------------------------------------
}
