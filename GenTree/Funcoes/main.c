#include "toHTML.h"
#include <glib.h>

int main(){

    GList* individuos = NULL;

    Individuo* andre = (Individuo*) malloc (sizeof(Individuo));

    andre->id = 1;
    andre->nome = strdup("André Augusto Costa Santos");
    andre->sexo = 1;

    Individuo* maria = (Individuo*) malloc (sizeof(Individuo));

    maria->id = 2;
    maria->nome = strdup("Luísa Maria Carneiro Costa");
    maria->sexo = 2;
    maria->foto = "../Dados/Fotos/4.jpg";

    andre->mae=maria;

    Individuo* manuel = (Individuo*) malloc (sizeof(Individuo));

    manuel->id = 3;
    manuel->nome = strdup("Manuel Ruas da Costa");
    
    maria->pai=manuel;

    Individuo* amelia = (Individuo*) malloc (sizeof(Individuo));

    amelia->id = 4;
    amelia->nome = strdup("Amélia Carneiro Costa");
    amelia->sexo = 2;

    maria->mae = amelia;
    manuel->conjugue=amelia;
    amelia->conjugue=manuel;

    individuos = g_list_prepend(individuos,manuel);
    individuos = g_list_prepend(individuos,andre);
    individuos = g_list_prepend(individuos,maria);
    individuos = g_list_prepend(individuos,amelia);


    toHTML(individuos);
    return 0;
}
