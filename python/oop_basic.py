import math
from datetime import datetime
import time

# #ex1
# class Point:
#     x = 10
#     y = 10
#     def __init__(self, x=0, y=0):
#         if type(x) in [int, float] and type(y) in [int, float]:
#             self.x = x
#             self.y = y
#         else:
#             print("error type entered")
#     def default_from_origin(self, x, y):
#         distance = math.sqrt(((self.x - Point.x)**2) + ((self.y - Point.y)**2))
#         print(distance)
        

class Node:
   def __init__(self, data=None):
        self.data = data
        self.next = None

class SList:
    def __init__(self):
        self.head_node = None

    def push(self, data):
        if self.head_node is None:
            self.head_node = Node(data)
        else:
            new_node = Node(data)
            new_node.next = self.head_node
            self.head_node = new_node
        
    def pop(self):
        self.head_node = self.head_node.next

    def head(self):
            return self.head_node.data

    def len(self):
        counter = 0
        temp = self.head_node
        while temp:
            counter += 1
            temp = temp.next
        return counter

    def Is_Empty(self):
        return self.head_node == None


# new_list = SList()
# assert(True == new_list.Is_Empty())
# assert(0 == new_list.len())

# for i in range(1,5):
#     new_list.push(i)
# assert(False == new_list.Is_Empty())
# assert(4 == new_list.head())
# assert(4 == new_list.len())

# for i in range(1,5):
#     new_list.pop()

# assert(0 == new_list.len())
# assert(True == new_list.Is_Empty())


class Machine:
    def __init__(self, type=1):
        self.type = type
        self.price = 2 if type == 1 else 5
        self.turn_on_time = 0.0
        self.time_was_active = 0.0
        self.total_cost = 0
        self.is_active = False
         
    def start_machine(self):
        if not self.is_active:
            self.turn_on_time = datetime.now()
            self.is_active = True
            
    def shutdown_machine(self):
        if self.is_active:
            time_was_active = datetime.now() - self.turn_on_time
            self.total_cost += ((int(time_was_active.total_seconds()) * self.price))
            self.is_active = False
            
    def get_current_price(self):
        if self.is_active:
            self.update
        return self.total_cost
        
    def update(self):
        self.shutdown_machine
        self.start_machine
        
        
machine_a = Machine(1)
machine_b = Machine(1)   
machine_c = Machine(1)  
machine_d = Machine(2) 
machine_e = Machine(2)

machine_a.start_machine()
machine_b.start_machine()
machine_c.start_machine()
machine_d.start_machine()
time.sleep(1)
machine_e.start_machine()
time.sleep(1)
machine_b.shutdown_machine()
time.sleep(1)
machine_a.shutdown_machine()
machine_c.shutdown_machine()
machine_d.shutdown_machine()
machine_e.shutdown_machine()

total = 0
list = [machine_a, machine_b, machine_c, machine_d, machine_e]
for i in range(len(list)):
    total += list[i].total_cost
print("total cost is: ", total)







    
    
    
        
        
        
        
    


