from datetime import datetime
import unittest
import time


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
    
        
class Test_machine(unittest.TestCase):
    def setUp(self):
        self.machine1 = Machine(1)
        self.machine2 = Machine(2)
        
    def test_init(self):
        self.assertEqual(self.machine1.price, 2)
        self.assertEqual(self.machine2.price, 5)
        self.assertNotEqual(self.machine2.price, 20)
        self.assertFalse(self.machine1.price == self.machine2.price)
        self.assertTrue(self.machine1.price != self.machine2.price)
        self.assertTrue(self.machine1.type == 1)
        self.assertTrue(self.machine2.type == 2)
        self.assertTrue(self.machine2.is_active == False)
        self.assertTrue(self.machine1.is_active == False)
        
    def test_start_machine(self):
        self.assertTrue(self.machine1.is_active == False)
        self.assertTrue(self.machine2.is_active == False)
        self.machine1.start_machine()
        self.machine2.start_machine()
        self.assertTrue(self.machine1.is_active == True)
        self.assertTrue(self.machine2.is_active == True)
        
    def test_shutdown_machine(self):
        self.assertFalse(self.machine1.is_active)
        self.machine1.start_machine()
        self.assertTrue(self.machine1.is_active)
        self.machine1.shutdown_machine()
        self.assertFalse(self.machine1.is_active)
        
    def test_get_current_price(self):
        self.machine1.start_machine()
        self.assertEqual(self.machine1.price, 2)
        self.assertTrue(self.machine1.is_active)
        time.sleep(1)
        curr_price = self.machine1.get_current_price()
        self.assertEqual(self.machine1.total_cost, curr_price)
        
        

        
        
        
        

