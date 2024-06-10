
//############################################################################
/* As funções definidas neste arquivo estão explicadas no arquivo "get&set_dados.h". 
Nesse código você encontrá comentários a nível de variáveis e procedimentos.
##############################################################################*/

//Trabalho 1 da disciplina de Organização de Arquivos

#include "getset_dados.h"

//Definição da estrutura do cabeçalho do arquivo de dados
struct registro_cabecalho{
    char status;
    long int topo; long int prox_reg_disponivel;
    int n_reg_disponiveis;
    int n_reg_removidos;
};


//Definição da estrutura do registro de dados
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

char get_status(CABECALHO* cabecalho){
    //Pega o status do registro cabeçalho do arquivo de dados
    if(cabecalho == NULL){
        return '0';
    }
    return cabecalho->status;
}

int getID(DADOS* registro){
    //Pega o ID do registro de dados
    if(registro == NULL){
        return -1;
    }
    return registro->id;
}

long int getTopo(CABECALHO* registro){
    //Pega o topo do registro de cabeçalho do arquivo de dados
    if(registro == NULL){
        return -1;
    }
    return registro->topo;
}

int getnRemovidos(CABECALHO* registro){
    //Pega o número de registros removidos do registro de cabeçalho do arquivo de dados
    if(registro == NULL){
        return -1;
    }
    return registro->n_reg_removidos;
}

int getnRegDisponiveis(CABECALHO* registro){
    //Pega o número de registros disponíveis do registro de cabeçalho do arquivo de dados
    if(registro == NULL){
        return -1;
    }
    return registro->n_reg_disponiveis;
}

long int getProxRegDisponivel(CABECALHO* registro){
    //Pega o byteoffset do próximo registro disponível do registro de cabeçalho do arquivo de dados
    if(registro == NULL){
        return -1;
    }
    return registro->prox_reg_disponivel;
}

void set_nRegDisponiveis(CABECALHO* registro, int n){
    //Atualiza o número de registros disponíveis do registro de cabeçalho do arquivo de dados
    if(registro == NULL){
        return;
    }
    registro->n_reg_disponiveis = n;
}

void set_nRegRemovidos(CABECALHO* registro, int n){
    //Atualiza o número de registros removidos do registro de cabeçalho do arquivo de dados
    if(registro == NULL){
        return;
    }
    registro->n_reg_removidos = n;
}

void set_topo(CABECALHO* registro, int n){
    //Atualiza o topo do registro de cabeçalho do arquivo de dados
    if(registro == NULL){
        return;
    }
    registro->topo = n;
}

void setProxRegDisponivel(CABECALHO* registro, long int n){
    //Atualiza o campo de próximo registro disponível do registro de cabeçalho no arquivo de dados
    if(registro == NULL){
        return;
    }
    registro->prox_reg_disponivel = n;
}

int get_tam(long int endereco, FILE* arquivo_dados){
    //Vai para o endereço especficiado e lê o campo de removido
    fseek(arquivo_dados, endereco, SEEK_SET);
    char removido;
    fread(&removido, sizeof(char), 1, arquivo_dados);
    if(removido == '1'){
        //Se o registro realmente foi removido, lê o campo de tamanho do registro e o retorna
        int tam;
        fread(&tam, sizeof(int), 1, arquivo_dados);
        return tam;
    }
    else{
        //Se o registro não foi removido, retorna -1 (flag de erro)
        return -1;
    }
}

long int get_prox(long int endereco, FILE* arquivo_dados){

    //Vai para o endereço especificado e lê o campo de proximo registro (byteoffset)
    fseek(arquivo_dados, endereco + 5, SEEK_SET);
    long int prox;
    fread(&prox, sizeof(long int), 1, arquivo_dados);

    //Retorna o valor lido.
    return prox;
}
