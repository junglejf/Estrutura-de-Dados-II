#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "arvore_b.h"
#include "metadados.h"
#include "no.h"
#include "cliente.h"


int busca(int cod_cli, char *nome_arquivo_metadados, char *nome_arquivo_dados, int *pont, int *encontrou) {
    FILE *meta = fopen(nome_arquivo_metadados, "r+b");
    Metadados *metadado = le_metadados(meta);
    *pont = metadado->pont_raiz;
    if (metadado->pont_prox_no_livre == 0) {
        *pont = 0;
        *encontrou = 0;
        free(metadado);
        fclose(meta);
        return 0;
    }
    free(metadado);
    fclose(meta);
    FILE *dados = fopen(nome_arquivo_dados, "r+b");
    fseek(dados, *pont, SEEK_SET);
    No *no = le_no(dados);
    *encontrou = 0;
    int i = 0;
    while (!(*encontrou)) {
        i = 0;
        while (i < no->m && no->clientes[i]->cod_cliente <= cod_cli) {
            if (no->clientes[i]->cod_cliente == cod_cli) {
                *encontrou = 1;
                break;
            }
            i++;
        }
        if (!(*encontrou)) {
            if (no->p[i] != -1) {
                *pont = no->p[i];
                fseek(dados, *pont, SEEK_SET);
                no = le_no(dados);
            } else {
                break;
            }
        }
    }
    if (!(*encontrou)) {
        int j = 0;
        while (j < no->m && no->clientes[j]->cod_cliente < cod_cli)
            j++;
        i = j;
    }
    libera_no(no);
    fclose(dados);
    return i;
}

int insere(int cod_cli, char *nome_cli, char *nome_arquivo_metadados, char *nome_arquivo_dados) {
    int pont_atual, encontrou, pos;
    pos = busca(cod_cli, nome_arquivo_metadados, nome_arquivo_dados, &pont_atual, &encontrou);
    if (encontrou)
        return -1;
    FILE *meta_arq = fopen(nome_arquivo_metadados, "r+b");
    FILE *dados_arq = fopen(nome_arquivo_dados, "r+b");
    
    No *no_atual;
    Metadados *meta = le_metadados(meta_arq);
    if (meta->pont_prox_no_livre == 0) {
        no_atual = no(0, -1);
    } else {
        fseek(dados_arq, pont_atual, SEEK_SET);
        no_atual = le_no(dados_arq);
    }
    
    Cliente *novo_cliente = cliente(cod_cli, nome_cli);
    int pont = pont_atual;
    insere_rec(novo_cliente, meta_arq, dados_arq, no_atual, pont_atual, pos, -1, &pont);
    
    free(novo_cliente);
    libera_no(no_atual);
    fclose(dados_arq);
    fclose(meta_arq);
    return pont;
}

