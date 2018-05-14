#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "no.h"


void imprime_no(No *no)
{
	int i;
	printf("%d, %d, (", no->m, no->pont_pai);
	for (i = 0; i < 2 * D; i++) {
		printf("%d, ", no->p[i]);
	}
	printf("%d), (\n", no->p[i]);
	for (i = 0; i < 2 * D; i++) {
		printf("  ");
		if (no->clientes[i])
			imprime_cliente(no->clientes[i]);
	}
	printf(")\n");
}

No *no(int m, int pont_pai)
{
	int i;
	No *no = (No *) malloc(sizeof(No));
	if (no) memset(no, 0, sizeof(No));
	no->m = m;
	no->pont_pai = pont_pai;
	no->p = (int *) malloc(sizeof(int) * (2 * D + 1));
	no->clientes = (Cliente **) malloc(sizeof(Cliente *) * 2 * D);
	for (i = 0; i < 2 * D; i++) {
		no->p[i] = -1;
		no->clientes[i] = NULL;
	}
	no->p[2 * D] = -1;
	return no;
}

No *no_vazio()
{
	return no(0, -1);
}

No *cria_no(int m, int pont_pai, int size, ...)
{
	No *n = no(m, pont_pai);
	int i;
	va_list ap;
	va_start(ap, size);
	for (i = 0; i < n->m + 1; i++) {
		n->p[i] = va_arg(ap, int);
	}
	for (i = 0; i < n->m; i++) {
		n->clientes[i] = va_arg(ap, Cliente *);
	}
	va_end(ap);
	return n;
}

void salva_no(No *no, FILE *out)
{
	int i;
	fwrite(&no->m, sizeof(int), 1, out);
	fwrite(&no->pont_pai, sizeof(int), 1, out);
	//garantidamente, sempre havera pelo menos 1 chave no noh
    //portanto, p0 sempre vai existir
	fwrite(&no->p[0], sizeof(int), 1, out);

	Cliente *vazio = cliente(-1, "");

	for (i = 0; i < 2 * D; i++) {
		if (no->clientes[i]) {
			salva_cliente(no->clientes[i], out);
		} else {
			salva_cliente(vazio, out);
		}
		fwrite(&no->p[i + 1], sizeof(int), 1, out);
	}
	free(vazio);
}

No *le_no(FILE *in)
{
	int i;
	No *no = (No *) malloc(sizeof(No));
	if (0 >= fread(&no->m, sizeof(int), 1, in)) {
		free(no);
		return NULL;
	}
	fread(&no->pont_pai, sizeof(int), 1, in);
	no->p = (int *) malloc(sizeof(int) * (2 * D + 1));
	no->clientes = (Cliente **) malloc(sizeof(Cliente *) * 2 * D);

	fread(&no->p[0], sizeof(int), 1, in);
	for (i = 0; i < no->m; i++) {
		no->clientes[i] = le_cliente(in);
		fread(&no->p[i + 1], sizeof(int), 1, in);
	}

	// Termina de ler dados nulos para resolver problema do cursor
	// Dados lidos sao descartados
	Cliente *vazio;
	int nul = -1;
	for (i = no->m; i < 2 * D; i++) {
		no->clientes[i] = NULL;
		vazio = le_cliente(in);
		fread(&no->p[i + 1], sizeof(int), 1, in);
		free(vazio);
	}
	return no;
}

int cmp_no(No *n1, No *n2)
{
	int i;
	if (n1 == NULL) {
		return (n2 == NULL);
	}
	if (n1->m != n2->m) {
		return 0;
	}
	if (n1->pont_pai != n2->pont_pai) {
		return 0;
	}
	for (i = 0; i < 2 * D + 1; i++) {
		if (n1->p[i] != n2->p[i]) {
			return 0;
		}
	}
	for (i = 0; i < 2 * D; i++) {
		if (!cmp_cliente(n1->clientes[i], n2->clientes[i])) {
			return 0;
		}
	}
	return 1;
}

int tamanho_no()
{
	return sizeof(int) + // m
		sizeof(int) + // pont_pai
		sizeof(int) * (2 * D + 1) + // p
		tamanho_cliente() * (2 * D); // clientes
}

void libera_no(No *no)
{
	int i;
	for (i = 0; i < 2 * D; i++) {
		free(no->clientes[i]);
	}
	free(no->clientes);
	free(no->p);
	no->clientes = NULL;
	no->p = NULL;
	free(no);
}