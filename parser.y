%code top{
#include <stdio.h>
#include "scanner.h"
#include "semantic.h"
}
%code provides{
void yyerror(const char *);
extern int yylexerrs;
extern int semanticErrs;
}
%defines "parser.h"
%output "parser.c"
%token IDENTIFICADOR PROGRAMA FIN LEER ESCRIBIR VARIABLES CODIGO  DEFINIR CONSTANTE
%token ASIGNACION ":="
%left '-' '+'
%left '*' '/'
%precedence NEG
%define api.value.type {char *}
%define parse.error verbose
%%

todo : {load();} PROGRAMA definicionVariables definicionCodigo FIN {stop();if (yynerrs || yylexerrs || semanticErrs) YYABORT;} 
definicionVariables : VARIABLES listaVariables ;
listaVariables : unaVariable
	| listaVariables unaVariable
	;
unaVariable : DEFINIR IDENTIFICADOR ';' {definirIdentificador($IDENTIFICADOR);}
	| error ';'
	;
definicionCodigo : CODIGO listaSentencias ;
listaSentencias : sentencia
	| listaSentencias sentencia
	;
sentencia : LEER '(' listaIdentificadores ')' ';'
	| ESCRIBIR '(' listaExpresiones ')' ';'
	| IDENTIFICADOR ASIGNACION expresion ';' {asignarIdentificador($IDENTIFICADOR, $expresion);}
	| error ';'
	;
listaIdentificadores : IDENTIFICADOR {readIdentificador($IDENTIFICADOR);}
	| listaIdentificadores ',' IDENTIFICADOR {readIdentificador($IDENTIFICADOR);}
	;
listaExpresiones : expresion {writeIdentificador($expresion);}
	| listaExpresiones ',' expresion
	;
expresion: expresion '+' expresion  {$$ = hacerOperacion("ADD", $1, $3);}
	| expresion '-' expresion {$$ = hacerOperacion("SUBS", $1, $3);}
	| expresion '*' expresion {$$ = hacerOperacion("MULT", $1, $3);}
	| expresion '/' expresion {$$ = hacerOperacion("DIV", $1, $3);}
	| '(' expresion ')'
	| '-' expresion %prec NEG {if(yynerrs || yylexerrs || semanticErrs){YYERROR;};$$ = hacerOperacion("INV", $2, "");}
	| IDENTIFICADOR {invocarIdentificador($1);}
	| CONSTANTE
	;

%%
