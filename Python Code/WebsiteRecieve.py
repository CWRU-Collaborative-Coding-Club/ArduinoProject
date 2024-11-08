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
def arduino(input):
    send(f"{input}")
    return f"{input}"
    
if __name__ == '__main__':
    app.run(debug=True, port=5000)
    

