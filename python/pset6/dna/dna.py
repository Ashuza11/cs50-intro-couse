###

# Dna.py

# M. Ashuza

# A program that identifies a person based on their DNA

###
from sys import argv, exit
import csv


def Compute_longest_num_of_cons_seq_repeats(s, sub):
    # Calculate the maximun num of times a substring is repeated
    # O(len(s)): time complesty O(len(s)): Memory space
    ans = [0] * len(s)
    for i in range(len(s) - len(sub), - 1, -1):
        if s[i: i + len(sub)] == sub:
            if i + len(sub) > len(s) - 1:
                ans[i] = 1
            else:
                ans[i] = 1 + ans[i + len(sub)]
    return max(ans)


def print_match(reader, actual):
    for line in reader:
        person = line[0]
        values = [int(val) for val in line[1:]]
        if values == actual:
            print(person)
            return
    print("No match")


def main():
    # Check for argv lenght
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    databases = argv[1]
    # For each STR Open CSV file and DNA sequence
    # Read contents into memory
    with open(databases) as csv_file:
        reader = csv.reader(csv_file)
        all_seq = next(reader)[1:]

        sequences = argv[2]
        with open(sequences) as txt_file:
            s = txt_file.read()

            # Compute the longest num of consecutive repeats int DNA sequence
            actual = [Compute_longest_num_of_cons_seq_repeats(s, seq) for seq in all_seq]

        # Compare STRs counts against each row in the CSV file
        print_match(reader, actual)


# Python syntax for runing the main function
if __name__ == "__main__":
    main()
