#include "vetorIndex.h"

//Permitir acesso direto aos dados da struct
struct registro_dados_index {
    int chave;
    long long int byteoffset;
};

DADOS_INDEX* criar_vetor(int tamanho){
    DADOS_INDEX* vetor = (DADOS_INDEX*)malloc(sizeof(DADOS_INDEX)*tamanho);
    for(int i = 0; i < tamanho; i++){
        vetor[i].chave = -1;
        vetor[i].byteoffset = -1;
    }
    return vetor;
}

void inserir_ordenado(DADOS_INDEX* vetor, DADOS_INDEX* registro, int tamanho){
    for(int i = 0; i < tamanho;i++){
        if(vetor[i].chave == -1){
            vetor[i].chave = registro->chave;
            vetor[i].byteoffset = registro->byteoffset;
            break;
        }
        else{
            if(vetor[i].chave > registro->chave){
                for(int j = tamanho-1; j > i; j--){
                    vetor[j].chave = vetor[j-1].chave;
                    vetor[j].byteoffset = vetor[j-1].byteoffset;
                }
                vetor[i].chave = registro->chave;
                vetor[i].byteoffset = registro->byteoffset;
                break;
            }
        }
    }
}

void remover_ordenado(DADOS_INDEX* vetor, DADOS_INDEX*registro, int inicio, int fim, int tamanho){ 
    int pos = fim+inicio/2;
   
    if(inicio <= fim){
        if(vetor[pos].chave == registro->chave){
            vetor[pos].chave = -1;
            vetor[pos].byteoffset = -1;

            for(int i = pos; i < tamanho-1; i++){
                vetor[i].chave = vetor[i+1].chave;
                vetor[i].byteoffset = vetor[i+1].byteoffset;
            }

            printf("Removeu o menino!\n");
            return;
        }
        else if(vetor[pos].chave > registro->chave){
            remover_ordenado(vetor, registro, inicio, pos-1, tamanho);
        }
        else if(vetor[pos].chave < registro->chave){
            remover_ordenado(vetor, registro, pos+1, fim, tamanho);
        }
    }
}

void apagar_vetor(DADOS_INDEX**vetor, int tamanho){
    free(*vetor);
}

void imprimir_vetor(DADOS_INDEX* vetor, int tamanho){
    for(int i = 0; i < tamanho; i++){
        printf("[%d, %lld]\n", vetor[i].chave, vetor[i].byteoffset);
    }
}