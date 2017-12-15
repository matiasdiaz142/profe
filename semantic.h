#ifndef SEMANTIC_H
#define SEMANTIC_H

void definirIdentificador(char *nuevoIdentificador);
void invocarIdentificador(char *nuevoIdentificador);
char *hacerOperacion(char *operador, char *exp1, char *exp2);
void writeIdentificador(char *identificador);
void readIdentificador(char *identificador);
void asignarIdentificador(char *identificador, char *valor);
void load();
void stop();
#endif
