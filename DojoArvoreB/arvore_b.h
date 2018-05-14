#ifndef ARVORE_B_H
#define ARVORE_B_H

#include <stdio.h>
#include "no.h"

// Executa busca em Arquivos utilizando Arvore B
// Assumir que ponteiro para proximo noh eh igual a -1 quando nao houver proximo noh
// cod_cli: chave do cliente que esta sendo buscado
// nome_arquivo_metadados: nome do arquivo que contem os metadados
// nome_arquivo_dados: nome do arquivo que contem a arvore B
// pont: ponteiro para indicar pagina que contem chave (se encontrar)
//   ou ultima pagina examinada (caso contrario)
// encontrou: ponteiro para indicar se encontrou o cliente
//	 1 se encontrou, 0 caso contrario
// Retorna posicao em que a chave se encontra dentro da pagina (se encontrar)
//   ou a posicao, na pagina pont, onde a chave deveria estar inserida
int busca(int cod_cli, char *nome_arquivo_metadados, char *nome_arquivo_dados, int *pont, int *encontrou);

// Executa insercao em Arquivos Indexados por Arvore B
// cod_cli: chave do cliente que esta sendo inserido
// nome_cli: nome do cliente a ser inserido
// nome_arquivo_metadados: nome do arquivo que contem os metadados
// nome_arquivo_dados: nome do arquivo que contem a arvore B
// Retorna o endereco onde o cliente foi inserido, ou -1 se nao conseguiu inserir
int insere(int cod_cli, char *nome_cli, char *nome_arquivo_metadados, char *nome_arquivo_dados);

void insere_rec(Cliente *novo_cliente, FILE *meta_arq, FILE *dados_arq, No *no_atual, int pont_atual, int pos, int pont_novo_filho, int *pont);

// Executa exclusao em Arquivos Indexados por Arvores B
// cod_cli: chave do cliente a ser excluido
// nome_arquivo_metadados: nome do arquivo que contem os metadados
// nome_arquivo_dados: nome do arquivo que contem a arvore B
// Retorna o endereco do cliente que foi excluido, ou -1 se cliente nao existe
int exclui(int cod_cli, char *nome_arquivo_metadados, char *nome_arquivo_dados);

void exclui_rec(FILE *meta_arq, FILE *dados_arq, No *no_atual, int pont_atual, int pos);

void imprime_arvore_b(No *no, FILE *arq);

#endif