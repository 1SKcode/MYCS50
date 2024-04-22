#include <cs50.h>
#include <stdio.h>

int getSum1(long);
int main(void)
{
    long num = get_long("Number: ");
    if (getSum1(num) % 10 == 0)
    {
        int dif = num / 100000000000000;
        if (num / 1000000000000000 == 0 && (num / 10000000000000 == 34 || num / 10000000000000 == 37)) // 15
        {
            printf("AMEX\n");
        }
        else if (num / 10000000000000000 == 0 && (dif == 51 || dif == 52 || dif == 53 || dif == 54 || dif == 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((num / 10000000000000 == 0 && num / 1000000000000 == 4) ||
                 (num / 10000000000000000 == 0 && num / 1000000000000000 == 4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    // printf("%i\n", getSum1(num));
}

int getSum1(long l)
{
    int sum = 0;
    long i = 1;
    int digit = 0;
    int digit1 = 0;
    while (l / i > 0)
    {
        digit = 2 * ((l % (i * 100)) / (i * 10));
        digit1 = (l % (i * 10)) / i;
        sum += digit1;
        i *= 100;

        if (digit / 10 == 1)
        {
            int num1 = digit % 10 + digit / 10;
            sum += num1;
        }
        else
        {
            sum += digit;
        }
    }
    return sum;
}

//  4003600000000014
//Давайте умножим каждую из подчеркнутых цифр на 2:
// 1•2 + 0•2 + 0•2 + 0•2 + 0•2 + 6•2 + 0•2 + 4•2

//Это дает нам:
// 2 + 0 + 0 + 0 + 0 + 12 + 0 + 8

//Теперь сложим цифры этих продуктов (то есть, не самих продуктов) вместе:
// 2 + 0 + 0 + 0 + 0 + 1 + 2 + 0 + 8 = 13

//Теперь давайте добавим эту сумму (13) к сумме цифр, которые не были умножены на 2 (начиная с конца).:
// 13 + 4 + 0 + 0 + 0 + 0 + 0 + 3 + 0 = 20

//Да, последняя цифра в этой сумме (20) равна 0, так что эта карта законна!
