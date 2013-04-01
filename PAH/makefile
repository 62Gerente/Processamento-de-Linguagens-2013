pah: latex
	gcc -o pah pah.c
	rm *.o *.yy.c

latex: linkedlist.o utilities.o functionsLatex.o latex.yy.c
	gcc -o latex latex.yy.c utilities.o linkedlist.o functionsLatex.o -lfl 

utilities.o: utilities.c
	gcc -c utilities.c

linkedlist.o: LinkedList/linkedlist.c
	gcc -c LinkedList/linkedlist.c

functionsLatex.o: functionsLatex.c
	gcc -c functionsLatex.c

latex.yy.c: latex.fl
	flex -o latex.yy.c latex.fl

test: pah
	./pah ../Exemplos/exemplo

clear:
	rm *.o *.yy.c latex pah Latex.tex Html.html
