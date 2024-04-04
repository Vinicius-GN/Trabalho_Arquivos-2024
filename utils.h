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


/*
@brief Estrutura que representa o cabeçalho do arquivo binário

*/
FILE* abrir_arquivo(const char* nome_arquivo, const char* modo);


void escrever_cabecalho(FILE* arquivo, CABECALHO* cabecalho);


CABECALHO* ler_cabecalho(FILE* arquivo);


void escrever_registro_dados(DADOS* registro, FILE* arquivo);


DADOS* init_registro_dados(void);


CABECALHO* init_arquivo_binario(FILE* arquivo);


void apagar_registro(DADOS** registro);

void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);

DADOS* split_linha(FILE* arquivo_in, const char* linha);


bool funcionalidade1(void);


bool funcionalidade2(void);


bool funcionalidade3(void);

#endif