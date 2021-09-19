from flask import Flask, request
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

app.run(host='0.0.0.0', port=8080)