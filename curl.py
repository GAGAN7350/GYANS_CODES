from sympy.physics.vector import *
from sympy import var
x, y, z = var('x y z')
v= ReferenceFrame('v')
F=v[0]*v[1]**2*v.x+2*v[0]**2*v[1]*v[2]*v.y-3*v[1]*v[2]**2*v.z
G= curl (F,v)
F=F.subs([(v[0],x) ,(v[1],y) ,(v[2],z)])
print (" Given vector point function is ")
print(F)
G=G.subs([(v[0],x) ,(v[1],y) ,(v[2],z)])
print (" curl of F=")
print(G)