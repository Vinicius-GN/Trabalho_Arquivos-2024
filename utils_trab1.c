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
        registro_dados->idade = -1; 
    }
    printf("%d ", registro_dados->idade);

    //Ler os campos de tamanho variavel:

    //Ler o nome
    scan_quote_string(nome);
    if(strlen(nome) == 0){
        registro_dados->tam_Nome = -1;
    }
    else{
        registro_dados->tam_Nome = strlen(nome);
        contador_campo_var += registro_dados -> tam_Nome;
        registro_dados->nome = (char*)malloc(sizeof(registro_dados->tam_Nome * sizeof(char)));
        strcpy(registro_dados->nome, nome);
    }
    printf("%s %ld ", registro_dados->nome, strlen(nome));

    //Ler a nacionalidade
    scan_quote_string(nacionalidade);
    if(strlen(nacionalidade) == 0){
        registro_dados->tam_Nacionalidade = -1;
    }
    else{
        registro_dados->tam_Nacionalidade = strlen(nacionalidade);
        contador_campo_var += registro_dados->tam_Nacionalidade;
        registro_dados->nacionalidade= (char*)malloc(sizeof(registro_dados->tam_Nacionalidade * sizeof(char)));
        strcpy(registro_dados->nacionalidade, nacionalidade);
    }
    printf("%s %ld ", registro_dados->nacionalidade, strlen(nacionalidade));

    //Ler o clube
    scan_quote_string(clube);
    if(strlen(clube) == 0){
        registro_dados->tam_Clube = -1;
    }
    else{
        registro_dados->tam_Clube = strlen(clube);
        contador_campo_var += registro_dados->tam_Clube;
        registro_dados->clube = (char*)malloc(sizeof(registro_dados->tam_Clube * sizeof(char)));
        strcpy(registro_dados->clube, clube);
    }
    printf("%s %d", registro_dados->clube, registro_dados->tam_Clube);

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

