import os
import datetime


from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Get the user's id
    user_id = session["user_id"]

    # Get user's stocks and shares
    holdings = db.execute(
        "SELECT stock_symbol, quantity FROM stocks WHERE user_id=?", (user_id,)
    )

    # Get user's cash balance
    cash_balance = db.execute("SELECT cash FROM users WHERE id=?", (user_id,))[0][
        "cash"
    ]

    # Lookup the current price for each stock and calculate total value
    total_holdings_value = 0
    for holding in holdings:
        symbol = holding["stock_symbol"]
        shares = holding["quantity"]
        current_price = lookup(symbol)
        if current_price is None:
            # Handle the error, e.g., by showing an error message to the user
            return apology("Failed to fetch the current price for the stock", 400)
        price = current_price["price"]
        total_value = shares * price
        holding["price"] = price
        holding["total_value"] = total_value
        holding["name"] = symbol
        total_holdings_value += total_value

    # Calculate grand total
    grand_total = float(total_holdings_value + cash_balance)
    total_holdings_value = float(total_holdings_value)
    cash_balance = float(cash_balance)

    # Render the index.html template, passing in the holdings, cash balance, and grand total
    return render_template(
        "index.html",
        holdings=holdings,
        cash_balance=cash_balance,
        grand_total=grand_total,
        total_holdings_value=total_holdings_value,
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares_str = request.form.get("shares")

        if not symbol:
            return apology("must provide symbol")
        elif not shares_str:
            return apology("must provide number of shares")
        try:
            shares = int(shares_str)
            if shares <= 0:
                return apology("must provide a valid number of shares")
        except ValueError:
            return apology("must provide a valid number of shares")

        stock = lookup(symbol)

        if stock is None:
            return apology("Invalid symbol")

        # Get the user's id
        user_id = session["user_id"]

        # Get the user's cash balance
        cash_balance = db.execute("SELECT cash FROM users WHERE id=?", (user_id,))[0][
            "cash"
        ]
        cash_balance = float(cash_balance)

        # Get the stock's price at the time of purchase
        purchase_price = float(stock["price"])

        # Get the time of the stock purchase
        purchase_date = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        # Calculate the total cost of the purchase
        total_cost = stock["price"] * shares

        # Check if the user has enough cash to make the purchase
        if total_cost > cash_balance:
            return apology("Insufficient funds")
        else:
            # Update the user's cash balance
            cash = cash_balance - total_cost
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, user_id)

            # Add the purchase to the 'stocks' database
            db.execute(
                "INSERT INTO stocks (user_id, stock_symbol, purchase_price, purchase_date, quantity) VALUES (?, ?, ?, ?, ?)",
                user_id,
                symbol,
                stock["price"],
                purchase_date,
                shares,
            )
            # Get the new quantity of the purchased stock
            new_quantity = db.execute(
                "SELECT quantity FROM stocks WHERE user_id=? AND stock_symbol=?",
                user_id,
                symbol,
            )[0]["quantity"]

            # Respond with a message indicating a successful purchase
            flash(f"You've successfully purchased {shares} shares of {symbol}!")
            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Get the user's id
    user_id = session["user_id"]

    # Fetch user's transaction history
    transactions = db.execute(
        """
    SELECT 'BUY' AS type, stock_symbol AS symbol, quantity AS shares, purchase_price AS price,
           (purchase_price * quantity) AS total_value, datetime(purchase_date, 'localtime') AS date
    FROM stocks
    WHERE user_id = ?
    UNION
    SELECT 'SELL' AS type, stock_symbol AS symbol, quantity AS shares, sell_price AS price,
           (sell_price * quantity) AS total_value, datetime(sell_date, 'localtime') AS date
    FROM stocks
    WHERE user_id = ? AND sell_date IS NOT NULL
    ORDER BY date DESC
""",
        user_id,
        user_id,
    )

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        # Ensure username was submitted
        username = request.form.get("username")
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        password = request.form.get("password")
        if not password:
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], password):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")
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
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol")
        symbol = request.form.get("symbol")
        stock = lookup(symbol)
        if stock is None:
            return apology("Invalid symbol")

        # Pass the price to the template
        price = usd(stock["price"])
        return render_template("quoted.html", stock=stock, price=price)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        # Ensure username was submitted
        username = request.form["username"]
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        password = request.form["password"]
        if not password:
            return apology("must provide password", 400)

        # Ensure password was confirmed
        confirmation = request.form["confirmation"]
        if not confirmation:
            return apology("must confirm password", 400)

        # Ensure password and confirmation match
        if password != confirmation:
            return apology("passwords do not match", 400)

        # Ensure username is not already taken
        if db.execute("SELECT * FROM users WHERE username = ?", username):
            return apology("username is already taken", 400)

        # Hash the password
        hashed_password = generate_password_hash(password)

        # Insert the user into the database
        db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            username,
            hashed_password,
        )

        # Redirect to the login page after registration
        return redirect("/login")

    else:
        # Render the registration template if method is GET
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    shares_sold = request.form.get("shares")
    if not shares_sold.isdigit() or int(shares_sold) <= 0:
        return apology("Invalid number of shares")

    # Get user's stocks and shares
    user_id = session["user_id"]
    holdings = db.execute(
        "SELECT stock_symbol, SUM(quantity) AS total_shares FROM stocks WHERE user_id=? GROUP BY stock_symbol HAVING total_shares > 0",
        (user_id,),
    )

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares_sold_str = request.form.get("shares")

        if not symbol:
            return apology("must provide symbol")
        elif not shares_sold_str:
            return apology("must provide shares")
        try:
            shares_sold = int(shares_sold_str)
            if shares_sold <= 0:
                return apology("must provide positive shares")
        except ValueError:
            return apology("must provide a valid number of shares")

        stock = lookup(symbol)

        if stock is None:
            return apology("Invalid symbol")

        # Check if the user owns enough shares to sell
        for holding in holdings:
            if (
                holding["stock_symbol"] == symbol
                and holding["total_shares"] < shares_sold
            ):
                return apology("Not enough shares to sell")

        # Get the user's cash balance
        cash_balance = db.execute("SELECT cash FROM users WHERE id=?", (user_id,))[0][
            "cash"
        ]
        cash_balance = float(cash_balance)

        # Get the stock's price at the time of sale
        sell_price = float(stock["price"])

        # Get the time of the stock sale
        sell_date = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        # Calculate the total value of the sale
        total_value = stock["price"] * shares_sold

        # Update the user's cash balance
        cash = cash_balance + total_value
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, user_id)

        # Update the user's stock quantity
        db.execute(
            "INSERT INTO stocks (user_id, stock_symbol, sell_price, sell_date, quantity) VALUES (?, ?, ?, ?, ?)",
            user_id,
            symbol,
            stock["price"],
            sell_date,
            -shares_sold,
        )

        # Get the new quantity of the sold stock
        new_quantity = db.execute(
            "SELECT SUM(quantity) AS total_shares FROM stocks WHERE user_id=? AND stock_symbol=? GROUP BY stock_symbol",
            user_id,
            symbol,
        )[0]["total_shares"]

        # Respond with a message indicating a successful sale
        flash(f"You've successfully sold {shares_sold} shares of {symbol}!")
        return redirect("/")
    else:
        return render_template("sell.html", holdings=holdings)
