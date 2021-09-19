from flask import Flask, request
app = Flask('app')

@app.route('/')
def intro():
  return 'Moonscape API'

@app.route('/input', methods = ['GET'])
def input():
  if request.method == 'GET':
    sleep = request.args.get('sleep')
  return sleep

app.run(host='0.0.0.0', port=8080)