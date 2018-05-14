#ifndef REGISTRO_INDICE_IDADE_H
#define REGISTRO_INDICE_IDADE_H

#include <stdio.h>

typedef struct RegistroIndiceIdade {
	int idade;
	int pt;
	int q;
} RegistroIndiceIdade;

// Imprime registro de indice_idade
void imprime_registro_indice_idade(RegistroIndiceIdade *registro_indice_idade);

// Cria registro de indice_idade. Lembrar de usar free(indice_idade)
RegistroIndiceIdade *registro_indice_idade(int idade, int pt, int q);

// Salva registro_indice_idade no arquivo out, na posicao atual do cursor
void salva_registro_indice_idade(RegistroIndiceIdade *registro_indice_idade, FILE *out);

// Le um registro de indice de idade do arquivo in na posicao atual do cursor
// Retorna um ponteiro para registro_indice_idade lido do arquivo
RegistroIndiceIdade *le_registro_indice_idade(FILE *in);

// Compara dois registros 
// Retorna 1 se os valores dos atributos de ambos forem iguais
// e 0 caso contrario
int cmp_registro_indice_idade(RegistroIndiceIdade *r1, RegistroIndiceIdade *r2);

// Retorna tamanho do registro em bytes
int tamanho_registro_indice_idade();

#endif