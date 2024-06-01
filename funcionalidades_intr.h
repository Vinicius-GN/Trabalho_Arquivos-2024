#ifndef FUNCIONALIDADES_H
    #define FUNCIONALIDADES_H

// Include dos headers necessários
#include "manipulacao_dados.h"
#include "lista_trabintr.h"

//Typedef das estruturas de dados utilizadas para a busca de registros
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
 * @brief Faz n buscas no arquivo binário e escreve os registros correspondentes na saída padrão
 * 
 * A funcionalidade 3 ou também referida no arquivo de descrição do trabalho como "SELECT" com consideração da clausula "WHERE" é utilizada
 * para processar um arquivo binário, percorrendo todos os registros e imprimindo aqueles que correspondem aos paramêtros passados na busca.
 * Os campos nulos são tratados de forma correta, os registros marcados como logicamente removidos não são exibidos e as buscas de parâmetros
 * únicos são paradas após encontrar um registro correspondente.
 * 
 * @param void
 * @return void
 */
void funcionalidade3(void);

#endif