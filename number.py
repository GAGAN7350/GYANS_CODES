import shelve
def data():
    with shelve.open('user.db') as db:
        db['username'] = input("Enter username: ")
        db['age'] = int(input("Enter age: "))
def rdata():
    with shelve.open('user_data.db') as db:
        print(f"Username: {db.get('username', 'Not found')}")
        print(f"Age: {db.get('age', 'Not found')}")
choice = input("1. Store Data 2. Retrieve Data: ")
if choice == '1': data()
elif choice == '2':rdata()