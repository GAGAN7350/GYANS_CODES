import os 
a=os.listdir('C:\\Users\\HP\\start.py')
i=1
for name in a:
    if name.endswith(".py"):
        new_name="code"+str(i)+".py"
        os.rename(name,new_name)
        i+=1