pah: pah_latex pah_html
	gcc -o pah pah.c	
	cp pah_html /usr/local/bin/pah_html
	cp pah_latex /usr/local/bin/pah_latex

pah_latex: linkedlist.o utilities.o functionsLatex.o latex.yy.c
	gcc -o pah_latex latex.yy.c utilities.o linkedlist.o functionsLatex.o -lfl 
	chmod 755 pah_latex

pah_html: linkedlist.o utilities.o functionsHtml.o html.yy.c
	gcc -o pah_html html.yy.c utilities.o linkedlist.o functionsHtml.o -lfl 
	chmod 755 pah_html

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

install: pah	
	chmod 755 pah
	cp pah /usr/local/bin/pah
	cp man.1 /usr/share/man/man1/pah.1

uninstall: 
	rm -f /usr/local/bin/pah_latex
	rm -f /usr/local/bin/pah_html
	rm -f /usr/local/bin/pah
	rm -f /usr/share/man/man1/pah.1
	make clean	

clean:
	rm *.o *.yy.c pah_latex pah_html pah *.tex *.html
