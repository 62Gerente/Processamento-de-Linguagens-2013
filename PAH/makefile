pah: linkedlist.o utilities.o functionsLatex.o pah.yy.c
	gcc -o pah pah.yy.c utilities.o linkedlist.o functionsLatex.o -lfl 

utilities.o: utilities.c
	gcc -c utilities.c

linkedlist.o: LinkedList/linkedlist.c
	gcc -c LinkedList/linkedlist.c

functionsLatex.o: functionsLatex.c
	gcc -c functionsLatex.c

pah.yy.c: pah.fl
	flex -o pah.yy.c pah.fl

teste: pah
	./pah < ../Exemplos/exemplo

clean:
	rm *.o *.yy.c pah
