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

#   @app.route('/iot/<path:input>')
#   def iot(input):
#       send(f"{escape(input)}")
#       return f"{escape(input)}"
    
@app.route('/iot', methods=['POST'])
def iotPost():
    requestData = request.json
    send(str(requestData))
    return requestData

if __name__ == '__main__':
    app.run(debug=True, port=5000)
    

