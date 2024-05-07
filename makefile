all: Main

Main : Main.o entropie.o attribut.o stockage.o
	gcc -o Main Main.o attribut.o stockage.o entropie.o -lm

Main.o : Main.c
	gcc -c Main.c

entropie.o : entropie.c entropie.h attribut.o stockage.o
	gcc -c entropie.c -lm

attribut.o : attribut.c attribut.h
	gcc -c attribut.c


stockage.o :stockage.c stockage.h
	gcc -c stockage.c

clean: 
	rm -f stockage.o attribut.o entropie.o 