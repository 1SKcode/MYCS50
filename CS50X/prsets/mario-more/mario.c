#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;

    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int i = 0; i < height; i++)
    {
        int cpaces = i + 1; // 1. Print cpaces
        while (cpaces < height)
        {
            printf(" ");
            cpaces++;
        }

        int hashesLeft = i + 1; // 2. Print left
        while (hashesLeft > 0)
        {
            printf("#");
            hashesLeft--;
        }
        printf("  "); // 3. Print GAP

        int hashesRight = i + 1; // 4. Print right
        while (hashesRight > 0)
        {
            printf("#");
            hashesRight--;
        }
        printf("\n");
    }
}