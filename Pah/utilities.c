#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilities.h"

char* substring(char* str, int posi, int offset){
    char *res = (char*) malloc (offset) ;    
    str+=posi;
    strncpy(res, str, offset) ;
    return res;
}
