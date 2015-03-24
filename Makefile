FLAGS = -lm -lX11
EXEC = fractals gallery

all: $(EXEC)

fractals: fractals.o gfx3.o
	gcc fractals.o gfx3.o $(FLAGS) -o fractals

gallery: gallery.o gfx3.o
	gcc gallery.o gfx3.o $(FLAGS) -o gallery

fractals.o: fractals.c gfx3.h
	gcc -c fractals.c

gallery.o: gallery.c gfx3.h
	gcc -c gallery.c

gfx3.o: gfx3.c
	gcc -c gfx3.c

.PHONY: clean
clean:
	-rm *.o $(EXEC)
