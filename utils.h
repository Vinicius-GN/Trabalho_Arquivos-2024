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

/**
 * @brief recebe o endereço do ponteiro da struct que guarda o cabeçalho e libera a struct
 * 
 * @param cabecalho endereço do ponteiro do cabeçalho
 * @return void
*/
void apagar_cabecalho(CABECALHO** cabecalho);

/**
 * @brief lê um registro do arquivo binário passado como parâmetro e guarda os campos no registro passado
 * 
 * Essa função lê um registro do arquivo binário, campo a campo, alocando memória para os campos de tamanho variável.
 * 
 * @param arquivo_bin ponteiro do arquivo de onde o registro será lido
 * @param registro ponteiro da struct aonde os dados lidos serão guardados
 * @return void
*/
void ler_registro(FILE* arquivo_bin, DADOS* registro);

/**
 * @brief printa na tela os dados do registro conforme pedido no arquivo de descrição do trabalho
 * 
 * essa função printa o registro da maneira especificada no arquivo de descrição do trabalho, mas também libera a memória
 * dos campos variáveis do registro.
 * 
 * @param registro ponteiro da struct do registro a ser printado
 * @return void
*/
void print_registro(DADOS* registro);

/**
 * @brief 
 * 
 * @param cabecalho 
 * @return 
*/
char get_status(CABECALHO* cabecalho);
int getID(DADOS* registro);

void debug (void);
#endif