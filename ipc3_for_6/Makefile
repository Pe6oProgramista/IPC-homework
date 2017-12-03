all:
	gcc cyclicRead.c -lrt -o read.o
	gcc cyclicWrite.c -lrt -o write.o
	gcc freeMemory.c -lrt -o free.o

	gnome-terminal -x sh -c "sudo ./write.o|less"
	sudo ./read.o

clear:
	sudo ./free.o
	sudo rm -f *o a.out
