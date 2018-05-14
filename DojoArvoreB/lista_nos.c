#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdarg.h>

#include "lista_nos.h"


void imprime_nos(ListaNos *lc)
{
	int i;
	for (i = 0; i < lc->qtd; i++) {
		imprime_no(lc->lista[i]);
	}
}

ListaNos *cria_nos(int qtd, ...)
{
	va_list ap;
	ListaNos *lc = (ListaNos *)  malloc(sizeof(ListaNos));
	lc->qtd = qtd;
	lc->lista = (No **) malloc(sizeof(No *) * (qtd));
	int i;
	va_start(ap, qtd);
	for (i = 0; i < qtd; i++) {
        lc->lista[i] = va_arg(ap, No *);
    }
    va_end(ap);
    return lc;
}

void salva_nos(char *nome_arquivo, ListaNos *lc)
{
	FILE *out = fopen(nome_arquivo, "wb");
	int i;
	for (i = 0; i < lc->qtd; i++) {
		salva_no(lc->lista[i], out);
	}
	fclose(out);
}

ListaNos * le_nos(char *nome_arquivo)
{
	int qtd = 0;
	ListaNos *lc = (ListaNos *)  malloc(sizeof(ListaNos));
	FILE *in = fopen(nome_arquivo, "rb");
	if (in != NULL) {
		No *no = NULL;
		while((no = le_no(in)) != NULL) {
			qtd += 1;
			libera_no(no);
		}
		fseek(in, 0, SEEK_SET);
		lc->qtd = qtd;
		lc->lista = (No **) malloc(sizeof(No *) * (qtd));
		qtd = 0;
		while((no = le_no(in)) != NULL) {
			lc->lista[qtd++] = no;
		}
		fclose(in);
	} else {
		lc->qtd = 0;
		lc->lista = NULL;
	}
	return lc;
}

int cmp_nos(ListaNos *c1, ListaNos *c2)
{
	if (c1->qtd != c2->qtd) {
		return 0;
	}
	int i;
	for (i = 0; i < c1->qtd; i++) {
		if (!cmp_no(c1->lista[i], c2->lista[i])) {
			return 0;
		}
	}
	return 1;
}

void libera_nos(ListaNos *lc)
{
	int i;
	for (i = 0; i < lc->qtd; i++) {
		libera_no(lc->lista[i]);
	}
	free(lc->lista);
	free(lc);
}
