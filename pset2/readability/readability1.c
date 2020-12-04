/**

  * Readability

  * M. Ashuza

  * A program that computes the approximate grade level needed.

  **/

#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    string s = get_string("Text: ");

    int num_of_word, num_of_sentences, num_of_letters;
    num_of_word = 1;
    num_of_sentences = num_of_letters = 0;

    // Couting the number of L, S, and W

    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (isalpha(s[i]))
        {
            num_of_letters++;
        }
        if ((i == 0 && s[i] != ' ') || (i != len - 1 && s[i] == ' ' && s[i + 1] != ' '))
        {
            num_of_word++;
        }
        if (s[i] == ',' || s[i] == '?' || s[i] == '!')
        {
            num_of_sentences++;
        }
    }

    // Doind the math
    float L = (num_of_letters / (float) num_of_word) * 100;
    float S = (num_of_sentences / (float) num_of_word) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Print the result
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (idenx >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}