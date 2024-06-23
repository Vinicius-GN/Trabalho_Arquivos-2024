#include "utils_arvB.h"

//Trabalho prático 2 da disciplina de Organização de Arquivos

//############################################################################
/* As funções definidas neste arquivo estão explicadas no arquivo "arv_B.h". 
Nesse código você encontrá comentários a nível de variáveis e procedimentos.*/
//############################################################################

/*
##############################################################
    Alunos: Vinicius Gustierrez Neves          N°USP: 14749363
            Augusto Cavalcante Barbosa Pereira N°USP: 14651531
##############################################################
*/

//Definição da estrutura de cabeçalho da árvore B
struct arvB{
    char status; //Atualizado no inicio e no final da execução de "contrucao_arvB"
    int noRaiz; // Atualizado quando há promoção na raiz
    int proxRRN; //Atualizado quando há split de nó ou com a criação da raiz
    int nroChaves; //Atualizado a cada inserção de registros
    char lixo[47]; //Caracteres para preenchimento "$" dos 60bytes de cada nó
};

//Definição da struct dos nós dessa árvore que conterão as informações dos registros de dados disponíveis 
struct no_Arvb{
    //Informações do nó
    int altura_No;
    int nroChaves;

    //Informações dos registros de indíce na árvore
    int C1;
    long int PR1;
    int C2;
    long int PR2;
    int C3;
    long int PR3;

    //Informações dos nós filhos em nível inferior
    int P1;
    int P2;
    int P3;
    int P4;
};

//Definição da estrutura do registro de dados do arquivo de dados para ser acessado diretamente.
struct registro_dados{
    char removido;
    int tamanho_registro;
    long int prox_reg;
    int id;
    int idade;
    int tam_Nome;
    char* nome;
    int tam_Nacionalidade;
    char* nacionalidade;
    int tam_Clube;
    char* clube;
    ;
};

//Estrutura de dados auxiliar 
struct promocao_no{
    int chavePromovida;
    long int byteOffsetPromovido;
    int novoNo; //RRN do novo nó (preciso já ter escrito ele no arquivo para saber o RRN dele)
    bool houvePromocao; //Flag para marcar se houve promoção ou não recursivamente
};

void apagar_no(NO_ARVB** no){
    //Libera a memória alocada para o nó
    if(*no != NULL){
        free(*no);
        *no = NULL;
    }
}

void imprimir_no_arvB(NO_ARVB* no){
    //Imprime o nó
    printf("Altura do nó: %d\n", no->altura_No);
    printf("Número de chaves: %d\n", no->nroChaves);
    printf("Chave 1: %d\n", no->C1);
    printf("Byteoffset 1: %ld\n", no->PR1);
    printf("Chave 2: %d\n", no->C2);
    printf("Byteoffset 2: %ld\n", no->PR2);
    printf("Chave 3: %d\n", no->C3);
    printf("Byteoffset 3: %ld\n", no->PR3);
    printf("Filho 1: %d\n", no->P1);
    printf("Filho 2: %d\n", no->P2);
    printf("Filho 3: %d\n", no->P3);
    printf("Filho 4: %d\n", no->P4);
}

void ler_no_arvB(FILE* arquivo, int RRN, NO_ARVB* no){
    //Lê um nó da árvore B

    //Vai para o RRN do nó a ser lido
    fseek(arquivo, RRN*TAMANHO_NO + TAMANHO_CABECALHO, SEEK_SET); //Ta vcerto isso?

    //Lê as informações do nó
    fread(&(no->altura_No), sizeof(int), 1, arquivo);
    fread(&(no->nroChaves), sizeof(int), 1, arquivo);
    fread(&(no->C1), sizeof(int), 1, arquivo);
    fread(&(no->PR1), sizeof(long int), 1, arquivo);
    fread(&(no->C2), sizeof(int), 1, arquivo);
    fread(&(no->PR2), sizeof(long int), 1, arquivo);
    fread(&(no->C3), sizeof(int), 1, arquivo);
    fread(&(no->PR3), sizeof(long int), 1, arquivo);
    fread(&(no->P1), sizeof(int), 1, arquivo);
    fread(&(no->P2), sizeof(int), 1, arquivo);
    fread(&(no->P3), sizeof(int), 1, arquivo);
    fread(&(no->P4), sizeof(int), 1, arquivo);

}

void escrever_no_arvB(FILE* arquivo_indice, NO_ARVB* no){
    //Escreve um nó da árvore B
    fwrite(&(no->altura_No), sizeof(int), 1, arquivo_indice);
    fwrite(&(no->nroChaves), sizeof(int), 1, arquivo_indice);
    fwrite(&(no->C1), sizeof(int), 1, arquivo_indice);
    fwrite(&(no->PR1), sizeof(long int), 1, arquivo_indice);
    fwrite(&(no->C2), sizeof(int), 1, arquivo_indice);
    fwrite(&(no->PR2), sizeof(long int), 1, arquivo_indice);
    fwrite(&(no->C3), sizeof(int), 1, arquivo_indice);
    fwrite(&(no->PR3), sizeof(long int), 1, arquivo_indice);
    fwrite(&(no->P1), sizeof(int), 1, arquivo_indice);
    fwrite(&(no->P2), sizeof(int), 1, arquivo_indice);
    fwrite(&(no->P3), sizeof(int), 1, arquivo_indice);
    fwrite(&(no->P4), sizeof(int), 1, arquivo_indice);

    //Força a escrita no arquivo
    fflush(arquivo_indice);
}

int get_chave(NO_ARVB* no, int pos){
    //Retorna a chave do nó na posição "pos" descoberta pelo loop da inserçãos
    if(pos == 1){
        return no->C1;
    }
    else if(pos == 2){
        return no->C2;
    }
    else if(pos == 3){
        return no->C3;
    }
    else{
        printf("Posição inválida\n");
        return -1;
    }
}

long int get_valor(NO_ARVB* no, int pos){
    //Retorna a chave do nó na posição "pos" descoberta pelo loop da inserçãos
    if(pos == 1){
        return no->PR1;
    }
    else if(pos == 2){
        return no->PR2;
    }
    else if(pos == 3){
        return no->PR3;
    }
    else{
        printf("Posição inválida\n");
        return -1;
    }
}

int get_filho(NO_ARVB* no, int pos){
    //Retorna o filho do nó na posição "pos" descoberta pelo loop da inserçãos
    if(pos == 1){
        return no->P1;
    }
    else if(pos == 2){
        return no->P2;
    }
    else if(pos == 3){
        return no->P3;
    }
    else if(pos == 4){
        return no->P4;
    }
    else{
        printf("Posição inválida do filho\n");
        return -1;
    }
}
