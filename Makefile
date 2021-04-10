CC=gcc
LIBS=-lSOIL -lGL -lGLEW -lglut -lGLU -lm

main: main.c
	$(CC) $? $(LIBS) -o $@ 
run: main 
	./main
clean:
	rm main
