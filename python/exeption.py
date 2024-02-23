class Validation(Exception):
    msg = None
    def __init__(self, error_num):
        self.error = error_num
        if error_num == 0:
           self.msg = "missing special chars"
        elif error_num == 1:
            self.msg = "password must include upper and lower charactors"
        elif error_num == 2:
            self.msg = "password must contain numbers"
        
    def __str__(self):
        if self.msg:
            return (self.msg)
        return("unknone error")
       
    


def check_special(password):
    for c in password:
        if c == "@" or c == "#" or c == "%" or c == "&":
            return True
    raise Validation(0)


def check_upper(password):
    if password.islower() is True:
        raise Validation(1)
    return True
    


def check_lower(password):
    if password.isupper() is True:
        raise Validation(1)
    return True
    


def check_numbers(password):
    if any(char.isdigit() for char in password):
     return True
    raise Validation(2)


def check_password(password):
    if check_special(password) and check_upper(password)\
    and check_lower(password)  and len(password) >= 8\
    and check_numbers(password) :
        return True
    return False



try:
    print("1st password check: " + str(check_password("shlomke")))
except Validation as error_num:
    print(error_num)
 
try:   
    print("2nd password check: " + str(check_password("Shlomke99!@")))
except Validation as error_num:
    print(error_num)
try:
    print("3rd password check: " + str(check_password("shlomkell!@")))
except Validation as error_num:
    print(error_num)