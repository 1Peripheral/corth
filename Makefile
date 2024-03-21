CC = gcc
FLAGS = -std=c11 -Werror -Wall -Wpedantic
OUT = corth 

default :
	$(CC) *.c -o build/$(OUT) $(FLAGS)
	
run :
	./build/$(OUT)

