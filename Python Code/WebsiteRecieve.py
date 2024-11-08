from flask import Flask
from markupsafe import escape
from ArduinoSend import send


app = Flask(__name__)
@app.route("/<name>")
def hello(name):
    return f"Hello, {escape(name)}!"

@app.route("/")
def hello_world():
    return "<p>Hello, World!</p>"

@app.route('/iot/<path:input>')
def arduino(path):
    send(f"{path}")
    return f"{input}"
    

