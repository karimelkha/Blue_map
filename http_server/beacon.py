

import sqlite3
from app_constant import DATABASE 

class beacons:
    COLUMN_NAMES = ["UserName"]
    
    conn = None
    def __init__(self,db_path = DATABASE):
        if db_path == "":
            raise ValueError
        
        try :
            self.conn = sqlite3.connect(db_path, check_same_thread=False)
        except ConnectionError:
            raise 
        self.cur = self.conn.cursor()
        query = "CREATE TABLE IF NOT EXISTS BEACONS( UserName VARCHAR(32) PRIMARY KEY UNIQUE );"
            
        self.cur.execute(query)
    
    def all_beacon(self):

        query = "SELECT * FROM BEACONS "
        fields = self.cur.execute(query).fetchall()
        ret = []
        for field in fields :
            ret.append(field[0])
        return ret

            
    def retrieve_beacon(self,beacon_name):
        if beacon_name == "" :
            raise ValueError

        query = "SELECT * FROM BEACONS WHERE UserName = '" +beacon_name +"'"
        fields = self.cur.execute(query).fetchall()
        if fields[0][0] != None:
            return fields[0][0] 
        else :
            return None
    
    def add_beacon(self,beacon_name,seq_nr=0) :

        query = "INSERT INTO BEACONS (" +beacons.COLUMN_NAMES[0]
        var_field = "(?"
        for col in beacons.COLUMN_NAMES[1:] :
            query +=   " , " + col 
            var_field += ",?"

        query += ") values " + var_field +")"
        try :
            self.cur.execute(query,(beacon_name,))
        except sqlite3.IntegrityError :
            print("User already in the database")
        self.conn.commit()
