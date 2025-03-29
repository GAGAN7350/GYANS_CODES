def generator():
    
    for i in range(5, 10):
        yield i

gen=generator() 
print(next(gen))
print(next(gen))
print(next(gen))
print(next(gen))
print(next(gen))       