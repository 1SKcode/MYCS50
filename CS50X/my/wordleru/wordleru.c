#include <cs50.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <wctype.h>

// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN L"\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW L"\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED L"\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET L"\e[0;39m"

// user-defined function prototypes
void get_wstring(wchar_t *buffer, int wordsize);
int check_wchar_word(wchar_t *guess, int wordsize, int status[], wchar_t *choice);
void print_wchar_word(wchar_t *guess, int wordsize, int status[]);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        wprintf(L"Используй: ./wordle размер_слова\n");
        return 1;
    }

    int wordsize = 0;

    if (atoi(argv[1]) >= 5 && atoi(argv[1]) <= 8)
    {
        wordsize = atoi(argv[1]);
    }
    else
    {
        wprintf(L"Ошибка: размер слова можеть быть тольок 5, 6, 7, или 8\n");
        return 1;
    }

    setlocale(LC_ALL, "");

    char filename[15];
    snprintf(filename, sizeof(filename), "%i.txt", wordsize);

    FILE *wordlist = fopen(filename, "r");
    if (wordlist == NULL)
    {
        wprintf(L"Ошибка открытия файла: %s.\n", filename);
        return 1;
    }

    // load word file into an array of size LISTSIZE
    wchar_t options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fwscanf(wordlist, L"%ls", options[i]);
        options[i][wordsize] = L'\0'; // null-terminate the string
    }

    // pseudorandomly select a word for this game
    srand(time(NULL));
    wchar_t choice[wordsize + 1];
    wcscpy(choice, options[rand() % LISTSIZE]);

    // allow one more guess than the length of the word
    int guesses = wordsize + 1;
    bool won = false;

    // print greeting, using ANSI color codes to demonstrate
    wprintf(GREEN L"Это игра WORDLE - RU" RESET L"\n");
    wprintf(L"У тебя есть %i попыток чтобы отгадать %i-буквенное слово\n", guesses, wordsize);

    // main game loop, one iteration for each guess
    for (int i = 0; i < guesses; i++)
    {
        // obtain user's guess
        wchar_t guess[wordsize + 1];
        get_wstring(guess, wordsize);

        // array to hold guess status, initially set to zero
        int status[wordsize];

        // set all elements of status array initially to 0, aka WRONG
        for (int j = 0; j < wordsize; j++)
        {
            status[j] = 0;
        }

        // Calculate score for the guess
        int score = check_wchar_word(guess, wordsize, status, choice);

        wprintf(L"Попытка %i: ", i + 1);

        // Print the guess
        print_wchar_word(guess, wordsize, status);

        // if they guessed it exactly right, set terminate loop
        if (score == EXACT * wordsize)
        {
            won = true;
            wprintf(L"ТЫ ВЫИГРАЛ!\n");
            return 0;
        }
    }

    // Print the game's result
    wprintf(L"%ls\n", choice);
    return 0;
}

void get_wstring(wchar_t *buffer, int wordsize)
{
    wprintf(L"Введи %i-буквенное слово: ", wordsize);
    fgetws(buffer, wordsize + 1, stdin);

    // Удаление символов новой строки из буфера ввода
    size_t len = wcslen(buffer);
    if (len > 0 && buffer[len - 1] == L'\n')
    {
        buffer[len - 1] = L'\0'; // Удаление символа новой строки
    }

    // Очистка буфера stdin, чтобы избежать проблемы с символом новой строки
    int c;
    while ((c = fgetwc(stdin)) != L'\n' && c != WEOF)
        ;
}

int check_wchar_word(wchar_t *guess, int wordsize, int status[], wchar_t *choice)
{
    int score = 0;

    // compare guess to choice and score points as appropriate, storing points in status
    for (int i = 0; i < wordsize; i++)
    {
        for (int j = 0; j < wordsize; j++)
        {
            if (guess[i] != choice[i] && guess[i] == choice[j])
                status[i] = CLOSE;
        }
        if (guess[i] == choice[i])
        {
            status[i] = EXACT;
        }
        //wprintf(L"G: %lc|S: %i|C: %lc\n", guess[i], status[i], choice[i]);
    }
    for (int j = 0; j < wordsize; j++)
    {
        score += status[j];
        // wprintf(L"Score - %i\n", score);
    }
    return score;
}

void print_wchar_word(wchar_t *guess, int wordsize, int status[])
{
    // print word character-for-character with correct color coding, then reset terminal font to normal
    for (int i = 0; i < wordsize; i++)
    {
        if (status[i] == 1)
        {
            wprintf(YELLOW L"%lc" RESET, guess[i]);
        }
        else if (status[i] == 2)
        {
            wprintf(GREEN L"%lc" RESET, guess[i]);
        }
        else
        {
            wprintf(L"%lc", guess[i]);
        }
    }

    wprintf(L"\n");
    return;
}
