import os

from cs50 import SQL
from flask import Flask, render_template, request, session, redirect, flash
from flask_session import Session
from tempfile import mkdtemp
from cs50 import SQL
from datetime import datetime
import smtplib
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import login_required

# Configure application
app = Flask(__name__)

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


# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///users.db")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")

        # Ensure username & password was submitted
        if not username or not password:
            error_statement = "All fields required..."
            return render_template("login.html", error_statement=error_statement,
            usernamee=username, password=password)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            error_statement = "Invalid Username/Password..."
            return render_template("login.html", error_statement=error_statement,
            usernamee=username, password=password)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    return render_template("login.html")

@app.route('/')
@login_required
def index():
    # User reached route via GET (as by clicking a link or via redirect)
    return render_template("index.html")


@app.route('/register', methods=["GET", "POST"])
def register():
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username & password was submitted
        if not username or not password or not confirmation:
            error_statement = "All fields required..."
            return render_template("register.html", error_statement=error_statement,
            usernamee=username, password=password, confirmation=confirmation)

        # Ensure password & confirmation match
        elif not confirmation == password:
            error_statement = "Passwords Do Not Match..."
            return render_template("register.html", error_statement=error_statement,
            user_id=user_id, usernamee=username, password=password, confirmation=confirmation)

        # hash password imput by user
        hash = generate_password_hash(password)

        # Check if username exist in database and insert
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
            return redirect("/")

        # If username exists return error
        except:
            error_statement = "Username already exists..."
            return render_template("register.html", error_statement=error_statement,
            username=username, password=password, confirmation=confirmation)

    # User reached route via GET (as by clicking a link)
    return render_template("register.html")


@app.route('/subscribe', methods=["GET", "POST"])
@login_required
def subscribe():

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        user_id = session["user_id"]
        first_name = request.form.get("first_name")
        last_name = request.form.get("last_name")
        email = request.form.get("email")

        #Send reqest to gmail, alert user, alert my email to new subscription
        message = "You have been subcribed to our newsletter."
        server = smtplib.SMTP("smtp.gmail.com", 587)
        server.starttls()
        server.login("cgiyard@gmail.com", "##########")
        server.sendmail("cgiyard@gmail.com", email, message)

        # Ensure first name last name & email entered
        if not first_name or not last_name or not email:
            error_statement = "All fields required..."
            return render_template("subscribe.html", error_statement=error_statement,
            first_name=first_name, last_name=last_name, email=email)

        # Check if first name last name & email exist in database and insert
        try:
            db.execute("INSERT INTO subscriptions (user_id, first_name, last_name, email) VALUES (?, ?, ?, ?)", user_id, first_name, last_name, email)
            return redirect("/form")

        # If first name last name or email exist, return error
        except:
            error_statement = "Firstname/Lastname/email already exists..."
            return render_template("subscribe.html", error_statement=error_statement,
            first_name=first_name, last_name=last_name, email=email)

    # User reached route via GET (as by clicking a link)
    return render_template("subscribe.html")

@app.route('/blockchain')
@login_required
def blockchain():
    # User reached route via GET (as by clicking a link)
    return render_template("blockchain.html")

@app.route('/cryptocurrency')
@login_required
def cryptocurrency():
    # User reached route via GET (as by clicking a link)
    return render_template("cryptocurrency.html")

@app.route('/defi')
@login_required
def defi():
    # User reached route via GET (as by clicking a link)
    return render_template("defi.html")

@app.route('/nfts')
@login_required
def nfts():
    # User reached route via GET (as by clicking a link)
    return render_template("nfts.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to homepage
    return redirect("/")

@app.route('/form')
@login_required
def form():
    """Thank user"""
    # User reached route via GET (as by filling out subscription form)
    if request.method == "GET":
        message = "Thank you for subscribing."
        return render_template("form.html", message=message)

    return render_template("form.html")


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change():
    """Change user password"""

    # User reached route via GET (as by clicking a link)
    if request.method == "GET":
        return render_template("password.html")
    else:
        password = request.form.get("password")

        # Ensure password entered
        if password == "":
            error_statement = "All fields required..."
            return error_statement

        # generate new password hash
        p_hash = generate_password_hash(password)

        # Update users new password
        db.execute("UPDATE users SET hash = ? WHERE id = ?",p_hash, session["user_id"])

        # Redirect user to the login homepage
        return redirect("/login")
