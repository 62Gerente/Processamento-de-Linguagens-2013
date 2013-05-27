%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Estruturas/Individuo.h"
#include "../Estruturas/Evento.h"
#include "util.h"

Individuo *indiv ;
Evento *ev;
GList *nomes ; 
GList *pessoas ;
GList *eventos ;
%}

%token NOME DATA PARENTESCO FOTO HIST CASOUCOM INFSEXO EVENTOREF EVENTO FICHEIRO NUM SEXO ESPACO
%token NOMEEVENTO DESCRICAOEVENTO TEXTO ESPACOS

%union{
  int n ;
  char* texto ;
  Individuo* indiv ;
  Evento* evento ;
  GList *lista ;
}

%type <n> NUM Id
%type <texto> NOME DATA PARENTESCO FOTO HIST CASOUCOM INFSEXO EVENTOREF EVENTO FICHEIRO SEXO ESPACOS
%type <texto> CData DataNasc DataMorte TEXTO
%type <evento> Evento EventoInf ListaEventoInf 
%type <lista> Texto MaisTexto 
%type <lista> NomeIndiv
%type <indiv> DatasOpt Individuo ListaInf Informacao RefIndividuo InformacaoExtra

%%

GenTree : ListaEvIndiv
	;

ListaEvIndiv : Evento  /*'\n'*/  ListaEvIndiv
	     | Individuo /*'\n'*/ ListaEvIndiv
	     | 
	     ;

Evento : EVENTO ESPACOS Id '\n' ListaEventoInf { $$ = eventoRec($5, NULL);  $$->id = $3; eventos = g_list_append(eventos, $$); }

ListaEventoInf : EventoInf '\n' ListaEventoInf 	 { $$ = eventoRec($1, $3);}
	       | 	   		       	 { $$ = NULL ;}
	       ;	       

EventoInf : NOMEEVENTO ESPACOS TEXTO  	  { $$ = init_evento(); $$->nome = $3 ;}
	  | DESCRICAOEVENTO ESPACOS TEXTO { $$ = init_evento(); $$->descricao = $3 ;}
	  ; 

Individuo : NOME ESPACOS NomeIndiv DatasOpt Id '\n' ListaInf  { $$ = indivRec($4, NULL); $$->id = $5; $3 = g_list_prepend($3, $1); $$->nome = g_list_para_string($3); g_list_free(nomes); $$ = indivRec($$, $7); resolverParentescos($$, pessoas); pessoas = g_list_append(pessoas, $$);}
	  ;

NomeIndiv : NOME ESPACOS NomeIndiv	{ $1 = adicionar_espaco_inicio($1); $3 = g_list_prepend($3, $1); $$ = $3; }
	  | 	 	 	     	{ $$ = NULL; }
	  ; 

DatasOpt : DataNasc ESPACOS DataMorte ESPACOS { $$ = init_individuo(); $$->data_nascimento = $1; $$->data_morte = $3;}
	 | DataNasc ESPACOS 	      	      { $$ = init_individuo(); $$->data_nascimento = $1;		     }
	 | DataMorte ESPACOS 		      { $$ = init_individuo(); $$->data_morte = $1;  			     }
	 | 	     			      { $$ = NULL;							     }
	 ;  

DataNasc  : '*' CData { $$ = $2;}
	  ;
DataMorte : '+' CData { $$ = $2;}
	  ;	

CData 	: 'c' DATA	{ char* s = "cerca de " ; char *res = (char*)malloc(strlen(s)+strlen($2)+1); memset(res, '\0', strlen(s)+strlen($2)+1); strcat(res, s); strcat(res, $2); $$ = res ;}
	| DATA 	   	{ $$ = $1; }
	;

ListaInf : Informacao '\n' ListaInf	{ $$ = indivRec($1, $3); }
	 | 	      	   		{ $$ = NULL;		 }
	 ;


Informacao : | ZeroOuMaisEsp FOTO ESPACOS FICHEIRO					{ $$ = init_individuo(); $$->foto = $4;		                                        } 	
	     | ZeroOuMaisEsp HIST ESPACOS FICHEIRO					{ $$ = init_individuo(); $$->historias = g_list_prepend($$->historias, $4);		}
	     | ZeroOuMaisEsp CASOUCOM ESPACOS CData ESPACOS RefIndividuo              	{ $6->data_casamento = $4; resolverParentescos($6, pessoas); $$ = processarCasamento($6, &pessoas) ; }
	     | ZeroOuMaisEsp INFSEXO ESPACOS SEXO					{ $$ = init_individuo(); if(strcmp($4, "Masculino")==0) $$->sexo = 1; else $$->sexo = 2;}
	     | ZeroOuMaisEsp EVENTOREF ESPACOS NUM ESPACOS CData			{ $$ = init_individuo(); Evento *e = encontrar_evento(eventos, $4); if(e) { e->data = $6; $$->eventos = g_list_prepend($$->eventos, e);} }
	     | ZeroOuMaisEsp PARENTESCO ESPACOS RefIndividuo 				{ resolverParentescos($4, pessoas); $$ = processarParentesco($2, $4, &pessoas); }
	     ;

RefIndividuo : NOME ESPACOS NomeIndiv DatasOpt Id InformacaoExtra	{ $$ = indivRec($4, $6); $3 = g_list_prepend($3, $1); $$->id = $5; $$->nome = g_list_para_string($3); g_list_free(nomes); }
	     | Id   	    	      	       	  			{ $$ = init_individuo(); $$->id = $1 ;}
	     ;

InformacaoExtra : ESPACOS '{' '\n' ListaInf '}'					{ $$ = $4 ;}
		|     	   	    						{ $$ = NULL ;}
		; 


Id : '[' NUM ']' { $$ = $2 ;}

UmOuMaisEsp : ESPACO
	    | ESPACO UmOuMaisEsp
	    ;

ZeroOuMaisEsp : ESPACOS
	      | 
	      ; 

UmaOuMaisQbL  : '\n' UmaOuMaisQbL
	      | '\n'
	      ;      

ZeroOuMaisQbL  : '\n' ZeroOuMaisQbL
	       | 
	       ;

Texto : NOME MaisTexto			{ $$ = g_list_prepend($2, $1); }
      ;

MaisTexto : ESPACOS NOME MaisTexto	{ $3 = g_list_prepend($3, $2); $3 = g_list_prepend($3, $1); $$ = $3;}
	  | 	    	 	   	{ $$ = NULL;  }
	  ;


%%

#include "lex.yy.c"

int yyerror () {
	
  fprintf(stderr, "Erro sintatico: (%s) linha:%d\n", yytext, yylineno) ;
  //yyerrok();
  return 1 ;
}

int main () {
  
  indiv = init_individuo() ;
  ev = init_evento() ;
  yyparse() ;
  //imprimir_individuo(indiv) ;
  g_list_foreach(eventos, imprimir_evento, NULL) ;
  g_list_foreach(pessoas, imprimir_individuo, NULL) ;
  return 0 ;
}

