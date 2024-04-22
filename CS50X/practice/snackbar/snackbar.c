// Practice using structs
// Practice writing a linear search function

/**
 * Beach Burger Shack has the following 10 items on their menu
 * Burger: $9.5
 * Vegan Burger: $11
 * Hot Dog: $5
 * Cheese Dog: $7
 * Fries: $5
 * Cheese Fries: $6
 * Cold Pressed Juice: $7
 * Cold Brew: $3
 * Water: $2
 * Soda: $2
 */

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Number of menu items
// Adjust this value (10) to number of items input below
#define NUM_ITEMS 10
#define RED "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET "\e[0;39m"
// Menu itmes have item name and price
typedef struct
{
    string item;
    float price;
} menu_item;

// Array of menu items
menu_item menu[NUM_ITEMS];

// Add items to menu
void add_items(void);

// Calculate total cost
float get_cost(string item);

int main(void)
{
    add_items();

    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i].price);
    }
    printf("\n");

    float total = 0;
    while (true)
    {
        string item = get_string("Enter a food item: ");
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }

        total += get_cost(item);
    }

    printf("Your total cost is: $%.2f\n", total);
}

// Add at least the first four items to the menu array
void add_items(void)
{
    menu[0].item = "Burger";
    menu[0].price = 9.5;

    menu[1].item = "Vegan Burger";
    menu[1].price = 11.0;

    menu[2].item = "Hot Dog";
    menu[2].price = 5.0;

    menu[3].item = "Cheese Dog";
    menu[3].price = 7.0;

    menu[4].item = "Fries";
    menu[4].price = 5.0;

    menu[5].item = "Cheese Fries";
    menu[5].price = 6.0;

    menu[6].item = "Cold Pressed Juice";
    menu[6].price = 7.0;

    menu[7].item = "Cold Brew";
    menu[7].price = 3.0;

    menu[8].item = "Water";
    menu[8].price = 2.0;

    menu[9].item = "Soda";
    menu[9].price = 2.0;
}

// Search through the menu array to find an item's cost
float get_cost(string item)
{
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        int srtLen = strlen(menu[i].item);
        int strChoiseLen = strlen(item);

        char lowerItem[srtLen + 1];
        char lowerItemChoise[strChoiseLen + 1];

        for (int j = 0; j < srtLen; j++)
        {
            lowerItem[j] = tolower(menu[i].item[j]);
        }
        lowerItem[srtLen] = '\0';

        for (int j = 0; j < strChoiseLen; j++)
        {
            lowerItemChoise[j] = tolower(item[j]);
        }
        lowerItemChoise[strChoiseLen] = '\0';

        if (strcmp(lowerItem, lowerItemChoise) == 0)
        {
            return menu[i].price;
        }
    }
    printf(RED "Invalid Item!!" RESET "\n");
    return 0.0;
}