#include "toHTML.h"
#include "../Estruturas/Individuo.h"
#include "../Estruturas/Evento.h"
#include <glib.h>

int main(){

    Evento* museu = (Evento*) malloc (sizeof(Evento));
    museu->id = 1;
    museu->nome = strdup("Visita ao Museu");
    museu->data = strdup("25/10/1998");
    museu->descricao = strdup("Visita guiada ao Museu D. Diogo de Souza em Braga, grupo de arqueólogos de braga e famílias");

    Evento* churrasco = (Evento*) malloc (sizeof(Evento));
    churrasco->id = 2;
    churrasco->nome = strdup("Churrasco");
    churrasco->descricao = strdup("Churrasco familiar no magusto em casa dos visinhos ");

    Evento* visita = (Evento*) malloc (sizeof(Evento));
    visita->id = 3;
    visita->nome = strdup("Visita de estudo");
    visita->data = strdup("15/11/1918");
    visita->descricao = strdup("Visita de estudo aos laboratórios da universidade do minho, no intuito da disciplica de Fisica e Quimica");


    GList* individuos = NULL;

    Individuo* andre = (Individuo*) malloc (sizeof(Individuo));

    andre->id = 1;
    andre->nome = strdup("André Augusto Costa Santos");
    andre->sexo = 1;

    andre->historias = g_list_prepend(andre->historias,"../Dados/Historias/latim.txt");
    andre->historias = g_list_prepend(andre->historias,"../Dados/Historias/capuchinho.txt");

    Individuo* maria = (Individuo*) malloc (sizeof(Individuo));

    maria->id = 2;
    maria->nome = strdup("Luísa Maria Carneiro Costa");
    maria->sexo = 2;
    maria->foto = "../Dados/Fotos/4.jpg";

    maria->eventos = g_list_prepend(maria->eventos,museu);
    maria->eventos = g_list_prepend(maria->eventos,churrasco);
    maria->eventos = g_list_prepend(maria->eventos,visita);

    andre->mae=maria;

    Individuo* manuel = (Individuo*) malloc (sizeof(Individuo));

    manuel->id = 3;
    manuel->nome = strdup("Manuel Ruas da Costa");
    
    manuel->historias = g_list_prepend(manuel->historias,"../Dados/Historias/latim.txt");

    maria->pai=manuel;

    Individuo* amelia = (Individuo*) malloc (sizeof(Individuo));

    amelia->id = 4;
    amelia->nome = strdup("Amélia Carneiro Costa");
    amelia->sexo = 2;

    maria->mae = amelia;
    manuel->conjugue=amelia;
    amelia->conjugue=manuel;

    amelia->eventos = g_list_prepend(amelia->eventos,museu);
    amelia->eventos = g_list_prepend(amelia->eventos,visita);


    individuos = g_list_prepend(individuos,manuel);
    individuos = g_list_prepend(individuos,andre);
    individuos = g_list_prepend(individuos,maria);
    individuos = g_list_prepend(individuos,amelia);


    toHTML(individuos);
    return 0;
}
