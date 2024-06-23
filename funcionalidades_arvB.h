#ifndef FUNCIONALIDADES_ARVB
#define FUNCIONALIDADES_ARVB

//Trabalho prático 2 da disciplina de Organização de Arquivos

#include "arv_B.h"
#include "getset_dados.h"

//Typedef das estruturas utilizadas no trabalho prático 2
typedef struct no_Arvb NO_ARVB;
typedef struct arvB ARVB;
typedef struct registro_cabecalho CABECALHO;
typedef struct registro_dados DADOS;

/**
 * @brief Construção de um arquivo de indice com a estrutura de árvore B e impressão do binário na tela
 * 
 * A ideia desta funcionalidade é receber um arquivo de dados e construir um arquivo de índice com a estrutura de árvore B.
 * A árvore B é construida inteiramente por meio da função "construcao_arvB" que recebe o arquivo de dados e o arquivo de índice.
 * O status do arquivo de indices é corretamente inicializado como "0" e atualizado para "1" ao final da execução.
 * 
 * @param void 
 * @return void
*/
void funcionalidade7(void);

/**
 * @brief Recuperação de dados na árvore B utilizando ID como chave de busca
 * 
 * Descrever um pouco mais
 * 
 * @param void
 * @return void
*/
void funcionalidade8(void);

/**
 * @brief Recuperação dos DADOS de registros que satisfaçam os campos solicitados pelo usuário
 * 
 * Descrever um pouco mais
 * 
 * @param void
 * @return void
*/
void funcionalidade9(void);

/**
 * @brief Inserção de novos registros nos arquivos de dados e de índice utilizando a abordagem dinâmica (reutilização de espaço)
 * 
 * Descrever um pouco mais
 * 
 * @param void
 * @return void
*/
void funcionalidade10(void);

#endif