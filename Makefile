CC = gcc
FILE = printf.c \
main.c \
helpers.c
LIB_STANDARD = -L $(LIBRARY_PATH)/standard -I $(LIBRARY_PATH)/standard -lstandard
LIB_BUFFER = -L $(LIBRARY_PATH)/buffers -I $(LIBRARY_PATH)/buffers -lbuffer

all:
	$(CC) $(FILE) -g $(LIB_BUFFER) $(LIB_STANDARD) 

clean:
	rm a.out