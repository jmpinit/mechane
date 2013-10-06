import socket
import json

HOST = '18.238.6.197'    # The remote host
PORT = 7000              # The same port as used by the server
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
s.send('Hello, world')
buf = ""
while True:
	# buf += s.recv (1024)
	# if '\n' in buf:
	# 	item = json.loads(buf[:])
	data = s.recv(1024)
	# print json.dumps(data)
	# print json.loads(data)[0]["x"]
	try:
		if json.loads(data)["z"] == True:
			print "Z AXIS ENGAGE"
		if json.loads(data)["z"] == False:
			print "Z AXIS RETRACT"
	except:
		pass

	try:
		print '(' + str(json.loads(data)["x"]) + ', ' + str(json.loads(data)["y"]) + ')'
	except:
		pass
	# for item in json.loads(data):
		# print '(' + str(item["x"]) + ', ' + str(item["y"]) + ')'
	if data == "":
		break




