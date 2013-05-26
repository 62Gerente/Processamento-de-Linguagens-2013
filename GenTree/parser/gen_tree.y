%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Estruturas/Individuo.h"
#include "../Estruturas/Evento.h"
#include "util.h"

Individuo *indiv ;
GList *nomes ; 
GList *pessoas ;
GList *eventos ;
%}

%token NOME DATA PARENTESCO FOTO HIST CASOUCOM INFSEXO EVENTOREF EVENTO FICHEIRO NUM SEXO ESPACO
%token NOMEEVENTO DESCRICAOEVENTO TEXTO

%union{
  int n ;
  char* texto ;
  Evento* evento ;
}

%type <n> NUM Id
%type <texto> NOME DATA PARENTESCO FOTO HIST CASOUCOM INFSEXO EVENTOREF EVENTO FICHEIRO SEXO
%type <texto> CData DataNasc DataMorte TEXTO
%type <evento> Evento EventoInf ListaEventoInf

%%

GenTree : ListaEvIndiv
	;

ListaEvIndiv : Evento '\n' ListaEvIndiv
	    /* | Individuo '\n' '\n' ListaEvIndiv*/
	     | 
	     ;

Evento : EVENTO UmOuMaisEsp Id '\n' ListaEventoInf { $5->id = $3; $$ = $5; eventos = g_list_append(eventos, $$); }

ListaEventoInf : EventoInf '\n' ListaEventoInf { $$ = $1;}
	       | 
	       ;	       

EventoInf : NOMEEVENTO UmOuMaisEsp TEXTO  { $$->nome = $3 ;}
	  | DESCRICAOEVENTO UmOuMaisEsp TEXTO { $$->descricao = $3 ;}
	  ;

Individuo : NOME UmOuMaisEsp NomeIndiv DatasOpt Id '\n' ListaInf 	{ nomes = g_list_prepend(nomes, $1); indiv->nome = g_list_para_string(nomes); g_list_free(nomes); indiv->id = $5; imprimir_individuo(indiv, NULL); }
	  ;

NomeIndiv : NOME UmOuMaisEsp NomeIndiv { $1 = adicionar_espaco_inicio($1); nomes = g_list_prepend(nomes, $1) ;}
	  | 
	  ; 

DatasOpt : DataNasc UmOuMaisEsp DataMorte UmOuMaisEsp { indiv->data_nascimento = $1; indiv->data_morte = $3;}
	 | DataNasc UmOuMaisEsp { indiv->data_nascimento = $1;}
	 | DataMorte UmOuMaisEsp { indiv->data_morte = $1;}
	 | 
	 ;  

DataNasc  : '*' CData { $$ = $2;}
	  ;
DataMorte : '+' CData { $$ = $2;}
	  ;	

CData 	: 'c' DATA { char* s = "cerca de " ; char *res = (char*)malloc(strlen(s)+strlen($2)+1); memset(res, '\0', strlen(s)+strlen($2)+1); strcat(res, s); strcat(res, $2); $$ = res ;}
	| DATA { $$ = $1; }
	;

ListaInf : Informacao '\n' ListaInf
	 | 
	 ;

Informacao : /*PARENTESCO ' ' RefIndividuo*/
	   | FOTO UmOuMaisEsp FICHEIRO { indiv->foto = $3 ;} 	
	   | HIST UmOuMaisEsp ListaFicheiros
	   /*| CASOUCOM UmOuMaisEsp CData UmOuMaisEsp RefIndividuo*/
	   | INFSEXO UmOuMaisEsp SEXO { if(strcmp($3, "Masculino")==0) indiv->sexo = 1; else indiv->sexo = 2;}
	   | EVENTOREF UmOuMaisEsp NUM UmOuMaisEsp CData
	   ;

ListaFicheiros : FICHEIRO UmOuMaisEsp ListaFicheiros { indiv->historias = g_list_prepend(indiv->historias, $1) ;}
	       | FICHEIRO { indiv->historias = g_list_prepend(indiv->historias, $1) ;}
	       ;
/*
RefIndividuo : NOME DatasOpt InformacaoExtra
	     | Id
	     ;

InformacaoExtra : '{' '\n' ListaInf '}'
		| 
		; 
*/

Id : '[' NUM ']' { $$ = $2 ;}

UmOuMaisEsp : ESPACO
	    | ESPACO UmOuMaisEsp
	    ;

/*ZeroOuMaisEsp : ESPACO ZeroOuMaisEsp
	      | 
	      ; */

%%

#include "lex.yy.c"

int yyerror () {
	
  fprintf(stderr, "Erro sintatico: (%s) linha:%d\n", yytext, yylineno) ;
  //yyerrok();
  return 1 ;
}

int main () {
  
  indiv = init_individuo() ;
  yyparse() ;
  //imprimir_individuo(indiv) ;
  g_list_foreach(eventos, imprimir_evento, NULL) ;
  return 0 ;
}

