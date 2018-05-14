#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#define BEFORE_TEST before();

#define NOME_ARQUIVO "clientes.dat"
#define NOME_ARQUIVO_INDICE "indice_idade.dat"


#include <limits.h>
#include <stdlib.h>

#include "ufftest.h"
#include "lista_clientes.h"
#include "cliente.h"
#include "chave_secundaria.h"
#include "lista_registros_indice_idade.h"
#include "registro_indice_idade.h"



void before() {
	remove(NOME_ARQUIVO);
        remove(NOME_ARQUIVO_INDICE);
}

BEGIN_TESTS();

TEST("Indexa arquivo com um cliente");
if (!skip) {
	ListaClientes *tab_cliente;
        ListaRegistrosIndiceIdade *tab_indice;
        ListaRegistrosIndiceIdade *tab_indice_saida;

	tab_cliente = cria_clientes(1,
		cliente(1, "Carlos", 20));
	salva_clientes(NOME_ARQUIVO, tab_cliente);

	indexa(NOME_ARQUIVO, 1);

	tab_indice = cria_registros(1, 
                registro_indice_idade(20, 0, 1));
	tab_indice_saida = le_registros(NOME_ARQUIVO_INDICE);

	ASSERT_EQUAL_CMP(tab_indice, tab_indice_saida, cmp_registros);
	libera_clientes(tab_cliente);
        libera_registros(tab_indice);
	libera_registros(tab_indice_saida);
}

TEST("Indexa arquivo com dois clientes ordenados");
if (!skip) {
	ListaClientes *tab_cliente;
        ListaRegistrosIndiceIdade *tab_indice;
        ListaRegistrosIndiceIdade *tab_indice_saida;

	tab_cliente = cria_clientes(2,
		cliente(1, "Carlos", 18),
                cliente(2, "Ana", 20));
	salva_clientes(NOME_ARQUIVO, tab_cliente);

	indexa(NOME_ARQUIVO, 2);

	tab_indice = cria_registros(2, 
                registro_indice_idade(18, 0, 1),
                registro_indice_idade(20, 1, 1));
	tab_indice_saida = le_registros(NOME_ARQUIVO_INDICE);

	ASSERT_EQUAL_CMP(tab_indice, tab_indice_saida, cmp_registros);
	libera_clientes(tab_cliente);
        libera_registros(tab_indice);
	libera_registros(tab_indice_saida);
}

TEST("Indexa arquivo com dois clientes desordenados");
if (!skip) {
	ListaClientes *tab_cliente;
        ListaRegistrosIndiceIdade *tab_indice;
        ListaRegistrosIndiceIdade *tab_indice_saida;

	tab_cliente = cria_clientes(2,
		cliente(1, "Ana", 20),
                cliente(2, "Carlos", 18));
	salva_clientes(NOME_ARQUIVO, tab_cliente);

	indexa(NOME_ARQUIVO, 2);

	tab_indice = cria_registros(2, 
                registro_indice_idade(18, 1, 1),
                registro_indice_idade(20, 0, 1));
	tab_indice_saida = le_registros(NOME_ARQUIVO_INDICE);

	ASSERT_EQUAL_CMP(tab_indice, tab_indice_saida, cmp_registros);
	libera_clientes(tab_cliente);
        libera_registros(tab_indice);
	libera_registros(tab_indice_saida);
}


TEST("Indexa arquivo com dois clientes com a mesma idade");
if (!skip) {
	ListaClientes *tab_cliente;
        ListaRegistrosIndiceIdade *tab_indice;
        ListaRegistrosIndiceIdade *tab_indice_saida;

	tab_cliente = cria_clientes(2,
		cliente(1, "Ana", 20),
                cliente(2, "Carlos", 20));
	salva_clientes(NOME_ARQUIVO, tab_cliente);

	indexa(NOME_ARQUIVO, 2);

	tab_indice = cria_registros(1, 
                registro_indice_idade(20, 0, 2));
	tab_indice_saida = le_registros(NOME_ARQUIVO_INDICE);
        printf("gabarito:\n");
        imprime_registros(tab_indice);
        printf("resposta: \n");
        imprime_registros(tab_indice_saida);
        printf(":::::::::::::::::::;: \n");
	ASSERT_EQUAL_CMP(tab_indice, tab_indice_saida, cmp_registros);
	libera_clientes(tab_cliente);
        libera_registros(tab_indice);
	libera_registros(tab_indice_saida);
}


TEST("Indexa arquivo com cinco clientes");
if (!skip) {
	ListaClientes *tab_cliente;
        ListaRegistrosIndiceIdade *tab_indice;
        ListaRegistrosIndiceIdade *tab_indice_saida;

	tab_cliente = cria_clientes(5,
		cliente(1, "Ana", 18),
                cliente(2, "Carlos", 20),
                cliente(3, "Bruna", 22),
                cliente(4, "Marcos", 20),
                cliente(5, "Fernanda", 22));
	salva_clientes(NOME_ARQUIVO, tab_cliente);

	indexa(NOME_ARQUIVO, 5);

	tab_indice = cria_registros(3, 
                registro_indice_idade(18, 0, 1),
                registro_indice_idade(20, 1, 2),
                registro_indice_idade(22, 2, 2));
	tab_indice_saida = le_registros(NOME_ARQUIVO_INDICE);
        printf("gabarito:\n");
        imprime_registros(tab_indice);
        printf("resposta: \n");
        imprime_registros(tab_indice_saida);
        printf(":::::::::::::::::::;: \n");
	ASSERT_EQUAL_CMP(tab_indice, tab_indice_saida, cmp_registros);
	libera_clientes(tab_cliente);
        libera_registros(tab_indice);
	libera_registros(tab_indice_saida);
}

END_TESTS();