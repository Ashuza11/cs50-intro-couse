###
#
# Program: Houses.py
# Inport.py
# Autor: M. Ashuza
#
# A Progam for inporting data from a CSV file
#
###

# TODO
from cs50 import SQL
from sys import argv, exit
import csv

# Split_fonc: "Harry James Potter" -> ["Harry", "James", "Potter"] or
# if not middle name -> ["Harry", "none", "Potter"]


def Split_full_name(full_name):
    names = full_name.split()
    return names if len(names) >= 3 else [names[0], None, names[1]]


# Check for command-line arguments(argv)
if len(argv) != 2:
    print("Incorrect Number of Arguments")
    exit(1)

db = SQL("sqlite:///students.db")
csv_File = argv[1]

# Open CSV file given by command line argument
with open(csv_File) as csv_file:
    reader = csv.DictReader(csv_file)
    # For each parse name
    for row in reader:
        names = Split_full_name(row["name"])
        row["house"]
        row["birth"]
        # Insert each student into the students table of students.db
        # Structure of db: #id #Harry #James #Potter #house #birth
        db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                   names[0], names[1], names[2], row["house"], row["birth"])

