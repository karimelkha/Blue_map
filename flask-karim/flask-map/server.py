import SocketServer
from BaseHTTPServer import BaseHTTPRequestHandler
import json



def send_data():
	x=1
	y=1
	return x,y    

class MyHandler(BaseHTTPRequestHandler):
    def do_GET(self):

        # Insert your code here
        a,b = send_data()
        data_set = {"x" : a, "y" : b}
        json_dump = json.dumps(data_set)
        json_object = json.loads(json_dump)
        self.send_response(200)
        self.wfile.write(json_object)
        return MyHandler

httpd = SocketServer.TCPServer(("", 80), MyHandler)
httpd.serve_forever()
