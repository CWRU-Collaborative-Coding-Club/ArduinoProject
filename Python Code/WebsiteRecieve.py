from flask import Flask, request
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
def iot(input):
    send(f"{input}")
    return f"{input}"
    
@app.route('/iotPOST', methods=['POST'])
def iotPOST():
    request_data = request.get_json()
    send(f"{request_data}")
    return f"{request_data}"
    
if __name__ == '__main__':
    app.run(debug=True, port=5000)
    

