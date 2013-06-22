#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include "LinkedList/linkedlist.h"

/* Estrutura para uma linha */
typedef struct sRow{
    int nrColumns;
    int head;
    LinkedList columns;
}*Row;

/* Função que dá uma string parcial */
char* substring(char* str, int posi, int offset);

/* Função que cria uma linha de uma tabela*/
Row createRow(int head);






#endif