void insere_rec(Cliente *novo_cliente, FILE *meta_arq, FILE *dados_arq, No *no_atual, int pont_atual, int pos, int pont_novo_filho, int *pont) {
    if (no_atual->m < 2*D) {
        int i;
        for (i=no_atual->m; i>pos; i--) {
            no_atual->clientes[i] = no_atual->clientes[i-1];
            no_atual->p[i+1] = no_atual->p[i];
        }
        no_atual->clientes[pos] = novo_cliente;
        no_atual->p[pos+1] = pont_novo_filho;
        no_atual->m++;
        fseek(dados_arq, pont_atual, SEEK_SET);
        salva_no(no_atual, dados_arq);
    } else {
        Cliente *vetor_cliente[2*D+1];
        int i, cont = 0;
        for (i=0; i<2*D+1; i++) {
            if (i != pos) {
                vetor_cliente[i] = no_atual->clientes[cont];
                cont++;
            }
        }
        vetor_cliente[pos] = novo_cliente;
        
        int vetor_pont[(2*D+1)+1];
        cont = 0;
        for (i=0; i<(2*D+1)+1; i++) {
            if (i != pos+1) {
                vetor_pont[i] = no_atual->p[cont];
                cont++;
            }
        }
        vetor_pont[pos+1] = pont_novo_filho;
        
        for (i=0; i<D; i++) {
            no_atual->clientes[i] = vetor_cliente[i];
            no_atual->p[i] = vetor_pont[i];
        }
        no_atual->p[D] = vetor_pont[D];
        for (i=D; i<2*D; i++) {
            no_atual->clientes[i] = NULL;
            no_atual->p[i+1] = -1;
        }
        no_atual->m = D;
        
        No *no_novo = no(D, no_atual->pont_pai);
        for (i=0; i<D; i++) {
            no_novo->clientes[i] = vetor_cliente[(D+1)+i];
            no_novo->p[i] = vetor_pont[(D+1)+i];
        }
        no_novo->p[D] = vetor_pont[2*D+1];
        no_novo->m = D;
        
        fseek(meta_arq, 0, SEEK_SET);
        Metadados *meta = le_metadados(meta_arq);
        int pont_novo_no = meta->pont_prox_no_livre;
        meta->pont_prox_no_livre += tamanho_no();
        
        if (vetor_cliente[D]->cod_cliente == novo_cliente->cod_cliente) {
            *pont = no_atual->pont_pai;
        } else {
            for (i=D+1; i<2*D+1; i++) {
                if (vetor_cliente[i]->cod_cliente == novo_cliente->cod_cliente) {
                    *pont = pont_novo_no;
                    break;
                }
            }
        }
        
        No *no_pai;
        if (no_atual->pont_pai != -1) {
            fseek(dados_arq, no_atual->pont_pai, SEEK_SET);
            no_pai = le_no(dados_arq);
            i = 0;
            while (i < no_pai->m && vetor_cliente[D]->cod_cliente > no_pai->clientes[i]->cod_cliente)
                i++;
        } else {
            no_pai = no(0, -1);
            no_pai->p[0] = pont_atual;
            no_atual->pont_pai = meta->pont_prox_no_livre;
            no_novo->pont_pai = meta->pont_prox_no_livre;
            
            meta->pont_raiz = meta->pont_prox_no_livre;
            meta->pont_prox_no_livre += tamanho_no();
            
            i = 0;
        }
        
        fseek(meta_arq, 0, SEEK_SET);
        salva_metadados(meta, meta_arq);
        fseek(dados_arq, pont_novo_no, SEEK_SET);
        salva_no(no_novo, dados_arq);
        fseek(dados_arq, pont_atual, SEEK_SET);
        salva_no(no_atual, dados_arq);
        
        insere_rec(vetor_cliente[D], meta_arq, dados_arq, no_pai, no_atual->pont_pai, i, pont_novo_no, pont);
        
        for (i=0; i<D+1; i++) {
            if (no_novo->p[i] != -1) {
                fseek(dados_arq, no_novo->p[i], SEEK_SET);
                No *temp = le_no(dados_arq);
                temp->pont_pai = pont_novo_no;
                fseek(dados_arq, no_novo->p[i], SEEK_SET);
                salva_no(temp, dados_arq);
                libera_no(temp);
            }
        }
        
        libera_no(no_novo);
        libera_no(no_pai);
        for (i=0; i<2*D+1; i++)
            free(vetor_cliente[i]);
        free(meta);
    }
}

int exclui(int cod_cli, char *nome_arquivo_metadados, char *nome_arquivo_dados) {
    int pont_atual, encontrou, pos;
    pos = busca(cod_cli, nome_arquivo_metadados, nome_arquivo_dados, &pont_atual, &encontrou);
    if (!encontrou)
        return -1;
    FILE *meta_arq = fopen(nome_arquivo_metadados, "r+b");
    FILE *dados_arq = fopen(nome_arquivo_dados, "r+b");
    fseek(dados_arq, pont_atual, SEEK_SET);
    No *no_atual = le_no(dados_arq);
    int pont = pont_atual;
    exclui_rec(meta_arq, dados_arq, no_atual, pont_atual, pos);
    libera_no(no_atual);
    fclose(dados_arq);
    fclose(meta_arq);
    return pont;
}

