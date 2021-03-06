import sqlite3
from app_constant import DATABASE 

class position:
    def __init__(self,D1,D2,D3,beacon):
        self.D1 = D1
        self.D2 = D2
        self.D3 = D3
        self.beacon = beacon


class positions:
    COLUMN_NAMES = ["SequenceN","X","Y","beacon"]
    conn = None
    def __init__(self,db_path):
        if db_path == "":
            raise ValueError
        
        try :
            self.conn = sqlite3.connect(db_path)
        except ConnectionError:
            raise 
        self.cur = self.conn.cursor()
        query = "CREATE TABLE IF NOT EXISTS POSITIONS( ID	INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT, SequenceN INTEGER NOT NULL, X NOT NULL, Y INTEGER NOT NULL,Timestamp DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL,beacon VARCHAR(32),FOREIGN KEY(beacon) references BEACONS(UserName));"
            
        self.cur.execute(query)
        

    def add_position(self,beacon_name) :
	 
        query = "INSERT INTO POSITIONS (" +COLUMN_NAMES[0]
        var_field = "(?"
        for col in COLUMN_NAMES[1:] :
            query +=   " , " + col 
            var_field += ",?"

        query += ") values " + var_field +")"

        self.cur.execute(query,(usr.name,usr.password,usr.pubkey,usr.ip))
    #     self.conn.commit()

    # def get_user(self,usr_name) :
    #     """ Return an app_user from the database
	# 	Args:
	# 	usr_name (String) : the name of the user we want to retrieve
		
	# 	Returns:
    #         appUser: the user retrieved from the database
	# """ 
    #     query = "SELECT * FROM "+self.owner.name+" WHERE "+USERNAME_COL_NAME + " = '" +usr_name +"'"
    #     fields = self.cur.execute(query).fetchall()
    #     print(fields[0])
    #     return app_user(fields[0][0],fields[0][1],fields[0][2],fields[0][3])

    # def get_users(self) :
    #     """ Return all the app users from the database

	# 	Returns:
    #         appUser[]: the users retrieved from the database
	# """ 
    #     query = "SELECT * FROM "+self.owner.name
    #     fields = self.cur.execute(query).fetchall()
    #     users = []
    #     for usr_info in fields :
    #         users.append(app_user(usr_info[0],usr_info[1],usr_info[2],usr_info[3]))

    #     return users