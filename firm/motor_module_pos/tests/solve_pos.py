# solve for equations describing cartesian coordinates of drawbot pen in terms of the location of the two motors and lengths of the two strings attached to it.
from sympy import *

m1_x = Symbol("m1_x")
m1_y = Symbol("m1_y")
m2_x = Symbol("m2_x")
m2_y = Symbol("m2_y")

x = Symbol("x")
y = Symbol("y")

a = Symbol("a")
b = Symbol("b")

eqs = solve([x**2 + y**2 - a**2, (sep-x)**2 + y**2 - b**2], [x, y])
print "x = " + str(eqs[0][0])
print "y = " + str(eqs[0][1])

print ""

print "x = " + str(eqs[1][0])
print "y = " + str(eqs[1][1])
