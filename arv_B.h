#ifndef ARV_B
#define ARV_B

#include <stdio.h>
#include <stdlib.h>
#include "manipulacao_dados.h"

#define TAMANHO_NO 60
#define MAX_NRO 3
#define TAMANHO_CABECALHO 60

//Typedef das estruturas de dados para o arquivo de índice
typedef struct no_Arvb NO_ARVB;
typedef struct arvB ARVB;
typedef struct registro_cabecalho CABECALHO;
typedef struct registro_dados DADOS;

//Typedef de estrututra auxiliar
typedef struct promocao_no PROMOCAO;

//Definição das funcionalidades

/**
 * @brief Inicializa a árvore B
 * 
 * @param void
 * @return ARVB*
*/
ARVB * init_arvB(void);

/**
 * @brief Inicializa um nó da árvore B
 * 
 * @param void
 * @return NO_ARVB*
*/
NO_ARVB * init_no(void);

/**
 * @brief Função que insere um registro na árvore B
 * 
 * @param arquivo Arquivo de dados
 * @param arv Árvore B
 * @param status Status a ser definido para o arquivo
 * 
 * @return void
*/
void set_status_arvB(FILE *arquivo, char status, ARVB *arv);
//Set status (Arquivo, registro de cabeçalho, status)

//função de promoção de um registro de indice
//funcção de inserção na arvb
//função de leitura dos dados de um nó na memória
//função de escrita desses dados na memória 
void construcao_arvB(FILE *arquivo_dados, FILE *arquivo_index, CABECALHO *registro_cabecalho_dados);


#endif