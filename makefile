all: Main

Main : Main.o arbre_de_decision.o  entropie.o attribut.o stockage.o
	gcc -o Main Main.o arbre_de_decision.o attribut.o stockage.o entropie.o -lm -g

Main.o : Main.c
	gcc -c Main.c -g

arbre_de_decision.o : arbre_de_decision.c arbre_de_decision.h entropie.o attribut.o stockage.o
	gcc -c arbre_de_decision.c -lm -g

entropie.o : entropie.c entropie.h attribut.o stockage.o
	gcc -c entropie.c -lm -g

attribut.o : attribut.c attribut.h
	gcc -c attribut.c -g


stockage.o :stockage.c stockage.h
	gcc -c stockage.c -g

clean: 
	rm -f stockage.o attribut.o entropie.o 