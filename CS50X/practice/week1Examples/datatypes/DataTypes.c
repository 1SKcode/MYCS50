//https://cs50.harvard.edu/extension/2023/fall/shorts/data_types/
#include<stdio.h>
#include<cs50.h>

int main(void)
{
    int intVar = 2147483647;          // 32 bits(4 bytes) = +-2 147 000 000
    uint uintVar = 2147483647;      // 32 bits = 4 290 000 000
    uintVar = uintVar*2;
    char charVar = 'S';                      //8 bits(1 byte)

    float floatVar = 2.11231232;             //32 bits (4 bytes)
    double doubleVar = 2.11231232;           //64 bits (8 bytes)

    //void voidVar;                          //nothing. Is a type, but not a data type

    bool boolVar = true;                      //Boolean (#include<cs50.h>)
    string strVar = "This is a string";       //series of characters (#include<cs50.h>)

    int a, b, c, d, e;           // Можем объявлять так
    a=3, b=4, c=5;
    int num;                     // variable declaration - ОБЪЯВЛЕНИЕ ПЕРЕМЕННОЙ
    num = 20;                    // assignment - ПРИСВАИВАНИЕ ЗНАЧЕНИЯ ПЕРЕМЕННОЙ

    int num1 = 20, num2= 40;     // initializatoin - ИНИЦИАЛИЗАЦИЯ

    printf("Int: %i\n", intVar);
    printf("Uint: %i\n", uintVar);
    printf("Int: %i\n", intVar);
    printf("Int: %i\n", intVar);
    printf("Int: %i\n", intVar);

    //ДОДЕЛАТЬ
    
}