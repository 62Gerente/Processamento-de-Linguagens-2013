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
    indiv->historias = indiv->eventos = indiv->parentescos = NULL ;
    return indiv ;
}

Evento* init_evento () {
  
  Evento *ev = (Evento*) malloc (sizeof(Evento)) ;
  ev->id = -1 ;
  ev->nome = ev->descricao = ev->data = NULL ;
  return ev ;
}

ParentPorResolver* init_parentesco () {

  ParentPorResolver *res = (ParentPorResolver*) malloc (sizeof(ParentPorResolver)) ;
  res->parentesco = NULL ;
  res->id = -1 ;
  return res ;
}

void imprimir_individuo (gpointer data, gpointer user_data) {
  
  if(data == NULL)
    return ;
  if(user_data != NULL)
    user_data = NULL ;
  Individuo *i = (Individuo*)data ;
  printf("Individuo\n") ;
  printf("  Id: %d\n", i->id) ;
  if(i->nome != NULL)
    printf("  Nome: %s\n", i->nome) ;
  if(i->sexo != 0)
    printf("  Sexo: %d\n", i->sexo) ;
  if(i->data_nascimento != NULL)
    printf("  Data de nascimento: %s\n", i->data_nascimento) ;
  if(i->data_morte != NULL)
    printf("  Data de morte: %s\n", i->data_morte) ;
  if(i->data_casamento != NULL)
    printf("  Data de casamento: %s\n", i->data_casamento) ;
  if(i->foto != NULL)
    printf("  Foto: %s\n", i->foto) ;
  if(i->pai != NULL) {
    printf("  Pai: %d\n", i->pai->id) ;
  }
  if(i->mae != NULL) {
    printf("  Mae: %d\n", i->mae->id) ;
  }
  if(i->conjugue != NULL) {
    printf("  Conjugue: %d\n", i->conjugue->id) ;
  }
  if(i->historias != NULL) {
    printf("  Historias: ") ;
    g_list_foreach(i->historias, (GFunc)printf, NULL) ;
    printf("\n") ;
  }
  if(i->eventos != NULL) {
    printf("  Eventos: ") ;
    g_list_foreach(i->eventos, (GFunc)imprimir_evento, (int*)1) ;
    printf("\n") ;
  }
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
  
  if(str == NULL)
    return NULL ;
  char* aux = strdup(str) ;
  memset(str, '\0', strlen(str)) ;
  str[0] = ' ' ;
  strcat(str, aux) ;
  free(aux) ;
  return str ;
}

gint comparar_individuo (gconstpointer a, gconstpointer b) {

  int res ;
  if( a == NULL || b == NULL)
    return -1 ;
  Individuo *i1 = (Individuo*)a ;
  Individuo *i2 = (Individuo*)b ;
  if(i1->id == i2->id)
    res = 0 ;
  else if(i1->id > i2->id)
    res = 1 ;
  else
    res = -1 ;
  return res ;
}

Individuo* encontrar_individuo (GList* lista, int id) {
  
  if(lista == NULL)
    return NULL ;
  Individuo *i = NULL ;
  Individuo *aux = init_individuo() ;
  aux->id = id ;
  GList *l_aux = g_list_find_custom(lista, aux, comparar_individuo) ;
  if(l_aux != NULL)
    i = (Individuo*)l_aux->data ;
  free(aux);
  return i ;
}

gint comparar_evento (gconstpointer a, gconstpointer b) {

  if( a == NULL || b == NULL)
    return -1 ;
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
  
  Evento *aux = init_evento(), *res = NULL ;
  aux->id = id ;
  GList *l_aux = g_list_find_custom(lista, aux, comparar_evento) ;
  if(l_aux)
    res = l_aux->data ;
  free(aux);
  return res ;
}

