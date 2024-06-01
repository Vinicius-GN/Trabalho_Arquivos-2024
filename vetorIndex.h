#ifndef VETORINDEX_H
    #define VETORINDEX_H

#include "funcionalidades_trab1.h"
#include "manipulacao_dados.h" 
#include <stdio.h>

// Typedef das estruturas de dados para o arquivo de índice
typedef struct no NO;
typedef struct registro_dados_index DADOS_INDEX;
typedef struct registro_cabecalho_index CABECALHO_INDEX;

/**
 * @brief Criação da estrutura de um vetor de índices.
 * 
 * Essa estrutura de dados é essencial para a criação do arquivo de índices, uma vez que 
 * permite a inserção de todas as chaves de índice em um vetor ordenado, facilitando a posterior escrita
 * desses dados para o arquivo de índices.
 * 
 * @param void
 * @return Vetor de índices alocado e inicializado.
 */
DADOS_INDEX* criar_vetor(void);

/** 
 * @brief Insere um registro de index no Vetor de índices de forma ordenada 
 * 
 * Esta abordagem de inserção ordenada é essencial para manter a ordenação do vetor de índices (por chave) 
 * e garantir a correta escrita no arquivo de índices.
 * 
 * @param lista Ponteiro para o vetor de índices.
 * @param registro Ponteiro para o registro a ser inserido.
 * @param tamanho Tamanho do vetor de índices.
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

/**
 * @brief Realiza uma busca binária no arquivo de indices para encontrar o registro com a chave passada como parâmetro.
 * 
 * Essa função é utilizada de forma a evitar que um registro seja inserido novamente e para buscas durante a remoção de registros.
 * 
 * @param vetor Vetor de índices.
 * @param chave Chave a ser buscada.
 * @param inicio Índice de início da busca.
 * @param fim Índice de fim da busca.
 * @return long int Byteoffset do registro com a chave buscada.
 */
long int busca_binaria_index(DADOS_INDEX* vetor, int chave, int inicio, int fim);


/**
 * @brief Função auxiliar para liberação de memória das estruturas de dados que incluem índice.
 * 
 * @param registro_cabecalho_index Duplo ponteiro para o registro de cabeçalho do arquivo de índices.
 * @param registro_index Duplo ponteiro para o registro de índice.
 * @param registro_dados Duplo ponteiro para o registro de dados.
 * @return void
*/
void liberar_memoria(CABECALHO_INDEX **registro_cabecalho_index, DADOS_INDEX **registro_index, DADOS **registro_dados);


#endif