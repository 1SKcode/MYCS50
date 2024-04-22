#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    //ИНИЦИАЛИЗАЦИЯ-------------
    int size = 0;
    int newValue = 0;
    do
    {
        printf("Введите размер начального массива -->  ");
        if (scanf("%d", &size) == 0)
        {
            // Очистка буфера ввода в случае неудачного ввода
            while (getchar() != '\n');
            continue;
        }
    }
    while (size <= 0);

    // ВЫДЕЛЕНИЕ ЗАПРОШЕННОГО МЕСТА ПОД МАССИВ
    int *list = malloc(size * sizeof(int));
    if (list == NULL)
    {
        printf("Ошибка выделения паямяти!\n");
        return 1;
    }
    printf("Памяти под массив выделено %lu * %d = %lu байт динамически\nИнициализированы нулями:\n",
     sizeof(int), size, size * sizeof(int));

    // Инициализация нулями
    for (int i = 0; i < size; i++)
    {
        list[i] = 0;
        printf("%d - ", list[i]);
    }
    printf("\n");

    //ВВОД
    for (int i = 0; i < size; i++)
    {
        printf("Введите элемент %d -->  ", i + 1);
        scanf("%d", &list[i]);
    }

    //Вывод заполненного массива
    for (int i = 0; i < size; i++)
    {
        printf("%d - ", list[i]);
    }
    printf("\n");

    while(1)
    {
        int new_size;
        printf("Сколько ячеек добавить? -->  ");
        scanf("%d", &new_size);

        int *tmp = realloc(list, (size + new_size) * sizeof(int));
        if (tmp == NULL)
        {
            printf("Ошибка выделения паямяти!\n");
            free(list);
            return 2;
        }
        list = tmp;
        printf("Памяти под массив выделено %lu + (%lu * %d) = %lu байт динамически\n"
            "Инициализированы нулями:\n",
            size * sizeof(int), sizeof(int), new_size, size * sizeof(int) + (sizeof(int) * new_size));

        // Инициализация нулями
        for (int i = size; i < size + new_size; i++)
        {
            tmp[i] = 0;
        }

        // ВЫВОД С НУЛЯМИ
        for (int i = 0; i < new_size + size; i++)
        {
            printf("%d - ", tmp[i]);
        }
        printf("\n");

        for (int i = size; i < size + new_size; i++)
        {
            printf("Введите элемент %d -->  ", i + 1);
            scanf("%d", &tmp[i]);
        }

        size += new_size;

        for (int i = 0; i < size; i++)
        {
            printf("%d - ", list[i]);
        }
        printf("\n");

        printf("Добавить ячеек? (y) -->  ");
        char c;
        scanf(" %c", &c);
        if(c != 'y')
        {
            free(list);
            return 0;
        }
    }
}
