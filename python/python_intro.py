def ex1(ch, string):
    return string.count(ch)


# ex2
def flip_number(num):
    return str(num)[::-1] # the coolest way


# ex3
def celsius_to_fahr(num):
    return num*1.8 + 32


# ex4
def is_year_leap(year):
    if year % 400 == 0 or (year % 4 == 0 and year % 100 != 0):
        return True
    else:
        return False


# ex5 helpers
def check_special(password):
    for c in password:
        if c is "@" or c is "#" or c is "%" or c is "&":
            return True
    return False


def check_upper(password):
    if password.islower() is True:
        return False
    return True


def check_lower(password):
    if password.isupper() is True:
        return False
    return True


def check_numbers(password):
    return any(char.isdigit() for char in password)


def check_password(password):
    if check_special(password) and check_upper(password)\
    and check_lower(password)  and len(password) >= 8\
    and check_numbers(password) :
        return True
    return False


# ex6
def sum_of_devisors(num):
    res = 0
    for i in range(1, num + 1):
        if num % i == 0:
            res += i
    return res


# ex7
def money_break(money):
    amounts = [1, 2, 5, 10, 20, 50, 100, 200]
    res = {}
    for amount in amounts:
        res[amount] = money // amount
    return res


# ex8
def is_prime(num):
    for i in range(2, num):
        if num % i == 0:
            return False
    return True

