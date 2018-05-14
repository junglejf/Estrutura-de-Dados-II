#ifndef NO_H
#define NO_H

#define LIBERADO 0
#define OCUPADO 1

#define D 2

#include <stdio.h>

#include "cliente.h"

typedef struct No {
	int m;                  // Número de clientes do nó
	int pont_pai;           // Ponteiro para o nó raiz
	int *p;                 // Lista de ponteiros para filhos do nó
	Cliente **clientes;     // Lista de clientes do nó
} No;

// Imprime noh
void imprime_no(No *no);

// Cria noh. Lembrar de usar libera_no(no)
No *no(int m, int pont_pai);

// Cria noh folha. Lembrar de usar libera_no(no)
No *no_vazio();

// Cria noh com dados. Lembrar de usar libera_no(no)
// Size deve ser 2m + 1
No *cria_no(int m, int pont_pai, int size, ...);

// Grava uma pagina (noh) no arquivo em disco
void salva_no(No *no, FILE *out);

// Le uma pagina (noh) do disco
No *le_no(FILE *in);

// Compara dois nohs
// Retorna 1 se os valores dos atributos de ambos forem iguais
// e 0 caso contrario
int cmp_no(No *n1, No *n2);

// Retorna tamanho do noh em bytes
int tamanho_no();

// Libera noh e clientes
void libera_no(No *no);

#endif