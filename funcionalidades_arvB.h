#ifndef FUNCIONALIDADES_ARVB
#define FUNCIONALIDADES_ARVB

#include "arv_B.h"
#include "getset_dados.h"

//Typedef das estruturas de dados para o arquivo de índice
typedef struct no_Arvb NO_ARVB;
typedef struct arvB ARVB;
typedef struct registro_cabecalho CABECALHO;
typedef struct registro_dados DADOS;
/**
 * @brief Construção da arv_B e impressão do binário na tela
 * 
 * @param void 
 * @return void
*/
void funcionalidade7(void);

/**
 * @brief Recuperação de dados na árvore B utilizando ID (simples)
 * 
 * @param void
 * @return void
*/
void funcionalidade8(void);

/**
 * @brief Recuperação dos DADOS de registros que satisfaçam os campos solicitados (parece ser simples)
 * 
 * @param void
 * @return void
*/
void funcionalidade9(void);

/**
 * @brief Inserção de novos registros na arv_B e arquivo de dados (A função de inserção com reaporveitamento 
 * de espaço já esta pronta e a de inserção na árvore B provavelmente vai estar)
 * 
 * @param void
 * @return void
*/
void funcionalidade10(void);

#endif