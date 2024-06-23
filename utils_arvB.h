#ifndef UTILS_ARVB
#define UTILS_ARVB

//Trabalho prático 2 da disciplina de Organização de Arquivos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAMANHO_NO 60
#define MAX_NRO 3
#define TAMANHO_CABECALHO 60

//Typedef das estruturas de dados para o arquivo de índice
typedef struct no_Arvb NO_ARVB;
typedef struct arvB ARVB;
typedef struct registro_cabecalho CABECALHO;
typedef struct registro_dados DADOS;

/**
 * @brief Libera a memória de um nó da árvore B.
 * 
 * @param no Ponteiro duplo para um nó da árvore B
 * @return void
 */
void apagar_no(NO_ARVB** no);

/**
 * @brief Imprime os dados de um nó da árvore B
 * 
 * @param no Nó da árvore B
 * @return void
 */
void imprimir_no_arvB(NO_ARVB* no);

/**
 * @brief Lẽ um nó da árvore B no arquivo de índice baseando-se no RRN passado como argumento.
 * 
 * @param arquivo Ponteiro para o arquivo de índice
 * @param RRN RRN do nó a ser lido
 * @param no Nó da árvore B a ser preenchido
 * 
 * @return void
 */
void ler_no_arvB(FILE* arquivo, int RRN, NO_ARVB* no);

/**
 * @brief Escreve um nó da árvore B no arquivo de índice. O ponteiro do arquivo deve estar na posição correta do RRN do nó.
 * 
 * @param arquivo_indice Ponteiro para o arquivo de índice
 * @param no Nó da árvore B a ser escrito
 * 
 * @return void
 */
void escrever_no_arvB(FILE* arquivo_indice, NO_ARVB* no);

/**
 * @brief Retorna o valor da chave do registro na posição "pos"
 * 
 * @param no Nó da árvore B
 * @param pos Posição da chave no nó
 * 
 * @return int
 */
int get_chave(NO_ARVB* no, int pos);

/**
 * @brief Retorna o valor do byteoffset do registro na posição "pos"
 * 
 * @param no Nó da árvore B
 * @param pos Posição da byteoffset no nó
 * 
 * @return long int
 */
long int get_valor(NO_ARVB* no, int pos);

/**
 * @brief Retorna o RRN do filho do nó na posição "pos"
 * 
 * @param no Nó da árvore B
 * @param pos Posição do filho
 * 
 * @return int
 */
int get_filho(NO_ARVB* no, int pos);


#endif