#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

void gradeCalculation(string t);
int lettersCalc(string t, int l);
int wordsCalc(string t, int l);
int sentencesCalc(string t, int l);

int main(void)
{
    string text = get_string("Text: ");

    gradeCalculation(text);
}

void gradeCalculation(string t)
{
    int length = strlen(t);
    int count_letters = lettersCalc(t, length);
    int count_words = wordsCalc(t, length);
    int count_sentences = sentencesCalc(t, length);

    float average_of_letters = (float) count_letters / count_words * 100;
    float average_of_sentences = (float) count_sentences / count_words * 100;
    int index = round(0.0588 * average_of_letters - 0.296 * average_of_sentences - 15.8);

    // OUTPUT
    if (index > 16)
        printf("Grade 16+\n");
    else if (index < 1)
        printf("Before Grade 1\n");
    else
        printf("Grade %i\n", index);
}

int lettersCalc(string t, int l)
{
    int count = 0;
    for (int i = 0; i < l; i++)
    {
        if (isalpha(tolower(t[i])))
        {
            count++;
        }
    }
    return count;
}

// Looking for space signs
int wordsCalc(string t, int l)
{
    int count = 0;
    for (int i = 0; i < l; i++)
    {
        if ((int) t[i] == 32)
        {
            count++;
        }
    }
    return count + 1;
}

// We are looking for "!" "." and "?" in the text which signal to us about the completion of the sentence
int sentencesCalc(string t, int l)
{
    int count = 0;
    for (int i = 0; i < l; i++)
    {
        if ((int) t[i] == '!' || (int) t[i] == '.' || (int) t[i] == '?')
        {
            count++;
        }
    }
    return count;
}
