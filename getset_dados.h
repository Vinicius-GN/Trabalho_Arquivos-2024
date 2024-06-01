#ifndef GETSET_DADOS_H
    #define GETSET_DADOS_H

// Include dos headers necessários
#include "manipulacao_dados.h"

//Typedef das estruturas de dados para o arquivo de índice
typedef struct registro_cabecalho_index CABECALHO_INDEX;
typedef struct registro_dados_index DADOS_INDEX;

/**
 * @brief Pega o status do arquivo de dados salvo no registro de cabeçalho.
 * 
 * @param cabecalho Ponteiro para o registro de cabeçalho cujo status é lido e retornado.
 * @return char 
 */
char get_status(CABECALHO* cabecalho);

/**
 * @brief Pega o ID do registro de dados.
 * 
 * @param registro Ponteiro para o registro de dados cujo ID deve ser retornado.
 * @return int 
 */
int getID(DADOS* registro);

/**
 * @brief Retorna o valor do campo "topo" do registro de cabeçalho.
 * 
 * @param registro Ponteiro para o registro de cabeçalho cujo topo é lido e retornado.
 * @return long int 
 */
long int getTopo(CABECALHO* registro);

/**
 * @brief Retorna o valor do campo "n_reg_removidos" do registro de cabeçalho.
 * 
 * @param registro Ponteiro para o registro de cabeçalho cujo n_reg_removidos é lido e retornado.
 * @return int
 */
int getnRemovidos(CABECALHO* registro);

/**
 * @brief Retorna o valor do campo "n_reg_disponiveis" do registro de cabeçalho.
 * 
 * @param registro Ponteiro para o registro de cabeçalho cujo "n_reg_disponiveis" é lido e retornado.
 * @return int
 */
int getnRegDisponiveis(CABECALHO* registro);

/**
 * @brief Retorna o valor do campo "prox_reg_disponivel" do registro de cabeçalho.
 * 
 * @param registro Ponteiro para o registro de cabeçalho cujo "prox_reg_disponivel" é lido e retornado.
 * @return long int
 */
long int getProxRegDisponivel(CABECALHO* registro);

/**
 * @brief Altera o valor do campo "n_reg_disponiveis" do registro de cabeçalho do arquivo de dados.
 * 
 * @param registro Ponteiro para o registro de cabeçalho cujo "n_reg_disponiveis" é alterado.
 * @param n Novo valor do campo "n_reg_disponiveis".
 * @return void 
 */
void set_nRegDisponiveis(CABECALHO* registro, int n);

/**
 * @brief Altera o valor do campo "n_reg_removidos" do registro de cabeçalho do arquivo de dados.
 * 
 * @param registro Ponteiro para o registro de cabeçalho cujo "n_reg_removidos" é alterado.
 * @param n Novo valor do campo "n_reg_removidos".
 * @return void
 */
void set_nRegRemovidos(CABECALHO* registro, int n);

/**
 * @brief Altera o valor do campo "topo" do registro de cabeçalho do arquivo de dados.
 * 
 * @param registro Ponteiro para o registro de cabeçalho cujo "topo" é alterado.
 * @param n Novo valor do campo "topo".
 * @return void 
 */
void set_topo(CABECALHO* registro, int n);

/**
 * @brief Altera o valor do campo "prox_reg_disponivel" (byteoffset) do registro de cabeçalho do arquivo de dados.
 * 
 * @param registro Ponteiro para o registro de cabeçalho cujo "prox_reg_disponivel" é alterado.
 * @param n Novo valor do campo "prox_reg_disponivel".
 * @return void
*/
void setProxRegDisponivel(CABECALHO* registro, long int n);

/**
 * @brief Pega o valor do campo "tamanho" de um registro de dados cujo byteoffset é passado como parâmetro.
 * 
 * @param endereco Byteoffset do endereço do registro de dados.
 * @param arquivo_dados Ponteiro para o arquivo de dados.
 * @return int Tamanho do registro de dados
 */
int get_tam(long int endereco, FILE* arquivo_dados);

/**
 * @brief Pega o valor do campo "prox_reg" de um registro de dados cujo byteoffset é passado como parâmetro.
 * 
 * @param endereco Byteoffset do endereço do registro de dados.
 * @param arquivo_dados Ponteiro para o arquivo de dados.
 * @return long int Byteoffset do próximo registro de dados removido na lista.
 */
long int get_prox(long int endereco, FILE* arquivo_dados);


#endif