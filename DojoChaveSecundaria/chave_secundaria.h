#ifndef CHAVE_SECUNDARIA_H
#define CHAVE_SECUNDARIA_H
#include "registro_indice_idade.h"
#include "lista_clientes.h"
#include "lista_registros_indice_idade.h"

// Executa o algoritmo de Lefkowitz para indexar o arquivo por idade
// nome_arquivo: nome do arquivo que contem os registros a serem indexados
// tam: número de registros do arquivo
void indexa(char *nome_arquivo, int tam);

//recebe uma lista temporária ordenada e a lista não ordenada e cria o arquivo de ponteiros
void arq_ponteiros(ListaClientes *lc, ListaClientes *raw , FILE *out);
#endif