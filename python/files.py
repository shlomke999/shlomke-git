from string import ascii_lowercase

def create_files():
    for i in ascii_lowercase:
        with open(i + ".txt", "w") as a:
            a.write(i)
        a.close
               
def read_n_lines(file_name, n_lines):
    with open(file_name, "r") as a:
        for i in range(n_lines):
            print(a.readline())
    a.close
   

def corona_stuff():
    with open("corona.csv", "r") as file:
        file.readline()
        lines = file.readlines()
        max_vaccinated = 0
        max_unvaccinated = 0
        min_vaccinated = 50
        hospitalization_time = 0
        min_unvaccinated = 50
        for l in lines:
            l = l.split(",")
            hospitalization_time += int(l[4])
            if ((l[6]) == 'Y\n' and max_vaccinated < int(l[1])):#update vaccinated max age
                max_vaccinated = int(l[1])
            if ((l[6]) == 'Y\n' and min_vaccinated > int(l[1])):#update vaccinated min age
                min_vaccinated = int(l[1])
            if ((l[6]) == 'N\n' and max_unvaccinated < int(l[1])):#update unvaccinated max age
                max_unvaccinated = int(l[1])
            if ((l[6]) == 'N\n' and min_unvaccinated > int(l[1])):#update unvaccinated min age
                min_unvaccinated = int(l[1])
        print("avg hospitalization: ", int(hospitalization_time) / len(lines))
        print("max unvaccinated age: ", max_unvaccinated)        
        print("min unvaccinated age: ", min_unvaccinated)
        print("max vaccinated age: ", max_vaccinated)
        print("min vaccinated age: ", min_vaccinated)

def get_data(data):
    with open("corona.csv", "r") as file, open ("filter.txt", "w") as output_file:
        l = file.readline()
        l = l.split(",")
        index = l.index(data)
        lines = file.readlines()
        for l in lines:
            l = l.split(",")
            output_file.write(data + ":" + l[index] + "\n")  
 
 
if __name__ == '__main__':   
    #create_files()      
    read_n_lines("/home/shlomi/test_file", 3)              
    corona_stuff()
    get_data("Time_between_positive_and_recovery")
             
    
