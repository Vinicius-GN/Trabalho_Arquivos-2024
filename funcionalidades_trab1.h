#ifndef FUNCIONALIDADES_TRAB1_H
    #define FUNCIONALIDADES_TRAB1_H

// Include dos headers necessários
#include "manipulacao_dados.h" 
#include "vetorIndex.h"
#include "abordagem_dinamica.h"
#include "getset_dados.h"

//Typedef das estruturas de dados para o arquivo de índice
typedef struct registro_cabecalho_index CABECALHO_INDEX;
typedef struct registro_dados_index DADOS_INDEX;

#define TAMANHO_REGISTRO_INDEX 13 //Tamanho do registro de índice (13 bytes)

//Function definitions

/**
 * @brief Cria um arquivo de índice simples primário, a partir de um arquivo de dados, cujo campo de busca é o ID.
 * 
 * Essa função começa abrindo o arquivo de dados e fazendo a verificação do seu status. Em seguida, lê-se os registros disponíveis do arquivo de dados, que são organizados de forma ordenada (pelo ID) 
 * por um vetor de índices. Por fim, esse vetor de indices é escrito no arquivo de índices e o status do arquivo de índices é atualizado. Utilizamos a função fornecida "binarioNaTela" para imprimir o arquivo binário de índice.
 * 
 * @param void
 * @return void 
 */
void funcionalidade4(void);

/**
 * @brief 
 * 
 * @param 
 * @return void
 */
void funcionalidade5(void);

/**
 * @brief Inserção de novos registros no arquivo de dados de entrada, utilizando a abordagem dinâmica e indexação primária.
 * 
 * Essa função começa abrindo o arquivo de dados e fazendo a verificação do seu status. Também inicaliza-se o arquivo de índices por meio da função "create_index", que  
 * lê o arquivo de dados e escreve os valores de ID e Byteoffset dos registros disponíveis no arquivo de índices. Em seguida, lê-se os registros a serem inseridos no arquivo de dados
 * e, dependendo da disponibilidade, utiliza-se a reutilização de espaço por meio da estratégia best-fit. Por fim, atualiza-se o status do arquivo de dados e imprime os arquivos binários (índice e dados).
 * 
 * @param void
 * @return void
 */
void funcionalidade6(void);


//Funções auxiliares para tratar a variável de controle dos registros inseridos.
int incrementar_count_reg(void);
int get_count_reg(void);


#endif