Individuo* processarCasamento (Individuo* conjugue, GList **lista) {

  if(conjugue == NULL || lista == NULL)
    return NULL;
  Individuo *res = init_individuo() ;
  GList *l = *lista ;
  Individuo *noivo_pesq = encontrar_individuo(l, conjugue->id) ;
  if(noivo_pesq == NULL) {
    res->conjugue = conjugue ;
    res->data_casamento = conjugue->data_casamento ;
    *lista = g_list_append(l, conjugue) ;
  }
  else {
    noivo_pesq->data_casamento = conjugue->data_casamento ;
    res->conjugue = noivo_pesq ;
    res->data_casamento = conjugue->data_casamento ;    
  }  
  ParentPorResolver *prr = (ParentPorResolver*) malloc (sizeof(ParentPorResolver)) ;
  char *parentesco = (char*) malloc(sizeof(char)*3) ; parentesco[0] = 'C' ; parentesco[1] = 'C' ; parentesco[2] = '\0' ;
  prr->parentesco = parentesco ;
  prr->id = conjugue->id ;
  res->parentescos = g_list_append(res->parentescos, prr) ;
  return res ;
}


void imprimir_evento (gpointer data, gpointer user_data) {
  
  if(data == NULL)
    return ;
  Evento *ev = (Evento*)data ;
  if(user_data)
    printf(" %d", ev->id) ;
  else {
    printf("Evento\n") ;
    printf("  Id: %d\n", ev->id) ;
    if(ev->nome != NULL)
      printf("  Nome: %s\n", ev->nome) ;
    if(ev->descricao != NULL)
      printf("  Descricao: %s\n", ev->descricao) ;
    if(ev->data != NULL)
      printf("  Data: %s\n", ev->data) ;
  }
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

  if(i1 && i2)
    res->parentescos = g_list_concat(i1->parentescos, i2->parentescos) ;
  else if(i1)
    res->parentescos = i1->parentescos ;
  else if(i2)
    res->parentescos = i2->parentescos ;

  if(i1)
    free(i1);
  if(i2)
    free(i2);
  return res ;
}

char* substring(char* str, int posi, int offset){
 
  if(str == NULL)
    return NULL ;
  char *res = (char*) malloc (offset+1) ;    
  str+=posi;
  memset(res, '\0', offset+1);
  strncpy(res, str, offset) ;
  res[offset] = '\0' ;
  return res;
}

Individuo* processarParentesco (char* parentesco, Individuo* i, GList** l) {
  
  if(parentesco == NULL || i == NULL || l == NULL)
    return NULL ;
  Individuo *res = init_individuo() ;
  Individuo *iPesq = encontrar_individuo(*l, i->id) ;
  if(iPesq == NULL)
    *l = g_list_append(*l, i) ;
  else
    i = iPesq ;
  if(strcmp(parentesco, "M") == 0)
    res->mae = i ;
  else if(strcmp(parentesco, "P") == 0)
    res->pai = i ;
  else {
    ParentPorResolver *prr = init_parentesco() ;
    prr->parentesco = parentesco ;
    prr->id = i->id ;
    res->parentescos = g_list_append(res->parentescos, prr) ;
  }
  return res ;
}
    
void resolverUmParentesco (Individuo *i, ParentPorResolver *prr,  GList *l) {

  if(!i || !prr)
    return ;
  Individuo *iPesq = encontrar_individuo(l, prr->id) ;
  if(iPesq == NULL)
    return ;
  if(strcmp(prr->parentesco, "MP") == 0) {
    if(i->mae != NULL)
      i->mae->pai = iPesq ;
  }
  else if(strcmp(prr->parentesco, "MM") == 0) {
    if(i->mae != NULL)
      i->mae->mae = iPesq ;
  }
  else if(strcmp(prr->parentesco, "PM") == 0) {
    if(i->pai != NULL)
      i->pai->mae = iPesq ;
  }
  else if(strcmp(prr->parentesco, "PP") == 0) {
    if(i->pai != NULL)
      i->pai->pai = iPesq ;
  }
  else if(strcmp(prr->parentesco, "F") == 0) {
    if(i->sexo == 1)
      iPesq->pai = i ;
    else if (i->sexo == 2)
      iPesq->mae = i;
  } else if(strcmp(prr->parentesco, "CC") == 0)
    iPesq->conjugue = i ;
}

void resolverParentescos (Individuo *i, GList *l) {
  
  if(!i)
    return ;
  unsigned int j ;
  for(j = 0; j < g_list_length(i->parentescos); j++)
    resolverUmParentesco(i, (ParentPorResolver*)g_list_nth_data(i->parentescos, j), l) ;
  g_list_free(i->parentescos) ;
}
