#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <limits.h>
#include "registro_indice_idade.h"
#include <stdlib.h>
#include "chave_secundaria.h"
#include "lista_clientes.h"
#include "lista_registros_indice_idade.h"
#define NOME_ARQUIVO_INDICE "indice_idade.dat"
int TEST =1;

void indexa(char *nome_arquivo, int tam)
{
    FILE *in = fopen(nome_arquivo, "r+b");
    FILE *out = fopen(NOME_ARQUIVO_INDICE,"w+b");
    ListaClientes *lc = le_clientes(nome_arquivo);
    ListaClientes *lc_raw = le_clientes(nome_arquivo);
    //imprime_clientes(lc);
    sort_by_age(lc_raw);
    arq_ponteiros(lc_raw,lc,out);
    //imprime_clientes(lc_raw);
    ListaRegistrosIndiceIdade *r = le_registros(NOME_ARQUIVO_INDICE);
    imprime_registros(r);
    libera_registros(r);
    imprime_clientes(lc);
    printf("\n### teste :%d ###\n ",TEST++);
        
    imprime_clientes(lc_raw);
    
        
    libera_clientes(lc);
    fclose(in);
    fclose(out);
    printf("\n ---------------------------- \n");
    
}

void arq_ponteiros(ListaClientes *lc, ListaClientes *raw , FILE *out){
    
    for(int i=0;i<lc->qtd;i++){
        if(lc->lista[i] && lc->lista[i]->idade != -1){
            int age = lc->lista[i]->idade;
            int qtd = 1;
            int p = busca_cliente(lc->lista[i]->cod_cliente,raw);
            for(int j=i+1;j<lc->qtd;j++){
                if(lc->lista[i]->idade == lc->lista[j]->idade){
                    qtd++;
                    lc->lista[j]->idade = -1;
                }
            }
            RegistroIndiceIdade *ri = registro_indice_idade(age,p,qtd);
            imprime_registro_indice_idade(ri);
            salva_registro_indice_idade(ri,out);
            free(ri);
        }    
    }

}