pah: latex html
	gcc -o pah pah.c	

latex: linkedlist.o utilities.o functionsLatex.o latex.yy.c
	gcc -o latex latex.yy.c utilities.o linkedlist.o functionsLatex.o -lfl 

html: linkedlist.o utilities.o functionsHtml.o html.yy.c
	gcc -o html html.yy.c utilities.o linkedlist.o functionsHtml.o -lfl 


utilities.o: utilities.c
	gcc -c utilities.c

linkedlist.o: LinkedList/linkedlist.c
	gcc -c LinkedList/linkedlist.c

functionsLatex.o: functionsLatex.c
	gcc -c functionsLatex.c

functionsHtml.o: functionsHtml.c
	gcc -c functionsHtml.c	

latex.yy.c: latex.fl
	flex -o latex.yy.c latex.fl

html.yy.c: html.fl
	flex -o html.yy.c html.fl	

test: pah
	./pah relatorio

testHtml: pah
	./pah --html relatorio

testLatex: pah
	./pah --latex relatorio

clean:
	rm *.o *.yy.c latex html pah *.tex *.html
