#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functionsLatex.h"
#include "LinkedList/linkedlist.h"
#include "utilities.h"

/* Função que fecha a ultima tag aberta */
void endLatexTag(LinkedList l){
    printf("%s",(char*)(popLinkedList(l)));
}

/* Início de negrito em latex */
void beginBoldLatex(LinkedList l){
    printf("\\textbf{");
    addCloseTagLatex(l);
}

/* Início de itálico em latex */
void beginItalicLatex(LinkedList l){
    printf("\\textit{");
    addCloseTagLatex(l);
}

/* Início de sublinhado em latex */ 
void beginUnderlineLatex(LinkedList l){
    printf("\\underline{");
    addCloseTagLatex(l);
}

/* Início de um título em latex */ 
void beginTitleLatex(LinkedList l,int level){
    int i;
    printf("\\");
    for(i=1; i<level; i++)
           printf("sub");
    printf("section{");
    addCloseTagLatex(l);
}

/* Adiciona á lista ligada a tag default de fim em latex */
void addCloseTagLatex(LinkedList l){
    pushLinkedList(l,(void*)"}");
}

/* Tag de índice em latex */
void addIndexLatex(){
	printf("\\tableofcontents");
}

/* Início de uma lista ordenada em latex */
void beginOrderListLatex(){
    printf("\\begin{enumerate}");
}

/* Fim de uma lista ordenada em latex */
void endOrderListLatex(){
    printf("\\end{enumerate}");
}

/* Início de uma lista não ordenada em latex */
void beginUnorderListLatex(){
    printf("\\begin{itemize}");
}

/* Fim de uma lista não ordenada em latex */
void endUnorderListLatex(){
    printf("\\end{itemize}");
}

/* Início de um dicionário em latex */
void beginDictionaryLatex(){
    printf("\\begin{description}");
}

/* Fim de um dicionário em latex */
void endDictionaryLatex(){
    printf("\\end{description}");
}

/* Início de entrada de dicionário */
void beginDictionaryEntryLatex(LinkedList l){
    printf("\\item[");
    pushLinkedList(l,(void*)"]");
}

/* Adiciona item numa lista */
void addItemLatex(){
    printf("\\item ");
}

/* Início de uma imagem em Latex */
void beginImageLatex(LinkedList l){
    printf("\\begin{figure}[h]\n");
    printf("\\centering\n");
    printf("\\includegraphics{");
    pushLinkedList(l,(void*)"}\n\\end{figure}");
} 

/* Fim do include graphics de uma imagem */
void endImagePathLatex(){
    printf("}\n");
}

/* Início da legenda de uma imagem em Latex */
void beginImageCaptionLatex(){
    printf("\\caption{");
}

/* Início de um link em Latex */
void beginLinkLatex(LinkedList l){
    printf("\\href{");
    addCloseTagLatex(l);
}

/* Fim do campo URL de um link em Latex */
void endURLLatex(){
    printf("}");
}

/* Início do campo Texto de um link em Latex */
void beginLinkTextLatex(){
    printf("{");
}

/* Comentário de linha em Latex */
void addLineCommentLatex(){
    printf("%s","%");
}

/* Início de comentário multilinha em Latex */
void beginCommentLatex(){
    printf("\\begin{comment}");
}

/* Fim de comentário multilinha em Latex */
void endCommentLatex(){
    printf("\\end{comment}");
}

/* Início de verbatim em Latex */
void beginVerbatimLatex(){
    printf("\\begin{verbatim}");
}

/* Fim de verbatim em Latex */
void endVerbatimLatex(){
    printf("\\end{verbatim}");
}

/* Início de verbatim de linha em Latex */
void beginVerbatimLineLatex(){
    printf("\\verb@");
}

/* Fim de verbatim de linha em Latex */
void endVerbatimLineLatex(){
    printf("@");
}

/* Capa em Latex */
void addCoverLatex(){
    printf("\\maketitle");
}

/* Título em Latex */
void addTitleLatex(char* title){
    printf("\\title{ %s }",title);
}

/* Autor em Latex */
void addAuthorLatex(char* author){
    printf("\\author{ %s }",author);
}

/* Título em Latex */
void addDateLatex(char* date){
    printf("\\date{ %s }",date);
}

/* Imprime as colunas de uma tabela */
void printColumns(LinkedElem columns, int head){
    if(columns){
        char* column = (char*) columns->data;
        printColumns(columns->next,head);
        
        if(head){
            printf(" \\textbf{ %s } ",column);
        }else{
            printf(" %s ",column);
        }

        if(!columns->next){
            printf("&");
        }
    }
}

/* Imprime as linhas de uma tabela */
void printRows(LinkedElem table){
    if(table){

        Row row = (Row) table->data;
        
        printRows(table->next);
        if(table->next){
            printf("\\\\\n"); 
        }
        printf("\\hline\n");  
    
        printColumns(row->columns->elems,row->head);
    }
}

/* Faz tabela em Latex */
void addTableLatex(LinkedList table){
    int i,max = 0;
    LinkedElem rows = table->elems;
    while(rows){
        Row row = (Row) rows->data;
        if(row->nrColumns > max){
            max = row->nrColumns;
        }
        rows = rows->next;
    }

    printf("\\begin{table}[!htpb]\n");
    printf("\\centering\n");
    printf("\\begin{tabular}{||");
    for(i=0;i<max;i++){
        printf("c|");
    }
    printf("|}\n");

    printRows(table->elems);

    printf("\\\\\n\\hline\n\\end{tabular}\n");
    printf("\\end{table}\n");

    clearLinkedList(table);
}

/* Coluna de uma tabela em Latex */
void newColumnLatex(LinkedList table, char* c){
    Row row = (Row) table->elems->data;

    row->nrColumns++;

    char* column = (char*) malloc (sizeof (c));

    strcpy(column,c);

    pushLinkedList(row->columns,column);
}

/* Linha de uma tabela em Latex */
void newRowLatex(LinkedList table, char* c, int head){
    Row row = createRow(head);
    
    row->nrColumns++;
    
    char* column = (char*) malloc (sizeof (c));
    strcpy(column,c);

    pushLinkedList(row->columns,column);

    pushLinkedList(table,row);
}
