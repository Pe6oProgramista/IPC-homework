all:
	gcc cyclicRead.c -lrt -o read.o
	gcc cyclicWrite.c -lrt -o write.o
	gcc deleteMemory.c -lrt -o delete.o

	gnome-terminal -x sh -c "sudo ./write.o|less"
	sudo ./read.o

clear:
	./delete.o
	rm -f *o a.out