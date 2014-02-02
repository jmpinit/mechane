#! /usr/bin/env python

import os, sys
import time
import math, cmath
from subprocess import Popen, PIPE, call
from threading import Thread
from Queue import Queue, Empty
from blessings import Terminal

import avr_fs
import util

# check arguments
args = {}
if len(sys.argv) == 4:
	args['mcu'] = sys.argv[1]
	args['freq'] = sys.argv[2]
	args['file'] = sys.argv[3]
else:
	print "usage: mcu frequency file"
	sys.exit(1)

term = Terminal()

class MotorModule(object):
	def __init__(self, x, y):
		self.x = x
		self.y = y
		self.rotation = 0 # radians
		self.radius = 1 # meters

		self.rotchars = ["-", "/", "|", "\\", "-", "/", "|", "\\"]
		
	def length(self):
		return self.rotation * self.radius

	def render(self, t):
		rotchar = self.rotchars[int(8 * self.rotation / (2*math.pi)) % len(self.rotchars)]

		with t.location(self.x-1, self.y-1):
			print "---"
		with t.location(self.x-1, self.y):
			print "|"+rotchar+"|"
		with t.location(self.x-1, self.y+1):
			print "---"

class Drawbot(object):
	def __init__(self, m1, m2):
		self.separation = math.sqrt((m2.x-m1.x)**2 + (m2.y-m1.y)**2)
		
		# play out enough wire
		m1.rotation = 4 * self.separation / (2 * math.pi * m1.radius)
		m2.rotation = 4 * self.separation / (2 * math.pi * m2.radius)
		
		self.m1 = m1
		self.m2 = m2

	def render(self, t):
		a = self.m1.length()
		b = self.m2.length()

		x = self.m1.x + (a**2 - b**2 + self.separation**2)/(2*self.separation)
		inside = (-(a - b - self.separation)*(a + b - self.separation)*(a + b + self.separation)/self.separation**2)
		y = self.m1.y + cmath.sqrt(inside).real/2

		ln1 = util.get_line(self.m1.x, self.m1.y, int(x), int(y))
		ln2 = util.get_line(self.m2.x, self.m2.y, int(x), int(y))

		for (lx, ly) in ln1:
			with t.location(int(lx), int(ly)):
				print "*"
		for (lx, ly) in ln2:
			with t.location(int(lx), int(ly)):
				print "*"
		with t.location(int(x), int(y)):
			print "X"

		self.m1.render(t)
		self.m2.render(t)

motor_left = MotorModule(term.width/4, term.height/4)
motor_right = MotorModule(3*term.width/4, term.height/4)
bot = Drawbot(motor_left, motor_right)
motors = [motor_left, motor_right]

# AVR devices
serial = Queue()

# setup FUSE filesystem for intercepting simulator output
def run_fs():
	if not os.path.exists("/tmp/avr"):
		os.mkdir("/tmp/avr")
	if not os.path.exists("/tmp/avr-src"):
		os.mkdir("/tmp/avr-src")

	passthrough = avr_fs.Passthrough("/tmp/avr-src")
	passthrough.devices[u'serial'] = serial

	print "mounting fs..."
	avr_fs.mount(passthrough, "/tmp/avr")

fs_thread = Thread(target=run_fs)
fs_thread.daemon = True
fs_thread.start()

print "fs thread started"

# connect to simulator
ON_POSIX = 'posix' in sys.builtin_module_names
avr_connection = Popen(
	[
		"simulavr", "-V",
		"-d", args['mcu'],
		"-F", args['freq'],
		"-W", "0xC6,/tmp/avr/serial",
		"--file", args['file']
	],
	stdout=PIPE, bufsize=1, close_fds=ON_POSIX
)

print "simulator starting"

msg = ""

term.enter_fullscreen()
print term.clear
term.move(0, 0)
print term.bold('= Mechane Simulation =!')

try:
	while True:
		print term.clear

		# get output from simulation
		try:
			msg += serial.get_nowait()
		except Empty:
			pass

		with term.location(0, 2):
			print "serial: " + msg

		bot.m1.rotation += math.pi/8
		bot.m2.rotation += math.pi/8
		bot.render(term)
		"""
		for motor in motors:
			motor.render(term)
			motor.rotation += 360/8
		"""
		time.sleep(1/10.0)
except KeyboardInterrupt:
	term.exit_fullscreen()
	call(['fusermount', '-u', '/tmp/avr'])
	call(['rm', '-r', '/tmp/avr', '/tmp/avr-src'])
	pass

#serial_thread = Thread(target=enqueue_output, args=(os.fdopen(os.open(outpipes['serial'], os.O_RDONLY | os.O_NONBLOCK)), serial_queue))
#serial_thread.daemon = True # thread dies with the program
#serial_thread.start()
