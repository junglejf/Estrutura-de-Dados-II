#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>
#include <stdlib.h>

#include "registro_indice_idade.h"


void imprime_registro_indice_idade(RegistroIndiceIdade *registro_indice_idade)
{
	printf("%d, %d, %d \n", registro_indice_idade->idade, registro_indice_idade->pt, registro_indice_idade->q);
}

RegistroIndiceIdade *registro_indice_idade(int idade, int pt, int q)
{
	RegistroIndiceIdade *registro_indice_idade = (RegistroIndiceIdade *) malloc(sizeof(RegistroIndiceIdade));
	if (registro_indice_idade) memset(registro_indice_idade, 0, sizeof(RegistroIndiceIdade));
	registro_indice_idade->idade = idade;
	registro_indice_idade->pt = pt;
	registro_indice_idade->q = q;
        return registro_indice_idade;
}

void salva_registro_indice_idade(RegistroIndiceIdade *registro_indice_idade, FILE *out)
{
	fwrite(&registro_indice_idade->idade, sizeof(int), 1, out);
	fwrite(&registro_indice_idade->pt, sizeof(int), 1, out);
        fwrite(&registro_indice_idade->q, sizeof(int), 1, out);
}

RegistroIndiceIdade *le_registro_indice_idade(FILE *in)
{
	RegistroIndiceIdade *registro_indice_idade = (RegistroIndiceIdade *) malloc(sizeof(RegistroIndiceIdade));
	if (0 >= fread(&registro_indice_idade->idade, sizeof(int), 1, in)) {
		free(registro_indice_idade);
		return NULL;
	}
	fread(&registro_indice_idade->pt, sizeof(int), 1, in);
        fread(&registro_indice_idade->q, sizeof(int), 1, in);
	return registro_indice_idade;
}

int cmp_registro_indice_idade(RegistroIndiceIdade *r1, RegistroIndiceIdade *r2)
{
	if (r1 == NULL) {
		return (r2 == NULL);
	}
	if (r1->idade != r2->idade) {
		return 0;
	}
	if (r1->pt != r2->pt) {
		return 0;
	}
	if (r1->q != r2->q) {
		return 0;
	}return 1;
}

int tamanho_registro_indice_idade()
{
	return sizeof(int) + // idade
		sizeof(int) + // pt
		sizeof(int); // q
}