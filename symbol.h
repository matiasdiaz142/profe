#ifndef SYMBOL_H
#define SYMBOL_H

extern struct elem *identificadoresDefinidos;
struct elem *estaDefinido(char *nuevoIdentificador);
void push(struct elem **pila, char *identificador);

#endif
