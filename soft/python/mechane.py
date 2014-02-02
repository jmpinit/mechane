import serial
import math

#########################################
#CONSTANT LIST
#########################################

pos = "post"
vel = "velo"
stop = "stop"
reset = "rset"
update = "updt"

okMessage = "OK"


class motorModule:
    # each motor module is abstracted to an object
    self.p, self.i, self.d = 0,0,0
    #experiment to find vals later?

    
    def __init__(self, serAddress, name, ticksPerrev):

        self.name = name
        self.ticksPerrev = ticksPerRev
        self.pos = 0

        try:
            self.ser = serial.Serial(serAddress)
        except Exception:
            print("can't connect to " + self.name)

        else:
            print("something went wrong establishing serial")

    def heartbeat(self):
        if self.ser:
            # send "ok?" message here
            if self.ser.readline() == okMessage:
                #if serial connected AND atmega working
                return True
            else:
                print("no heartbeat from module " + self.name)
                return False

        else:
            print("lost connection to module " + self.name)
            return False

    def movePos(self, delta ):
        #put module into pos mode here? may not be necessary
        #delta in rads
        
        if heartbeat():
            self.ser.write(delta / (2*pi) * self.ticksPerrev)
            self.pos += delta / (2*pi) * self.ticksPerrev

    def updatePos(self):
        # update internal position according to module
        if heartbeat():
            self.ser.write(update)
            self.pos = self.ser.readline()
            print("module " + name + " updated position")

    def getPos(self)
        updatePos()
        return self.pos

    def halt(self):
        #stop module from moving
        if heartbeat():
            self.ser.write(stop)
            print("module " + name + " stopped")

    def moveVel(self, vel):
        #put module into pos mode here? may not be necessary
        #delta in rads
        
        if heartbeat():
            self.ser.write(vel)
        
            
            
                
        
