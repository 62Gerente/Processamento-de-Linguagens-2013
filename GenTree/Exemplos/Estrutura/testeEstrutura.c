#include <glib.h>
#include "../../Estruturas/Individuo.h"
#include "../../Estruturas/Evento.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {

    Individuo* andre = (Individuo*) malloc (sizeof(Individuo));

    andre->id = 1;
    andre->nome = strdup("Andre Santos");
    
    Individuo* manuel = (Individuo*) malloc (sizeof(Individuo));
    manuel->nome = strdup("Manuel Santos");
    manuel->eventos = NULL;

    andre->pai = manuel;
    
    andre->historias = g_list_prepend(andre->historias,"História linda");
    andre->historias = g_list_prepend(andre->historias,"História feia");

    Evento* jogo = (Evento*) malloc (sizeof(Evento));
    jogo->descricao = strdup("Gerente faz 10 golos");

    Evento* corrida = (Evento*) malloc (sizeof(Evento));
    corrida->descricao = strdup("Gerente corre muito");

    andre->pai->eventos = g_list_append(andre->pai->eventos,jogo); 
    andre->pai->eventos = g_list_insert(andre->pai->eventos,corrida,1); 

    printf("Nome: %s\n",andre->nome);
    printf("Nome Pai: %s\n",andre->pai->nome);
    g_list_foreach(andre->historias, (GFunc)printf, NULL);


    printf("\n");

    int i;

    GList* evpai = andre->pai->eventos; 

    evpai = g_list_reverse(evpai);


    printf("Nr Eventos: %d\n",g_list_length(evpai));

    for(i=0; i<g_list_length(evpai); i++)
        printf("Evento: %s\n",
                ((Evento*)g_list_nth_data(evpai,i))->descricao);

    
    return 0; 
}
