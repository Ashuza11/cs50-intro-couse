import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

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

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Query database for getting user' transaction
    rows = db.execute("""
        SELECT symbol, SUM(shares) as totalShares
        FROM transactions
        WHERE user_id = :user_id
        GROUP BY symbol
        HAVING totalShares > 0;
    """, user_id=session["user_id"])
    holdings = []

    # Loop through the data
    for row in rows:
        stock = lookup(row["symbol"])
        holdings.append({
            "symbol": stock["symbol"],
            "name": stock["name"],
            "shares": row["totalShares"],
            "price": usd(stock["price"]),
            "total": usd(stock["price"] * row["totalShares"])
        })
        grand_total += stock["price"] * row["totalShares"]
    # Query database for getting user' cash
    rows = db.execute("SELECT cash FROM users WHERE id=:user_id", user_id=session["user_id"])
    cash = rows[0]["cash"]

    return render_template("index.html", holdings=holdings, cash=usd(cash))


# Check if fieleds(names, passwords ..) are provided
def is_provided(field):
    if not request.form.get(field):
        return apology(f"Must provide {field}", 403)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Ensure symbol name and number of shares was provided
        find_missing_errors = is_provided("symbol") or is_provided("shares")
        if find_missing_errors:
            return find_missing_errors
        elif not request.form.get("shares").isdigit():
            return apology("Invalid number of shares")

        # Search for stocks
        symbol = request.form.get("symbol").upper()
        shares = int(request.form.get("shares"))
        stock = lookup(symbol)
        if stock is None:
            return apology("Invalid symbol")
        # Query database for calculating the transanction
        rows = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
        cash = rows[0]["cash"]

        updated_cash = cash - shares * stock["price"]
        if updated_cash < 0:
            return apology("can't afford")
        # Query database for updating users cash
        db.execute("UPDATE users SET cash=:updated_cash WHERE id=:id ",
                    updated_cash=updated_cash,
                    id=session["user_id"])

        # Query database for transaction
        db.execute("""
            INSERT INTO transactions
                (user_id, symbol, shares, price)
            VALUES (:user_id, :symbol, :shares, :price)

        """,
        user_id = session["user_id"],
        symbol = stock["symbol"],
        shares = shares,
        price = stock["price"]
        )
        flash("Bougth")

        # Redirect user to home page
        return redirect("/")


    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        result_of_checks = is_provided("username") or is_provided("password")

        # Ensure password was submitted
        if result_of_checks != None:
            return result_of_checks

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


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        result_check = is_provided("symbol")
        if result_check is not None:
            return result_check
        symbol = request.form.get("symbol").upper()

        # check for stock in stocks
        stock = lookup(symbol)
        if stock == None:
            return apology("Invalid Symbol", 400)

        # stock funded
        return render_template("quoted.html", stock={
            'name': stock['name'],
            'symbol': stock['symbol'],
            'price': usd(stock['price'])
        })
    else:
        return render_template("quote.html")
# Register

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username  and password was submitted
        result_of_checks = is_provided("username") or is_provided("password") or is_provided("confirmation")
        if result_of_checks != None:
            return result_of_checks
        # Ensure password and password confirmation are the same
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("password and confirmation password must match")
        try:
            # Query database for username and password hash
            prim_key = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                    username=request.form.get("username"),
                    hash=generate_password_hash(request.form.get("password")))
        except:
            return apology("username already exist", 403)

        # Remember which user has logged in
        if prim_key is None:
            return apology("Registraction Error, check if username already exists.", 403)
        session["user_id"] = prim_key
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)