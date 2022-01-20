#!/usr/bin/python3
from flask import Flask, render_template, request, g
import sqlite3
from app_constant import DATABASE 
from beacon import *
from positions import *
app = Flask(__name__)

db_access = None
  
def init_func(smtg):
    with app.app_context():
        db = getattr(g, '_database', None)
        if db is None:
            db = g._database = sqlite3.connect(DATABASE)
        db_access = db
        bcs = beacons(DATABASE)
        pts = positions(DATABASE)
        bcs.add_beacon("ESP_PE")


@app.before_first_request(init_func)

@app.teardown_appcontext
def close_connection(exception):
    db = getattr(g, '_database', None)
    if db is not None:
        db.close()



@app.route("/")
def home():
    return render_template("index.html")
    



@app.route('/data', methods=['POST', 'GET'])
def data():
    error = None
    if request.method == 'POST':
        cur = get_db().cursor()
        content = request.json
        if retrieve_beacon(content["bId"]):
            print("beacon retrouvé")
        
        print(content["bId"])
        print(content["sId"])
        print(content["D"])

    
    # Return HTTP Code if not in db
    return "ok"

    
if __name__ == '__main__':
    before_first_request_func()
    app.run()

#export FLASK_APP=http_serv && export FLASK_RUN_HOST="localhost" && export FLASK_RUN_PORT="5000" && flask run