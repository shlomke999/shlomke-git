def remove_non_str_from_list(list1):
    return [i for i in list1 if isinstance(i, str)]

# ex2
# return string in a dict containing each letter and its occurence 
def str_to_dict(string):
    return {char:string.count(char) for char in string}

# ex3
# return a list containing onlly elements that are in both lists
def in_two_lists(list1, list2):
    res_list = []
    for elem in list1:
        if list1.count(elem) > 0 and list2.count(elem) > 0:
            res_list.append(elem) 
    return res_list

# ex4 
def unique_in_dict(dict):
    list = set(dict.values())
    return list

# ex5
# make left rotation using slice
def rotate_left(list):
    return (list[1:] + list[:1])  

# ex6
# remove every second element untill list is empty
def remove_and_print(list1):
     for i in range(1, len(list1)//2 + 1):
        print(list1[i])
        list1.remove(list1[i])

# ex7
def dict_to_tuples(dict):
    return list(dict.items()) #list is a built in word so no need for brackets

# ex8
def get_max_and_min_keys(dict):
    print(min(dict, key=dict.get))
    print(max(dict, key=dict.get))


numbers = ["lol", 3, "str", 7, "remains", 11]
list1 = [1, 3, 7, "shlomi", "liraz", "libby"]
list2 = [1, 5, 9, "shlomi", "lol", "libby"]
dict1 = {"Nepal": "Kathmandu", "Italy": "Rome", "England": "London", "Italy": "Rome"}
dict2 = {"Nepal": 20, "Italy": 168, "England": 36, "israel": 14}

print("ex1 test: " + str(remove_non_str_from_list(numbers)))      
print("ex2 test:  " + str(str_to_dict("shlomke lazar")))
print("ex3 text:  " + str(in_two_lists(list1, list2)))
print("ex4 test:  " + str(unique_in_dict(dict1)))
print("ex5 test:  " + str(rotate_left(list1)))
print(remove_and_print([1, 2, 3, 4, 5, 6, 7, 8, 9]))
print("ex7 test: " + str (dict_to_tuples(dict1)))
print(get_max_and_min_keys(dict2))






                