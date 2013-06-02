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

  int idPai ;
  int idMae ;
  int idConjugue ;

  GList* historias;               // Glist de char*
  GList* eventos;                 // Glist de Evento*
  GList* parentescos;             // GList de Relacoes por resolver* 

}Individuo;

typedef struct sParentPorResolver {

  char* parentesco ;
  int id ;
} ParentPorResolver ;

#endif
