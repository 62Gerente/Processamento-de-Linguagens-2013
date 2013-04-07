#!/bin/sh

for teste in exemplosHtml/*.pah
do
	nome=${teste%.pah}	
	echo "A processar o ficheiro $teste ..."	
	./pah --html $teste $nome.html 	
done



