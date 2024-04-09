#ifndef UTILS_H
    #define UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct registro_cabecalho CABECALHO;
typedef struct registro_dados DADOS;
typedef struct busca_no BN;
typedef struct busca_lista BL;


/**
 * @brief Abre um arquivo no modo especificado e com o nome especificado 
 * 
 * @param noma_arquivo Nome do arquivo a ser aberto 
 * @param modo Modo de abertura do arquivo
 * 
 * @return Arquivo aberto no modo especificado
 */
FILE* abrir_arquivo(const char* nome_arquivo, const char* modo);

/**
 * @brief Recebe um arquivo aberto e escreve o registro de cabeçalho no arquivo
 * 
 * @param arquivo Arquivo no qual o cabeçalho deve ser escrito
 * @param cabecalho Registro de cabeçalho a ser escrito
 * @return void
 */
void escrever_cabecalho(FILE* arquivo, CABECALHO* cabecalho);

/**
 * @brief Função para ler o registro de cabeçalho campo a campo
 * 
 * @param arquivo Arquivo do qual o cabeçalho é lido
 * @return CABECALHO* Ponteiro para o registro de cabeçalho lido
 */
CABECALHO* ler_cabecalho(FILE* arquivo);

/**
 * @brief Escreve no arquivo o registro de dados passado como parâmetro (campo a campo)
 * 
 * @param registro Registro de dados a ser escrito
 * @param arquivo Arquivo no qual o registro é escrito
 * @return void
 */
void escrever_registro_dados(DADOS* registro, FILE* arquivo);

/**
 * @brief Inicialização do registro de dados assim como especificado na descrição do trabalho
 * 
 * @param void
 * @return DADOS* Ponteiro para o registro de dados inicializado
 */
DADOS* init_registro_dados(void);

/**
 * @brief Inicializa o registro de cabeçalho e o escreve no arquivo especificado
 * 
 * O registro de cabeçalho é inciado de acordo com as recomendações.
 * 
 * @param arquivo arquivo no qual o cabeçalho é escrito campo a campo 
 * @return CABECALHO* 
 */
CABECALHO* init_arquivo_binario(FILE* arquivo);

/**
 * @brief Apaga o registro de dados passado como parâmetro, bem como os campos de tamanho variável.
 * 
 * @param registro Ponteiri para o endereço do registro de dados a ser apagado
 * @return void
 */
void apagar_registro(DADOS** registro);

/**
 * Funções passsadas na especificação do trabalho
*/
void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);

/**
 * @brief Recebe uma string que contem os dados de uma linha do arquivo csv e separa os campos em um registro
 * 
 * Nessa função, utilzamos dois metodos de tratamento dos dados de uma string (buffer retornado pelo fgets em um arquivo csv),
 * nos quais os campos de tamanho fixo e os campos de tamanho variável são salvos em seus respectivos campos.
 * O arquivo passado como parâmetro é fechado em caso de erro de execução.
 * 
 * @param arquivo_in Arquivo aberto, o qual é fechado em algum erro de execução da função
 * @param linha buffer com a linha lida do arquivo .csv
 * @return DADOS* Ponteiro para o registro de dados com os campos preenchidos
 */
DADOS* split_linha(FILE* arquivo_in, const char* linha);

void apagar_lista(BL** lista);
void add_lista(BL* lista, DADOS* registro);
void apagar_cabecalho(CABECALHO** cabecalho);
DADOS* ler_registro(FILE* arquivo_bin, DADOS* registro);
void print_registro(DADOS* registro);
void debug (void);
#endif