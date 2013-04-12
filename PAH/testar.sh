#!/bin/sh

rm exemplosHtml/*.html

for teste in exemplosHtml/*.pah
do
	nome=${teste%.pah}	
	echo "A processar o ficheiro $teste ..."	
	./pah --html $teste $nome.PAH.html
	#./pah --html $teste 
	#./html < $teste >  $nome.HTML.html
done



