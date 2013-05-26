#ifndef _UTIL_H_
#define _UTIL_H_

#include <glib.h>
#include "../Estruturas/Individuo.h"
#include "../Estruturas/Evento.h"

Individuo* init_individuo () ;
Evento* init_evento () ;

void imprimir_individuo (gpointer data, gpointer user_data) ;
void imprimir_eventos (GList* eventos) ;
void imprimir_historias (GList* historias) ;

char* g_list_para_string (GList *nomes) ;

char* adicionar_espaco_inicio (char* str) ;

gint comparar_individuo (gconstpointer a, gconstpointer b);
Individuo* encontrar_individuo (GList* lista, int id);

gint comparar_evento (gconstpointer a, gconstpointer b);
Evento* encontrar_evento (GList* lista, int id);

void processar_casamento (GList **lista, Individuo* actual, Individuo* conjugue) ;

void imprimir_evento (gpointer data, gpointer user_data) ;
#endif
