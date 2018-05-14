#ifndef LISTA_NOS_H
#define LISTA_NOS_H

#include "no.h"

typedef struct ListaNos {
	No **lista;
	int qtd;
} ListaNos;

// Imprime nohs
void imprime_nos(ListaNos *lc);

// Cria lista de nohs. Lembrar de usar libera_nos(lista_nos)
ListaNos *cria_nos(int qtd, ...);

// Salva lista de nohs no arquivo nome_arquivo
void salva_nos(char *nome_arquivo, ListaNos *lc);

// Le lista de nohs do arquivo nome_arquivo
ListaNos *le_nos(char *nome_arquivo);

// Compara duas listas de nohs
// Retorna 1 se os nohs das duas listas forem iguais
// e 0 caso contrario
int cmp_nos(ListaNos *c1, ListaNos *c2);

// Desaloca lista de nohs
void libera_nos(ListaNos *lc);

#endif