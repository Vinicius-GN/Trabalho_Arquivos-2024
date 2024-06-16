#ifndef UTILS_TRAB1_H
    #define UTILS_TRAB1_H

#include "manipulacao_dados.h"
#include "funcionalidades_trab1.h"
#include "vetorIndex.h"
#include "getset_dados.h"

typedef struct registro_dados_index DADOS_INDEX;

//Trabalho 1 da disciplina de Organização de Arquivos

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
 * @brief remove o registro lido do arquivo de dados e do indice, de forma que a lista de removidos fique em ordem crescente.
 * 
 * @param aux ponteiro para o registro lido que será removido.
 * @param arquivo_dados ponteiro para o arquivo de dados.
 * @param cabecalho_dados ponteiro para o cabeçalho do arquivo de dados.
 * @param cur_byte_offset posição atual dentro do arquivo de dados
 * @return void
 */
void remover_dados(DADOS* aux,FILE* arquivo_dados,CABECALHO* cabecalho_dados, long int cur_byte_offset);

/**
 * @brief compara o registro que foi lido os parâmetros da busca e determina se ele deve ser removido.
 * 
 * @param parametros ponteiro para o registro que guarda os pârametros da comparação para remoção.
 * @param aux ponteiro do registro que acaba de ser lido.
 * @return int
 */
int comparar_registros(DADOS* parametros, DADOS* aux);

/**
 * @brief Usa o byteoffset do registro de dados para inserir no final e atualiza o cabeçalho do arquivo de dados.
 * 
 * @param arquivo_dados Ponteiro para o arquivo de dados.
 * @param arquivo_index Ponteiro para o arquivo de índices.
 * @param registro_dados Ponteiro para o registro de dados a ser inserido no arquivo de dados.
 * @param registro_cabecalho_dados Ponteiro para o registro de cabeçalho do arquivo de dados.
 * @param vetor_index Vetor de índices.
 * @param registro_index Ponteiro para o registro de índice a ser inserido no arquivo de índice.
 * @return void
 */
void inserir_final(FILE* arquivo_dados, FILE* arquivo_index, DADOS* registro_dados, CABECALHO* registro_cabecalho_dados, DADOS_INDEX* vetor_index, DADOS_INDEX* registro_index);

/**
 * @brief Utiliza o endereço obtido pela função best_fit para inserir um registro de dados de forma a reutilizar o espaço disponível.
 * 
 * Esta função recebe os parâmetros abaixo listados e utiliza o endereço de um registro de dados 
 * lógicamente removido (encontrado no best-fit), de forma a inserir um novo registro no arquivo de 
 * dados fazendo reutilização de espaço. Ainda há o tratamento dos dados restantes do antigo registro, 
 * que são substituídos por "$" e a atualização do cabeçalho do arquivo de dados.
 * 
 * @param arquivo_dados Ponteiro para o arquivo de dados.
 * @param arquivo_index Ponteiro para o arquivo de índices.
 * @param registro_dados Ponteiro para o registro de dados a ser inserido no arquivo de dados.
 * @param registro_cabecalho_dados Ponteiro para o registro de cabeçalho do arquivo de dados.
 * @param vetor_index Vetor de índices.
 * @param registro_index Ponteiro para o registro de índice a ser inserido no arquivo de índice.
 * @param endereco Endereço que deve ser utilizado para reutilização de espaço.
 * @return void
 */
void insercao_dinamica(FILE* arquivo_dados, FILE* arquivo_index, DADOS* registro_dados, CABECALHO* registro_cabecalho_dados, DADOS_INDEX* vetor_index, DADOS_INDEX* registro_index, long int endereco);

/**
 * @brief Chama uma função recursiva para encontrar o melhor espaço disponível para inserir um registro de dados de forma dinâmica.
 * 
 * A função best_fit_recursivo é chamada e percorre linearmente os registros logicamente removidos do arquivo de dados (a partir do Topo), 
 * buscando o melhor espaço disponível para inserir um novo registro. Como os registros removidos estão ordenados por tamanho, a função
 * encontra o primeiro registro que cabe o novo registro a ser inserido (menor diferença de tamanho possível) e retorna esse endereço. 
 * Caso não encontre nehuma posição disponível, a função retorna -1 (não há espaço disponível para reutilização).
 * 
 * Ainda há a atualização da lista de registros lógicamente removidos, de forma a manter a ordenação por tamanho após a 
 * reutilização de espaço, caso um registro válido seja encontrado.
 * 
 * @param arquivo_dados Ponteiro para o arquivo de dados.
 * @param registro Ponteiro para o registro de dados a ser inserido.
 * @param cabecalho Ponteiro para o registro de cabeçalho do arquivo de dados.
 * @param endereco Endereço do registro de dados a ser inserido (inicialmente, o Topo).
 * @return 
 */
long int best_fit(FILE* arquivo_dados, DADOS* registro, CABECALHO* cabecalho, long int endereco);


void reaproveitamento_dados(FILE* arquivo_dados, DADOS* registro_dados, long int endereco);
#endif
