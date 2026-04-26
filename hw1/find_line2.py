import matplotlib.pyplot as plt 

fl=open("sine_part_b.csv","r")
ls=fl.read().split(",")
i=0
a=[1,2,3,4,5,6,7,8,9]
b=[2,3,4,5,6,7,8,9,10]

while i<len(b):
    b[i]=b[i+2]
    
print(b)


   




