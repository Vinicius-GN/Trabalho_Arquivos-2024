#ifndef VETORINDEX_H
    #define VETORINDEX_H

#include "funcionalidades_trab1.h"
#include "utils.h" 
#include <stdio.h>

//Struct definitions for index file
typedef struct no NO;
typedef struct registro_dados_index DADOS_INDEX;
typedef struct registro_cabecalho_index CABECALHO_INDEX;


/**
 * @brief Criaçção da estrutura de um vetor de índices.
 * 
 * Essa estrutura de dados é essencial para a criação do arquivo de índices, uma vez que 
 * permite a inserção de todas as chaves de índice em um vetor ordenado, facilitando a posterior escrita
 * desses dados para o arquivo de índices.
 * 
 * @param 
 * @return Vetor de índices alocado e inicializado.
 */
DADOS_INDEX* criar_vetor(int tamanho);

/** 
 * @brief 
 * 
 * @param 
 * @return void
 */
void inserir_ordenado(DADOS_INDEX* lista, DADOS_INDEX* registro, int tamanho);

/** 
 * @brief Remoção de um item do vetor de índices e manutenção da sua ordenação.
 * 
 * @param vetor Ponterio para o vetor de índices.
 * @param chave chave do registro a ser removido.
 * @param inicio Índice de início da busca.
 * @param fim Índice de fim da busca.
 * @param tamanho Tamanho do vetor.
 * @return void
 */
void remover_ordenado(DADOS_INDEX* vetor, int chave, int inicio, int fim, int tamanho);

/**
 * @brief Libera a memória alocada para a estrutura do vetor de índices.
 * 
 * @param vetor Ponteiro para o ponteiro do vetor de índices.
 * @return void
 */
void apagar_vetor(DADOS_INDEX** vetor);

/**
 * @brief Percorre linearmente o vetor de índices e imprime os valores de chave e byteoffset.
 * 
 * @param vetor Ponteiro para o vetor de índices.
 * @param tamanho Tamanho do vetor de índices.
 * @return 
 */
void imprimir_vetor(DADOS_INDEX* vetor, int tamanho);

/**
 * @brief Escreve o vetor de índices no arquivo de índices.
 * 
 * @param vetor_index Vetor com os índices a serem escritos no arquivo.
 * @param arquivo_index Arquivo de índices no qual o vetor será escrito.
 * @return void
 */
void escrever_vetor_index(DADOS_INDEX* vetor_index, FILE* arquivo_index);

/**
 * @brief Função auxiliar para escrever o status do arquivo de índices.
 * 
 * @param status Status a ser escrito no arquivo.
 * @param registro Cabeçalho a ser inicializado e escrito.
 * @param arquivo Arquivo no qual o cabeçalho é escrito.
 * @return void
 */
void set_arquivo_index(char status, CABECALHO_INDEX *cabecalho, FILE *arquivo);


#endif