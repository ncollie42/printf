CC = gcc
FILE = test.c 
LIB_LOCATION = $(DYLD_LIBRARY_PATH)

all:
	$(CC) $(FILE) -L $(LIB_LOCATION) -I $(LIB_LOCATION) -lnc 

clean:
	rm a.out