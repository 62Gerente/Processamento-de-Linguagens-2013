#ifndef _UTIL_H_
#define _UTIL_H_

#include <glib.h>
#include "../Estruturas/Individuo.h"
#include "../Estruturas/Evento.h"

#define ID_NULO -1

extern GHashTable *pessoasHash ;
extern int idIndividuo ;

Individuo* init_individuo () ;
Evento* init_evento () ;

void imprimir_individuo_hash (gpointer chave, gpointer valor, gpointer user_data) ;
void imprimir_eventos (GList* eventos) ;
void imprimir_historias (GList* historias) ;

char* g_list_para_string (GList *nomes) ;

char* adicionar_espaco_inicio (char* str) ;

gboolean compararIndividuo (gconstpointer a, gconstpointer b);

gint comparar_evento (gconstpointer a, gconstpointer b);
Evento* encontrar_evento (GList* lista, int id);

Individuo* processarCasamentoHash (Individuo* conjugue) ;

void imprimir_evento (gpointer data, gpointer user_data) ;

Evento* eventoRec (Evento* e1, Evento* e2) ;
Individuo* indivRec (Individuo* i1, Individuo* i2) ;

char* substring(char* str, int posi, int offset) ;

Individuo* processarParentescoHash (char* parentesco, Individuo* i) ;

void resolverUmParentescoHash (Individuo *i, ParentPorResolver *prr) ;
void resolverParentescosHash (gpointer chave, gpointer valor, gpointer userData) ;
void resolverTodosOsParentescos () ;

void casamentoAvos(int ela, int ele) ;

void inserirIndividuo (Individuo *i) ;
int encontrarId () ;
#endif
