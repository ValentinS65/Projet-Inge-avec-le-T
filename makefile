all: Main

Main : Main.o entropie.o attribut.o stockage.o
	gcc -o Main Main.o attribut.o stockage.o entropie.o -lm -Og -fsanitize=address,leak,undefined

Main.o : Main.c
	gcc -c Main.c -Og -fsanitize=address,leak,undefined

arbre_de_decision.o : arbre_de_decision.c arbre_de_decision.h entropie.o attribut.o stockage.o
	gcc -c arbre_de_decision.c -lm -g

entropie.o : entropie.c entropie.h attribut.o stockage.o
	gcc -c entropie.c -lm -Og -fsanitize=address,leak,undefined

attribut.o : attribut.c attribut.h
	gcc -c attribut.c -Og -fsanitize=address,leak,undefined


stockage.o :stockage.c stockage.h
	gcc -c stockage.c -Og -fsanitize=address,leak,undefined

clean: 
	rm -f stockage.o attribut.o entropie.o 