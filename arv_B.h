#ifndef ARV_B
#define ARV_B

//Trabalho prático 2 da disciplina de Organização de Arquivos

#include <stdio.h>
#include <stdlib.h>
#include "manipulacao_dados.h"
#include "abordagem_dinamica.h"
#include "utils_arvB.h"

#define TAMANHO_NO 60
#define MAX_NRO 3
#define TAMANHO_CABECALHO 60

//Typedef das estruturas de dados para o arquivo de índice
typedef struct no_Arvb NO_ARVB;
typedef struct arvB ARVB;
typedef struct registro_cabecalho CABECALHO;
typedef struct registro_dados DADOS;

//Typedef de estrututra auxiliar
typedef struct promocao_no PROMOCAO;

//Definição das funcionalidades

/**
 * @brief Inicializa a estrutura da árvore B e a retorna
 * 
 * @param void
 * @return ARVB*
*/
ARVB * init_arvB(void);

/**
 * @brief Inicializa um nó da árvore B e o retorna
 * 
 * @param void
 * @return NO_ARVB*
*/
NO_ARVB * init_no(void);

/**
 * @brief Função que altera e reescreve o status do arquivo de indices
 * 
 * @param arquivo Arquivo de dados
 * @param arv  Ponteiro para o cabeçalho da Árvore B
 * @param status Status a ser definido para o arquivo
 * 
 * @return void
*/
void set_status_arvB(FILE *arquivo, char status, ARVB *arv);


/**
 * @brief Função que cria um arquivo de indice seguindo a estrutura de arvoreB
 * 
 * Esta função recebe um arquivo de dados e um arquivo de índice e cria um arquivo de índice com a estrutura de árvore B.
 * A árvore B é construida inteiramente por meio desta função, por meio de leitura do arquivo de dados e inserção dos registros na árvore B.
 * A alteração dos status do arquivo de indices, bem como a escrita do cabeçalho da árvore B são feitas por meio de funções auxiliares.
 * 
 * @param arquivo_dados Arquivo de dados
 * @param arquivo_index Arquivo de índice
 * @param registro_cabecalho_dados Ponteiro para o cabeçalho do arquivo de dados
 * 
 * @return void
*/
void construcao_arvB(FILE *arquivo_dados, FILE *arquivo_index, CABECALHO *registro_cabecalho_dados);

/**
 * @brief Função que busca um registro por ID na árvore B e imprime os resultados da busca na tela.
 * 
 * @param index Arquivo de índice
 * @param id id a ser buscado
 * @param cabecalho Ponteiro para o cabeçalho da árvore B
 * 
 * @return long int;
*/
long int busca_arvB(FILE *index, int id, ARVB *cabecalho);


/**
 * @brief Função que aloca um cabeçalho, lê o cabeçalho da árvore B do arquivo de indice e retorna o cabeçalho alocado e preenchido pela leitura.
 * 
 * @param arquivo Arquivo de índice
 * 
 * @return ARVB*;
*/
ARVB* ler_cabecalho_arvB(FILE* arquivo);

/**
 * @brief Função que insere um registro na árvore B
 * 
 * @param arquivo_index Arquivo de índice
 * @param arvore Ponteiro para o cabeçalho da Árvore B
 * @param chave Chave a ser inserida
 * @param byteoffset Byteoffset a ser inserido
 * 
 * @return void
*/
void inserir_arvB(FILE* arquivo_index, ARVB* arvore, int chave, long int byteoffset);

/**
 * @brief Função que escreve o cabeçalho da árvore B no arquivo de indice
 * 
 * @param arquivo Arquivo de índice
 * @param arvore Ponteiro para a Árvore B (cabeçalho)
 * 
 * @return void
 */
void escrever_cabecalho_arvB(FILE* arquivo, ARVB* arvore);

/*################# Funcionalidades de uso interno #################*/
//Essas funções não são chamadas diretamente pelo usuário, mas sim pelas funcionalidades acima descritas.
//A decisão por manter essas funções públicas foi tomada para facilitar a documentação do código e a organização das funções.

