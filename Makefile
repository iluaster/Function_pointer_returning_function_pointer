all: function_pointer_return_function_pointer

CC=gcc
CFLAGS= -g 
function_pointer_return_function_pointer: function_pointer_return_function_pointer.o
	$(CC) $(CFLAGS) -o function_pointer_return_function_pointer function_pointer_return_function_pointer.o
function_pointer_return_function_pointer.o:function_pointer_return_function_pointer.c
	$(CC) $(CFLAGS) -c function_pointer_return_function_pointer.c
	
clean:
	rm -f function_pointer_return_function_pointer.o
