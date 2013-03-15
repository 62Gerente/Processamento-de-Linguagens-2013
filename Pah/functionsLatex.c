#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functionsLatex.h"
#include "LinkedList/linkedlist.h"

void endLatexTag(LinkedList l){
    printf("%s",(char*)(popLinkedList(l)));
}
void beginBoldLatex(LinkedList l){
    printf("\\textbf{");
    addCloseTagLatex(l);
}
void beginItalicLatex(LinkedList l){
    printf("\\textit{");
    addCloseTagLatex(l);
}
void beginUnderlineLatex(LinkedList l){
    printf("\\underline{");
    addCloseTagLatex(l);
}
void beginTitleLatex(LinkedList l,int level){
    int i;
    printf("\\");
    for(i=1; i<level; i++)
           printf("sub");
    printf("section{");
    addCloseTagLatex(l);
}
void addCloseTagLatex(LinkedList l){
    pushLinkedList(l,(void*)"}");
}
