###

# credit.py

# M. Ashuza

# A program for validating credit card numbers.

###
from cs50 import get_int


def main():
    # Get the cc_number
    while True:
        cc_number = get_int("Number: ")
        if cc_number >= 0:
            break

    # Check validity of card brand
    if check_validity(cc_number):
        print_ccn_brand(cc_number)
    else:
        print("INVALID")


def check_validity(ccn):
    return checkSum(ccn)


def checkSum(ccn):
    sum = 0
    # Converting ccn into a string
    # 1037 -> "1037"
    # Get the value from 0 up to lenht of str -1
    for i in range(len(str(ccn))):
        if (i % 2 == 0):
            sum += ccn % 10
        else:
            # 2 * 9 = 18
            digit = 2 * (ccn % 10)
            # break that 18 as 1 + 8
            sum += digit // 10 + digit % 10
        ccn //= 10  # ccn needs to be reduced so that to move one digit over

    return sum % 10 == 0


# Print the card brand
def print_ccn_brand(ccn):
    # American express brand
    if (ccn >= 34e13 and ccn < 35e13) or (ccn >= 37e13 and ccn < 38e13):
        print("AMEX")
    elif ccn >= 51e14 and ccn < 56e14:
        print("MASTERCARD")
    elif (ccn >= 4e12 and ccn < 5e12) or (ccn >= 4e15 and ccn < 5e15):
        print("VISA")
    else:
        print("INVALID")


# Python syntax for runing the main function
if __name__ == "__main__":
    main()
