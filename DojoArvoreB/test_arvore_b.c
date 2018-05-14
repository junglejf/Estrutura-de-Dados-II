#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#define BEFORE_TEST before();

#define NOME_ARQUIVO_DADOS "clientes.dat"
#define NOME_ARQUIVO_METADADOS "metadados.dat"

#include <limits.h>
#include <stdlib.h>

#include "ufftest.h"
#include "lista_clientes.h"
#include "cliente.h"
#include "lista_nos.h"
#include "no.h"
#include "metadados.h"
#include "arvore_b.h"


void before()
{
	remove(NOME_ARQUIVO_DADOS);
	remove(NOME_ARQUIVO_METADADOS);
}

// Arvore B de altura H = 1, com apenas 1 noh (raiz eh uma folha) que tem 2 registros
// Ver arquivo ArvoreTesteDOJO.pdf para o desenho da arvore
void monta_arvore_h1()
{
	Metadados *tabMetadados = metadados(0, 1*tamanho_no());
	salva_arq_metadados(NOME_ARQUIVO_METADADOS, tabMetadados);
	// Estrutura do No: m, pont_pai, 2m + 1, lista de ponteiros, lista de clientes
	// Atencao: os ponteiros sao absolutos

	ListaNos *tabDados = cria_nos(1,
		cria_no(2, -1, 2 * 2 + 1,
			-1,
			-1,
			-1,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria")));
	salva_nos(NOME_ARQUIVO_DADOS, tabDados);
	free(tabMetadados);
	libera_nos(tabDados);
}

// Arvore B de altura H = 1, com apenas 1 noh (raiz eh uma folha) que tem 4 registros
// Ver arquivo ArvoreTesteDOJO.pdf para o desenho da arvore
void monta_arvore_h1_cheia()
{
	Metadados *tabMetadados = metadados(0, 1*tamanho_no());
	salva_arq_metadados(NOME_ARQUIVO_METADADOS, tabMetadados);
	// Estrutura do No: m, pont_pai, 2m + 1, lista de ponteiros, lista de clientes
	// Atencao: os ponteiros sao absolutos

	ListaNos *tabDados = cria_nos(1,
		cria_no(4, -1, 4 * 2 + 1,
			-1,
			-1,
			-1,
			-1,
			-1,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria"),
			cliente(15, "Bianca"),
			cliente(26, "Clara")
		));
	salva_nos(NOME_ARQUIVO_DADOS, tabDados);
	free(tabMetadados);
	libera_nos(tabDados);
}

// Arvore B de altura H = 2, com raiz e mais 3 folhas
// Ver arquivo ArvoreTesteDOJO.pdf para o desenho da arvore
void monta_arvore_h2()
{
	Metadados *tabMetadados = metadados(0, 4*tamanho_no());
	salva_arq_metadados(NOME_ARQUIVO_METADADOS, tabMetadados);
	// Estrutura do No: m, pont_pai, 2m + 1, lista de ponteiros, lista de clientes
	// Atencao: os ponteiros sao absolutos

	ListaNos *tabDados = cria_nos(4,
		cria_no(2, -1, 2 * 2 + 1, // No raiz
			1 * tamanho_no(),
			2 * tamanho_no(),
			3 * tamanho_no(),
			cliente(15, "Jose"),
			cliente(25, "Ronaldo")
		),
		cria_no(2, 0, 2 * 2 + 1, // Filho 1
			-1,
			-1,
			-1,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria")
		),
		cria_no(2, 0, 2 * 2 + 1, // Filho 2
			-1,
			-1,
			-1,
			cliente(17, "Joice"),
			cliente(20, "Mariana")
		),
		cria_no(3, 0, 3 * 2 + 1, // Filho 3
			-1,
			-1,
			-1,
			-1,
			cliente(30, "Bruna"),
			cliente(35, "Marcela"),
			cliente(37, "Leonardo")
		)
	);
	salva_nos(NOME_ARQUIVO_DADOS, tabDados);
	free(tabMetadados);
	libera_nos(tabDados);
}

// Arvore B de altura H = 2, com raiz e mais 3 folhas, 1 delas cheia
// Ver arquivo ArvoreTesteDOJO.pdf para o desenho da arvore
void monta_arvore_h2_cheia()
{
	Metadados *tabMetadados = metadados(0, 4*tamanho_no());
	salva_arq_metadados(NOME_ARQUIVO_METADADOS, tabMetadados);
	// Estrutura do No: m, pont_pai, 2m + 1, lista de ponteiros, lista de clientes
	// Atencao: os ponteiros sao absolutos

	ListaNos *tabDados = cria_nos(4,
		cria_no(2, -1, 2 * 2 + 1, // No raiz
			1 * tamanho_no(),
			2 * tamanho_no(),
			3 * tamanho_no(),
			cliente(15, "Jose"),
			cliente(25, "Ronaldo")
		),
		cria_no(2, 0, 2 * 2 + 1, // Filho 1
			-1,
			-1,
			-1,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria")
		),
		cria_no(4, 0, 4 * 2 + 1, // Filho 2
			-1,
			-1,
			-1,
			-1,
			-1,
			cliente(17, "Joice"),
			cliente(20, "Mariana"),
			cliente(21, "Deia"),
			cliente(23, "Bruno")
		),
		cria_no(3, 0, 3 * 2 + 1, // Filho 3
			-1,
			-1,
			-1,
			-1,
			cliente(30, "Bruna"),
			cliente(35, "Marcela"),
			cliente(37, "Leonardo")
		)
	);
	salva_nos(NOME_ARQUIVO_DADOS, tabDados);
	free(tabMetadados);
	libera_nos(tabDados);
}

// Arvore B de altura H = 3, com raiz que aponta para 2 nohs internos, e mais 6 folhas
// Ver arquivo ArvoreTesteDOJO.pdf para o desenho da arvore
void monta_arvore_h3()
{
	Metadados *tabMetadados = metadados(0, 9*tamanho_no());
	salva_arq_metadados(NOME_ARQUIVO_METADADOS, tabMetadados);
	// Estrutura do No: m, pont_pai, 2m + 1, lista de ponteiros, lista de clientes
	// Atencao: os ponteiros sao absolutos

	ListaNos *tabDados = cria_nos(9,
		cria_no(1, -1, 1 * 2 + 1, // No raiz
			1 * tamanho_no(),
			2 * tamanho_no(),
			cliente(37, "Ricardo")
		),
		cria_no(2, 0, 2 * 2 + 1, // Filho 1 da raiz
			3 * tamanho_no(),
			4 * tamanho_no(),
			5 * tamanho_no(),
			cliente(15, "Jose"),
			cliente(25, "Ronaldo")
		),
		cria_no(2, 0, 2 * 2 + 1, // Filho 2 da raiz
			6 * tamanho_no(),
			7 * tamanho_no(),
			8 * tamanho_no(),
			cliente(40, "Joao"),
			cliente(55, "Catarina")
		),
		cria_no(2, 1*tamanho_no(), 2 * 2 + 1, // Folha 1
			-1,
			-1,
			-1,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria")
		),
		cria_no(2, 1*tamanho_no(), 2 * 2 + 1, // Folha 2
			-1,
			-1,
			-1,
			cliente(17, "Joice"),
			cliente(20, "Mariana")
		),
		cria_no(2, 1*tamanho_no(), 2 * 2 + 1, // Folha 3
			-1,
			-1,
			-1,
			cliente(30, "Bruna"),
			cliente(35, "Marcela")
		),
		cria_no(2, 2*tamanho_no(), 2 * 2 + 1, // Folha 4
			-1,
			-1,
			-1,
			cliente(38, "Adriana"),
			cliente(39, "Fabio")
		),
		cria_no(2, 2*tamanho_no(), 2 * 2 + 1, // Folha 5
			-1,
			-1,
			-1,
			cliente(43, "Larissa"),
			cliente(50, "Tatiana")
		),
		cria_no(3, 2*tamanho_no(), 3 * 2 + 1, // Folha 6
			-1,
			-1,
			-1,
			-1,
			cliente(57, "Alice"),
			cliente(60, "JC"),
			cliente(70, "Lucas")
		)
	);
	salva_nos(NOME_ARQUIVO_DADOS, tabDados);
	free(tabMetadados);
	libera_nos(tabDados);
}

BEGIN_TESTS();

TEST("Busca 1 -- chave procurada esta na raiz. Raiz eh folha");
if (!skip) {
	int pont = INT_MAX, encontrou = INT_MAX, pos = INT_MAX;
	monta_arvore_h1();

	pos = busca(13, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_DADOS, &pont, &encontrou);
	ASSERT_EQUAL(0, pont);
	ASSERT_EQUAL(1, pos);
	ASSERT_TRUE(encontrou);
}

TEST("Busca 2 -- chave procurada nao esta na arvore. Raiz eh folha");
if (!skip) {
	int pont = INT_MAX, encontrou = INT_MAX, pos = INT_MAX;
	monta_arvore_h1();

	pos = busca(6, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_DADOS, &pont, &encontrou);
	ASSERT_EQUAL(0, pont);
	ASSERT_EQUAL(0, pos);
	ASSERT_FALSE(encontrou);
}

TEST("Busca 3 -- chave esta na arvore");
if (!skip) {
	int pont = INT_MAX, encontrou = INT_MAX, pos = INT_MAX;
	monta_arvore_h2();

	pos = busca(20, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_DADOS, &pont, &encontrou);
	ASSERT_EQUAL(2 * tamanho_no(), pont);
	ASSERT_EQUAL(1, pos);
	ASSERT_TRUE(encontrou);
}

TEST("Busca 4 -- chave nao esta na arvore");
if (!skip) {
	int pont = INT_MAX, encontrou = INT_MAX, pos = INT_MAX;
	monta_arvore_h2();

	pos = busca(16, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_DADOS, &pont, &encontrou);
	ASSERT_EQUAL(2 * tamanho_no(), pont);
	ASSERT_EQUAL(0, pos);
	ASSERT_FALSE(encontrou);
}

TEST("Busca 5 -- chave esta na arvore");
if (!skip) {
	int pont = INT_MAX, encontrou = INT_MAX, pos = INT_MAX;
	monta_arvore_h3();

	pos = busca(50, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_DADOS, &pont, &encontrou);
	ASSERT_EQUAL(7 * tamanho_no(), pont);
	ASSERT_EQUAL(1, pos);
	ASSERT_TRUE(encontrou);
}

TEST("Busca 6 -- chave nao esta na arvore");
if (!skip) {
	int pont = INT_MAX, encontrou = INT_MAX, pos = INT_MAX;
	monta_arvore_h3();

	pos = busca(26, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_DADOS, &pont, &encontrou);
	ASSERT_EQUAL(5 * tamanho_no(), pont);
	ASSERT_EQUAL(0, pos);
	ASSERT_FALSE(encontrou);
}

TEST("Busca 7 -- chave esta a esquerda");
if (!skip) {
	int pont = INT_MAX, encontrou = INT_MAX, pos = INT_MAX;
	monta_arvore_h2();

	pos = busca(13, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_DADOS, &pont, &encontrou);
	ASSERT_EQUAL(1 * tamanho_no(), pont);
	ASSERT_EQUAL(1, pos);
	ASSERT_TRUE(encontrou);
}

TEST("Insercao 1 em arvore de altura H = 1, sem particionamento");
if (!skip) {
	int pos = INT_MAX;
	monta_arvore_h1();

	pos = insere(11, "Vanessa", NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL(0, pos);

	ListaNos *tabDados = cria_nos(1,
		cria_no(3, -1, 3 * 2 + 1,
			-1,
			-1,
			-1,
			-1,
			cliente(10, "Joao"),
			cliente(11, "Vanessa"),
			cliente(13, "Ana Maria")));
	ListaNos *tabDadosSaida = le_nos(NOME_ARQUIVO_DADOS);

	ASSERT_EQUAL_CMP(tabDados, tabDadosSaida, cmp_nos);
	libera_nos(tabDados);
	libera_nos(tabDadosSaida);
}

TEST("Insercao 2 em arvore de altura H = 2, sem particionamento");
if (!skip) {
	int pos = INT_MAX;
	monta_arvore_h2();

	pos = insere(11, "Vanessa", NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL(1 * tamanho_no(), pos);

	ListaNos *tabDados = cria_nos(4,
		cria_no(2, -1, 2 * 2 + 1, // No raiz
			1 * tamanho_no(),
			2 * tamanho_no(),
			3 * tamanho_no(),
			cliente(15, "Jose"),
			cliente(25, "Ronaldo")
		),
		cria_no(3, 0, 3 * 2 + 1, // Filho 1
			-1,
			-1,
			-1,
			-1,
			cliente(10, "Joao"),
			cliente(11, "Vanessa"),
			cliente(13, "Ana Maria")
		),
		cria_no(2, 0, 2 * 2 + 1, // Filho 2
			-1,
			-1,
			-1,
			cliente(17, "Joice"),
			cliente(20, "Mariana")
		),
		cria_no(3, 0, 3 * 2 + 1, // Filho 3
			-1,
			-1,
			-1,
			-1,
			cliente(30, "Bruna"),
			cliente(35, "Marcela"),
			cliente(37, "Leonardo")
		)
	);
	ListaNos *tabDadosSaida = le_nos(NOME_ARQUIVO_DADOS);

	ASSERT_EQUAL_CMP(tabDados, tabDadosSaida, cmp_nos);
	libera_nos(tabDados);
	libera_nos(tabDadosSaida);
}

TEST("Insercao 3 em arvore de altura H = 2. Exige particionamento de uma pagina folha");
if (!skip) {
	int pos = INT_MAX;
	monta_arvore_h2_cheia();

	pos = insere(16, "Vanessa", NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL(2 * tamanho_no(), pos);

	ListaNos *tabDados = cria_nos(5,
		cria_no(3, -1, 3 * 2 + 1, // No raiz
			1 * tamanho_no(),
			2 * tamanho_no(),
			4 * tamanho_no(),
			3 * tamanho_no(),
			cliente(15, "Jose"),
			cliente(20, "Mariana"),
			cliente(25, "Ronaldo")
		),
		cria_no(2, 0, 2 * 2 + 1, // Filho 1
			-1,
			-1,
			-1,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria")
		),
		cria_no(2, 0, 2 * 2 + 1, // Filho 2
			-1,
			-1,
			-1,
			cliente(16, "Vanessa"),
			cliente(17, "Joice")
		),
		cria_no(3, 0, 3 * 2 + 1, // Filho 3
			-1,
			-1,
			-1,
			-1,
			cliente(30, "Bruna"),
			cliente(35, "Marcela"),
			cliente(37, "Leonardo")
		),
		cria_no(2, 0, 2 * 2 + 1, // Novo Filho
			-1,
			-1,
			-1,
			cliente(21, "Deia"),
			cliente(23, "Bruno")
		)
	);
	ListaNos *tabDadosSaida = le_nos(NOME_ARQUIVO_DADOS);

	ASSERT_EQUAL_CMP(tabDados, tabDadosSaida, cmp_nos);
	libera_nos(tabDados);
	libera_nos(tabDadosSaida);
}

TEST("Insercao 4 em arvore de altura H = 2, chave de registro ja existe -- nao inserir");
if (!skip) {
	int pos = INT_MAX;
	monta_arvore_h2();

	pos = insere(13, "Vanessa", NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL(-1, pos);

	ListaNos *tabDados = cria_nos(4,
		cria_no(2, -1, 2 * 2 + 1, // No raiz
			1 * tamanho_no(),
			2 * tamanho_no(),
			3 * tamanho_no(),
			cliente(15, "Jose"),
			cliente(25, "Ronaldo")
		),
		cria_no(2, 0, 2 * 2 + 1, // Filho 1
			-1,
			-1,
			-1,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria")
		),
		cria_no(2, 0, 2 * 2 + 1, // Filho 2
			-1,
			-1,
			-1,
			cliente(17, "Joice"),
			cliente(20, "Mariana")
		),
		cria_no(3, 0, 3 * 2 + 1, // Filho 3
			-1,
			-1,
			-1,
			-1,
			cliente(30, "Bruna"),
			cliente(35, "Marcela"),
			cliente(37, "Leonardo")
		)
	);
	ListaNos *tabDadosSaida = le_nos(NOME_ARQUIVO_DADOS);

	ASSERT_EQUAL_CMP(tabDados, tabDadosSaida, cmp_nos);
	libera_nos(tabDados);
	libera_nos(tabDadosSaida);
}

TEST("Insercao 5 em arvore de altura H = 1 cheia, que causa aumento na altura da arvore");
if (!skip) {
	int pos = INT_MAX;
	monta_arvore_h1_cheia();

	pos = insere(11, "Vanessa", NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL(0, pos);

	ListaNos *tabDados = cria_nos(3,
		cria_no(2, 2 * tamanho_no(), 2 * 2 + 1, // Antigo noh raiz
			-1,
			-1,
			-1,
			cliente(10, "Joao"),
			cliente(11, "Vanessa")),
		cria_no(2, 2 * tamanho_no(), 2 * 2 + 1, // Novo noh folha
			-1,
			-1,
			-1,
			cliente(15, "Bianca"),
			cliente(26, "Clara")),
		cria_no(1, -1, 1 * 2 + 1, // Novo noh raiz
			0 * tamanho_no(),
			1 * tamanho_no(),
			cliente(13, "Ana Maria")));
	ListaNos *tabDadosSaida = le_nos(NOME_ARQUIVO_DADOS);

	ASSERT_EQUAL_CMP(tabDados, tabDadosSaida, cmp_nos);
	libera_nos(tabDados);
	libera_nos(tabDadosSaida);

	Metadados *tabMetadados = metadados(2 * tamanho_no(), 3 * tamanho_no());
	Metadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
	ASSERT_EQUAL_CMP(tabMetadados, tabMetadadosSaida, cmp_metadados);
	free(tabMetadados);
	free(tabMetadadosSaida);
}

TEST("Exclusao 1 em arvore de altura H = 2 cheia, nao eh necessario concatenacao");
if (!skip) {
	int pos = INT_MAX;
	monta_arvore_h2_cheia();

	pos = exclui(20, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL(2 * tamanho_no(), pos);

	ListaNos *tabDados = cria_nos(4,
		cria_no(2, -1, 2 * 2 + 1, // No raiz
			1 * tamanho_no(),
			2 * tamanho_no(),
			3 * tamanho_no(),
			cliente(15, "Jose"),
			cliente(25, "Ronaldo")
		),
		cria_no(2, 0, 2 * 2 + 1, // Filho 1
			-1,
			-1,
			-1,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria")
		),
		cria_no(3, 0, 3 * 2 + 1, // Filho 2
			-1,
			-1,
			-1,
			-1,
			cliente(17, "Joice"),
			cliente(21, "Deia"),
			cliente(23, "Bruno")
		),
		cria_no(3, 0, 3 * 2 + 1, // Filho 3
			-1,
			-1,
			-1,
			-1,
			cliente(30, "Bruna"),
			cliente(35, "Marcela"),
			cliente(37, "Leonardo")
		)
	);
	ListaNos *tabDadosSaida = le_nos(NOME_ARQUIVO_DADOS);

	ASSERT_EQUAL_CMP(tabDados, tabDadosSaida, cmp_nos);
	libera_nos(tabDados);
	libera_nos(tabDadosSaida);
}

TEST("Exclusao 2 em arvore de altura H = 2, nao eh necessario concatenacao");
if (!skip) {
	int pos = INT_MAX;
	monta_arvore_h2_cheia();

	pos = exclui(15, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL(0 * tamanho_no(), pos);

	ListaNos *tabDados = cria_nos(4,
		cria_no(2, -1, 2 * 2 + 1, // No raiz
			1 * tamanho_no(),
			2 * tamanho_no(),
			3 * tamanho_no(),
			cliente(17, "Joice"),
			cliente(25, "Ronaldo")
		),
		cria_no(2, 0, 2 * 2 + 1, // Filho 1
			-1,
			-1,
			-1,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria")
		),
		cria_no(3, 0, 3 * 2 + 1, // Filho 2 atualizado
			-1,
			-1,
			-1,
			-1,
			cliente(20, "Mariana"),
			cliente(21, "Deia"),
			cliente(23, "Bruno")
		),
		cria_no(3, 0, 3 * 2 + 1, // Filho 3
			-1,
			-1,
			-1,
			-1,
			cliente(30, "Bruna"),
			cliente(35, "Marcela"),
			cliente(37, "Leonardo")
		)
	);
	ListaNos *tabDadosSaida = le_nos(NOME_ARQUIVO_DADOS);

	ASSERT_EQUAL_CMP(tabDados, tabDadosSaida, cmp_nos);
	libera_nos(tabDados);
	libera_nos(tabDadosSaida);
}

TEST("Exclusao 3 em arvore de altura H = 2, eh necessario redistribuicao");
if (!skip) {
        //printf("\nExclusao 3\n");
	int pos = INT_MAX;
	monta_arvore_h2();

	pos = exclui(17, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL(2 * tamanho_no(), pos);

	ListaNos *tabDados = cria_nos(4,
		cria_no(2, -1, 2 * 2 + 1, // No raiz
			1 * tamanho_no(),
			2 * tamanho_no(),
			3 * tamanho_no(),
			cliente(15, "Jose"),
			cliente(30, "Bruna")
		),
		cria_no(2, 0, 2 * 2 + 1, // Filho 1
			-1,
			-1,
			-1,
			cliente(10, "Joao"),
			cliente(13, "Ana Maria")
		),
		cria_no(2, 0, 2 * 2 + 1, // Filho 2 atualizado
			-1,
			-1,
			-1,
			cliente(20, "Mariana"),
			cliente(25, "Ronaldo")
		),
		cria_no(2, 0, 2 * 2 + 1, // Filho 3 atualizado
			-1,
			-1,
			-1,
			cliente(35, "Marcela"),
			cliente(37, "Leonardo")
		)
	);
	ListaNos *tabDadosSaida = le_nos(NOME_ARQUIVO_DADOS);

	ASSERT_EQUAL_CMP(tabDados, tabDadosSaida, cmp_nos);
	libera_nos(tabDados);
	libera_nos(tabDadosSaida);
}

TEST("Exclusao 4 em arvore de altura H = 2 cheia, eh necessario redistribuicao");
if (!skip) {
	int pos = INT_MAX;
	monta_arvore_h2_cheia();

	pos = exclui(13, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL(1 * tamanho_no(), pos);

	ListaNos *tabDados = cria_nos(4,
		cria_no(2, -1, 2 * 2 + 1, // No raiz atualizado
			1 * tamanho_no(),
			2 * tamanho_no(),
			3 * tamanho_no(),
			cliente(17, "Joice"),
			cliente(25, "Ronaldo")
		),
		cria_no(2, 0, 2 * 2 + 1, // Filho 1 atualizado
			-1,
			-1,
			-1,
			cliente(10, "Joao"),
			cliente(15, "Jose")
		),
		cria_no(3, 0, 3 * 2 + 1, // Filho 2 atualizado
			-1,
			-1,
			-1,
			-1,
			cliente(20, "Mariana"),
			cliente(21, "Deia"),
			cliente(23, "Bruno")
		),
		cria_no(3, 0, 3 * 2 + 1, // Filho 3
			-1,
			-1,
			-1,
			-1,
			cliente(30, "Bruna"),
			cliente(35, "Marcela"),
			cliente(37, "Leonardo")
		)
	);
	ListaNos *tabDadosSaida = le_nos(NOME_ARQUIVO_DADOS);

	ASSERT_EQUAL_CMP(tabDados, tabDadosSaida, cmp_nos);
	libera_nos(tabDados);
	libera_nos(tabDadosSaida);
}

TEST("Exclusao 5 em arvore de altura H = 2 cheia, eh necessario concatenacao");
if (!skip) {
        int pos = INT_MAX;
	monta_arvore_h2();

	pos = exclui(13, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL(1 * tamanho_no(), pos);

	ListaNos *tabDados = cria_nos(4,
		cria_no(1, -1, 1 * 2 + 1, // No raiz atualizado
			1 * tamanho_no(),
			3 * tamanho_no(),
			cliente(25, "Ronaldo")
		),
		cria_no(4, 0, 4 * 2 + 1, // Filho 1 atualizado
			-1,
			-1,
			-1,
			-1,
			-1,
			cliente(10, "Joao"),
			cliente(15, "Jose"),
			cliente(17, "Joice"),
			cliente(20, "Mariana")
		),
		cria_no(2, 0, 2 * 2 + 1, // Filho 2 agora eh lixo.
			-1,                  // Ficou como estava originalmente, mas nao ha ninguem apontando para ele
			-1,
			-1,
			cliente(17, "Joice"),
			cliente(20, "Mariana")
		),
		cria_no(3, 0, 3 * 2 + 1, // Filho 3 nao sofreu modificacoes
			-1,
			-1,
			-1,
			-1,
			cliente(30, "Bruna"),
			cliente(35, "Marcela"),
			cliente(37, "Leonardo")
		)
	);
	ListaNos *tabDadosSaida = le_nos(NOME_ARQUIVO_DADOS);
	ASSERT_EQUAL_CMP(tabDados, tabDadosSaida, cmp_nos);
	libera_nos(tabDados);
	libera_nos(tabDadosSaida);
}


END_TESTS();