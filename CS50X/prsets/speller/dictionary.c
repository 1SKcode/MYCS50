// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char lowc_w[LENGTH + 1];
    for (int i = 0; word[i]; i++)
    {
        lowc_w[i] = tolower(word[i]);
    }
    lowc_w[strlen(word)] = '\0';

    // Hash the word to determine the index in the table
    int index = hash(lowc_w);

    // Traverse the linked list at that index
    for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
    {
        // Compare the word with the current node's word
        if (strcmp(cursor->word, lowc_w) == 0)
        {
            // Word found in the dictionary
            return true;
        }
    }

    // Word not found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hashVal = 0;
    for (int i = 0; word[i]; i++)
    {
        hashVal += tolower(word[i]);
    }
    return hashVal % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Read words from dictionary and insert into hash table
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory for a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            return false;
        }

        // Copy the word to the node (convert to lowercase for case-insensitivity)
        for (int i = 0; word[i]; i++)
        {
            word[i] = tolower(word[i]);
        }
        strcpy(new_node->word, word);

        // Hash the word to determine the index in the table
        int index = hash(word);

        // Insert the new node at the beginning of the linked list
        new_node->next = table[index];
        table[index] = new_node;
    }

    // Close the file
    fclose(file);

    // Loading successful
    return true;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int count = 0;
    for (int i = 0; i < N; i++)
    {
        for (node *cursor = table[i]; cursor != NULL; cursor = cursor->next)
        {
            count++;
        }
    }
    return count;
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *temp = table[i]->next;
            free(table[i]);
            table[i] = temp;
        }
    }
    return true;
}

