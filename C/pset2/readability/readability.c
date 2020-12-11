/**

  * Readability

  * M. Ashuza

  * A program that computes the approximate grade level needed.

  **/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string s = get_string("Text: ");
    int num_of_letters = 0;
    int num_of_word = 1;
    int num_of_sentences = 0;

// Count number of word sentences and letters
    for (int i = 0; i < strlen(s); i++)
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
        {
            num_of_letters++;
        }
        else if (s[i] == ' ')
        {
            num_of_word++;
        }
        else if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            num_of_sentences++;
        }
    }
// Calculate using the Coleman-Liau index
    float grade = 0.0588 * (100 * (float) num_of_letters / (float) num_of_word) - 0.296 * (100 * (float) num_of_sentences
                  / (float) num_of_word) - 15.8;
// Print the grade
    if (grade < 16 && grade >= 0)
    {
        printf("Grade %i\n", (int) round(grade));
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }

}