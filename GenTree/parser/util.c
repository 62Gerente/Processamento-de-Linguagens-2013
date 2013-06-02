#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"

Individuo* init_individuo () {

    Individuo *indiv = (Individuo*) malloc (sizeof(Individuo)) ;
    indiv->id = ID_NULO ;
    indiv->sexo = 0 ;
    indiv->nome = indiv->data_nascimento = indiv->data_morte = indiv->data_casamento = indiv->foto = NULL ;
    indiv->idPai = indiv->idMae = indiv->idConjugue = ID_NULO ;
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

void imprimir_individuo_hash (gpointer chave, gpointer valor, gpointer user_data) {
  
  if(valor == NULL)
    return ;
  if(user_data != NULL || !chave)
    user_data = NULL ;
  Individuo *i = (Individuo*)valor ;
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
  if(i->idPai != ID_NULO) {
    printf("  Pai: %d\n", i->idPai) ;
  }
  if(i->idMae != ID_NULO) {
    printf("  Mae: %d\n", i->idMae) ;
  }
  if(i->idConjugue != ID_NULO) {
    printf("  Conjugue: %d\n", i->idConjugue) ;
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

gboolean compararIndividuo (gconstpointer a, gconstpointer b) {

  if( a == NULL || b == NULL)
    return FALSE ;
  int *i1 = (int*)a ;
  int *i2 = (int*)b ;
  if(*i1 == *i2)
    return TRUE ;
  else
    return FALSE ;
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

Individuo* processarCasamentoHash (Individuo* conjugue) {

  if(conjugue == NULL)
    return NULL;
  Individuo *res = init_individuo() ;
  Individuo *noivo_pesq = (Individuo*)g_hash_table_lookup(pessoasHash, &(conjugue->id)) ;
  int *chave = (int*) malloc (sizeof(int)) ;
  *chave = conjugue->id ;
  res->idConjugue = *chave ;
  res->data_casamento = conjugue->data_casamento ;
  if(noivo_pesq == NULL) {
    g_hash_table_insert(pessoasHash, chave, conjugue) ;
  }
  else {
    g_hash_table_insert(pessoasHash, chave, indivRec(noivo_pesq, conjugue)) ;
  }
  ParentPorResolver *prr = (ParentPorResolver*) malloc (sizeof(ParentPorResolver)) ;
  char *parentesco = (char*) malloc(sizeof(char)*3) ; parentesco[0] = 'C' ; parentesco[1] = 'C' ; parentesco[2] = '\0' ;
  prr->parentesco = parentesco ;
  prr->id = *chave ;
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
  if(i1 && i1->id != ID_NULO)
    res->id = i1->id ;
  else if(i2 && i2->id != ID_NULO)
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
  if(i1 && i1->idPai != ID_NULO)
      res->idPai = i1->idPai ;
  else if(i2 && i2->idPai != ID_NULO)
    res->idPai = i2->idPai ;
  if(i1 && i1->idMae != ID_NULO)
    res->idMae = i1->idMae ;
  else if(i2 && i2->idMae != ID_NULO)
    res->idMae = i2->idMae ;
  if(i1 && i1->idConjugue != ID_NULO)
    res->idConjugue = i1->idConjugue ;
  else if(i2 && i2->idConjugue != ID_NULO)
    res->idConjugue = i2->idConjugue ;

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

Individuo* processarParentescoHash (char* parentesco, Individuo* i) {
  
  if(parentesco == NULL || i == NULL)
    return NULL ;
  Individuo *res = init_individuo() ;
  Individuo *iPesq = g_hash_table_lookup(pessoasHash, &(i->id)) ;
  int *chave = (int*) malloc (sizeof(int)) ;
  *chave = i->id ;
  if(iPesq == NULL)
    g_hash_table_insert(pessoasHash, chave, i) ;
  else
    g_hash_table_insert(pessoasHash, chave, indivRec(iPesq, i)) ;
  if(strcmp(parentesco, "M") == 0)
    res->idMae = *chave ;
  else if(strcmp(parentesco, "P") == 0)
    res->idPai = *chave ;
  else {
    ParentPorResolver *prr = init_parentesco() ;
    prr->parentesco = parentesco ;
    prr->id = *chave ;
    res->parentescos = g_list_append(res->parentescos, prr) ;
  }
  return res ;
}    

void resolverUmParentescoHash (Individuo *i, ParentPorResolver *prr) {

  if(!i || !prr)
    return ;
  Individuo *iPesq = g_hash_table_lookup(pessoasHash, &(prr->id)), *p ;
  if(iPesq == NULL)
    return ;
  if(strcmp(prr->parentesco, "MP") == 0) {
    p = g_hash_table_lookup(pessoasHash, &(i->idMae)) ;
    if(p != NULL)
      p->idPai = prr->id ;
  }
  else if(strcmp(prr->parentesco, "MM") == 0) {
    p = g_hash_table_lookup(pessoasHash, &(i->idMae)) ;
    if(p != NULL)
      p->idMae = prr->id ;
  }
  else if(strcmp(prr->parentesco, "PM") == 0) {
    p = g_hash_table_lookup(pessoasHash, &(i->idPai)) ;
    if(p != NULL)
      p->idMae = prr->id ;
  }
  else if(strcmp(prr->parentesco, "PP") == 0) {
    p = g_hash_table_lookup(pessoasHash, &(i->idPai)) ;
    if(p != NULL)
      p->idPai = prr->id ;
  }
  else if(strcmp(prr->parentesco, "F") == 0) {
    if(i->sexo == 1)
      iPesq->idPai = i->id ;
    else if (i->sexo == 2)
      iPesq->idMae = i->id ;
  } else if(strcmp(prr->parentesco, "CC") == 0) {
    iPesq->idConjugue = i->id ;
  }
}

void resolverParentescosHash (gpointer chave, gpointer valor, gpointer userData) {
  
  if(userData || chave)
    userData = NULL ;
  if(!valor)
    return ;
  Individuo *i = (Individuo*)valor ;
  for(; g_list_length(i->parentescos) > 0 ;) {
    ParentPorResolver *prr = (ParentPorResolver*)(i->parentescos->data) ;
    resolverUmParentescoHash(i, prr) ;
    i->parentescos = g_list_remove(i->parentescos, prr) ;
  }
  g_list_free(i->parentescos) ;
}

void resolverTodosOsParentescos () {

  g_hash_table_foreach(pessoasHash, resolverParentescosHash, NULL) ;
}

void inserirIndividuo (Individuo *i) {

  int *chave = (int*) malloc (sizeof(int)) ;
  *chave = i->id ;
  Individuo *iPesq = (Individuo*) g_hash_table_lookup(pessoasHash, chave) ;
  if(iPesq == NULL) {
    g_hash_table_insert(pessoasHash, chave, i) ;
  } else {
    g_hash_table_insert(pessoasHash, chave, indivRec(iPesq, i)) ;
  }
}

int encontrarId () {
  
  gboolean flag = TRUE ;
  int i = idIndividuo ;
  while(flag) {
    if(g_hash_table_lookup(pessoasHash, &i) == NULL)
      flag = FALSE ;
    else
      i++ ;
  }
  idIndividuo = i+1 ;
  return i ;
}
