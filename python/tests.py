import unittest

class BankAccount:
  def __init__(self, id):
    self.id = id
    self.balance = 0

  def withdraw(self, amount):
    if self.balance >= amount:
      self.balance -= amount
      return True
    return False

  def deposit(self, amount):
    self.balance += amount
    return True

      

class Test_bank(unittest.TestCase):
  
      def test_arrange(self):
         account1 = BankAccount(1)
         self.assertTrue(account1)
         self.assertEqual(account1.id, 1)
         self.assertNotEqual(account1.balance, 1)
         
         
      def test_deposit(self):
          account1 = BankAccount(1)
          self.assertNotEqual(account1.balance, 100000)
          account1.deposit(100000)
          self.assertEqual(account1.balance, 100000)
          self.assertNotEqual(account1.balance, 5)
          
          
      def test_withdraw(self):
          account1 = BankAccount(1)
          self.assertFalse(account1.withdraw(1000000))
          self.assertNotEqual(account1.balance, 1000)
          account1.deposit(500)
          self.assertEqual(account1.balance, 500)
          
          #pytest
          assert (account1.balance == 500)
          assert (account1.balance != 600)
          
          

if __name__ == '__main__':
   unittest.main()
      












