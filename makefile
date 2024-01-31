all: exec
	
fonctionT.o: fonctionT.c fonction.h
	gcc -c fonctionT.c -o fonctionT.o
	
fonctionS.o: fonctionS.c fonction.h
	gcc -c fonctionS.c -o fonctionS.o
	
main.o: main.c fonction.h
	gcc -c main.c -o main.o
	
exec: main.o fonctionS.o fonctionT.o
	gcc main.o fonctionS.o fonctionT.o -o exec
