#!/usr/bin/python3
from flask import Flask, render_template, request, g
import sqlite3
from app_constant import DATABASE 
from beacon import *
from positions import *
from samples import *
app = Flask(__name__)

db_access = None
bcs = None
pts = None
smps = None

def init_func(smtg=""):
    global db_access,bcs,pts,smps
    with app.app_context():
        db = getattr(g, '_database', None)
        if db is None:
            db = g._database = sqlite3.connect(DATABASE)
        db_access = db
        bcs = beacons(DATABASE)
        pts = positions(DATABASE)
        smps = samples(DATABASE)

        bcs.add_beacon("ESP_PE")
        


@app.before_first_request(init_func)

# @app.teardown_appcontext
# def close_connection(exception):
#     db = getattr(g, '_database', None)
#     if db is not None:
#         db.close()



@app.route("/")
def home():
    if request.method == 'POST':
        print("Tried POST query")
    return render_template("index.html")




@app.route('/data', methods=['POST', 'GET'])
def data():
    error = None
    if request.method == 'POST':
        cur = db_access.cursor()
        content = request.json
        if bcs.retrieve_beacon(content["B"]):
            print("Beacon : " + content["B"])
            print("Scanner : " + content["S"])
            print("Distance : " + content["D"])
        else :
            return "Beacon not found",404        
    rx_smp = sample(content["B"],content["S"],content["D"])
    smps.add_sample(rx_smp)
    # Return HTTP Code if not in db
    return "ok",200

    
if __name__ == '__main__':
    before_first_request_func()
    app.run()

#export FLASK_APP=http_serv && export FLASK_RUN_HOST="localhost" && export FLASK_RUN_PORT="5000" && flask run