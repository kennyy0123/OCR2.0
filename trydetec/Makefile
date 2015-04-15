## Simple SDL mini code
 
CC=clang
 
CPPFLAGS= `pkg-config gtk+-2.0 --cflags` `pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3 -g
#CFLAGS=-std=c99 -g
LDFLAGS=
LDLIBS= `pkg-config --libs gtk+-2.0` `pkg-config --libs sdl` -lSDL_image -lm
 
SRC=detection.c filtre.c main.c
OBJ= ${SRC:.c=.o}
 
all: main
 
main: ${OBJ}
 
clean:
	rm -f *~ *.o
	rm -f main
 
# END
