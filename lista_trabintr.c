#include "lista_trabintr.h"

struct registro_cabecalho{
    char status;
    long long int topo;
    long long int prox_reg_disponivel;
    int n_reg_disponiveis;
    int n_reg_removidos;
};

//Esturura de dados utilizada para a busca de registro na funcionalidade 3
struct busca_no{
    DADOS* registro;
    BN* prox;
};
struct busca_lista{
    BN* ini;
    BN* fim;
};

//Definição da estrutura do registro de dados
struct registro_dados{
    char removido;
    int tamanho_registro;
    long long int prox_reg;
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

void add_lista(BL* lista, DADOS* registro){
    //aloca um novo registro e copia os dados do registro auxiliar pra ele
    BN* no = (BN*) malloc(sizeof(BN));
    no->prox=NULL;
    no->registro= (DADOS*) malloc(sizeof(DADOS));
    no->registro->id = registro->id;
    no->registro->idade = registro->idade;
    no->registro->tam_Nome = registro->tam_Nome;
    no->registro->tam_Nacionalidade = registro->tam_Nacionalidade;
    no->registro->tam_Clube = registro->tam_Clube;
    //checa se as strings não estam vazias antes de alocar e copiar
    if(registro->tam_Nome!=0){
        no->registro->nome = (char*) malloc(30*sizeof(char));
        strcpy(no->registro->nome,registro->nome);
    }
    if(registro->tam_Nacionalidade!=0){
        no->registro->nacionalidade = (char*) malloc(30*sizeof(char));
        strcpy(no->registro->nacionalidade,registro->nacionalidade);
    }
    if(registro->tam_Clube!=0){
        no->registro->clube = (char*) malloc(30*sizeof(char));
        strcpy(no->registro->clube,registro->clube);
    }
    //checa se a lista está vazia e realiza a inserção do registro
    if(lista->ini==NULL){
        lista->ini = no;
        lista->fim = no;
    }
    else{
        lista->fim->prox = no;
        lista->fim = no;
    }
}
void apagar_lista(BL** lista){
    //inicializo as variavéis usadas para percorrer a lista
    BN *node, *ant;
    ant = (*lista)->ini;
    //se assegura de que a lista não está vazia para evitar segfault
    if(ant!=NULL){
        node=ant->prox;
    }
    //percorre a lista liberando o nó e o registro anterior
    while(ant!=NULL){
        apagar_registro(&(ant->registro));
        ant->prox=NULL;
        free(ant);
        ant=node;
        if(node!=NULL)
            node=node->prox;
    }
    //libera a lista em si
    (*lista)->ini=NULL;
    (*lista)->fim=NULL;
    free(*lista);
    lista=NULL;
}