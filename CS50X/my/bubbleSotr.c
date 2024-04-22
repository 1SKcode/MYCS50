#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define GREEN "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET "\e[0;39m"
#define MAXINDEX 100000

int arrayA[MAXINDEX];
int size = 0;

void choiseMenu(void);
void randArr();
void reverseArr();
void sortedArr();
void bubbleSort();
void writeArr();

int main(int argc, string argv[])
{
    system("clear");
    while(true)
    {
        choiseMenu();
        bubbleSort();
        writeArr();
    }

    return 0;
}

void choiseMenu(void)
{
    printf(GREEN"СОРТИРОВКА ПУЗЫРЬКОМ"RESET "\n---------Выберите режим---------\n"
            YELLOW"1"RESET" - рандомные значения в массиве\n"
            YELLOW"2"RESET" - значения в обратном порядке\n"
            YELLOW"3"RESET" - уже отсортированный массив\n"
            );

    int choise = 0;
    do
    {
        choise = get_int("---> ");
    }
    while(choise <= 0 || choise > 3);


    system("clear");
    printf( YELLOW"Сколько элементов создать?"RESET" - от 2 до 100000\n");

    do
    {
        size = get_int("---> ");
    }
    while(size < 2 || size > 100000);

    switch(choise)
    {
        case 1:
            randArr();
            break;
        case 2:
            reverseArr();
            break;
        case 3:
            sortedArr();
            break;

        default:
            printf("switch-case error");
    }
    writeArr();
}

void randArr()
{
    srand(time(NULL));

    for(int i = 0; i < size; i++)
    {
        arrayA[i] = rand() % 10000 + 1;
    }
}

void reverseArr()
{
    for(int n = size, i = 0; n >= 0; n--, i++)
    {
        arrayA[i] = n;
    }
}

void sortedArr()
{
    for(int i = 0; i < size; i++)
    {
        arrayA[i] = i+1;
    }
}

void bubbleSort()
{
    int sw_c = -1;
    int buff = 0;
    int notSorted = size;
    while(sw_c != 0)
    {
        sw_c = 0;
        for(int i = 1; i < notSorted; i++)
        {
            if(arrayA[i - 1] > arrayA[i])
            {
                buff = arrayA[i];
                arrayA[i] = arrayA[i - 1];
                arrayA[i - 1] = buff;
                sw_c++;
            }
        }
        notSorted--;
    }
}

void writeArr()
{
    char a = get_char("Вывести на экран? y/n\n---> ");

    if(a == 'y' || a == 'Y')
    {
        for(int i = 0; i < size; i++)
        {
            printf("%i-", arrayA[i]);
        }
        printf("\n");
    }
}
