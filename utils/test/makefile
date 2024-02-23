objects = main.o foo.o
GD = -ansi -pedantic-errors -Wall -Wextra -g -o
GC = -ansi -pedantic-errors -Wall -Wextra -g -DNDEBUG -O3 -o
NAME = fooer.out


fooer.out : $(objects)
							gcc -o fooer.out $(objects)
							
foo.o : ../src/makefile/foo.c ../include/foo.h
							gcc -c $(SRCDIR)/makefile/foo.c
		
main.o : main.c ../include/foo.h
							gcc -c main.c



all &: $(objects) debug release
			


							

OBJDIR := /home/shlomi/git/utils
SRCDIR := $(OBJDIR)/src
INCLUDEDIR := $(OBJDIR)/include
TESDIR := $(OBJDIR)/test

	
debug : 
			$(cc) $(GC) $(NAME) $(objects)
			
release :
			$(cc) $(GD) $(NAME) $(objects)
			


clean :
			rm fooer.out ./*.o
			
			
touch : 

			touch main.o foo.o


