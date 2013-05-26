#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"

Individuo* init_individuo () {

    Individuo *indiv = (Individuo*) malloc (sizeof(Individuo)) ;
    indiv->id = -1 ;
    indiv->sexo = 0 ;
    indiv->nome = indiv->data_nascimento = indiv->data_morte = indiv->data_casamento = indiv->foto = NULL ;
    indiv->pai = indiv->mae = indiv->conjugue = NULL ;
    indiv->historias = indiv->eventos = NULL ;
    return indiv ;
}

Evento* init_evento () {
  
  Evento *ev = (Evento*) malloc (sizeof(Evento)) ;
  ev->id = -1 ;
  ev->nome = ev->descricao = ev->data = NULL ;
  return ev ;
}


void imprimir_individuo (gpointer data, gpointer user_data) {
  
  if(user_data)
    user_data = NULL ;
  Individuo *i = (Individuo*)data ;
  printf("Individuo\n") ;
  printf("  Id: %d\n", i->id) ;
  if(i->nome != NULL)
    printf("  Nome: %s\n", i->nome) ;
  printf("  Sexo: %d\n", i->sexo) ;
  if(i->data_nascimento != NULL)
    printf("  Data de nascimento: %s\n", i->data_nascimento) ;
  if(i->data_morte != NULL)
    printf("  Data de morte: %s\n", i->data_morte) ;
  if(i->data_casamento != NULL)
    printf("  Data de casamento: %s\n", i->data_casamento) ;
  if(i->foto != NULL)
    printf("  Foto: %s\n", i->foto) ;
  if(i->pai != NULL)
    imprimir_individuo(i->pai, NULL) ;
  if(i->mae != NULL)
    imprimir_individuo(i->mae, NULL) ;
  if(i->conjugue != NULL)
    imprimir_individuo(i->conjugue, NULL) ;
  if(i->historias != NULL)
    g_list_foreach(i->historias, (GFunc)printf, NULL) ;
  if(i->eventos != NULL)
    g_list_foreach(i->eventos, (GFunc)imprimir_evento, NULL) ;
}

char* g_list_para_string (GList *nomes) {

  char *res ;
  int tamanho = 1 ;
  int comprimento = g_list_length(nomes) ;
  int i ;
  for(i = 0; i < comprimento; i++) 
    tamanho += strlen((char*)g_list_nth_data(nomes, i)) ;
  res = (char*) malloc (tamanho) ;
  memset(res, '\0', tamanho) ;
  for(i = 0; i < comprimento; i++) 
    strcat(res, (char*)g_list_nth_data(nomes, i)) ;
  return res ;
}

char* adicionar_espaco_inicio (char* str) {
  
  char* aux = strdup(str) ;
  memset(str, '\0', strlen(str)) ;
  str[0] = ' ' ;
  strcat(str, aux) ;
  free(aux) ;
  return str ;
}

gint comparar_individuo (gconstpointer a, gconstpointer b) {

  Individuo *i1 = (Individuo*)a ;
  Individuo *i2 = (Individuo*)b ;
  if(i1->id == i2->id)
    return 0 ;
  else if(i1->id > i2->id)
    return 1 ;
  else
    return -1 ;
}

Individuo* encontrar_individuo (GList* lista, int id) {
  
  Individuo *aux = init_individuo() ;
  aux->id = id ;
  Individuo *i = (Individuo*)(g_list_find_custom(lista, aux, comparar_individuo)->data) ;
  free(aux);
  return i ;
}

gint comparar_evento (gconstpointer a, gconstpointer b) {

  Evento *e1 = (Evento*)a ;
  Evento *e2 = (Evento*)b ;
  if(e1->id == e2->id)
    return 0 ;
  else if(e1->id > e2->id)
    return 1 ;
  else
    return -1 ;
}

Evento* encontrar_evento (GList* lista, int id) {
  
  Evento *aux = init_evento() ;
  aux->id = id ;
  Evento *i = (Evento*)(g_list_find_custom(lista, aux, comparar_evento)->data) ;
  free(aux);
  return i ;
}

void processar_casamento (GList **lista, Individuo* actual, Individuo* conjugue) {

  if(actual == NULL || *lista == NULL || conjugue == NULL)
    return ;
  GList *l = *lista ;
  Individuo *noivo_pesq = encontrar_individuo(l, conjugue->id) ;
  if(noivo_pesq == NULL) {
    actual->conjugue = conjugue ;
    actual->data_casamento = conjugue->data_casamento ;
    conjugue->conjugue = actual ;
    *lista = g_list_append(l, conjugue) ;
  }
  else {
    noivo_pesq->data_casamento = conjugue->data_casamento ;
    noivo_pesq->conjugue = actual ;
    actual->conjugue = noivo_pesq ;
    actual->data_casamento = conjugue->data_casamento ;
  }  
}


void imprimir_evento (gpointer data, gpointer user_data) {
  
  if(user_data)
    user_data = NULL ;
  Evento *ev = (Evento*)data ;
  printf("Evento\n") ;
  printf("  Id: %d\n", ev->id) ;
  if(ev->nome != NULL)
    printf("  Nome: %s\n", ev->nome) ;
  if(ev->descricao != NULL)
    printf("  Descricao: %s\n", ev->descricao) ;
  if(ev->data != NULL)
    printf("  Data: %s\n", ev->data) ;
}
