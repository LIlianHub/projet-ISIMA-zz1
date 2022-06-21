SRC=AlgoVie.c
EXE=exec

CC=gcc
CFLAGS:=-Wall -Wextra -lm -MMD -Og -g $(sdl2-config --cflags)
#CFLAGS:=-Wall -Wextra -MMD -O2 $(sdl2-config --cflags)  # pour la version release
LDFLAGS:=-lSDL2_image -lSDL2_ttf -lSDL2_gfx -lm -lSDL2

OBJ=$(addprefix objets/,$(SRC:.c=.o))
DEP=$(addprefix dependances/,$(SRC:.c=.d))

all: $(OBJ) 
	$(CC) -o $(EXE) $^ $(LDFLAGS)

objets/%.o: %.c
	@mkdir -p objets
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf objets core *.o

-include $(DEP)
