objects = main.o foo.o
GD = -ansi -pedantic-errors -Wall -Wextra -g -o
GC = -ansi -pedantic-errors -Wall -Wextra -g -DNDEBUG -O3 -o
NAME = fooer.out


all &: $(objects) debug release
			

fooer.out : $(objects)
							cc -o fooer.out $(objects)
							

	
debug : 
			$(cc) $(GC) $(NAME) $(objects)
			
release :
			$(cc) $(GD) $(NAME) $(objects)
			


clean :
			rm fooer.out $(objects)


