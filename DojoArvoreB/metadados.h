#ifndef METADADOS_H
#define METADADOS_H

#include <stdio.h>

typedef struct Metadados {
	int pont_raiz;
	int pont_prox_no_livre;
} Metadados;

// Imprime metadados
void imprime_metadados(Metadados *metadados);

// Cria metadados. Lembrar de usar free(metadados)
Metadados *metadados(int pont_raiz, int pont_prox_no_livre);

// Salva metadados no arquivo out, na posicao atual do cursor
void salva_metadados(Metadados *metadados, FILE *out);

// Salva metadados no arquivo nome_arquivo
void salva_arq_metadados(char *nome_arquivo, Metadados *metadados);

// Le um metadados do arquivo in na posicao atual do cursor
// Retorna um ponteiro para metadados lido do arquivo
Metadados *le_metadados(FILE *in);

// Le metadados do arquivo nome_arquivo
Metadados *le_arq_metadados(char *nome_arquivo);

// Compara dois metadados
// Retorna 1 se os valores dos atributos de ambos forem iguais
// e 0 caso contrario
int cmp_metadados(Metadados *c1, Metadados *c2);

// Retorna tamanho do metadados em bytes
int tamanho_metadados();

#endif