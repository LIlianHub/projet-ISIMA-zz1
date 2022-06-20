Programme:objets/main.o objets/fonctionsSDL.o objets/fenetres.o
	gcc -o Programme objets/main.o objets/fonctionsSDL.o objets/fenetres.o -g

objets/main.o:sources/main.c headers/fonctionsSDL.h headers/fenetres.h
	gcc -c sources/main.c -Wall -Wextra -o objets/main.o -g

objets/fonctionsSDL.o:sources/fonctionsSDL.c headers/fonctionsSDL.h
	gcc -c sources/fonctionsSDL.c -Wall -Wextra -o objets/fonctionsSDL.o -g

objets/fenetres.o:sources/fenetres.c headers/fenetres.h
	gcc -c sources/fenetres.c -Wall -Wextra -o objets/fenetres.o -g
