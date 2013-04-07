#!/bin/sh

for teste in *.pah
do
	nome=${teste%.pah}	
	echo "A processar o ficheiro $teste ..."	
	../html < $teste > $nome.html 	
done



