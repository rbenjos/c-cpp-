CC = gcc
FLAGS = -Wextra -Wvla -Wall -g -std=99
default: NumericalAnalyzer

NumericalAnalyzer: NumericalAnalyzer.o libinfi.a
    ${CC} ${FLAGS} NumericalAnalyzer.o -L. -lm -linfi -o NumericalAnalyzer

NumericalAnalyzer.o: NumericalAnalyzer.c
    ${CC} ${FLAGS} -c NumericalAnalyzer.c

libinfi.a: infi.o infi.h
    ar rcs libinfi.a infi.o infi.h

infi.o: infi.c
    ${CC} ${FLAGS} -c infi.c infi.h

clean:
    rm -f *.o *.a NumericalAnalyzer

.PHONY: clean