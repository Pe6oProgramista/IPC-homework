# za dva otdelni terminala
all:
	gcc namedPipeMaker.c -o make.o
	gcc dumbNamedPipeWriter.c -o write.o
	gcc dumbNamedPipeReader.c -o read.o

	./make.o

	gnome-terminal -x sh -c "./read.o"
	./write.o
	# `pwd` | --working-directory

# za edin terminal
dumbPipe:
	gcc dumbPipe2.c -o dumbPipe.o
	./dumbPipe.o

# trie vsichki suzdadeni failove
clear:
	rm -f *.o namedPipe a.out


