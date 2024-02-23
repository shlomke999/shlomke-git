
.PHONY: debug release

CC = gcc
INC = ../../include
TEST = ../../test
REL = ../../bin/release
DEB = ../../bin/debug
TARGET = 100k_threads

all : release debug
release : CFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
debug : CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g

release : main_r.o $(TARGET)_r.o 
	$(CC) $(CFLAGS) $? -o $(REL)/$(TARGET).out

debug : main_d.o $(TARGET)_d.o 
	$(CC) $(CFLAGS) $? -o $(DEB)/$(TARGET).out


main_r.o : $(TEST)/$(TARGET)_test.c
	$(CC) $(CFLAGS) -c $? -o $@

$(TARGET)_r.o : $(TARGET).c
	$(CC) $(CFLAGS) -c $? -o $@

main_d.o : $(TEST)/$(TARGET)_test.c
	$(CC) $(CFLAGS) -c $? -o $@

$(TARGET)_d.o : $(TARGET).c
	$(CC) $(CFLAGS) -c $? -o $@
	
clean:
	rm -f *.o ../../bin/debug/$(TARGET).out ../../bin/release/$(TARGET).out

