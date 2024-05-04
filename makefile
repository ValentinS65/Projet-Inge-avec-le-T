all: Main

Main : Main.o entropie.o attribut.o arbre_de_decision_v2.o
	gcc -o Main Main.o attribut.o arbre_de_decision_v2.o entropie.o -lm

Main.o : Main.c
	gcc -c Main.c

entropie.o : entropie.c entropie.h attribut.o arbre_de_decision_v2.o
	gcc -c entropie.c -lm

attribut.o : attribut.c attribut.h
	gcc -c attribut.c


arbre_de_decision_v2.o :arbre_de_decision_v2.c arbre_de_decision_v2.h
	gcc -c arbre_de_decision_v2.c

clean: 
	rm -f arbre_de_decision_v2.o attribut.o