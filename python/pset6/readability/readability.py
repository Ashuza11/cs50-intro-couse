###

# credit.py

# M. Ashuza

# A program for validating credit card numbers.

###
from cs50 import get_string

num_words, num_letters, num_sentences = 0, 0, 0
# Get user input
s = get_string("Text: ").strip()  # " progarmming " -> "progarmming"

# Iterate over every single letter
# to count num of letter, words and sentences
for i in range(len(s)):
    if (i == 0 and s[i] != " ") or (i != len(s) - 1 and s[i] == " " and s[i + 1] != " "):
        num_words += 1
    if s[i].isalpha():
        num_letters += 1
    if s[i] == "." or s[i] == "!" or s[i] == "?":
        num_sentences += 1

# Calculate using the Coleman-Liau index
L = num_letters / num_words * 100
S = num_sentences / num_words * 100
index = round(0.0588 * L - 0.296 * S - 15.8)

# Print the grade level
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")

