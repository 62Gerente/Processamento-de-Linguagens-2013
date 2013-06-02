gentree : gen_tree.y gen_tree.l util.c ../Funcoes/toHTML.c
	flex gen_tree.l
	bison gen_tree.y
	gcc -o gentree gen_tree.tab.c util.c ../Funcoes/toHTML.c  `pkg-config --cflags --libs glib-2.0` -Wall -Wextra -O2 -ly
	chmod 755 gentree

install: gentree
	sudo cp gentree /usr/local/bin/gentree
	sudo cp man.1 /usr/share/man/man1/gentree.1

uninstall:
	sudo rm -f /usr/local/bin/gentree
	sudo rm -f /usr/share/man/man1/gentree.1
	make clean

clean:
	rm lex.yy.c gen_tree.tab.c gentree

test_linux: gentree
	./gentree < ../Dados/dados_teste.txt
	google-chrome ../HTML/index.html

test_mac: gentree
	./gentree < ../Dados/dados_teste.txt
	open ../HTML/index.html

test: gentree
	./gentree < ../Dados/dados_teste.txt
