class holi:
    def __init__(self,color,ballon):
        self.color = color
        self.ballon = ballon

    def show_details(self):
        print("Color is : ",self.color)
        print("Ballon is : ",self.ballon)

class waterballon(holi):
    def __init__(self,color,ballon,water):
        super().__init__(color,ballon)
        self.water = water

    def show_details(self):
        super().show_details()
        print("Water is : ",self.water)

a=waterballon("Blue","Big","Present")
a.show_details()                