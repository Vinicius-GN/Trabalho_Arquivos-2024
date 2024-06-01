#ifndef LISTA_TRABINR_H
    #define LISTA_TRABINR_H

#include "manipulacao_dados.h"

//Typedef das estruturas de dados utilizadas para a busca de registros
typedef struct busca_no BN;
typedef struct busca_lista BL;
typedef struct registro_cabecalho CABECALHO;
typedef struct registro_dados DADOS;

/**
 * @brief recebe uma lista encadeada e libera todos nós assim como a lista em si
 * 
 * @param lista endereço do ponteiro da lista a ser liberada 
 * @return void
*/
void apagar_lista(BL** lista);

/**
 * @brief recebe o endereço de um registro e adiciona ele a lista
 * 
 * Essa função aloca um nó e o inicializa contendo o registro passado, após isso o adiciona ao final da lista e
 * atualiza as variáveis da lista.
 * 
 * @param lista ponteiro para a lista em que o registro será adicionado
 * @param registro ponteiro para o registro que será adicionado na lista
 * @return void
*/
void add_lista(BL* lista, DADOS* registro);


#endif