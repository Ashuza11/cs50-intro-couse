// A program that first asks the user how much change is owed
// and then spits out the minimum number of coins
//  Author M. Ashuza


#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float dollars;
    // Get user's input
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);

    int cents = round(dollars * 100);
    int coins = 0;

    int denom[] = {25, 10, 5, 1};
    int drawers = 4;

    // Use the greedy algorithms by dividing
    for (int i = 0; i < drawers; i++)
    {
        coins += cents / denom[i];
        cents %= denom[i];
    }
    printf("%i\n", coins);

}