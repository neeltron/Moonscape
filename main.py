from flask import Flask, request, jsonify
from replit import db
import datetime
app = Flask('app')

@app.route('/')
def intro():
  return 'Moonscape API'

data = []

timestamp = datetime.datetime.now()
print(timestamp)

@app.route('/input', methods = ['GET'])
def input():
  if request.method == 'GET':
    sleep = request.args.get('sleep')
    timestamp = datetime.datetime.now()
    db[timestamp] = sleep
    print(timestamp)
    print(sleep)
  return sleep

@app.route('/endpoint', methods = ['GET'])
def endpoint():
  sleep_data = []
  if request.method == 'GET':
    for i in db:
      sleep_data.append({'timestamp': i, 'sleep_level': db[i]})
  return jsonify(sleep_data)

app.run(host='0.0.0.0', port=8080)
