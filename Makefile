# Shane Sims
# <EMAIL>

MAIN    = main
CSOURCE = ${MAIN}.c calc_large.c
OBJECTS = ${CSOURCE:.c=.o}
EXECBIN = ${MAIN}

GCC     = gcc 
CFLAGS  = -g -Wall -Wextra -O0 -std=gnu99

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS} ${CFLAGS}

%.o : %.c
	${GCC} -c $< ${CFLAGS}

clean :
	rm ${EXECBIN} ${OBJECTS}
