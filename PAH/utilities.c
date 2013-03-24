#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilities.h"
#include "LinkedList/linkedlist.h"

char* substring(char* str, int posi, int offset){
    char *res = (char*) malloc (offset) ;    
    str+=posi;
    strncpy(res, str, offset) ;
    return res;
}

Row createRow(int head){
    Row new = (Row) malloc (sizeof (struct sRow));
    new->nrColumns = 0;
    new->head = head;
    new->columns = createLinkedList(NULL,NULL);

    return new;
}
