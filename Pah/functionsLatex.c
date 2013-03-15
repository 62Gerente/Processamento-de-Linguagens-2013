#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void endLatexTag(){
    printf("%s",(char*)(popLinkedList(closeTags)));
}
void beginBoldLatex(){
    printf("\\textbf{");
    addCloseTagLatex();
}
void beginItalicLatex(){
    printf("\\textit{");
    addCloseTagLatex();
}
void beginUnderlineLatex(){
    printf("\\underline{");
    addCloseTagLatex();
}
void beginTitleLatex(int level){
    int i;
    printf("\\");
    for(i=1; i<level; i++)
           printf("sub");
    printf("section{");
    addCloseTagLatex();
}
void addCloseTagLatex(){
    pushLinkedList(closeTags,(void*)"}");
}
