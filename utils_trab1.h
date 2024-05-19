#ifndef UTILS_TRAB1_H
    #define UTILS_TRAB1_H

#include "utils.h"
#include "funcionalidades_trab1.h"
#include "vetorIndex.h"

typedef struct registro_dados_index DADOS_INDEX;

DADOS* ler_input_dados(void);
char get_status(CABECALHO* cabecalho);
int getID(DADOS* registro);
long long getTopo(CABECALHO* registro);
int getnRemovidos(CABECALHO* registro);
int getnRegDisponiveis(CABECALHO* registro);
long long int getProxRegDisponivel(CABECALHO* registro);
void set_nRegDisponiveis(CABECALHO* registro, int n);
void set_nRegRemovidos(CABECALHO* registro, int n);
void set_topo(CABECALHO* registro, int n);
void setProxRegDisponivel(CABECALHO* registro, long long int n);
bool busca_binaria_index(DADOS_INDEX* vetor, int chave, int inicio, int fim);
long long int best_fit(FILE* arquivo_dados, DADOS* registro, CABECALHO* cabecalho, long long int endereco);
void reaproveitamento_dados(FILE* arquivo_dados, DADOS* registro_dados, long long int endereco);

void inserir_final(FILE* arquivo_dados, FILE* arquivo_index, DADOS* registro_dados, CABECALHO* registro_cabecalho_dados, DADOS_INDEX* vetor_index, DADOS_INDEX* registro_index);
void insercao_dinamica(FILE* arquivo_dados, FILE* arquivo_index, DADOS* registro_dados, CABECALHO* registro_cabecalho_dados, DADOS_INDEX* vetor_index, DADOS_INDEX* registro_index, long long int endereco);
#endif