/**
 * @brief Função que insere um registro na árvore B recursivamente.
 * 
 * Essa função é chamada pela função "inserir_arvB". Ela realiza todas as operações de tratamento de inserção de um registro na árvore B,
 * incluindo a chamada do "split_no", caso necessário, e o retorno recursivo das promoções entre os niveis da árvore.
 * 
 * @param arquivo_index Arquivo de índice
 * @param arvore Ponteiro para o cabeçalho da Árvore B
 * @param RRN RRN do nó atual
 * @param chave Chave a ser inserida
 * @param byteoffset Byteoffset a ser inserido
 * 
 * @return PROMOCAO (struct que guarda os dados das entre os níveis da árvore)
*/
PROMOCAO inserir_arvB_recursivo(FILE* arquivo_index, ARVB* arvore, int RRN, int chave, long int byteoffset);

/**
 * @brief Função que insere um registro em um nó folha.
 * 
 * Essa função recebe os parâmetros abaixo listados e insere um registro em um nó folha da árvore B. Nesse caso, há apenas a necessidade de 
 * descolcar os dados do nó para a direita e inserir o registro na posição correta, a depender do argumento "pos" e da quantidade de registros presentes no nó.
 * 
 * @param arquivo Arquivo de índice
 * @param no Nó a ser inserido
 * @param RRN RRN do nó
 * @param pos Variavel que indica a posição para a inserção do registro
 * @param chave Chave a ser inserida
 * @param byteoffset Byteoffset a ser inserido
 * 
 * @return void
*/
void insercao_noFolha(FILE* arquivo, NO_ARVB* no, int RRN, int pos, int chave, long int byteoffset);

/**
 * @brief Função que insere um registro em um nó interno (não folha).
 * 
 * Segue o mesmo princípio da função "insercao_noFolha", porém, nesse caso, há a necessidade de inserir um filho no nó, além do registro.
 * Essa função normalmente é aplicada quando há a promoção de um registro e é necessário, além de inserir o registro, colocar o RRN do novo nó
 * criado pelo split no nível inferior da árvore na posição correta.
 * 
 * @param arquivo Arquivo de índice
 * @param no Nó a ser inserido
 * @param RRN RRN do nó
 * @param pos Variavel que indica a posição para a inserção do registro
 * @param chave Chave a ser inserida
 * @param byteoffset Byteoffset a ser inserido
 * @param filho Filho a ser inserido
 * 
 * @return void
*/
void inserir_noInterno(FILE* arquivo, NO_ARVB* no, int RRN, int pos, int chave, long int byteoffset, int filho);

/**
 * @brief Função que divide um nó da árvore B
 * 
 * Essa função é chamada pela função "inserir_arvB_recursivo" e é responsável por dividir um nó da árvore B, caso ele esteja cheio e 
 * haja inserção nele.
 * A função divide o nó atual em dois nós, promovendo um registro para o nível superior da árvore e retornando a promoção para a função recursiva.
 * Ademais, o split é feito de forma a manter a ordem dos registros no nó e a ordem dos filhos, caso o nó seja um nó interno, e o tratamento dos
 * casos de split é realizado baseando-se na posição que o registro deve ser inserido, não tuilizando um vetor auxiliar para tal procedimento, assim como apontado
 * pelo algoritmo dos slides da disciplina.
 * 
 * @param arquivo Arquivo de índice
 * @param arvore Ponteiro para o cabeçalho da Árvore B
 * @param no_atual Nó a ser dividido
 * @param RRN RRN do nó
 * @param chave Chave a ser inserida
 * @param pos Variavel que indica a posição para a inserção do registro (auxilia no tratamento dos casos de split)
 * @param byteoffset Byteoffset a ser inserido
 * @param promocao_recursiva Promoção a ser retornada para a função recursiva
 * 
 * @return PROMOCAO (struct que guarda os dados das entre os níveis da árvore)
*/
PROMOCAO split_no(FILE* arquivo, ARVB* arvore, NO_ARVB* no_atual, int RRN, int chave, int pos, long int byteoffset, PROMOCAO promocao_recursiva);

#endif