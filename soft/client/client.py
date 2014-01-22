import socket
import json
import math
import serial

# ser1 = serial.Serial("/dev/tty.LeftMotor-RNI-SPP")  # open first serial port
# ser2 = serial.Serial("/dev/tty.usbmodem1421")

def convert(x,y):  #opens a URL and gets the result
	# print x
	# print y
	A = 1625-(900-2*y)
	b1 = 650 + 2*x
	b2 = 2900 - b1

	l1 = math.sqrt( (math.pow(A, 2)+math.pow(b1, 2)) )
	l2 = math.sqrt( (math.pow(A, 2)+math.pow(b2, 2)) )
	# print l1
	# print l2

	return {"l1": l1, "l2": l2}

HOST = 'localhost'    # The remote host
PORT = 7000              # The same port as used by the server
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
s.send('Hello, world')

previous = {"l1": 2177, "l2": 2177, "x": 400, "y": 450}
delta = {"l1": 0, "l2": 0, "x": 0, "y": 0}

while True:
	data = s.recv(1024)
	print data
	# try:
	# 	pass
	# 	#if json.loads(data)["z"] == True:
	# 		#print "Z AXIS ENGAGE"
	# 	#if json.loads(data)["z"] == False:
	# 		#print "Z AXIS RETRACT"
	# except:
	# 	pass

	# try:

	# 	new = convert(json.loads(data)["x"],json.loads(data)["y"])


	# 	delta["l1"] = new["l1"]-previous["l1"]
	# 	delta["l2"] = new["l2"]-previous["l2"]
	# 	delta["x"] = new["x"]-previous["x"]
	# 	delta["y"] = new["y"]-previous["y"]

	# 	#print "New " + "(" + str(int(new["l1"])) + ", " + str(int(new["l2"]))+ ")"
	# 	# print "Old " + str(int(previous["l1"])) + ", " + str(int(previous["l2"]))
	# 	#print "Delta " + "(" + str(int(delta["l1"])) + ", " + str(int(delta["l2"]))+ ")"

	# 	previous = new;

	# 	print delta["y"]

	# 	if(delta["y"] > 0):
	# 		msg = str(int(delta["y"]))+",1,100\n"
	# 		ser1.write(msg)
	# 		print msg
	# 	else:
	# 		msg = str(int(abs(delta["y"])))+",0,100\n"
	# 		ser1.write(msg)
	# 		print msg

	# 	if(delta["x"] > 0):
	# 		msg = str(int(delta["y"]))+",1,100\n"
	# 		ser2.write(msg)
	# 		print msg
	# 	else:
	# 		msg = str(int(abs(delta["y"])))+",0,100\n"
	# 		ser2.write(msg)
	# 		print msg

	# 	# print '(' + str(json.loads(data)["x"]) + ', ' + str(json.loads(data)["y"]) + ')'
	# 	# print '(' + str(convert(json.loads(data)["x"],json.loads(data)["y"])["l1"]) + ', ' + str(convert(json.loads(data)["x"],json.loads(data)["y"])["l2"]) + ')'
	# 	print '\n'
	# except:
	# 	pass
	# # previous = 
	# # for item in json.loads(data):
	# 	# print '(' + str(item["x"]) + ', ' + str(item["y"]) + ')'
	# if data == "":
	# 	break





