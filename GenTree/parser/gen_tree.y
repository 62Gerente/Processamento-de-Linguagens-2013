%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Estruturas/Individuo.h"
#include "../Estruturas/Evento.h"
#include "util.h"
//#include "../Funcoes/toHTML.h"

GHashTable *pessoasHash ;
GList *eventos ;
int idIndividuo = 4004 ;
%}

%token NOME DATA DATA_OU_ID PARENTESCO FOTO HIST CASOUCOM INFSEXO EVENTOREF EVENTO NUM SEXO ESPACO
%token NOMEEVENTO DESCRICAOEVENTO TEXTO ESPACOS

%union{
  int n ;
  char* texto ;
  Individuo* indiv ;
  Evento* evento ;
  GList *lista ;
}

%type <n> NUM Id IdIndiv Num
%type <texto> NOME DATA DATA_OU_ID PARENTESCO FOTO HIST CASOUCOM INFSEXO EVENTOREF SEXO ESPACOS
%type <texto> Data CData DataNasc DataMorte TEXTO CDataOpt
%type <evento> Evento EventoInf ListaEventoInf 
%type <lista> Nome NomeOpt NomeOptEsp
%type <indiv> DatasOpt Individuo ListaInf Informacao RefIndividuo InformacaoExtra

%%

GenTree : '\n' ListaEvIndiv			 { resolverTodosOsParentescos() ;}
	| ListaEvIndiv				 { resolverTodosOsParentescos() ;}
	;

ListaEvIndiv : Evento  /*'\n'*/  ListaEvIndiv
	     | Individuo /*'\n'*/ ListaEvIndiv	 { inserirIndividuo($1); }
	     |
	     ;

Evento : EVENTO ESPACOS Id '\n' ListaEventoInf   { $$ = eventoRec($5, NULL);  $$->id = $3; eventos = g_list_append(eventos, $$); }

ListaEventoInf : EventoInf '\n' ListaEventoInf 	 { $$ = eventoRec($1, $3);}
	       | 	   		       	 { $$ = NULL ;}
	       ;	       

EventoInf : NOMEEVENTO ESPACOS TEXTO		 { $$ = init_evento(); $$->nome = $3 ;}
	  | DESCRICAOEVENTO ESPACOS TEXTO 	 { $$ = init_evento(); $$->descricao = $3 ;}
	  ; 

Individuo : Nome DatasOpt IdIndiv '\n' ListaInf  { $$ = indivRec($2, NULL); $$->id = $3; $$->nome = g_list_para_string($1); $$ = indivRec($$, $5);}
	  | NOME '\n' ListaInf	   	       	 { $$ = init_individuo(); $$->nome = $1; $$->id = encontrarId(); $$ = indivRec($$, $3);  }
	  ; 

Nome	  : NOME NomeOpt			 { $2 = g_list_prepend($2, $1); $$ = $2; }
	  ;

NomeOpt   : NomeOptEsp			         { $$ = $1 ; }
	  | '%' Num ESPACOS			 { $$ = NULL;      }
	  | '/' NOME NomeOpt			 { char* res = (char*)malloc(strlen($2)+2); memset(res, '\0', strlen($2)+2); strcat(res, " "); strcat(res, $2); $3 = g_list_prepend($3, res); $$ = $3; }
	  ;

NomeOptEsp : ESPACOS NOME NomeOpt		 { char* res = (char*)malloc(strlen($1)+strlen($2)); sprintf(res, "%s%s", $1, $2); $3 = g_list_prepend($3, res); $$ = $3 ;}
	   | ESPACOS 	  			 { $$ = NULL; }
	   ;

DatasOpt : DataNasc ESPACOS DataMorte ESPACOS	 { $$ = init_individuo(); $$->data_nascimento = $1; $$->data_morte = $3;}
	 | DataNasc ESPACOS 	      	      	 { $$ = init_individuo(); $$->data_nascimento = $1;		     }
	 | DataMorte ESPACOS 		      	 { $$ = init_individuo(); $$->data_morte = $1; 			     }
	 | 	     			      	 { $$ = NULL;							     }
	 ;  

DataNasc  : '*' CData				 { $$ = $2;}
	  ;
DataMorte : '+' CData				 { $$ = $2;}
	  ;	

CDataOpt  : CData ESPACOS			 { $$ = $1;}
	  | 	      	     			 { $$ = NULL;}
	  ;

CData 	: 'c' Data				 { char* s = "cerca de " ; char *res = (char*)malloc(strlen(s)+strlen($2)+1); memset(res, '\0', strlen(s)+strlen($2)+1); strcat(res, s); strcat(res, $2); $$ = res ;}
	| Data 	   				 { $$ = $1; }
	;

Data 	: DATA					 { $$ = $1 ;}
	| DATA_OU_ID				 { $$ = $1 ;}

ListaInf : Informacao '\n' ListaInf		 { $$ = indivRec($1, $3); }
	 | 	      	   			 { $$ = NULL;		 }
	 ;


Informacao :   ZeroOuMaisEsp FOTO ESPACOS TEXTO					{ $$ = init_individuo(); $$->foto = $4;		                                        } 	
	     | ZeroOuMaisEsp HIST ESPACOS TEXTO					{ $$ = init_individuo(); $$->historias = g_list_prepend($$->historias, $4);		}
	     | ZeroOuMaisEsp CASOUCOM ESPACOS CDataOpt RefIndividuo             { $5->data_casamento = $4; $$ = processarCasamentoHash($5) ; }
	     | ZeroOuMaisEsp INFSEXO ESPACOS SEXO				{ $$ = init_individuo(); if(strcmp($4, "Masculino")==0) $$->sexo = 1; else $$->sexo = 2;}
	     | ZeroOuMaisEsp EVENTOREF ESPACOS Num ESPACOS CData		{ $$ = init_individuo(); Evento *e = encontrar_evento(eventos, $4); if(e) { e->data = $6; $$->eventos = g_list_prepend($$->eventos, e);} }
	     | ZeroOuMaisEsp PARENTESCO ESPACOS RefIndividuo 			{ $$ = processarParentescoHash($2, $4); }
	     ;

RefIndividuo : Nome DatasOpt IdIndiv InformacaoExtra				{ $$ = indivRec($2, $4); $$->id = $3; $$->nome = g_list_para_string($1);}
	     | IdIndiv   	    	      	       	  			{ $$ = init_individuo(); $$->id = $1 ;}
	     ;

InformacaoExtra : ESPACOS '{' '\n' ListaInf '}'					{ $$ = $4 ;}
		|     	   	    						{ $$ = NULL ;}
		; 

IdIndiv : Id									{ $$ = $1; }
	|    									{ $$ = encontrarId();}
	;


Id : '[' Num ']'								{ $$ = $2 ;}

Num : NUM    	   								{ $$ = $1 ;}
    | DATA_OU_ID   								{ $$ = atoi($1) ;}

ZeroOuMaisEsp : ESPACOS
	      | 
	      ; 

%%

#include "lex.yy.c"

int yyerror () {
	
  fprintf(stderr, "Erro sintatico: (%s) linha:%d\n", yytext, yylineno) ;
  //yyerrok();
  return 1 ;
}

int main () {

  pessoasHash = g_hash_table_new(g_int_hash, compararIndividuo) ;
  yyparse() ;
  g_list_foreach(eventos, imprimir_evento, NULL) ;
  g_hash_table_foreach(pessoasHash, imprimir_individuo_hash, NULL) ;
  //toHTML(pessoas) ;
  return 0 ;
}

