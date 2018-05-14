#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <string.h>
#define tab_size 127 // tamanho da ASCII como referência
#define TAM 8

typedef struct {
    char cod[9];
    char simbol;
} Tabela;

Tabela tabela_asc[tab_size];

void int_to_bin(int n,char c[]){
    int i=1;
    c[0] = '\0';
    for( i = 1; i<=8;i++){
        if(n%2){
            c[8-i] = '1';
        }else{
            c[8-i] = '0';
        }
        n=n/2;
        
    }
    
}

void gera_ASCII(){
    char c=0,binario[TAM];
    int i, asc_value;
    for(int i=0; i<tab_size;i++){
        tabela_asc[i].simbol = c;
        asc_value = c;
        c++;
        int_to_bin(asc_value,tabela_asc[i].cod);
        //printf("bin: %s \n", tabela_asc[i].cod);
    }

}
void imprime(){
    for(int i=0; i<tab_size;i++){
            
            printf("%s - ",tabela_asc[i].cod);
            printf("%c \n",tabela_asc[i].simbol);
            
    }
}


void codifica(char c[],Tabela tab[], int tamanho_tabela){
    int i=0 , j;
    printf("\n##################\n###    ANTES   ### \n##################\n\n %s\n",c);
    
    printf("\n##################\n### CODIFICADO ### \n##################\n\n");
    while(c[i]!='\0'){
        j = 0;
        while(tab[j].simbol != c[i] && j<tamanho_tabela) j++;
        printf("%s",tab[j].cod);
        printf("-%c <> ",tab[j].simbol); //checar se é a letra correta
        i++;
    }
}
int main() {
    gera_ASCII();
    imprime();
    char c[100];
    scanf("%[^\n]",c);
    codifica(c,tabela_asc,127);
    return 0;
}


