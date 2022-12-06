CC=gcc
OPTS=-g -std=c99 -Werror

all: main.o predictor.o custom.o tournament.o gshare.o utils.o
	$(CC) $(OPTS) -lm -o predictor main.o predictor.o custom.o tournament.o gshare.o utils.o

main.o: main.c predictor.h
	$(CC) $(OPTS) -c main.c

predictor.o: predictor.h predictor.c gshare.h tournament.h custom.h
	$(CC) $(OPTS) -c predictor.c

custom.o: custom.h custom.c predictor.h utils.h
	$(CC) $(OPTS) -c custom.c

tournament.o: tournament.h tournament.c predictor.h utils.h
	$(CC) $(OPTS) -c tournament.c

gshare.o: gshare.h gshare.c predictor.h utils.h
	$(CC) $(OPTS) -c gshare.c

utils.o: utils.h utils.c
	$(CC) $(OPTS) -c utils.c

clean:
	rm -f *.o predictor;
