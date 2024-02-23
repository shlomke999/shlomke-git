import os
import sys
import stat
import areas


def is_global(name):
    return True if name in globals().keys() else False

#ex3
def print_os_data():
    print("ex3:  os name: ", os.uname()[0])
    print("ex3:  logged in user: ", os.getlogin())
    print("ex3:  working directory: ", os.getcwd())
    
#ex4
def print_cli_args():
    print(sys.argv[::-1])

#ex5:  takes file name from the command line, searches for it in the system, and 
# checks the executable permission. If it's missing - change it for the owner and group but not for others.
def findfile(filename):
    for (root, dirs, files) in os.walk('/', topdown=True):
        if filename in files:
            return os.path.join(root, filename)#return absolute file path


def executable_permission(file_path):
    if os.access(file_path, os.X_OK) == False:  #execution permission missing
        current_permissions = stat.S_IMODE(os.lstat(file_path).st_mode)

        #change executable permissions:
        owner_group_exec_perm = stat.S_IXGRP | stat.S_IXUSR
        os.chmod(file_path, current_permissions | owner_group_exec_perm)
        print("ex5:  permissions change succesfully")             
                
          
print("ex1:  ", is_global('__doc__'))
print("ex2:  circle_area: ", areas.circle_area(3.22))
print("ex2:  triangle_area: ", areas.triangle_area(3.22, 4))
print("ex2:  rectangle_area: ", areas.rectangle_area(3.22, 4))
print_os_data()
print_cli_args()

path = findfile(sys.argv[1])
if path == None:
    sys.exit("file not found...Exiting...")
executable_permission(path) 






