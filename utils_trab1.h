#ifndef UTILS_TRAB1_H
    #define UTILS_TRAB1_H

#include "utils.h"
#include "funcionalidades_trab1.h"
#include "vetorIndex.h"

typedef struct registro_dados_index DADOS_INDEX;

/**
 * @brief Ler os dados de um registro de cabeçalho a ser inserido no arquivo de dados.
 * 
 * Essa função aloca e inicializar um registro de dados, lẽ as entradas do usuário por meio da função fornecida Scan_quote_string e retorna o registro de dados
 * com os valores lidos e o correto tratamento de campos nulos.
 * 
 * @param void 
 * @return DADOS*
 */
DADOS* ler_input_dados(void);

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
 * @brief 
 * 
 * @param 
 * @return 
 */
long int busca_binaria_index(DADOS_INDEX* vetor, int chave, int inicio, int fim);

/**
 * @brief 
 * 
 * @param 
 * @return 
 */
void remover_dados(DADOS* aux,FILE* arquivo_dados,CABECALHO* cabecalho_dados, long int cur_byte_offset);

/**
 * @brief 
 * 
 * @param 
 * @return 
 */
void inserir_final(FILE* arquivo_dados, FILE* arquivo_index, DADOS* registro_dados, CABECALHO* registro_cabecalho_dados, DADOS_INDEX* vetor_index, DADOS_INDEX* registro_index);

/**
 * @brief 
 * 
 * @param 
 * @return 
 */
void insercao_dinamica(FILE* arquivo_dados, FILE* arquivo_index, DADOS* registro_dados, CABECALHO* registro_cabecalho_dados, DADOS_INDEX* vetor_index, DADOS_INDEX* registro_index, long int endereco);

/**
 * @brief 
 * 
 * @param 
 * @return 
 */
long int best_fit(FILE* arquivo_dados, DADOS* registro, CABECALHO* cabecalho, long int endereco);
#endif
