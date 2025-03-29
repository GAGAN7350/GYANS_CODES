class person: 
    def __init__(self,name,age):
        self.name = name
        self.age = age
        self.version = 1.0  

p=person("Gyan", 69)
print(p.__dict__)
print(help(person))        