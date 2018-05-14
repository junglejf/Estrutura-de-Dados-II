#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "geracao_particoes.h"
#include "nomes.h"
#include "cliente.h"
#include "limits.h"


void classificacao_interna(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M) {
	//TODO: Inserir aqui o codigo do algoritmo de geracao de particoes
}

void selecao_com_substituicao(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M) {
	FILE *in = fopen(nome_arquivo_entrada, "rb");
	Cliente *vetor[M];
	int tamanho, i = 0;
	while (i<M && (vetor[i] = le_cliente(in))) {
		i++;
	}
	tamanho = i;
	Nomes *p = nome_arquivos_saida;
	int cont;
	while (!feof(in)) {
		FILE *out = fopen(p->nome, "wb");
		cont = 0;
		while (cont < M) {
			int menor = cont;
			for (i=cont+1; i<M; i++) {
				if (vetor[i]->cod_cliente < vetor[menor]->cod_cliente) {
					menor = i;
				}
			}
			Cliente *anterior = vetor[menor];
			salva_cliente(vetor[menor], out);
			vetor[menor] = le_cliente(in);
			if (!(vetor[menor]) || vetor[menor]->cod_cliente < anterior->cod_cliente) {
				if (!vetor[menor]) {
					tamanho--;
				}
				Cliente *temp = vetor[cont];
				vetor[cont] = vetor[menor];
				vetor[menor] = temp;
				cont++;
			}
		}
		if (!feof(in)) {
			salva_cliente(cliente(INT_MAX, ""), out);
		}
		fclose(out);
		p = p->prox;
	}
	if (tamanho > 0) {
		FILE *out = fopen(p->nome, "wb");
		cont = 0;
		if (tamanho > 1) {
			while (cont < tamanho) {
				int menor = cont;
				for (i=cont+1; i<tamanho; i++) {
					if (vetor[i]->cod_cliente < vetor[menor]->cod_cliente) {
						menor = i;
					}
				}
				salva_cliente(vetor[menor], out);
				if (menor != cont) {
					Cliente *temp = vetor[cont];
					vetor[cont] = vetor[menor];
					vetor[menor] = temp;
				}
				cont++;
			}
		} else if (tamanho == 1) {
			salva_cliente(vetor[0], out);
		}
		fclose(out);
	}
    fclose(in);
}

void selecao_natural(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M, int n) {
	//TODO: Inserir aqui o codigo do algoritmo de geracao de particoes
}