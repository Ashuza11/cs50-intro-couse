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
int find_lenght(long long n);

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
    // check the length brand
    int len = find_lenght(cc_number);
    return (len == 13 || len == 15 || len == 16) && checksum(cc_number);
}

// Get the lenght of the ccnumber
int find_lenght(long long n)
{
    int len;
    for (len = 0; n != 0; n /= 10)
    {
        len++;
    }
    return len;
}

// Luhn’s Algorithm /check sum

bool checksum(long long cc_n)
{
    int sum = 0;
    for (int i = 0; cc_n != 0; i++, cc_n /= 10)
    {
        if (i % 2 == 0)
        {
            sum += cc_n % 10; 
        }
        else
        {
            int digit = 2 * (cc_n % 10); // Multiply every other digit by 2
            sum += digit / 10 + digit % 10;
        }
    }
    return (sum % 10) == 0;
}

// Print the brand
void print_cc_number(long long cc_n)
{
    if ((cc_n >= 34e13 && cc_n < 35e13) || (cc_n >= 37e13 && cc_n < 38e13))
    {
        printf("AMEX\n");
    }
    else if (cc_n >= 51e14 && cc_n < 56e14)
    {
        printf("MASTERCARD\n");
    }
    else if ((cc_n >= 4e12 && cc_n < 5e12) || (cc_n >= 4e15 && cc_n < 5e15))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}



