#ifndef FUNCIONALIDADES_TRAB1_H
    #define FUNCIONALIDADES_TRAB1_H

#include "utils.h" 
#include "vetorIndex.h"
#include "utils_trab1.h"

//Struct definitions for index file
typedef struct registro_cabecalho_index CABECALHO_INDEX;
typedef struct registro_dados_index DADOS_INDEX;

#define TAMANHO_REGISTRO_INDEX 13 //Tamanho do registro de índice (13 bytes)
#define TAMANHO_VETOR_INDEX 1050 //Tamanho do vetor de índices (1050 registros)


//Function definitions

/**
 * @brief 
 * 
 * @param 
 * @return 
 */
void funcionalidade4(void);

/**
 * @brief 
 * 
 * @param 
 * @return 
 */
void funcionalidade5(void);

/**
 * @brief 
 * 
 * @param 
 * @return 
 */
void funcionalidade6(void);


//Funções auxiliares para tratar a variável de controle dos registros inseridos.
int incrementar_count_reg(void);
int get_count_reg(void);


#endif