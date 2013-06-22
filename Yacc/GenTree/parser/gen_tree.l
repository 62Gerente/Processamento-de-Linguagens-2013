%option noyywrap
%option yylineno

%%

[ \t]+			{ yylval.texto = strdup(yytext) ; 
  			  return ESPACOS; }

[\n]+ 			{ return '\n';} 

[\[\]\*\+\nc\{\}\%\/]	{ return yytext[0];}

\S			{ return INFSEXO ;}

\N			{ return NOMEEVENTO ;}

\D			{ return DESCRICAOEVENTO ;}

CC			{ return CASOUCOM ;}

FOTO			{ return FOTO ;}

HIST			{ return HIST ;}

EVENTO			{ return EVENTO ;}

ev			{ return EVENTOREF ;}

(Masculino|Feminino)		{ yylval.texto = strdup(yytext) ;
			  	return SEXO ; }

(F|P|M|MM|MP|PM|PP)	{ yylval.texto = strdup(yytext) ;
			  return PARENTESCO ;}

(á|Á|à|À|â|Â|ã|Ã|é|É|ó|Ó|[a-zA-Z])+	       	{ yylval.texto = strdup(yytext) ;
	 	     	  return NOME ;}

[0-9][0-9][0-9][0-9]	{ yylval.texto = strdup(yytext) ;
			 return DATA_OU_ID ; }

([0-9][0-9]\/[0-9][0-9][0-9][0-9]|[0-9][0-9]\/[0-9][0-9]\/[0-9][0-9][0-9][0-9])	{ yylval.texto = strdup(yytext) ;
			 return DATA ; }

[0-9]+			{ yylval.n = atoi(yytext) ; 
   			  return NUM ;}

\"[^\"]*\"		{ yylval.texto = substring(yytext, 1, strlen(yytext)-2) ; 
			  return TEXTO ; }	

. 		       { yyerror() ;}

%%
