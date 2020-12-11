# A program that first asks the user how much change is owed
# and then spits out the minimum number of coins
# Author M. Ashuza

from cs50 import get_float

# Get User' input
while True:
    dollars = get_float("Change owed: ")
    if dollars >= 0:
        break

cents = round(dollars * 100)
coins = 0

denom = [25, 10, 5, 1]
drawers = 4

# User of greedy algorithms
for i in denom:
    # using the division in stead of substracting
    coins += cents // i
    cents %= i

print(coins)
