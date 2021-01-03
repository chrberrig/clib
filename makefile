SRC = clib http_reqs
CC = gcc

all: ${SRC}

%: %.o
	${CC} -o $@ $< -Wall -O3

%.o: %.c
	${CC} -c $< -Wall -O3

clean:
	rm *.o 


.PHONY: all clean install
