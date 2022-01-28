import sqlite3
from app_constant import DATABASE 

class sample:
    def __init__(self,scanner,beacon,distance):
        self.scanner = scanner
        self.beacon = beacon 
        self.distance = distance

class samples:
    COLUMN_NAMES = ["SCANNER","BEACON","DISTANCE"]
    conn = None
    def __init__(self,db_path):
        if db_path == "":
            raise ValueError
        
        try :
            self.conn = sqlite3.connect(db_path,check_same_thread=False)
        except ConnectionError:
            raise 
        self.cur = self.conn.cursor()
        query = "CREATE TABLE IF NOT EXISTS SAMPLES( ID	INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT,Timestamp DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL,SCANNER VARVHAR(32),BEACON VARVHAR(32), DISTANCE INTEGER NOT NULL,FOREIGN KEY(beacon) references BEACONS(UserName));"
            
        self.cur.execute(query)
        

    def add_sample(self,sample) :
	 
        query = "INSERT INTO SAMPLES (" + self.COLUMN_NAMES[0]
        var_field = "(?"
        for col in self.COLUMN_NAMES[1:] :
            query +=   " , " + col 
            var_field += ",?"

        query += ") values " + var_field +")"

        self.cur.execute(query,(sample.scanner,sample.beacon,sample.distance))
 