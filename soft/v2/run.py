import serial
import math

ser1 = serial.Serial("/dev/tty.usbserial-A4003GOG")  # open first serial port
# ser2 = serial.Serial("/dev/tty.usbmodem1421")


def position(degrees, type, id): #degrees are +/-, type is "rel" or "abs" (relative or absolute)
	pass
def velocity(speed, id): #speed isdeg/second
	pass
def pid(p, i, d, id): #first order, second order, third order
	pass #http://code.activestate.com/recipes/577231-discrete-pid-controller/

def resetCounter(id): #resets the position counter
	pass 
def digitalWrite(state, pin, id): #sets one of the extra pins to high or low
	pass

def holdPosition(id):
	pass #tells motor controller to keep current position via feedback

def getInfo(id): #enter "all" for id to get all information
 # returns a json object including the following information
 # - battery level
 # - current speed/direction
 # - current position from start 
 # - digital input (high/low)
 	pass

def move1d(distance, id): #moves one motor a given amount in degrees
	position(distance, "rel", id)
	return None

def move2d(x, y, separation, l1, l2, type, id1, id2): #x, y, separation, l1, l2 are in degrees
	# x is desired x motion (parallel to line of motors), y is desired y motion (perpendicular to line of motors)
	# separation is distance apart, necessary for math
	# l1 is degree extension of the first motor, l2 is degree extension of second motor
	# id1 and id2 are the two motors in question

	if type == "abs":
		target = convert(x, y, separation)

		print target["l1"] - l1
		print target["l2"] - l2

		position(target["l1"] - l1, "rel", id1)
		position(target["l2"] - l2, "rel", id1)
	if type == "rel":
		pass
	return None

def convert(x,y,separation): 
	#x measured from leftmost motor, y starts at 0 and increases downwards
	#basically: a^2 + b^2 = c^2, they share an "a" value
	#Both sides have different b values, and different calulated c (length) values

	a = y
	b1 = x
	b2 = separation - b1

	l1 = math.sqrt( (math.pow(a, 2)+math.pow(b1, 2)) )
	l2 = math.sqrt( (math.pow(a, 2)+math.pow(b2, 2)) )

	return {"l1": l1, "l2": l2}

move2d(10,10,100,50,50,"abs",1,2)

def move2dDrawbot():
	input("Place the two motors together. Press Enter to continue...")
	input("Leaving one motor unchanged, extend the second to it's furthest position. Be sure to only extend the string on the second motor. Press Enter to continue...")
	#gets the difference in degree revolution of the second motor, this is the 100% length measure
	pass

def drawBitmap():
	# rastarizes a bmp file
	pass

# def convert(l1,l2,separation): 
# 	#x measured from leftmost motor, y starts at 0 and increases downwards
# 	#basically: a^2 + b^2 = c^2, they share an "a" value
# 	#Both sides have different b values, and different calulated c (length) values
# 	a = y
# 	b1 = x
# 	b2 = separation - b1
# 	l1 = math.sqrt( (math.pow(a, 2)+math.pow(b1, 2)) )
# 	l2 = math.sqrt( (math.pow(a, 2)+math.pow(b2, 2)) )
# 	return {"l1": l1, "l2": l2}
