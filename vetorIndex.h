#ifndef VETORINDEX_H
    #define VETORINDEX_H

#include "funcionalidades_trab1.h"
#include "utils.h" 
#include <stdio.h>

//Struct definitions for index file
typedef struct no NO;
typedef struct registro_dados_index DADOS_INDEX;


DADOS_INDEX* criar_vetor(int tamanho);
void inserir_ordenado(DADOS_INDEX* lista, DADOS_INDEX* registro, int tamanho);
void remover_ordenado(DADOS_INDEX* vetor, DADOS_INDEX* registro, int inicio, int fim, int tamanho);
void apagar_vetor(DADOS_INDEX** vetor);
void imprimir_vetor(DADOS_INDEX* vetor, int tamanho);


#endif