#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>
#include <stdlib.h>

#include "metadados.h"


void imprime_metadados(Metadados *metadados)
{
	printf("%d, %d\n", metadados->pont_raiz, metadados->pont_prox_no_livre);
}

Metadados *metadados(int pont_raiz, int pont_prox_no_livre)
{
	Metadados *metadados = (Metadados *) malloc(sizeof(Metadados));
	if (metadados) memset(metadados, 0, sizeof(Metadados));
	metadados->pont_raiz = pont_raiz;
	metadados->pont_prox_no_livre = pont_prox_no_livre;
	return metadados;
}

void salva_metadados(Metadados *metadados, FILE *out)
{
	fwrite(&metadados->pont_raiz, sizeof(int), 1, out);
	fwrite(&metadados->pont_prox_no_livre, sizeof(int), 1, out);
}

void salva_arq_metadados(char *nome_arquivo, Metadados *metadados)
{
	FILE *out = fopen(nome_arquivo, "wb");
	salva_metadados(metadados, out);
	fclose(out);
}


Metadados *le_metadados(FILE *in)
{
	Metadados *metadados = (Metadados *) malloc(sizeof(Metadados));
	if (0 >= fread(&metadados->pont_raiz, sizeof(int), 1, in)) {
		free(metadados);
		return NULL;
	}
	fread(&metadados->pont_prox_no_livre, sizeof(int), 1, in);
	return metadados;
}

Metadados *le_arq_metadados(char *nome_arquivo)
{
	FILE *in = fopen(nome_arquivo, "rb");
	Metadados *resultado = le_metadados(in);
	fclose(in);
	return resultado;
}


int cmp_metadados(Metadados *c1, Metadados *c2)
{
	if (c1 == NULL) {
		return (c2 == NULL);
	}
	if (c1->pont_raiz != c2->pont_raiz) {
		return 0;
	}
	if (c1->pont_prox_no_livre != c2->pont_prox_no_livre) {
		return 0;
	}
	return 1;
}

int tamanho_metadados()
{
	return sizeof(int) + // pont_raiz
		sizeof(int); // pont_prox_no_livre
}