// Não trata a propagação da concatenação para os nós superiores
void exclui_rec(FILE *meta_arq, FILE *dados_arq, No *no_atual, int pont_atual, int pos) {
    if (no_atual->p[0] != -1) {
        // Se no_atual não é folha
        int temp_pont = no_atual->p[pos+1];
        fseek(dados_arq, temp_pont, SEEK_SET);
        No *temp_no = le_no(dados_arq);
        while (temp_no->p[0] != -1) {
            temp_pont = temp_no->p[0];
            fseek(dados_arq, temp_pont, SEEK_SET);
            temp_no = le_no(dados_arq);
        }
        
        Cliente *temp_cliente = temp_no->clientes[0];
        exclui_rec(meta_arq, dados_arq, temp_no, temp_pont, 0);
        no_atual->clientes[pos] = temp_cliente;
        
        fseek(dados_arq, pont_atual, SEEK_SET);
        salva_no(no_atual, dados_arq);
        free(temp_cliente);
        libera_no(temp_no);
    } else {
        if (no_atual->m > D || no_atual->pont_pai == -1) {
            // Se no_atual tem mais que D clientes ou é raiz
            int i;
            for (i=pos; i<no_atual->m-1; i++) {
                no_atual->clientes[i] = no_atual->clientes[i+1];
                no_atual->p[i+1] = no_atual->p[i+2];
            }
            no_atual->clientes[no_atual->m-1] = NULL;
            no_atual->p[no_atual->m] = -1;
            no_atual->m--;
            if (no_atual->m == 0) {
                no_atual = NULL;
                fseek(meta_arq, 0, SEEK_SET);
                Metadados *meta = le_metadados(meta_arq);
                meta->pont_prox_no_livre = 0;
                fseek(meta_arq, 0, SEEK_SET);
                salva_metadados(meta, meta_arq);
                free(meta);
            }
            fseek(dados_arq, pont_atual, SEEK_SET);
            salva_no(no_atual, dados_arq);
        } else {
            fseek(dados_arq, no_atual->pont_pai, SEEK_SET);
            No *no_pai = le_no(dados_arq);
            int i = 0, pos_pont_atual;
            while (i < no_pai->m+1 && no_pai->p[i] != pont_atual)
                i++;
            pos_pont_atual = i;
            
            No *no_adj;
            int tamanho_vetor_cliente = 0;
            if (no_pai->p[pos_pont_atual+1] != -1) {
                // Se no_adj é o da direita
                fseek(dados_arq, no_pai->p[pos_pont_atual+1], SEEK_SET);
                no_adj = le_no(dados_arq);
                tamanho_vetor_cliente = no_atual->m + no_adj->m;
                
                Cliente *vetor_cliente[tamanho_vetor_cliente];
                int cont = 0;
                for (i=0; i<no_atual->m; i++) {
                    if (i != pos) {
                        vetor_cliente[cont++] = no_atual->clientes[i];
                    }
                }
                vetor_cliente[cont++] = no_pai->clientes[pos_pont_atual];
                for (i=0; i<no_adj->m; i++) {
                    vetor_cliente[cont++] = no_adj->clientes[i];
                }
                
                if (tamanho_vetor_cliente <= 2*D) {
                    // Concatenacao
                    int vetor_pont[tamanho_vetor_cliente+1];
                    cont = 0;
                    for (i=0; i<no_atual->m+1; i++) {
                        vetor_pont[cont++] = no_atual->p[i];
                    }
                    for (i=0; i<no_adj->m+1; i++) {
                        vetor_pont[cont++] = no_adj->p[i];
                    }
                    
                    for (i=0; i<tamanho_vetor_cliente; i++) {
                        no_atual->clientes[i] = vetor_cliente[i];
                    }
                    for (i=0; i<tamanho_vetor_cliente+1; i++) {
                        no_atual->p[i] = vetor_pont[i];
                    }
                    no_atual->m += no_adj->m;
                    
                    for (i=pos_pont_atual; i<no_pai->m-1; i++) {
                        no_pai->clientes[i] = no_pai->clientes[i+1];
                        no_pai->p[i+1] = no_pai->p[i+2];
                    }
                    no_pai->clientes[no_pai->m-1] = NULL;
                    no_pai->p[no_pai->m] = -1;
                    no_pai->m--;
                    
                    fseek(dados_arq, no_atual->pont_pai, SEEK_SET);
                    salva_no(no_pai, dados_arq);
                    fseek(dados_arq, pont_atual, SEEK_SET);
                    salva_no(no_atual, dados_arq);
                    
                    //exclui_rec(meta_arq, dados_arq, no_pai, no_atual->pont_pai, pos_pont_atual);
                    
                } else {
                    // Redistribuicao
                    cont = 0;
                    for (i=0; i<D; i++) {
                        no_atual->clientes[i] = vetor_cliente[cont++];
                    }
                    no_pai->clientes[pos_pont_atual] = vetor_cliente[cont++];
                    for (i=0; i<no_adj->m-1; i++) {
                        no_adj->clientes[i] = vetor_cliente[cont++];
                    }
                    no_adj->m--;
                    
                    fseek(dados_arq, no_pai->p[pos_pont_atual+1], SEEK_SET);
                    salva_no(no_adj,dados_arq);
                    fseek(dados_arq, no_atual->pont_pai, SEEK_SET);
                    salva_no(no_pai, dados_arq);
                    fseek(dados_arq, pont_atual, SEEK_SET);
                    salva_no(no_atual, dados_arq);
                }
                for (i=0; i<tamanho_vetor_cliente; i++) {
                    free(vetor_cliente[i]);
                }
            } else {
                // Se no_adj é o da esquerda
                fseek(dados_arq, no_pai->p[pos_pont_atual-1], SEEK_SET);
                no_adj = le_no(dados_arq);
                tamanho_vetor_cliente = no_atual->m + no_adj->m;
                
                Cliente *vetor_cliente[tamanho_vetor_cliente];
                int cont = 0;
                for (i=0; i<no_adj->m; i++) {
                    vetor_cliente[cont++] = no_adj->clientes[i];
                }
                vetor_cliente[cont++] = no_pai->clientes[pos_pont_atual-1];
                for (i=0; i<no_atual->m; i++) {
                    if (i != pos) {
                        vetor_cliente[cont++] = no_atual->clientes[i];
                    }
                }
                
                if (no_adj->m + no_atual->m < 2*D) {
                    // Concatenacao
                    for (i=0; i<tamanho_vetor_cliente; i++) {
                        no_adj->clientes[i] = vetor_cliente[i];
                    }
                    no_adj->m += no_atual->m;
                    
                    for (i=pos_pont_atual-1; i<no_pai->m-1; i++) {
                        no_pai->clientes[i] = no_pai->clientes[i+1];
                        no_pai->p[i+1] = no_pai->p[i+2];
                    }
                    no_pai->clientes[no_pai->m-1] = NULL;
                    no_pai->p[no_pai->m] = -1;
                    no_pai->m--;
                    
                    fseek(dados_arq, no_atual->pont_pai, SEEK_SET);
                    salva_no(no_pai, dados_arq);
                    fseek(dados_arq, no_pai->p[pos_pont_atual-1], SEEK_SET);
                    salva_no(no_adj, dados_arq);
                } else {
                    // Redistribuicao
                    cont = 0;
                    for (i=0; i<D; i++) {
                        no_adj->clientes[i] = vetor_cliente[cont++];
                    }
                    no_pai->clientes[pos_pont_atual-1] = vetor_cliente[cont++];
                    for (i=0; i<no_adj->m-1; i++) {
                        no_atual->clientes[i] = vetor_cliente[cont++];
                    }
                    no_atual->m = no_adj->m-1;
                    no_adj->m = D;
                    
                    fseek(dados_arq, no_pai->p[pos_pont_atual-1], SEEK_SET);
                    salva_no(no_adj,dados_arq);
                    fseek(dados_arq, no_atual->pont_pai, SEEK_SET);
                    salva_no(no_pai, dados_arq);
                    fseek(dados_arq, pont_atual, SEEK_SET);
                    salva_no(no_atual, dados_arq);
                }
                for (i=0; i<tamanho_vetor_cliente; i++) {
                    free(vetor_cliente[i]);
                }
            }
            libera_no(no_adj);
            libera_no(no_pai);
        }
    }
}

void imprime_arvore_b(No *raiz, FILE *arq) {
    imprime_no(raiz);
    int cont = 0;
    No *t;
    while (raiz->p[cont] != -1) {
        fseek(arq, raiz->p[cont], SEEK_SET);
        t = le_no(arq);
        imprime_arvore_b(t, arq);
        cont++;
    }
    free(t);
}
