PWD = $(shell PWD)
IDIR =./include
CC=g++
CFLAGS=-I$(IDIR)

ODIR=.
LDIR =../lib

LIBS=-lm

_DEPS = fastSA.h init_placement.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o fastSA.o init_placement.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -std=c++11 $(CFLAGS) -c -o $@ $< $(LIBS)

main: $(OBJ)
	$(CC) -std=c++11 $(CFLAGS) -o main.out $^ $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.out *~ core $(INCDIR)/*~ 