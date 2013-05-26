%option noyywrap
%option yylineno

/* | [a-zA-Z ]+\/[a-zA-Z ]*[a-zA-Z] */

%%

[ \t]                   { return ESPACO;}

[\[\]\*\+\nc]		{ return yytext[0];}

\S			{ return INFSEXO ;}

\N			{ return NOMEEVENTO ;}

\D			{ return DESCRICAOEVENTO ;}

CC			{ return CASOUCOM ;}

FOTO			{ return FOTO ;}

HIST			{ return HIST ;}

EVENTO			{ yylval.evento = init_evento(); 
			  return EVENTO ;}

EV			{ return EVENTOREF ;}

(Masculino|Feminino)		{ yylval.texto = strdup(yytext) ;
			  	return SEXO ; }

(F|P|M|MM|MP|PM|PP)	{ yylval.texto = strdup(yytext) ;
			  return PARENTESCO ;}

[a-zA-Z]+	       	{ char* res = (char*)malloc(strlen(yytext)+2); memset(res, '\0', strlen(yytext)+2); strcpy(res, yytext); yylval.texto = res ;
	 	     	  return NOME ;}

[a-zA-Z\/]+\.[a-zA-Z]+	       { yylval.texto = strdup(yytext) ;
		       	       	 return FICHEIRO ;}

				 /*([a-zA-Z ]*[a-zA-Z])	       { yylval.texto = strdup(yytext) ;
	 	     		return NOME ;} */

([0-9][0-9][0-9][0-9]|[0-9][0-9]\/[0-9][0-9][0-9][0-9]|[0-9][0-9]\/[0-9][0-9]\/[0-9][0-9][0-9][0-9])	{ yylval.texto = strdup(yytext) ;
			 return DATA ; }

[0-9]+			{ yylval.n = atoi(yytext) ;
   			  return NUM ;}

[a-zA-Z0-9 \t^\n]+	{ yylval.texto = strdup(yytext);
	   		  return TEXTO ;}

. 		       { yyerror() ;}

%%
