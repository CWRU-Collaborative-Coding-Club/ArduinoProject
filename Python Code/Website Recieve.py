from flask import Flask
from markupsafe import escape


app = Flask(__name__)
@app.route("/<name>")
def hello(name):
    return f"Hello, {escape(name)}!"

@app.route("/")
def hello_world():
    return "<p>Hello, World!</p>"

@app.route('/arduino/<int:arduino_id>/<int:red>/<int:green>/<int:blue>')
def arduino(arduino_id, red, green, blue):
    return f"Arduino ID: {escape(arduino_id)}, Red: {escape(red)}, Green: {escape(green)}, Blue: {escape(blue)})"

