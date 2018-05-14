#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdarg.h>

#include "lista_clientes.h"
#include "cliente.h"


void imprime_clientes(ListaClientes *lc)
{
	int i;
	for (i = 0; i < lc->qtd; i++) {
		imprime_cliente(lc->lista[i]);
	}
}

ListaClientes *cria_clientes(int qtd, ...)
{
	va_list ap;
	ListaClientes *lc = (ListaClientes *)  malloc(sizeof(ListaClientes));
	lc->qtd = qtd;
	lc->lista = (Cliente **) malloc(sizeof(Cliente *) * (qtd));
	int i;
	va_start(ap, qtd);
	for (i = 0; i < qtd; i++) {
        lc->lista[i] = va_arg(ap, Cliente *);
    }
    va_end(ap);
    return lc;
}

void salva_clientes(char *nome_arquivo, ListaClientes *lc)
{
	FILE *out = fopen(nome_arquivo, "wb");
	int i;
	for (i = 0; i < lc->qtd; i++) {
		salva_cliente(lc->lista[i], out);
	}
	fclose(out);
}

ListaClientes * le_clientes(char *nome_arquivo)
{
	int qtd = 0;
	ListaClientes *lc = (ListaClientes *)  malloc(sizeof(ListaClientes));
	FILE *in = fopen(nome_arquivo, "rb");
	if (in != NULL) {
		Cliente *cliente = NULL;
		while((cliente = le_cliente(in)) != NULL) {
			qtd += 1;
			free(cliente);
		}
		fseek(in, 0, SEEK_SET);
		lc->qtd = qtd;
		lc->lista = (Cliente **) malloc(sizeof(Cliente *) * (qtd));
		qtd = 0;
		while((cliente = le_cliente(in)) != NULL) {
			lc->lista[qtd++] = cliente;
		}
		fclose(in);
	} else {
		lc->qtd = 0;
		lc->lista = NULL;
	}
	return lc;
}

int cmp_clientes(ListaClientes *c1, ListaClientes *c2)
{
	if (c1->qtd != c2->qtd) {
		return 0;
	}
	int i;
	for (i = 0; i < c1->qtd; i++) {
		if (!cmp_cliente(c1->lista[i], c2->lista[i])) {
			return 0;
		}
	}
	return 1;
}

void libera_clientes(ListaClientes *lc)
{
	int i;
	for (i = 0; i < lc->qtd; i++) {
		free(lc->lista[i]);
	}
	free(lc->lista);
	free(lc);
}

void quickSort( ListaClientes *lc, int l, int r)
{
   int j;

   if( l < r ) 
   {
       j = partition( lc, l, r);
       quickSort( lc, l, j-1);
       quickSort( lc, j+1, r);
   }
	
}



int partition( ListaClientes *lc, int l, int r) {
   int pivot, i, j;
   Cliente *t;
   pivot = lc->lista[l]->idade;
   i = l; j = r+1;
		
   while( 1)
   {
   	do ++i; while( lc->lista[i]->idade <= pivot && i <= r );
   	do --j; while( lc->lista[j]->idade > pivot );
   	if( i >= j ) break;
   	t = lc->lista[i]; lc->lista[i] = lc->lista[j]; lc->lista[j] = t;
   }
   t = lc->lista[l]; lc->lista[l] = lc->lista[j]; lc->lista[j] = t;
   return j;
}

void sort_by_age(ListaClientes *lc){
    
    Cliente *t, *menor;
    
    for(int i=0; i<lc->qtd; i++){
        int pos =-1;
        menor = lc->lista[i];
        for(int j=i+1; j<lc->qtd;j++){
            if(lc->lista[j]->idade < menor->idade){
                menor = lc->lista[j];
                pos = j;
            }
        }
        if(pos > -1){
            t = lc->lista[i];
            lc->lista[i] = menor;
            lc->lista[pos] = t;
        }
    }
}

int busca_cliente(int cod_cli , ListaClientes *lc){
    if(!lc) return -1;
    for(int i=0; i<lc->qtd;i++){
        if(lc->lista[i]->cod_cliente == cod_cli){
            return i;
        }
    }
    return -1;
}