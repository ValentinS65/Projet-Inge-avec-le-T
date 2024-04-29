all: attribut

attribut : attribut.o arbre_de_decision_v2.o
	gcc -o attribut attribut.o arbre_de_decision_v2.o

attribut.o : attribut.c attribut.h
	gcc -c attribut.c

arbre_de_decision_v2.o :arbre_de_decision_v2.c arbre_de_decision_v2.h
	gcc -c arbre_de_decision_v2.c

clean: 
	rm -f arbre_de_decision_v2.o attribut.o