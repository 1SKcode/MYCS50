#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

long atoi(string input, int n);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }
    // Convert string to int
    printf("%li\n", atoi(input, strlen(input) - 1));
}

long atoi(string input, int n)
{
    if (n < 0 || (input[n] < '0' || input[n] > '9')) {
        return 0;
    }
    return (10 * atoi(input, n - 1) + (input[n]-'0'));
}
