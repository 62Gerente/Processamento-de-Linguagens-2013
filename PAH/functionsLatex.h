#ifndef _FUNCTIONS_LATEX_H
#define _FUNCTIONS_LATEX_H

#include "LinkedList/linkedlist.h"

/* Função que fecha a ultima tag aberta */
void endLatexTag(LinkedList l);

/* Início de negrito em latex */
void beginBoldLatex(LinkedList l);

/* Início de itálico em latex */
void beginItalicLatex(LinkedList l);

/* Início de sublinhado em latex */ 
void beginUnderlineLatex(LinkedList l);

/* Início de um título em latex */ 
void beginTitleLatex(LinkedList l,int level);

/* Adiciona á lista ligada a tag default de fim em latex */
void addCloseTagLatex(LinkedList l);

/* Tag de índice em latex */
void addIndexLatex();

/* Início de uma lista ordenada em latex */
void beginOrderListLatex();

/* Fim de uma lista ordenada em latex */
void endOrderListLatex();

/* Início de uma lista não ordenada em latex */
void beginUnorderListLatex();

/* Fim de uma lista não ordenada em latex */
void endUnorderListLatex();

/* Início de um dicionário em latex */
void beginDictionaryLatex();

/* Fim de um dicionário em latex */
void endDictionaryLatex();

/* Início de entrada de dicionário */
void beginDictionaryEntryLatex(LinkedList l);

/* Adiciona item numa lista */
void addItemLatex();

/* Início de uma imagem em Latex */
void beginImageLatex(LinkedList l);

/* Fim do include graphics de uma imagem */
void endImagePathLatex();

/* Início da legenda de uma imagem em Latex */
void beginImageCaptionLatex();

/* Início de um link em Latex */
void beginLinkLatex(LinkedList l);

/* Fim do campo URL de um link em Latex */
void endURLLatex();

/* Início do campo Texto de um link em Latex */
void beginLinkTextLatex();

/* Comentário de linha em Latex */
void addLineCommentLatex();

/* Início de comentário multilinha em Latex */
void beginCommentLatex();

/* Fim de comentário multilinha em Latex */
void endCommentLatex();

/* Início de verbatim em Latex */
void beginVerbatimLatex();

/* Fim de verbatim em Latex */
void endVerbatimLatex();

/* Início de verbatim de linha em Latex */
void beginVerbatimLineLatex();

/* Fim de verbatim de linha em Latex */
void endVerbatimLineLatex();

/* Capa em Latex */
void addCoverLatex();

/* Título em Latex */
void addTitleLatex(char* title);

/* Autor em Latex */
void addAuthorLatex(char* author);

/* Título em Latex */
void addDateLatex(char* date);

/* Faz tabela em Latex */
void addTableLatex(LinkedList table);

/* Coluna de uma tabela em Latex */
void newColumnLatex(LinkedList table, char* c);

/* Linha de uma tabela em Latex */
void newRowLatex(LinkedList table, char* column, int head);

#endif
