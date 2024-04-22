#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char lowerKey[26];
char upperKey[26];
#define LENGTH26 26

// prototypes
string substitution(string plaintext, string key);

int main(int argc, string argv[])
{
    // Checking for the correctness of the input arguments
    if (argc == 2)
    {
        if (strlen(argv[1]) != LENGTH26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else
        {
            for (int i = 0; i < LENGTH26; i++)
            {
                // Converting the key from the argument string to lowercase
                lowerKey[i] = tolower(argv[1][i]);
                upperKey[i] = toupper(argv[1][i]);
            }

            for (int i = 0; i < LENGTH26; i++)
            {

                if (!isalpha(argv[1][i]))
                {
                    printf("It was not a letter!\n");
                    return 1;
                }
            }
            for (int i = 0; i < LENGTH26 - 1; i++)
            {
                for (int j = i; j < LENGTH26 - 1; j++)
                {
                    if (lowerKey[i] == lowerKey[j + 1])
                    {
                        printf("ERROR: A duplicate letter was noticed\n");
                        return 1;
                    }
                }
            }
            // The user entered the arguments correctly ($ ./substitution VCHPRZGJNTLSKFBDQWAXEUYMOI)
            string plaintext = get_string("plaintext:  ");

            printf("ciphertext: %s\n", substitution(plaintext, argv[1]));
            return 0;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

string substitution(string plaintext, string key)
{
    string ciphertext = plaintext;
    int length = strlen(plaintext);
    for (int i = 0; i < length; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (plaintext[i] >= 65 && plaintext[i] <= 90)
                ciphertext[i] = upperKey[(int) plaintext[i] - 65];
            else
                ciphertext[i] = lowerKey[(int) plaintext[i] - 97];
        }
    }
    return ciphertext;
}
