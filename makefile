FNAME=clib
CC=gcc

all: ${FNAME}

${FNAME}: ${FNAME}.o
	${CC} -o ${FNAME} ${FNAME}.o

${FNAME}.o: ${FNAME}.c
	${CC} -c ${FNAME}.c

clean:
	rm ${FNAME}.o ${FNAME}


.PHONY: all clean install
