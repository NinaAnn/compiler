cc=gcc
target=compilor
obj=main.o interpreteur.o syntaxique.o calculator.o FileOpen.o
$(target):$(obj)
	$(cc) $(obj) -Wall -o $(target) -lm
main.o:main.c
	$(cc) -c main.c
interpreteur.o:interpreteur.c
	$(cc) -c interpreteur.c
factorielle.o:syntaxique.c
	$(cc) -c syntaxique.c
calculator.o:calculator.c
	$(cc) -c calculator.c
FileOpen.o:FileOpen.c
	$(cc) -c FileOpen.c

.PHONY:clean
	$(RM) *.o $(target
