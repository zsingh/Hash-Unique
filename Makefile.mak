SRC = table.c
FLAGS= -std=gnu99 -g -Wall

all: unique $(SRC)

unique: unique.c $(SRC)
	gcc unique.c -o unique $(SRC) $(FLAGS)
	
clean:
	rm -rf unique