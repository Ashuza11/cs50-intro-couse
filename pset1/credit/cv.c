/**

  * credit.c

  * M. Ashuza

  * A program for validating credit card numbers.

  **/

#include <cs50.h>
#include <math.h>
#include <stdio.h>

bool check_validity(long long cc_number);
bool checksum(long long cc_n);
void print_cc_number(long long cc_number);

int main(void)
{
       long long cc_number;
       // Get and validate user credit card number
       do
       {
           cc_number = get_long_long("Number: ");
       }
       while (cc_number < 0);

       // Check validity of the card brand
       if (check_validity(cc_number))
       {
           print_cc_number(cc_number);
       }
       else
       {
           printf("INVALID\n");
       }
}

bool check_validity(long long cc_number)
{
    // check the length 13, 15, 16
    int len;
    for (len = 0; cc_number != 0; cc_number /= 10)
    {
        len++;
    }
    return (len == 13 || len == 15 || len == 16) && checksum(cc_number);
}



//int find_lenght(long long n)

    // Finding length of card brand




// Luhn’s Algorithm /check sum

bool checksum(long long cc_n)
{
    int sum = 0;
    for (int i = 0; cc_n != 0; i++, cc_n /= 10)
    {
        if ( i % 2 == 0)
        {
            sum += cc_n % 10;
        }
        else
        {
            int digit = 2 * (cc_n % 10);
            sum += digit / 10 + digit % 10;
        }
    }
    return (sum % 10) == 0;
}

// Print the brand
void print_cc_number(long long cc_number)
{
    if ((cc_number >= 34e13 && cc_number < 35e13) || (cc_number >= 37e13 && cc_number < 38e13))
    {
        printf("AMEX\n");
    }
    else if (cc_number >= 51e14 && cc_number < 56e14)
    {
        printf("MASTERCARD\n");
    }
    else if ((cc_number >= 4e12 && cc_number < 5e12) || (cc_number >= 4e15 && cc_number < 5e15))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}