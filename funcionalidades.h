#ifndef FUNCIONALIDADES_H
    #define FUNCIONALIDADES_H

#include "utils.h"
typedef struct registro_cabecalho CABECALHO;
typedef struct registro_dados DADOS;
typedef struct busca_no BN;
typedef struct busca_lista BL;


/**
 * @brief Ler os dados de um arquivo .CSV e escreve-los em um arquivo binário
 * 
 * A funcionalidade 1 ou também referida no arquivo de descrição do trabalho como "CREATE_TABLE" é utilizada para 
 * processar um arquivo .csv e escrever os dados em um arquivo binário utilizando o tratamento de dados adequado e 
 * alterando o status do arquivo para 
 * 
 * @param void
 * @return void
 */
void funcionalidade1(void);

/**
 * @brief Ler os dados de um arquivo binário e escreve-los na saída padrão
 * 
 * A funcionalidade 2 ou também referida no arquivo de descrição do trabalho como "SELECT" é utilizada para
 * processar um arquivo binário e escrever os dados na saída padrão. Os campos nulos são tratados de forma correta
 * e os registros marcados como logicamente removidos não são exibidos.
 * 
 * @param void
 * @return void
 */
void funcionalidade2(void);

/**
 * @brief 
 * 
 * 
 * 
 * 
 * @param 
 * @return
 */
void funcionalidade3(void);

#endif