long long int getTopo(CABECALHO* registro){
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

int getnRegDisponiveis(CABECALHO* registro){
    if(registro == NULL){
        printf("Erro ao acessar o nRegDisponiveis do registro\n");
        return -1;
    }
    return registro->n_reg_disponiveis;
}

long long int getProxRegDisponivel(CABECALHO* registro){
    if(registro == NULL){
        printf("Erro ao acessar o proxRegDisponivel do registro\n");
        return -1;
    }
    return registro->prox_reg_disponivel;
}

void set_nRegDisponiveis(CABECALHO* registro, int n){
    if(registro == NULL){
        printf("Erro ao acessar o nRegDisponiveis do registro\n");
        return;
    }
    registro->n_reg_disponiveis = n;
}

void set_nRegRemovidos(CABECALHO* registro, int n){
    if(registro == NULL){
        printf("Erro ao acessar o nRegRemovidos do registro\n");
        return;
    }
    registro->n_reg_removidos = n;
}

void set_topo(CABECALHO* registro, int n){
    if(registro == NULL){
        printf("Erro ao acessar o topo do registro\n");
        return;
    }
    registro->topo = n;
}

void setProxRegDisponivel(CABECALHO* registro, long long int n){
    if(registro == NULL){
        printf("Erro ao acessar o proxRegDisponivel do registro\n");
        return;
    }
    registro->prox_reg_disponivel = n;
}

bool busca_binaria_index(DADOS_INDEX* vetor, int chave, int inicio, int fim){
    if(vetor == NULL){
        printf("Erro ao acessar o vetor\n");
        return false;
    }
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

int get_tam(long long int endereco, FILE* arquivo_dados){

    fseek(arquivo_dados, endereco, SEEK_SET);
    char removido;
    fread(&removido, sizeof(char), 1, arquivo_dados);
    if(removido == '1'){
        int tam;
        fread(&tam, sizeof(int), 1, arquivo_dados);
        return tam;
    }
    else{
        printf("Registro não removido, pegou o cara errado\n");
        return -1;
    }
}

int get_prox(long long int endereco, FILE* arquivo_dados){

    fseek(arquivo_dados, endereco + 5, SEEK_SET);
    long long int prox;
    fread(&prox, sizeof(long long int), 1, arquivo_dados);
    return prox;
}

long long best_fit_recursivo(FILE* arquivo_dados, DADOS* registro, CABECALHO* cabecalho, long long int endereco_anterior, long long int endereco_atual){
    if(endereco_atual == -1){ //A busca não encontrou um registro que caiba o novo registro a ser inserido
        printf("\nA busca não encontrou um registro que caiba o novo registro a ser inserido\n");
        return -1;
    }
    else{
        if(registro->tamanho_registro <= get_tam(endereco_atual, arquivo_dados)){
            printf("\nRegistro de reutilização encontrado! Diferença igual a %d\n", (get_tam(endereco_atual, arquivo_dados) - registro->tamanho_registro));
            long long int prox_atual = get_prox(endereco_atual, arquivo_dados);
            if(endereco_atual == endereco_anterior){
                printf("\nO registro a ser reutilizado é o topo\n");
                cabecalho->topo = prox_atual;
            }
            else{
                //Reescreve o ponteiro do registro anterior para apontar para o próximo registro
                printf("Reescri o ponteiro do registro anterior para apontar para o próximo registro\n");
                fseek(arquivo_dados, endereco_anterior + 5, SEEK_SET);
                fwrite(&prox_atual, sizeof(long long int), 1, arquivo_dados);
            }
            return endereco_atual;
        }
        else{
            return best_fit_recursivo(arquivo_dados, registro, cabecalho, endereco_atual, get_prox(endereco_atual, arquivo_dados));
        }
    }

}

long long int best_fit(FILE* arquivo_dados, DADOS* registro, CABECALHO* cabecalho, long long int endereco){
    return best_fit_recursivo(arquivo_dados, registro, cabecalho, endereco, endereco);
}


void reaproveitamento_dados(FILE* arquivo_dados, DADOS* registro_dados, long long int endereco){

    //Calcula a diferença entre o tamanho do registro a ser inserido e o tamanho do registro removido
    int tam_registro_rem = get_tam(endereco, arquivo_dados);
    int diferenca = tam_registro_rem - registro_dados->tamanho_registro;

    fseek(arquivo_dados, endereco, SEEK_SET); //Posiciona o ponteiro no início do registro a ser removido
    registro_dados->tamanho_registro = tam_registro_rem; //Atualiza o campo de tamanho do registro
    escrever_registro_dados(registro_dados, arquivo_dados); //Escreve o registro no arquivo

    printf("Diferença igual a %d\n", diferenca);
    
    //Preenche o resto do registro com '$'
    for(int i = 0; i < registro_dados->tamanho_registro; i++){
        fwrite("$", sizeof(char), 1, arquivo_dados);
    }
}

void inserir_final(FILE* arquivo_dados, FILE* arquivo_index, DADOS* registro_dados, CABECALHO* registro_cabecalho_dados, DADOS_INDEX* vetor_index, DADOS_INDEX* registro_index){
    // Como não há registros logicamente removidos, inserir no fim do arquivo:
    long long int endereco = getProxRegDisponivel(registro_cabecalho_dados);  
    registro_index->chave = registro_dados->id;
    registro_index->byteoffset = endereco;  
    printf("Endereço: %lld\n", endereco);

    // Uso o registro_cabecalho_dados->prox_reg_disponivel (byteoffset do final) e escreve o registro de dados lá
    fseek(arquivo_dados, endereco, SEEK_SET);   
    escrever_registro_dados(registro_dados, arquivo_dados);
    endereco = ftell(arquivo_dados);
    printf("Endereço: %lld\n", endereco);
    // endereco += registro_dados->tamanho_registro;
    // printf("Endereço: %lld\n", endereco);
    setProxRegDisponivel(registro_cabecalho_dados, endereco);

    //Incrementar o número de registros no cabeçalho
    int n_reg = getnRegDisponiveis(registro_cabecalho_dados);
    set_nRegDisponiveis(registro_cabecalho_dados, n_reg+1);

    // Inserir reg index no vetor de registros index
    int count_reg_index = incrementar_count_reg();
    inserir_ordenado(vetor_index, registro_index, count_reg_index);

    // Att o cabelçalho do arq de dados e reescrever ele(n registro depóniveis, prox_reg_disponivel)
    fseek(arquivo_dados, 0, SEEK_SET);  // Resetar o ponteiro do arquivo para o início

    printf("\nTopo: %lld\n", getTopo(registro_cabecalho_dados));
    printf("Prox: %lld\n", getProxRegDisponivel(registro_cabecalho_dados));
    printf("N Reg: %d\n", getnRegDisponiveis(registro_cabecalho_dados));
    printf("N Rem: %d\n", getnRemovidos(registro_cabecalho_dados));

    escrever_cabecalho(arquivo_dados, registro_cabecalho_dados); //Escreve o cabeçalho no arquivo de dados
}

void insercao_dinamica(FILE* arquivo_dados, FILE* arquivo_index, DADOS* registro_dados, CABECALHO* registro_cabecalho_dados, DADOS_INDEX* vetor_index, DADOS_INDEX* registro_index, long long int endereco){
//Caso encontre um endereço viável, inserimos o registro no endereço encontrado
    registro_index->chave = registro_dados->id;
    registro_index->byteoffset = endereco;  
    printf("Endereço: %lld\n", endereco);

    // Uso o endereço encontrado pelo best-fit para inserir meu novo registro
    fseek(arquivo_dados, endereco, SEEK_SET);   
    reaproveitamento_dados(arquivo_dados, registro_dados, endereco); //Substitui os caracteres faltantes por "$"

    //Incrementar o número de registros disponíveis no cabeçalho
    int n_reg = getnRegDisponiveis(registro_cabecalho_dados);
    set_nRegDisponiveis(registro_cabecalho_dados, n_reg+1);

    //Decrementar o número de registros removidos no cabeçalho
    int n_rem = getnRemovidos(registro_cabecalho_dados);
    set_nRegRemovidos(registro_cabecalho_dados, n_rem-1);

    // Inserir reg index no vetor de registros index
    int count_reg_index = incrementar_count_reg();
    inserir_ordenado(vetor_index, registro_index, count_reg_index);

    // Att o cabelçalho do arq de dados e reescrever ele(n registro depóniveis, prox_reg_disponivel)
    fseek(arquivo_dados, 0, SEEK_SET);  // Resetar o ponteiro do arquivo para o início

    printf("\nTopo: %lld\n", getTopo(registro_cabecalho_dados));
    printf("Prox: %lld\n", getProxRegDisponivel(registro_cabecalho_dados));
    printf("N Reg: %d\n", getnRegDisponiveis(registro_cabecalho_dados));
    printf("N Rem: %d\n", getnRemovidos(registro_cabecalho_dados));

    escrever_cabecalho(arquivo_dados, registro_cabecalho_dados); //Rescreve o cabeçalho no arquivo de dados
}