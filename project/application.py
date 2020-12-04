import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException
from werkzeug.security import check_password_hash, generate_password_hash
#from flask_mail import Mail, Message

from helpers import apology, login_required

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# # Configure session to use Mailsystem by storing data securely
# app.config["MAIL_DEFAULT_SENDER"] = os.getenv("MAIL_DEFAULT_SENDER")
# app.config["MAIL_PASSWORD"] = os.getenv("MAIL_PASSWORD")
# app.config["MAIL_PORT"] = 587
# app.config["MAIL_SERVER"] = "smtp.gmail.com"
# app.config["MAIL_USE_TLS"] = True
# app.config["MAIL_USERNAME"] = os.getenv("MAIL_USERNAME")
# mail = Mail(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///register.db")

# Evoid redondemcy by using is_provided function
def is_provided(field):
    if not request.form.get(field):
        return apology(f"Must provide {field}", 403)


# All Route
@app.route("/")
def index():
    """Show Home page"""
    return render_template("index.html")


@app.route("/course")
def course():
    """Show Resources"""
    return render_template("course.html")

@app.route("/course1")
def course1():
    """Show Resources"""
    return render_template("course1.html")


@app.route("/course2")
def course2():
    """Show Resources"""
    return render_template("course2.html")


@app.route("/online_courses")
def online_courses():
    """Show Resources"""
    return render_template("online_courses.html")

@app.route("/videos")
def videos():
    """Show Resources"""
    return render_template("videos.html")

@app.route("/contact")
def contact():
    """Show Resources"""
    return render_template("contact.html")

# Dictionaries for selected menu
FACULTY = [
    "Faculty of Theology",
    "Faculty of Low",
    "Faculty of Economics",
    "Faculty of Health and Community Development",
    "Faculty of Technology and Applied Sciences",
    "Faculty of Medicine"
]

LEVELS = [
    "Frechman/First-year student/G0",
    "Frechman/First-year student/G1",
    "Sophomore/Second-year student/G2",
    "Junior/G3",
    "Senior/L1/Tech1"
]


@app.route("/register", methods=["GET", "POST"])
def register():
    """"register user"""

    if request.method == "POST":
        # Ensure name, faculty, level, phonenumber and email where provided
        result_check = is_provided("username") or is_provided("password") or is_provided("confirmation") or is_provided("email") or is_provided("phone")

        if request.form.get("faculty") not in FACULTY or request.form.get("level") not in LEVELS:
            return apology("invalid faculty and/or level", 403)


        # Ensure the user fill in the form
        if result_check != None:
            return result_check

        # Ensure password and confirmation match
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords must match")

        # # Send th comfirmation mail to new members
        # message = Message("You are registered!", recipients=[email])
        # mail.send(message)

        # Query database for registering uers
        try:
                personal_info = db.execute("INSERT INTO users (username, hash, gender) VALUES (:username, :hash, :gender)",
                    username=request.form.get("username"),
                    hash=generate_password_hash(request.form.get("password")),
                    gender=request.form.get("gender"))


                academic_info = db.execute("INSERT INTO registrants (faculty, level, phone, email, user_id) VALUES (:faculty, :level, :phone, :email, :user_id)",
                    faculty=request.form.get("faculty"),
                    level=request.form.get("level"),
                    phone=request.form.get("phone"),
                    email=request.form.get("email"),
                    user_id = personal_info);
        except:
           return apology("username already exixt", 403)

        if personal_info is None:
            return apology("registration error", 403)

        if academic_info is None:
            return apology("registration error", 403)
        # Remember which user has logged in
        session["user_id"] = personal_info

        # flash("Registered!")
        return redirect("/")
    else:
        return render_template("register.html", faculty=FACULTY, level=LEVELS)




@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username and password was submitted
        result_check = is_provided("username") or is_provided("password")
        if result_check is not None:
            return result_check

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out"""
    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")

