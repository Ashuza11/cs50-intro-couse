#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    // Prompt user For height
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8); // If height is less than 1 or greater than 8 (or not an integer at all)

    // Iterate from 1 through height:
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        for (int j = 0; j < 2; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
