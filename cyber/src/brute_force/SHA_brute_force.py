import string
import hashlib
from itertools import permutations, combinations, product
import datetime


# encode() : Converts the string into bytes to be acceptable by hash function.
# hexdigest() : Returns the encoded data in hexadecimal format.
def sha1_encrypt(str):
    result = hashlib.sha1(str.encode())
    return result.hexdigest()
   
def sha256_encrypt(str):
    result = hashlib.sha256(str.encode())
    return result.hexdigest()

def convert_to_str(tupple):
    str = ''
    for i in tupple:
        str = str + i
    return str

def sha_bruteforce(hassed_password, password_len, char_set, hash_type):
    start_time = datetime.datetime.now()
    
    #product generate list of tuples with all combinations of char_set that we can iterate
    for t in product(char_set, repeat=password_len):
        guess_string = convert_to_str(t)
        
        if hash_type == "sha1":
            hashed_guess_string = sha1_encrypt(guess_string)
        elif hash_type == "sha256":
            hashed_guess_string = sha256_encrypt(guess_string)
        else: print("the function only support sha1 and sha256 cracking")
        
        if hashed_guess_string == hassed_password:
           print("cracking process took ", (datetime.datetime.now() - start_time).total_seconds(), "second\n")
           print("the hashed password is:")
           return guess_string
        
    print("the process took ", (datetime.datetime.now() - start_time).total_seconds(), "second. no match found\n")
    return None
  
#test 1: "noam" hashed with sha256              
#print(sha_bruteforce("ca64b53d393e0e2429f885347f37fe3d873bc676bf6ed74aeb8e86004de44c46", 4, list(string.ascii_lowercase), "sha256"))

#test 2: "noam" hashed with sha1
#print(sha_bruteforce("8c8bc0f5394e17e430672c522c5fc3af172df6cf", 4, list(string.ascii_lowercase), "sha1"))

#test 3: "libby" hashed with sha256              
#print(sha_bruteforce("7cf7b152874767a5b190cd48117669627a549810cc5768f638642ff021e8293a", 5, list(string.ascii_lowercase), "sha256"))

#test 4: "libby" hashed with sha1              
#print(sha_bruteforce("6b50e0eee4438c8ae5099a293de1312b06992b55", 5, list(string.ascii_lowercase), "sha1"))

#test 5: "123456" hashed with sha256              
#print(sha_bruteforce("8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92", 6, "1234567890", "sha256"))

#test 6: "123456" hashed with sha1              
#print(sha_bruteforce("7c4a8d09ca3762af61e59520943dc26494f8941b", 6, "1234567890", "sha1"))

#test 7: "1238456" hashed with sha256              
#print(sha_bruteforce("1d51f997fc08294a3590c5419c35ebdbf6f96f02974dc9d729b7c61121d3b790", 7, "1234567890", "sha256"))

#test 8: "1238456" hashed with sha1              
#print(sha_bruteforce("340d808206bda91cf6a9ac8e66e325529b0fa8b3", 7, "1234567890", "sha1"))
   
#test 9: "12838456" hashed with sha256              
#print(sha_bruteforce("d4730789f6386f9b75a73e268372cfb8da92ab80bf42b63432151b14fdddf896", 8, "1234567890", "sha256"))
  
#test 10: "12838456" hashed with sha1              
#print(sha_bruteforce("228a85d4cd4abfa23a63089978d49dba33c44a34", 8, "1234567890", "sha1"))

#test 11: "shlomi" hashed with sha256              
#print(sha_bruteforce("4ffe91842477f3a0621f8a0ccf32d36ec642f455666ecaedc181a0c7383faa5a", 6, list(string.ascii_lowercase), "sha256"))

#test 12: "shlomi" hashed with sha1              
#print(sha_bruteforce("6f01bf2e882e3bb6371d28d1418e5f729e7183e6", 6, list(string.ascii_lowercase), "sha1"))

#test 13: "5ern8" hashed with sha256              
#print(sha_bruteforce("569468f9305d186994f88253976d2763ddd7e87bb71fc0755599b2aa5bc0baed", 5, list(string.ascii_letters + string.digits), "sha256"))

#test 14: "5ern8" hashed with sha1             
#print(sha_bruteforce("cb78ac192bf5c9277ec49924d6430a95ea3db0d9", 5, list(string.ascii_letters + string.digits), "sha1"))

