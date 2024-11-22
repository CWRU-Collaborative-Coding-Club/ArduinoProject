from flask import Flask, request
from markupsafe import escape
from ArduinoSend import send
from flask_cors import CORS


app = Flask(__name__)
CORS(app)
@app.route("/<name>")
def hello(name):
    return f"Hello, {escape(name)}!"

#@app.route("/")
#def hello_world():
#    return "<p>Hello, World!</p>"

#   @app.route('/iot/<path:input>')
#   def iot(input):
#       send(f"{escape(input)}")
#       return f"{escape(input)}"
    
@app.route('/', methods=['POST'])
def iot():
    requestData = request.json
    print(requestData)
    send(str(requestData))
    return requestData

if __name__ == '__main__':
    app.run('0.0.0.0', debug=True, port=5000)