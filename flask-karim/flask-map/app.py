from flask import Flask, render_template
import sqlite3 as sql


app = Flask(__name__)

@app.route('/')
def home():
   return render_template('test.html')
if __name__ == '__main__':
   app.run()