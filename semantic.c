#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"
#include "scanner.h"
#include "parser.h"
extern int semanticErrs;
int variblesTemp = 0;

void definirIdentificador(char *nuevoIdentificador)
{
    if(estaDefinido(nuevoIdentificador) != NULL)
    {
        char str[60];
        sprintf(str,"Error semantico: identificador %s ya declarado", nuevoIdentificador);
        yyerror(str);
        semanticErrs++;
    }
    else
    {
        printf("Declare %s,Integer\n", nuevoIdentificador);
        push(&identificadoresDefinidos, nuevoIdentificador);
    }
}
void invocarIdentificador(char *nuevoIdentificador)
{
    if(estaDefinido(nuevoIdentificador) == NULL)
    {
        char str[60];
        sprintf(str,"Error semantico: identificador %s NO declarado", nuevoIdentificador);
        yyerror(str);
        semanticErrs++;
    }
}

char *hacerOperacion(char *operador, char *exp1, char *exp2)
{
    char *aux;
    aux = (char*)malloc(30);
    variblesTemp++;
    sprintf(aux, "Temp#%d", variblesTemp);
    definirIdentificador(aux);
    printf("%s %s,%s,%s\n", operador, exp1, exp2, aux);
    return aux;
}

void writeIdentificador(char *identificador)
{
    printf("Write %s,Integer\n", identificador);
}

void readIdentificador(char *identificador)
{
	printf("Read %s,Integer\n", identificador);
}

void asignarIdentificador(char *identificador, char *valor)
{
    printf("Store %s,%s\n", valor, identificador);
}

void load()
{
    printf("Load rtlib,\n");
}

void stop()
{
    printf("Stop ,\n");
}
