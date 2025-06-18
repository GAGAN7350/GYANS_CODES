from sympy import *
x= Symbol ('x')
y= Symbol ('y')
#a= Symbol ('a ')
#b= Symbol ('b ')
a=4
b=6
w3=4* integrate (1,(y,0 ,(b/a)* sqrt (a ** 2-x ** 2)) ,(x,0,a))
print (w3)