#include "utils_trab1.h"

struct registro_cabecalho_index
{
    char status;
};

struct registro_dados_index
{
    int chave;
    long long int byteoffset;
};

struct registro_cabecalho{
    char status;
    long long int topo;
    long long int prox_reg_disponivel;
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

DADOS* ler_input_dados()
{
    DADOS* registro_dados = init_registro_dados();

    //Ao todo, temos que cada registro incialmente tem 33 bytes de tamanho fixo. 
    int contador_tamanho = 33; 

    //Variável que acumulará o tamanho dos campos de tamanho variável para a alocação e contagem do tamanho do registro
    int contador_campo_var = 0;

    int id = 0;

    //Inicialização de strings auxiliares para armazenar os campos de tamanho variável
    char nome[100] = "\0";
    char nacionalidade[100] = "\0";
    char clube[100] = "\0";
    char idade[100] = "\0";

    //Ler os campos de input do usuario;
    scanf("%d", &registro_dados->id);
    scan_quote_string(idade);

    //Tranforma de string para inteiro
    registro_dados->idade = atoi(idade);
    if(registro_dados->idade == 0){
        registro_dados->idade = -1; //VERIFICARRRRRRR /////////////////////
    }
    printf("%d ", registro_dados->idade);

    //Ler os campos de tamanho variavel:

    //Ler o nome
    scan_quote_string(nome);
    if(strlen(nome) == 0){
        registro_dados->tam_Nome = 0;
    }
    else{
        registro_dados->tam_Nome = strlen(nome);
        contador_campo_var += registro_dados -> tam_Nome;
        registro_dados->nome = (char*)malloc(sizeof(registro_dados->tam_Nome));
        registro_dados->nome = nome;
    }
    printf("%s %ld ", registro_dados->nome, strlen(nome));

    //Ler a nacionalidade
    scan_quote_string(nacionalidade);
    if(strlen(nacionalidade) == 0){
        registro_dados->tam_Nacionalidade = 0;
    }
    else{
        registro_dados->tam_Nacionalidade = strlen(nacionalidade);
        contador_campo_var += registro_dados->tam_Nacionalidade;
        registro_dados->nacionalidade= (char*)malloc(sizeof(registro_dados->tam_Nacionalidade));
        registro_dados->nacionalidade = nacionalidade;
    }
    printf("%s %ld ", registro_dados->nacionalidade, strlen(nacionalidade));

    //Ler o clube
    scan_quote_string(clube);
    if(strlen(clube) == 0){
        registro_dados->tam_Clube = 0;
    }
    else{
        registro_dados->tam_Clube = strlen(clube);
        contador_campo_var = registro_dados->tam_Clube;
        registro_dados->clube = (char*)malloc(sizeof(registro_dados->tam_Clube));
        registro_dados->clube = clube;
    }
    printf("%s %ld", registro_dados->clube, strlen(clube));

    registro_dados->tamanho_registro = contador_tamanho + contador_campo_var;

    return registro_dados;
}

char get_status(CABECALHO* cabecalho){
    if(cabecalho == NULL){
        printf("Erro ao acessar o status do cabeçalho\n");
        return '0';
    }
    return cabecalho->status;
}

int getID(DADOS* registro){
    if(registro == NULL){
        printf("Erro ao acessar o ID do registro\n");
        return -1;
    }
    return registro->id;
}

int getTopo(CABECALHO* registro){
    if(registro == NULL){
        printf("Erro ao acessar o topo do registro\n");
        return -1;
    }
    return registro->topo;
}

int getnRemovidos(CABECALHO* registro){
    if(registro == NULL){
        printf("Erro ao acessar o nRemovidos do registro\n");
        return -1;
    }
    return registro->n_reg_removidos;
}

bool busca_binaria_index(DADOS_INDEX* vetor, int chave, int inicio, int fim){
    int pos = (inicio+fim)/2;
    if(inicio <= fim){
        if(vetor[pos].chave == chave){
            return true;
        }
        else if(vetor[pos].chave > chave){
            return busca_binaria_index(vetor, chave, inicio, pos-1);
        }
        else if(vetor[pos].chave < chave){
            return busca_binaria_index(vetor, chave, pos+1, fim);
        }
    }
    return false;
}