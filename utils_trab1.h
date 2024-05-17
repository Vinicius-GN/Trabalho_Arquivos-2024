#ifndef UTILS_TRAB1_H
    #define UTILS_TRAB1_H

#include "utils.h"
#include "index.h"

DADOS* ler_input_dados(void);
char get_status(CABECALHO* cabecalho);
int getID(DADOS* registro);
int getTopo(CABECALHO* registro);
int getnRemovidos(CABECALHO* registro);
bool busca_binaria_index(DADOS_INDEX* vetor, int chave, int inicio, int fim);

#endif
