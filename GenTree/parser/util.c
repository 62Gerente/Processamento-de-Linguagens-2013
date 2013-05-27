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
  
  if(nomes == NULL)
    return NULL ;
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


Evento* eventoRec (Evento* e1, Evento* e2) {

  Evento* res = init_evento();
  if(e1 && e1->id != -1)
    res->id = e1->id ;
  else if(e2 && e2->id != -1)
    res->id = e2->id ;
  if(e1 && e1->nome != NULL)
    res->nome = e1->nome ;
  else if(e2 && e2->nome != NULL)
    res->nome = e2->nome ;
  if(e1 && e1->descricao != NULL)
    res->descricao = e1->descricao ;
  else if(e2 && e2->descricao != NULL)
    res->descricao = e2->descricao ;
  if(e1 && e1->data != NULL)
    res->data = e1->data ;
  else if(e2 && e2->data != NULL)
    res->data = e2->data ;
  if(e1)
    free(e1);
  if(e2)
    free(e2);
  return res ;  
}

Individuo* indivRec (Individuo* i1, Individuo* i2) {

  Individuo* res = init_individuo() ;
  if(i1 && i1->id != -1)
    res->id = i1->id ;
  else if(i2 && i2->id != -1)
    res->id = i2->id ;
  if(i1 && i1->nome != NULL)
    res->nome = i1->nome ;
  else if(i2 && i2->nome != NULL)
    res->nome = i2->nome ;
  if(i1 && i1->sexo != 0)
    res->sexo = i1->sexo ;
  else if(i2 && i2->sexo != 0)
    res->sexo = i2->sexo ;
  if(i1 && i1->data_nascimento != NULL)
    res->data_nascimento = i1->data_nascimento ;
  else if(i2 && i2->data_nascimento != NULL)
    res->data_nascimento = i2->data_nascimento ;
  if(i1 && i1->data_morte != NULL)
    res->data_morte = i1->data_morte ;
  else if(i2 && i2->data_morte != NULL)
    res->data_morte = i2->data_morte ;
  if(i1 && i1->data_casamento != NULL)
    res->data_casamento = i1->data_casamento ;
  else if(i2 && i2->data_casamento != NULL)
    res->data_casamento = i2->data_casamento ;
  if(i1 && i1->foto != NULL)
    res->foto = i1->foto ;
  else if(i2 && i2->foto != NULL)
    res->foto = i2->foto ;
  if(i1 && i1->pai != NULL)
    res->pai = i1->pai ;
  else if(i2 && i2->pai != NULL)
    res->pai = i2->pai ;
  if(i1 && i1->mae != NULL)
    res->mae = i1->mae ;
  else if(i2 && i2->mae != NULL)
    res->mae = i2->mae ;
  if(i1 && i1->conjugue != NULL)
    res->conjugue = i1->conjugue ;
  else if(i2 && i2->conjugue != NULL)
    res->conjugue = i2->conjugue ;

  if(i1 && i2)
    res->historias = g_list_concat(i1->historias, i2->historias) ;
  else if(i1)
    res->historias = i1->historias ;
  else if(i2)
    res->historias = i2->historias ;
   
  if(i1 && i2)
    res->eventos = g_list_concat(i1->eventos, i2->eventos) ;
  else if(i1)
    res->eventos = i1->eventos ;
  else if(i2)
    res->eventos = i2->eventos ;

  if(i1)
    free(i1);
  if(i2)
    free(i2);
  return res ;
}

char* substring(char* str, int posi, int offset){
 
  char *res = (char*) malloc (offset+1) ;    
  str+=posi;
  memset(res, '\0', offset+1);
  strncpy(res, str, offset) ;
  res[offset] = '\0' ;
  return res;
}

Individuo* processarParentesco (char* parentesco, Individuo* i, GList** l) {
  
  Individuo *res = init_individuo() ;
  Individuo *iPesq = encontrar_individuo(*l, i->id) ;
  if(iPesq == NULL)
    *l = g_list_append(*l, i) ;
  if(strcmp(parentesco, "M") == 0)
    res->mae = i ;
  else if(strcmp(parentesco, "P") == 0)
    res->pai = i ;
  return res ;
}
    
