import socket
import json

HOST = '18.238.6.197'    # The remote host
PORT = 7000              # The same port as used by the server
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
s.send('Hello, world')
while True:
	data = s.recv(1024)
	# print json.dumps(data)
	# print json.loads(data)[0]["x"]
	for item in json.loads(data):
		print '(' + str(item["x"]) + ', ' + str(item["y"]) + ')'
	if data == "":
		break




