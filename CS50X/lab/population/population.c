#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int startSize = 9; // Prompt for start size
    int endSize = 9;   // Prompt for end size

    do
    {
        startSize = get_int("Start size: ");
    }
    while (startSize < 9);

    do
    {
        endSize = get_int("End size: ");
    }
    while (endSize < startSize);

    int born = 0;
    int died = 0;
    int years = 0;
    while (startSize < endSize) // Calculate number of years until we reach threshold
    {
        born = startSize / 3;
        died = startSize / 4;
        startSize = startSize + born - died;
        years++;
    }
    printf("Years: %i\n", years); // TODO: Print number of years
}
