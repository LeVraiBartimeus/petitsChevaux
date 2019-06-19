CC=gcc
CFLAGS=-Wall -Werror -Wextra
DEPS = main.h
OBJ = main.o affichage.o init.o interface.o jeu.o menu.o

all: jeu

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

jeu: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf jeu

