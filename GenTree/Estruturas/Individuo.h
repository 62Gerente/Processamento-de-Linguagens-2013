#ifndef _INDIV_H_
#define _INDIV_H_

#include <glib.h>

typedef struct sIndividuo{
    int id;
    char* nome;
    int sexo;                       // 0-ND 1-M 2-F
    char* data_nascimento;
    char* data_morte;
    char* data_casamento;
    char* foto;

    struct sIndividuo *pai; 
    struct sIndividuo *mae;
    struct sIndividuo *conjugue;

    GList* historias;
    GList* eventos;

}Individuo;

#endif
