src := $(wildcard src/*.c)
objects := $(src:.c=.o)


lufs : $(objects)
	gcc -o lufs $(objects)

src/%.o : src/%.c
	gcc -o $@ -c $<

clean :
	rm src/*.o
	rm lufs