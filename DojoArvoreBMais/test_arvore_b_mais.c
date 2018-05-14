#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#define BEFORE_TEST before();

#define NOME_ARQUIVO_METADADOS "metadados.dat"
#define NOME_ARQUIVO_INDICE "indice.dat"
#define NOME_ARQUIVO_DADOS "clientes.dat"

#include <limits.h>
#include <stdlib.h>

#include "ufftest.h"
#include "cliente.h"
#include "no_interno.h"
#include "no_folha.h"
#include "lista_clientes.h"
#include "lista_nos_internos.h"
#include "lista_nos_folhas.h"
#include "metadados.h"
#include "arvore_b_mais.h"


void before()
{
	remove(NOME_ARQUIVO_METADADOS);
	remove(NOME_ARQUIVO_INDICE);
	remove(NOME_ARQUIVO_DADOS);
}

// Arvore B+ de altura H = 1, com apenas 1 noh (raiz eh uma folha) que tem 2 registros
// Ver arquivo ArvoreTesteDOJO.pdf para o desenho da arvore
void monta_arvore_h1()
{
	Metadados *tabMetadados = metadados(0, 1, 0, 1 * tamanho_no_folha());
	salva_arq_metadados(NOME_ARQUIVO_METADADOS, tabMetadados);

	fclose(fopen(NOME_ARQUIVO_INDICE, "w"));

	ListaNosFolhas *tabDados = cria_nos_folhas(1,
		cria_no_folha(-1, -1, 2,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria")));
	salva_nos_folhas(NOME_ARQUIVO_DADOS, tabDados);
	free(tabMetadados);
	libera_nos_folhas(tabDados);
}

// Arvore B+ de altura H = 1, com apenas 1 noh (raiz eh uma folha) que tem 4 registros
// Ver arquivo ArvoreTesteDOJO.pdf para o desenho da arvore
void monta_arvore_h1_cheia()
{
	Metadados *tabMetadados = metadados(0, 1, 0, 1 * tamanho_no_folha());
	salva_arq_metadados(NOME_ARQUIVO_METADADOS, tabMetadados);

	fclose(fopen(NOME_ARQUIVO_INDICE, "w"));

	ListaNosFolhas *tabDados = cria_nos_folhas(1,
		cria_no_folha(-1, -1, 4,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria"),
			cliente(15, "Bianca"),
			cliente(26, "Clara")));
	salva_nos_folhas(NOME_ARQUIVO_DADOS, tabDados);
	free(tabMetadados);
	libera_nos_folhas(tabDados);
}

// Arvore B+ de altura H = 2, com raiz e mais 3 folhas
// Ordem de insercao das chaves na arvores: 10, 13, 15, 20, 25, 35, 37
// Ver arquivo ArvoreTesteDOJO.pdf para o desenho da arvore
void monta_arvore_h2()
{
	Metadados *tabMetadados = metadados(0, 0, tamanho_no_interno(), 3 * tamanho_no_folha());
	salva_arq_metadados(NOME_ARQUIVO_METADADOS, tabMetadados);
	// Estrutura do No Interno: m, pont_pai, aponta_folha, 2m + 1, lista de ponteiros, lista de chaves
	// Atencao: os ponteiros sao absolutos
	ListaNosInternos *tabIndice = cria_nos_internos(1,
		cria_no_interno(2, -1, 1, 2 * 2 + 1,
			0,
			1 * tamanho_no_folha(),
			2 * tamanho_no_folha(),
			15,
			25
		)
	);
	salva_nos_internos(NOME_ARQUIVO_INDICE, tabIndice);

	// Estrutura do No Folha: pont_pai, pont_prox, m, registros de clientes
	ListaNosFolhas *tabDados = cria_nos_folhas(3,
		cria_no_folha(0, 1 * tamanho_no_folha(), 2,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria")
		),
		cria_no_folha(0, 2 * tamanho_no_folha(), 2,
			cliente(15, "Jose"),
			cliente(20, "Mariana")
		),
		cria_no_folha(0, -1, 3,
			cliente(25, "Ronaldo"),
			cliente(35, "Marcela"),
			cliente(37, "Leonardo")
		)
	);
	salva_nos_folhas(NOME_ARQUIVO_DADOS, tabDados);
	free(tabMetadados);
	libera_nos_internos(tabIndice);
	libera_nos_folhas(tabDados);
}

// Arvore B+ de altura H = 2, com raiz e mais 3 folhas, 1 delas cheia
// Ordem de insercao das chaves na arvore: 10, 13, 15, 20, 25, 35, 37, 21, 23
// Ver arquivo ArvoreTesteDOJO.pdf para o desenho da arvore
void monta_arvore_h2_cheia()
{
	Metadados *tabMetadados = metadados(0, 0, tamanho_no_interno(), 3 * tamanho_no_folha());
	salva_arq_metadados(NOME_ARQUIVO_METADADOS, tabMetadados);
	// Estrutura do No Interno: m, pont_pai, aponta_folha, 2m + 1, lista de ponteiros, lista de chaves
	// Atencao: os ponteiros sao absolutos
	ListaNosInternos *tabIndice = cria_nos_internos(1,
		cria_no_interno(2, -1, 1, 2 * 2 + 1,
			0,
			1 * tamanho_no_folha(),
			2 * tamanho_no_folha(),
			15,
			25
		)
	);
	salva_nos_internos(NOME_ARQUIVO_INDICE, tabIndice);

	// Estrutura do No Folha: pont_pai, pont_prox, m, registros de clientes
	ListaNosFolhas *tabDados = cria_nos_folhas(3,
		cria_no_folha(0, 1 * tamanho_no_folha(), 2,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria")
		),
		cria_no_folha(0, 2 * tamanho_no_folha(), 4,
			cliente(15, "Jose"),
			cliente(20, "Mariana"),
			cliente(21, "Bruna"),
			cliente(23, "Bruno")
		),
		cria_no_folha(0, -1, 3,
			cliente(25, "Ronaldo"),
			cliente(35, "Marcela"),
			cliente(37, "Leonardo")
		)
	);
	salva_nos_folhas(NOME_ARQUIVO_DADOS, tabDados);
	free(tabMetadados);
	libera_nos_internos(tabIndice);
	libera_nos_folhas(tabDados);
}

// Arvore B+ de altura H = 2, com raiz e mais 5 folhas, 1 delas cheia
// Ver arquivo ArvoreTesteDOJO.pdf para o desenho da arvore
void monta_arvore_h2_completa()
{
	Metadados *tabMetadados = metadados(0, 0, tamanho_no_interno(), 5 * tamanho_no_folha());
	salva_arq_metadados(NOME_ARQUIVO_METADADOS, tabMetadados);
	// Estrutura do No Interno: m, pont_pai, aponta_folha, 2m + 1, lista de ponteiros, lista de chaves
	// Atencao: os ponteiros sao absolutos
	ListaNosInternos *tabIndice = cria_nos_internos(1,
		cria_no_interno(4, -1, 1, 4 * 2 + 1,
			0,
			1 * tamanho_no_folha(),
			2 * tamanho_no_folha(),
			3 * tamanho_no_folha(),
			4 * tamanho_no_folha(),
			15,
			25,
			40,
			70
		)
	);
	salva_nos_internos(NOME_ARQUIVO_INDICE, tabIndice);

	// Estrutura do No Folha: pont_pai, pont_prox, m, registros de clientes
	ListaNosFolhas *tabDados = cria_nos_folhas(5,
		cria_no_folha(0, 1 * tamanho_no_folha(), 2,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria")
		),
		cria_no_folha(0, 2 * tamanho_no_folha(), 4,
			cliente(15, "Jose"),
			cliente(20, "Mariana"),
			cliente(21, "Bruna"),
			cliente(23, "Bruno")
		),
		cria_no_folha(0, 3 * tamanho_no_folha(), 3,
			cliente(25, "Ronaldo"),
			cliente(35, "Marcela"),
			cliente(37, "Leonardo")
		),
		cria_no_folha(0, 4 * tamanho_no_folha(), 2,
			cliente(40, "Aline"),
			cliente(45, "Juca")
		),
		cria_no_folha(0, -1, 2,
			cliente(70, "Nicolas"),
			cliente(77, "Lina")
		)
	);
	salva_nos_folhas(NOME_ARQUIVO_DADOS, tabDados);
	free(tabMetadados);
	libera_nos_internos(tabIndice);
	libera_nos_folhas(tabDados);
}

// Arvore B de altura H = 3, com raiz que aponta para 2 nohs internos, e mais 6 folhas
// Ver arquivo ArvoreTesteDOJO.pdf para o desenho da arvore
void monta_arvore_h3()
{
	Metadados *tabMetadados = metadados(0, 0, 3 * tamanho_no_interno(), 6 * tamanho_no_folha());
	salva_arq_metadados(NOME_ARQUIVO_METADADOS, tabMetadados);
	// Estrutura do No Interno: m, pont_pai, aponta_folha, 2m + 1, lista de ponteiros, lista de chaves
	// Atencao: os ponteiros sao absolutos
	ListaNosInternos *tabIndice = cria_nos_internos(3,
		cria_no_interno(1, -1, 0, 1 * 2 + 1,
			1 * tamanho_no_interno(),
			2 * tamanho_no_interno(),
			37
		),
		cria_no_interno(2, 0, 1, 2 * 2 + 1,
			0 * tamanho_no_folha(),
			1 * tamanho_no_folha(),
			2 * tamanho_no_folha(),
			15,
			25
		),
		cria_no_interno(2, 0, 1, 2 * 2 + 1,
			3 * tamanho_no_folha(),
			4 * tamanho_no_folha(),
			5 * tamanho_no_folha(),
			39,
			55
		)
	);
	salva_nos_internos(NOME_ARQUIVO_INDICE, tabIndice);

	// Estrutura do No Folha: pont_pai, pont_prox, m, registros de clientes
	ListaNosFolhas *tabDados = cria_nos_folhas(6,
		cria_no_folha(1 * tamanho_no_interno(), 1 * tamanho_no_folha(), 2,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria")
		),
		cria_no_folha(1 * tamanho_no_interno(), 2 * tamanho_no_folha(), 2,
			cliente(15, "Jose"),
			cliente(20, "Mariana")
		),
		cria_no_folha(1 * tamanho_no_interno(), 3 * tamanho_no_folha(), 2,
			cliente(25, "Ronaldo"),
			cliente(35, "Marcela")
		),
		cria_no_folha(2 * tamanho_no_interno(), 4 * tamanho_no_folha(), 2,
			cliente(37, "Leonardo"),
			cliente(38, "Karla")
		),
		cria_no_folha(2 * tamanho_no_interno(), 5 * tamanho_no_folha(), 2,
			cliente(39, "Mario"),
			cliente(50, "Ricardo")
		),
		cria_no_folha(2 * tamanho_no_interno(), -1, 3,
			cliente(55, "Rosa"),
			cliente(60, "Michele"),
			cliente(70, "Rafael")
		)
	);
	salva_nos_folhas(NOME_ARQUIVO_DADOS, tabDados);
	free(tabMetadados);
	libera_nos_internos(tabIndice);
	libera_nos_folhas(tabDados);
}

BEGIN_TESTS();

TEST("Busca 1 -- chave procurada esta na raiz. Raiz eh folha");
if (!skip) {
	int pont_folha = INT_MAX, encontrou = INT_MAX, pos = INT_MAX;
	monta_arvore_h1();

	pos = busca(13, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, &pont_folha, &encontrou);
	ASSERT_EQUAL(0, pont_folha);
	ASSERT_EQUAL(1, pos);
	ASSERT_TRUE(encontrou);
}

TEST("Busca 2 -- chave procurada nao esta na arvore. Raiz eh folha");
if (!skip) {
	int pont_folha = INT_MAX, encontrou = INT_MAX, pos = INT_MAX;
	monta_arvore_h1();

	pos = busca(6, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, &pont_folha, &encontrou);
	ASSERT_EQUAL(0, pont_folha);
	ASSERT_EQUAL(0, pos);
	ASSERT_FALSE(encontrou);
}

TEST("Busca 3 -- chave esta na arvore");
if (!skip) {
	int pont_folha = INT_MAX, encontrou = INT_MAX, pos = INT_MAX;
	monta_arvore_h2();

	pos = busca(20, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, &pont_folha, &encontrou);
	ASSERT_EQUAL(1 * tamanho_no_folha(), pont_folha);
	ASSERT_EQUAL(1, pos);
	ASSERT_TRUE(encontrou);
}

TEST("Busca 4 -- chave nao esta na arvore");
if (!skip) {
	int pont_folha = INT_MAX, encontrou = INT_MAX, pos = INT_MAX;
	monta_arvore_h2();

	pos = busca(16, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, &pont_folha, &encontrou);
	ASSERT_EQUAL(1 * tamanho_no_folha(), pont_folha);
	ASSERT_EQUAL(1, pos);
	ASSERT_FALSE(encontrou);
}

TEST("Busca 5 -- chave esta na arvore");
if (!skip) {
	int pont_folha = INT_MAX, encontrou = INT_MAX, pos = INT_MAX;
	monta_arvore_h3();

	pos = busca(37, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, &pont_folha, &encontrou);
	ASSERT_EQUAL(3 * tamanho_no_folha(), pont_folha);
	ASSERT_EQUAL(0, pos);
	ASSERT_TRUE(encontrou);
}

TEST("Busca 6 -- chave nao esta na arvore");
if (!skip) {
	int pont_folha = INT_MAX, encontrou = INT_MAX, pos = INT_MAX;
	monta_arvore_h3();

	pos = busca(26, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, &pont_folha, &encontrou);
	ASSERT_EQUAL(2 * tamanho_no_folha(), pont_folha);
	ASSERT_EQUAL(1, pos);
	ASSERT_FALSE(encontrou);
}


TEST("Insercao 1 em arvore de altura H = 1, sem particionamento");
if (!skip) {
	int pos = INT_MAX;
	monta_arvore_h1();

	pos = insere(11, "Vanessa", NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL(0, pos);

	Metadados *tabMetadados = metadados(0, 1, 0, 1 * tamanho_no_folha());
	Metadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
	ASSERT_EQUAL_CMP(tabMetadados, tabMetadadosSaida, cmp_metadados);
	free(tabMetadados);
	free(tabMetadadosSaida);

	ListaNosFolhas *tabDados = cria_nos_folhas(1,
		cria_no_folha(-1, -1, 3,
			cliente(10, "Joao"),
			cliente(11, "Vanessa"),
			cliente(13, "Ana Maria")));
	ListaNosFolhas *tabDadosSaida = le_nos_folhas(NOME_ARQUIVO_DADOS);

	ASSERT_EQUAL_CMP(tabDados, tabDadosSaida, cmp_nos_folhas);
	libera_nos_folhas(tabDados);
	libera_nos_folhas(tabDadosSaida);
}

TEST("Insercao 2 em arvore de altura H = 2, sem particionamento");
if (!skip) {
	int pos = INT_MAX;
	monta_arvore_h2();

	pos = insere(11, "Vanessa", NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL(0, pos);

	Metadados *tabMetadados = metadados(0, 0, tamanho_no_interno(), 3 * tamanho_no_folha());
	Metadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
	ASSERT_EQUAL_CMP(tabMetadados, tabMetadadosSaida, cmp_metadados);
	free(tabMetadados);
	free(tabMetadadosSaida);

	ListaNosInternos *tabIndice = cria_nos_internos(1,
		cria_no_interno(2, -1, 1, 2 * 2 + 1,
			0,
			1 * tamanho_no_folha(),
			2 * tamanho_no_folha(),
			15,
			25
		)
	);
	ListaNosInternos *tabIndiceSaida = le_nos_internos(NOME_ARQUIVO_INDICE);
	ASSERT_EQUAL_CMP(tabIndice, tabIndiceSaida, cmp_nos_internos);
	libera_nos_internos(tabIndice);
	libera_nos_internos(tabIndiceSaida);

	ListaNosFolhas *tabDados = cria_nos_folhas(3,
		cria_no_folha(0, 1 * tamanho_no_folha(), 3,
			cliente(10, "Joao"),
			cliente(11, "Vanessa"),
			cliente(13, "Ana Maria")
		),
		cria_no_folha(0, 2 * tamanho_no_folha(), 2,
			cliente(15, "Jose"),
			cliente(20, "Mariana")
		),
		cria_no_folha(0, -1, 3,
			cliente(25, "Ronaldo"),
			cliente(35, "Marcela"),
			cliente(37, "Leonardo")
		)
	);
	ListaNosFolhas *tabDadosSaida = le_nos_folhas(NOME_ARQUIVO_DADOS);

	ASSERT_EQUAL_CMP(tabDados, tabDadosSaida, cmp_nos_folhas);
	libera_nos_folhas(tabDados);
	libera_nos_folhas(tabDadosSaida);
}

TEST("Insercao 3 em arvore de altura H = 2. Exige particionamento de uma pagina folha");
if (!skip) {
	int pos = INT_MAX;
	// Arvore tem um dos nohs folha cheio. E eh neste noh que a insercao ocorrera
	monta_arvore_h2_cheia();

	pos = insere(16, "Vanessa", NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL(1 * tamanho_no_folha(), pos);

	Metadados *tabMetadados = metadados(0, 0, tamanho_no_interno(), 4 * tamanho_no_folha());
	Metadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
	ASSERT_EQUAL_CMP(tabMetadados, tabMetadadosSaida, cmp_metadados);
	free(tabMetadados);
	free(tabMetadadosSaida);

	ListaNosInternos *tabIndice = cria_nos_internos(1,
		cria_no_interno(3, -1, 1, 3 * 2 + 1,
			0,
			1 * tamanho_no_folha(),
			3 * tamanho_no_folha(),
			2 * tamanho_no_folha(),
			15,
			20,
			25
		)
	);
	ListaNosInternos *tabIndiceSaida = le_nos_internos(NOME_ARQUIVO_INDICE);
	ASSERT_EQUAL_CMP(tabIndice, tabIndiceSaida, cmp_nos_internos);
	libera_nos_internos(tabIndice);
	libera_nos_internos(tabIndiceSaida);

	ListaNosFolhas *tabDados = cria_nos_folhas(4,
		cria_no_folha(0, 1 * tamanho_no_folha(), 2,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria")
		),
		cria_no_folha(0, 3 * tamanho_no_folha(), 2,
			cliente(15, "Jose"),
			cliente(16, "Vanessa")
		),
		cria_no_folha(0, -1, 3,
			cliente(25, "Ronaldo"),
			cliente(35, "Marcela"),
			cliente(37, "Leonardo")
		),
		cria_no_folha(0, 2 * tamanho_no_folha(), 3,
			cliente(20, "Mariana"),
			cliente(21, "Bruna"),
			cliente(23, "Bruno")
		)
	);
	ListaNosFolhas *tabDadosSaida = le_nos_folhas(NOME_ARQUIVO_DADOS);

	ASSERT_EQUAL_CMP(tabDados, tabDadosSaida, cmp_nos_folhas);
	libera_nos_folhas(tabDados);
	libera_nos_folhas(tabDadosSaida);
}

TEST("Insercao 4 em arvore de altura H = 2, chave de registro ja existe -- nao inserir");
if (!skip) {
	int pos = INT_MAX;
	monta_arvore_h2();

	pos = insere(13, "Manriana", NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL(-1, pos);

	Metadados *tabMetadados = metadados(0, 0, tamanho_no_interno(), 3 * tamanho_no_folha());
	Metadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
	ASSERT_EQUAL_CMP(tabMetadados, tabMetadadosSaida, cmp_metadados);
	free(tabMetadados);
	free(tabMetadadosSaida);

	ListaNosInternos *tabIndice = cria_nos_internos(1,
		cria_no_interno(2, -1, 1, 2 * 2 + 1,
			0,
			1 * tamanho_no_folha(),
			2 * tamanho_no_folha(),
			15,
			25
		)
	);
	ListaNosInternos *tabIndiceSaida = le_nos_internos(NOME_ARQUIVO_INDICE);
	ASSERT_EQUAL_CMP(tabIndice, tabIndiceSaida, cmp_nos_internos);
	libera_nos_internos(tabIndice);
	libera_nos_internos(tabIndiceSaida);

	ListaNosFolhas *tabDados = cria_nos_folhas(3,
		cria_no_folha(0, 1 * tamanho_no_folha(), 2,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria")
		),
		cria_no_folha(0, 2 * tamanho_no_folha(), 2,
			cliente(15, "Jose"),
			cliente(20, "Mariana")
		),
		cria_no_folha(0, -1, 3,
			cliente(25, "Ronaldo"),
			cliente(35, "Marcela"),
			cliente(37, "Leonardo")
		)
	);
	ListaNosFolhas *tabDadosSaida = le_nos_folhas(NOME_ARQUIVO_DADOS);

	ASSERT_EQUAL_CMP(tabDados, tabDadosSaida, cmp_nos_folhas);
	libera_nos_folhas(tabDados);
	libera_nos_folhas(tabDadosSaida);
}

TEST("Insercao 5 em arvore de altura H = 1 cheia, que causa aumento na altura da arvore");
if (!skip) {
	int pos = INT_MAX;
	monta_arvore_h1_cheia();

	pos = insere(11, "Vanessa", NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL(0, pos);

	Metadados *tabMetadados = metadados(0, 0, 1 * tamanho_no_interno(), 2 * tamanho_no_folha());
	Metadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
	ASSERT_EQUAL_CMP(tabMetadados, tabMetadadosSaida, cmp_metadados);
	free(tabMetadados);
	free(tabMetadadosSaida);

	ListaNosInternos *tabIndice = cria_nos_internos(1,
		cria_no_interno(1, -1, 1, 1 * 2 + 1,
			0,
			1 * tamanho_no_folha(),
			13
		)
	);
	ListaNosInternos *tabIndiceSaida = le_nos_internos(NOME_ARQUIVO_INDICE);
	ASSERT_EQUAL_CMP(tabIndice, tabIndiceSaida, cmp_nos_internos);
	libera_nos_internos(tabIndice);
	libera_nos_internos(tabIndiceSaida);

	ListaNosFolhas *tabDados = cria_nos_folhas(2,
		cria_no_folha(0, 1 * tamanho_no_folha(), 2,
			cliente(10, "Joao"),
			cliente(11, "Vanessa")
		),
		cria_no_folha(0, -1, 3,
			cliente(13, "Ana Maria"),
			cliente(15, "Bianca"),
			cliente(26, "Clara")
		)
	);
	ListaNosFolhas *tabDadosSaida = le_nos_folhas(NOME_ARQUIVO_DADOS);

	ASSERT_EQUAL_CMP(tabDados, tabDadosSaida, cmp_nos_folhas);
	libera_nos_folhas(tabDados);
	libera_nos_folhas(tabDadosSaida);
}

TEST("Insercao 6 em arvore de altura H = 2 completa. Folha esta cheia, raiz tambem");
if (!skip) {
	int pos = INT_MAX;
	monta_arvore_h2_completa();

	pos = insere(22, "Camila", NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL(5 * tamanho_no_folha(), pos);

	Metadados *tabMetadados = metadados(2 * tamanho_no_interno(), 0, 3 * tamanho_no_interno(), 6 * tamanho_no_folha());
	Metadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
	ASSERT_EQUAL_CMP(tabMetadados, tabMetadadosSaida, cmp_metadados);
	free(tabMetadados);
	free(tabMetadadosSaida);

	ListaNosInternos *tabIndice = cria_nos_internos(3,
		// Antigo noh raiz
		cria_no_interno(2, 2 * tamanho_no_interno(), 1, 2 * 2 + 1,
			0,
			1 * tamanho_no_folha(),
			5 * tamanho_no_folha(),
			15,
			21
		),
		// Noh que surgiu do particionamento da raiz
		cria_no_interno(2, 2 * tamanho_no_interno(), 1, 2 * 2 + 1,
			2 * tamanho_no_folha(),
			3 * tamanho_no_folha(),
			4 * tamanho_no_folha(),
			40,
			70
		),
		// Novo noh raiz
		cria_no_interno(1, -1, 0, 1 * 2 + 1,
			0,
			1 * tamanho_no_interno(),
			25
		)
	);
	ListaNosInternos *tabIndiceSaida = le_nos_internos(NOME_ARQUIVO_INDICE);
	ASSERT_EQUAL_CMP(tabIndice, tabIndiceSaida, cmp_nos_internos);
	libera_nos_internos(tabIndice);
	libera_nos_internos(tabIndiceSaida);

	ListaNosFolhas *tabDados = cria_nos_folhas(6,
		cria_no_folha(0, 1 * tamanho_no_folha(), 2,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria")
		),
		cria_no_folha(0, 5 * tamanho_no_folha(), 2,
			cliente(15, "Jose"),
			cliente(20, "Mariana")
		),
		cria_no_folha(1 * tamanho_no_interno(), 3 * tamanho_no_folha(), 3,
			cliente(25, "Ronaldo"),
			cliente(35, "Marcela"),
			cliente(37, "Leonardo")
		),
		cria_no_folha(1 * tamanho_no_interno(), 4 * tamanho_no_folha(), 2,
			cliente(40, "Aline"),
			cliente(45, "Juca")
		),
		cria_no_folha(1 * tamanho_no_interno(), -1, 2,
			cliente(70, "Nicolas"),
			cliente(77, "Lina")
		),
		cria_no_folha(0, 2 * tamanho_no_folha(), 3,
			cliente(21, "Bruna"),
			cliente(22, "Camila"),
			cliente(23, "Bruno")
		)
	);
	ListaNosFolhas *tabDadosSaida = le_nos_folhas(NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL_CMP(tabDados, tabDadosSaida, cmp_nos_folhas);
	libera_nos_folhas(tabDados);
	libera_nos_folhas(tabDadosSaida);
}

TEST("Exclusao 1 em arvore de altura H = 2 cheia, nao eh necessario concatenacao");
if (!skip) {
	int pos = INT_MAX;
	// Arvore tem um dos nohs folha cheio. E eh neste noh que a excusao ocorrera
	monta_arvore_h2_cheia();

	pos = exclui(20, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL(1 * tamanho_no_folha(), pos);

	Metadados *tabMetadados = metadados(0, 0, tamanho_no_interno(), 3 * tamanho_no_folha());
	Metadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
	ASSERT_EQUAL_CMP(tabMetadados, tabMetadadosSaida, cmp_metadados);
	free(tabMetadados);
	free(tabMetadadosSaida);

	ListaNosInternos *tabIndice = cria_nos_internos(1,
		cria_no_interno(2, -1, 1, 2 * 2 + 1,
			0,
			1 * tamanho_no_folha(),
			2 * tamanho_no_folha(),
			15,
			25
		)
	);
	ListaNosInternos *tabIndiceSaida = le_nos_internos(NOME_ARQUIVO_INDICE);
	ASSERT_EQUAL_CMP(tabIndice, tabIndiceSaida, cmp_nos_internos);
	libera_nos_internos(tabIndice);
	libera_nos_internos(tabIndiceSaida);

	ListaNosFolhas *tabDados = cria_nos_folhas(3,
		cria_no_folha(0, 1 * tamanho_no_folha(), 2,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria")
		),
		cria_no_folha(0, 2 * tamanho_no_folha(), 3,
			cliente(15, "Jose"),
			cliente(21, "Bruna"),
			cliente(23, "Bruno")
		),
		cria_no_folha(0, -1, 3,
			cliente(25, "Ronaldo"),
			cliente(35, "Marcela"),
			cliente(37, "Leonardo")
		)
	);
	ListaNosFolhas *tabDadosSaida = le_nos_folhas(NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL_CMP(tabDados, tabDadosSaida, cmp_nos_folhas);
	libera_nos_folhas(tabDados);
	libera_nos_folhas(tabDadosSaida);
}

TEST("Exclusao 2 em arvore de altura H = 2, eh necessario redistribuição");
if (!skip) {
	int pos = INT_MAX;
	monta_arvore_h2();

	pos = exclui(20, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL(1 * tamanho_no_folha(), pos);

	Metadados *tabMetadados = metadados(0, 0, tamanho_no_interno(), 3 * tamanho_no_folha());
	Metadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
	ASSERT_EQUAL_CMP(tabMetadados, tabMetadadosSaida, cmp_metadados);
	free(tabMetadados);
	free(tabMetadadosSaida);

        ListaNosInternos *tabIndice = cria_nos_internos(1,
		cria_no_interno(2, -1, 1, 2 * 2 + 1,
			0,
			1 * tamanho_no_folha(),
			2 * tamanho_no_folha(),
			15,
			35
		)
	);
        
	ListaNosInternos *tabIndiceSaida = le_nos_internos(NOME_ARQUIVO_INDICE);
	ASSERT_EQUAL_CMP(tabIndice, tabIndiceSaida, cmp_nos_internos);
	libera_nos_internos(tabIndice);
	libera_nos_internos(tabIndiceSaida);

	ListaNosFolhas *tabDados = cria_nos_folhas(3,
		cria_no_folha(0, 1 * tamanho_no_folha(), 2,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria")
		),
		cria_no_folha(0, 2 * tamanho_no_folha(), 2,
			cliente(15, "Jose"),
			cliente(25, "Ronaldo")
		),
		cria_no_folha(0, -1, 2,
			cliente(35, "Marcela"),
			cliente(37, "Leonardo")
		)
	);     
        
	ListaNosFolhas *tabDadosSaida = le_nos_folhas(NOME_ARQUIVO_DADOS);

	ASSERT_EQUAL_CMP(tabDados, tabDadosSaida, cmp_nos_folhas);
	libera_nos_folhas(tabDados);
	libera_nos_folhas(tabDadosSaida);
}

TEST("Exclusao 3 em arvore de altura H = 2, eh necessario redistribuicao");
if (!skip) {
	int pos = INT_MAX;
	// Arvore tem um dos nohs folha cheio. E eh neste noh que a excusao ocorrera
	monta_arvore_h2_cheia();

	pos = exclui(13, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL(0, pos);

	Metadados *tabMetadados = metadados(0, 0, tamanho_no_interno(), 3 * tamanho_no_folha());
	Metadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
	ASSERT_EQUAL_CMP(tabMetadados, tabMetadadosSaida, cmp_metadados);
	free(tabMetadados);
	free(tabMetadadosSaida);

	ListaNosInternos *tabIndice = cria_nos_internos(1,
		cria_no_interno(2, -1, 1, 2 * 2 + 1,
			0,
			1 * tamanho_no_folha(),
			2 * tamanho_no_folha(),
			20,
			25
		)
	);
	ListaNosInternos *tabIndiceSaida = le_nos_internos(NOME_ARQUIVO_INDICE);
	ASSERT_EQUAL_CMP(tabIndice, tabIndiceSaida, cmp_nos_internos);
	libera_nos_internos(tabIndice);
	libera_nos_internos(tabIndiceSaida);

	ListaNosFolhas *tabDados = cria_nos_folhas(3,
		cria_no_folha(0, 1 * tamanho_no_folha(), 2,
			cliente(10, "Joao"),
			cliente(15, "Jose")
		),
		cria_no_folha(0, 2 * tamanho_no_folha(), 3,
			cliente(20, "Mariana"),
			cliente(21, "Bruna"),
			cliente(23, "Bruno")
		),
		cria_no_folha(0, -1, 3,
			cliente(25, "Ronaldo"),
			cliente(35, "Marcela"),
			cliente(37, "Leonardo")
		)
	);
	ListaNosFolhas *tabDadosSaida = le_nos_folhas(NOME_ARQUIVO_DADOS);

	ASSERT_EQUAL_CMP(tabDados, tabDadosSaida, cmp_nos_folhas);
	libera_nos_folhas(tabDados);
	libera_nos_folhas(tabDadosSaida);
}


END_TESTS();