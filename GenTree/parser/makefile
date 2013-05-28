gen_tree : gen_tree.y gen_tree.l util.c ../Funcoes/toHTML.c
	flex gen_tree.l
	bison gen_tree.y
	gcc -o gen_tree gen_tree.tab.c util.c ../Funcoes/toHTML.c `pkg-config --cflags --libs glib-2.0` -Wall -Wextra -O2 -ly