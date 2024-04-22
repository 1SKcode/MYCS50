#include <stdio.h>
#include <cs50.h>


void add(int num1, int num2);
void sub(int num1, int num2);
void multip(int num1, int num2);
void div(int num1, int num2);

int main(void)
{
    bool contune = true;
    while(contune == true)
    {
        printf("Сложить два числа - 1\nВычестьть два числа - 2\nУмножить два числа - 3\nРазделить два числа - 4\n");
        int chose = get_int("");
        int x = get_int("Введите первое число: ");
        int y = get_int("Введите второе число: ");

        if(chose == 1)
        {
            add(x, y);
        }
        else if(chose == 2)
        {
            sub(x,y);
        }
        else if(chose == 3)
        {
            multip(x,y);
        }
        else
        {
            div(x,y);
        }

        char choise = get_char("Продолжить? Y/N -->  ");
        if(choise == 'y' || choise == 'Y')
        {
            contune = true;
        }
        else
            contune = false;
    }
}

    void add(int num1, int num2)
    {
        printf("Результат: %i\n",num1+num2);

    }

    void sub(int num1, int num2)
    {
        printf("Результат: %i\n",num1-num2);
    }

    void multip(int num1, int num2)
    {
        printf("Результат: %i\n",num1*num2);
    }

    void div(int num1, int num2)
    {
        printf("Результат: %f\n",(float)num1/num2);
    }
