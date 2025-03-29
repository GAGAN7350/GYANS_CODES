from math import sqrt
num=int(input("Enter the number of elements in the lsit: "))
for i in range(num):
    x=int(input("Enter a number: "))
total=0
for i in myList:
    total+=i
mean=total/num
total=0
for i in myList:
    total+=(i-mean)**2
variance=total/num
stdDev=sqrt(variance)
print('Mean:',mean)
print('Variance:',variance)
print('Standard Deviation:',"%.2f"%stdDev)