###
#
# Program: Houses.py
# Roster.py
# Autor: M. Ashuza
#
# A program that prints a list of students for a given house in alphabetical order
#
###

# TODO
from sys import argv, exit
from cs50 import SQL

# Check commnand-line arguments
if len(argv) != 2:
    print("Incorrect Number of Arguments")
    exit(1)

# Query data base for all student in house
db = SQL("sqlite:///students.db")
students_house = argv[1]
rows = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", students_house)
# Print out each student's full name and birth year
for row in rows:
    if row["middle"] != None:
        print(f'{row["first"]} {row["middle"]} {row["last"]}, born {row["birth"]}')
    else:
        print(f'{row["first"]} {row["last"]}, born {row["birth"]}')