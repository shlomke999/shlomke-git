from functools import reduce

def remove_words(list1, words_to_remove):
    return list(filter(lambda word: word not in words_to_remove, list1))

#ex2
def sort_list_numerically(list1):
    return list(sorted(list1, key=lambda x: int(x)))

#ex3
def sum_list(list1):
    return sum(map(lambda x: int(x), list1))

#ex4
def contruct_list_from_even_powers(list1):
      return [x * x for x in list1 if not x % 2]
  
#ex5
def discount_dict_values(dict1):
    for k, v in dict1.items():
        dict1[k] = v * 0.9
    return dict1      

#ex6
def string_to_geometria(string):
    gematria_table = {"א": 1, "ב": 2, "ג": 3, "ד": 4, "ה": 5,
                  'ו': 6, "ז": 7, "ח": 8, "ט": 9, "י": 10, "כ": 20, "ל": 30, "מ": 40, "נ": 50,
                  "ס": 60, "ע": 70, "פ": 80, "צ": 90, "ק": 100, "ר": 200, "ש": 300, "ת": 400,
                  "ך": 500, "ם": 600, "ן": 700, "ף": 800, "ץ": 900, ' ': 0}
    vals = list(map(lambda x: gematria_table[x], string))
    return reduce((lambda x,y: x + y), vals)


#ex7
def LuhnAlgorithm(card_num):
    res = str(card_num)[::-1][1::2]
    res = list(map(lambda x: int(x)*2 if int(x)*2 < 9 else int(x)*2 - 9, res))
    res = res + [int(x) for x in str(card_num)[::-1][::2]]
    res = reduce(lambda x, y: x + y, res)
    
    return res % 10 == 0


 
 
 
colors = ['orange', 'red', 'green', 'blue', 'white', 'black']
remove_colors = ['orange','black']
test_list = ['1234', '6878', '3434', '232', '8']
dict1 = {"watch": 100, "cap": 25, "mag": 50}
test_list2 = [4, 8, 3, 22, 18]

print("ex1:  " + str(remove_words(colors, remove_colors)))   
print("ex2:  " + str(sort_list_numerically(test_list)))
print("ex3:  total sum is:" + str(sum_list([4,-2,-2,1,2,3])))
print("ex4:  " + str(contruct_list_from_even_powers(test_list2)))
print("ex5:  " + str(discount_dict_values(dict1)))
print("ex6: ימולש in gimatria is:  " + str(string_to_geometria("שלומי")))
print("ex7:  is card valid: " + str(LuhnAlgorithm(4580375603606460) ))











