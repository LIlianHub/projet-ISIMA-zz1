Programme:objet/main.o objet/fonctionsSDL.o objet/fenetres.o
	gcc -o Programme objets/main.o objets/fonctionsSDL.o objets/fenetres.o -g

objet/main.o:sources/main.c headers/fonctionsSDL.h headers/fenetres.h
	gcc -c sources/main.c -Wall -Wextra -o objet/main.o -g

objet/fonctionsSDL.o:sources/fonctionsSDL.c headers/fonctionsSDL.h
	gcc -c sources/fonctionsSDL.c -Wall -Wextra -o objets/fonctionsSDL.o -g

objet/fenetres.o:sources/fenetres.c headers/fenetres.h
	gcc -c sources/fenetres.c -Wall -Wextra -o objets/fenetres.o -g
