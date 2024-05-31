//############################################################################
/* As funções definidas neste arquivo estão explicadas no arquivo "utils_trab1.h". 
Nesse código você encontrá comentários a nível de variáveis e procedimentos.
##############################################################################*/

#include "utils_trab1.h"

//Definição da estrutura de cabealho doo arquivo de índice
struct registro_cabecalho_index
{
    char status;
};

//Definição da estrutura dos registros de índice
struct registro_dados_index
{
    int chave;
    long int byteoffset;
};

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

DADOS* ler_input_dados()
{
    //Alocação e inicialização do registro de dados
    DADOS* registro_dados = init_registro_dados();

    //Ao todo, temos que cada registro incialmente tem 33 bytes de tamanho fixo. 
    int contador_tamanho = 33; 

    //Variável que acumulará o tamanho dos campos de tamanho variável para a alocação e contagem do tamanho do registro
    int contador_campo_var = 0;

    //Variável auxiliar para armazenar o ID do registro
    int id = 0;

    //Inicialização de strings auxiliares para armazenar os campos de tamanho variável
    char nome[100] = "\0";
    char nacionalidade[100] = "\0";
    char clube[100] = "\0";
    char idade[100] = "\0";

    /*-----Ler os campos de input do usuario-----*/

    //Ler o ID do jogador
    scanf("%d", &registro_dados->id);

    //Ler a idade do jogador
    scan_quote_string(idade);

    //Tranforma de string para inteiro usando a função atoi
    registro_dados->idade = atoi(idade);
    if(registro_dados->idade == 0){
        registro_dados->idade = -1; 
    }
    printf("%d ", registro_dados->idade);

    /*Ler os campos de tamanho variavel:*/

    //Ler o nome do jogador
    scan_quote_string(nome);
    if(strlen(nome) == 0){//Se a string for vazia, o tamanho do campo Nome é definido como 0
        registro_dados->tam_Nome = 0;
    }
    else{
        registro_dados->tam_Nome = strlen(nome); //Caso contrário, o tamanho do campo é a quantidade de caracteres da string
        contador_campo_var += registro_dados -> tam_Nome; //Acumula o tamanho do campo para a contagem do tamanho do registro
        registro_dados->nome = (char*)malloc(sizeof(registro_dados->tam_Nome * sizeof(char))); //Aloca memória para o campo
        strcpy(registro_dados->nome, nome); //Copia a string para o campo
    }
    printf("%s %ld ", registro_dados->nome, strlen(nome));

    //Ler a nacionalidade
    scan_quote_string(nacionalidade);
    if(strlen(nacionalidade) == 0){ //Se a string for vazia, o tamanho do campo Nacionalidade é definido como 0
        registro_dados->tam_Nacionalidade = 0;
    }
    else{
        registro_dados->tam_Nacionalidade = strlen(nacionalidade); //Caso contrário, o tamanho do campo é a quantidade de caracteres da string
        contador_campo_var += registro_dados->tam_Nacionalidade; //Acumula o tamanho do campo para a contagem do tamanho do registro
        registro_dados->nacionalidade= (char*)malloc(sizeof(registro_dados->tam_Nacionalidade * sizeof(char))); //Aloca memória para o campo
        strcpy(registro_dados->nacionalidade, nacionalidade); //Copia a string para o campo
    }
    printf("%s %ld ", registro_dados->nacionalidade, strlen(nacionalidade));

    //Ler o clube
    scan_quote_string(clube);
    if(strlen(clube) == 0){ //Se a string for vazia, o tamanho do campo Clube é definido como 0
        registro_dados->tam_Clube = 0;
    }
    else{
        registro_dados->tam_Clube = strlen(clube); //Caso contrário, o tamanho do campo é a quantidade de caracteres da string
        contador_campo_var += registro_dados->tam_Clube; //Acumula o tamanho do campo para a contagem do tamanho do registro
        registro_dados->clube = (char*)malloc(sizeof(registro_dados->tam_Clube * sizeof(char))); //Aloca memória para o campo
        strcpy(registro_dados->clube, clube); //Copia a string para o campo
    }
    printf("%s %d", registro_dados->clube, registro_dados->tam_Clube);

    registro_dados->tamanho_registro = contador_tamanho + contador_campo_var; //Atualiza o tamanho do registro de dados após ler os campos de input

    return registro_dados;
}

char get_status(CABECALHO* cabecalho){
    //Pega o status do registro cabeçalho do arquivo de dados
    if(cabecalho == NULL){
        printf("Erro ao acessar o status do cabeçalho\n");
        return '0';
    }
    return cabecalho->status;
}

int getID(DADOS* registro){
    //Pega o ID do registro de dados
    if(registro == NULL){
        printf("Erro ao acessar o ID do registro\n");
        return -1;
    }
    return registro->id;
}

long int getTopo(CABECALHO* registro){
    //Pega o topo do registro de cabeçalho do arquivo de dados
    if(registro == NULL){
        printf("Erro ao acessar o topo do registro\n");
        return -1;
    }
    return registro->topo;
}

int getnRemovidos(CABECALHO* registro){
    //Pega o número de registros removidos do registro de cabeçalho do arquivo de dados
    if(registro == NULL){
        printf("Erro ao acessar o nRemovidos do registro\n");
        return -1;
    }
    return registro->n_reg_removidos;
}

int getnRegDisponiveis(CABECALHO* registro){
    //Pega o número de registros disponíveis do registro de cabeçalho do arquivo de dados
    if(registro == NULL){
        printf("Erro ao acessar o nRegDisponiveis do registro\n");
        return -1;
    }
    return registro->n_reg_disponiveis;
}

long int getProxRegDisponivel(CABECALHO* registro){
    //Pega o byteoffset do próximo registro disponível do registro de cabeçalho do arquivo de dados
    if(registro == NULL){
        printf("Erro ao acessar o proxRegDisponivel do registro\n");
        return -1;
    }
    return registro->prox_reg_disponivel;
}

void set_nRegDisponiveis(CABECALHO* registro, int n){
    //Atualiza o número de registros disponíveis do registro de cabeçalho do arquivo de dados
    if(registro == NULL){
        printf("Erro ao acessar o nRegDisponiveis do registro\n");
        return;
    }
    registro->n_reg_disponiveis = n;
}

void set_nRegRemovidos(CABECALHO* registro, int n){
    //Atualiza o número de registros removidos do registro de cabeçalho do arquivo de dados
    if(registro == NULL){
        printf("Erro ao acessar o nRegRemovidos do registro\n");
        return;
    }
    registro->n_reg_removidos = n;
}

void set_topo(CABECALHO* registro, int n){
    //Atualiza o topo do registro de cabeçalho do arquivo de dados
    if(registro == NULL){
        printf("Erro ao acessar o topo do registro\n");
        return;
    }
    registro->topo = n;
}

void setProxRegDisponivel(CABECALHO* registro, long int n){
    //Atualiza o campo de próximo registro disponível do registro de cabeçalho no arquivo de dados
    if(registro == NULL){
        printf("Erro ao acessar o proxRegDisponivel do registro\n");
        return;
    }
    registro->prox_reg_disponivel = n;
}

long int busca_binaria_index(DADOS_INDEX* vetor, int chave, int inicio, int fim){
    if(vetor == NULL){
        printf("Erro ao acessar o vetor\n");
        return false;
    }
    int pos = (inicio+fim)/2;
    if(inicio <= fim){
        if(vetor[pos].chave == chave){
            return vetor[pos].byteoffset;
        }
        else if(vetor[pos].chave > chave){
            return busca_binaria_index(vetor, chave, inicio, pos-1);
        }
        else if(vetor[pos].chave < chave){
            return busca_binaria_index(vetor, chave, pos+1, fim);
        }
    }
    return -1;
}

int get_tam(long int endereco, FILE* arquivo_dados){

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

int get_prox(long int endereco, FILE* arquivo_dados){

    fseek(arquivo_dados, endereco + 5, SEEK_SET);
    long int prox;
    fread(&prox, sizeof(long int), 1, arquivo_dados);
    return prox;
}

void remover_dados(DADOS* aux,FILE* arquivo_dados,CABECALHO* cabecalho_dados, long int cur_byte_offset){
    long int reg_rem= cur_byte_offset, reg_prox = cabecalho_dados->topo ,reg_ant = -1,reg_atual=-1;
    int tam_reg = aux-> tamanho_registro, tam_atual=0;
    char lixo;
    aux->removido='1';
    while(reg_prox!=-1 && tam_reg > tam_atual){
        fseek(arquivo_dados,reg_prox,SEEK_SET);
        fread(&lixo,sizeof(char),1,arquivo_dados);
        fread(&tam_atual,sizeof(int),1,arquivo_dados);
        reg_ant = reg_atual;
        reg_atual = reg_prox;
        fread(&reg_prox,sizeof(long int),1,arquivo_dados);
    }
    if(reg_ant==-1 ){
        cabecalho_dados->topo = reg_rem;
    }
    else{
        fseek(arquivo_dados,reg_ant+sizeof(int)+sizeof(char),SEEK_SET);
        fwrite(&reg_rem,sizeof(long int),1,arquivo_dados);
    }
        fseek(arquivo_dados,reg_rem,SEEK_SET);
        fwrite(&(aux->removido),sizeof(char),1,arquivo_dados);
        fwrite(&tam_reg,sizeof(int),1,arquivo_dados);
        fwrite(&reg_atual,sizeof(long int),1,arquivo_dados);
        cabecalho_dados->n_reg_removidos++;
        cabecalho_dados->n_reg_disponiveis--;
        fseek(arquivo_dados,cur_byte_offset+tam_reg,SEEK_SET);

}

long long best_fit_recursivo(FILE* arquivo_dados, DADOS* registro, CABECALHO* cabecalho, long int endereco_anterior, long int endereco_atual){
    if(endereco_atual == -1){ //A busca não encontrou um registro que caiba o novo registro a ser inserido
        printf("\nA busca não encontrou um registro que caiba o novo registro a ser inserido\n");
        return -1;
    }
    else{
        if(registro->tamanho_registro <= get_tam(endereco_atual, arquivo_dados)){
            printf("\nRegistro de reutilização encontrado! Diferença igual a %d\n", (get_tam(endereco_atual, arquivo_dados) - registro->tamanho_registro));
            long int prox_atual = get_prox(endereco_atual, arquivo_dados);
            if(endereco_atual == endereco_anterior){
                printf("\nO registro a ser reutilizado é o topo\n");
                cabecalho->topo = prox_atual;
            }
            else{
                //Reescreve o ponteiro do registro anterior para apontar para o próximo registro
                printf("Reescri o ponteiro do registro anterior para apontar para o próximo registro\n");
                fseek(arquivo_dados, endereco_anterior + 5, SEEK_SET);
                fwrite(&prox_atual, sizeof(long int), 1, arquivo_dados);
            }
            return endereco_atual;
        }
        else{
            return best_fit_recursivo(arquivo_dados, registro, cabecalho, endereco_atual, get_prox(endereco_atual, arquivo_dados));
        }
    }

}

long int best_fit(FILE* arquivo_dados, DADOS* registro, CABECALHO* cabecalho, long int endereco){
    return best_fit_recursivo(arquivo_dados, registro, cabecalho, endereco, endereco);
}


void reaproveitamento_dados(FILE* arquivo_dados, DADOS* registro_dados, long int endereco){

    //Calcula a diferença entre o tamanho do registro a ser inserido e o tamanho do registro removido
    int tam_registro_rem = get_tam(endereco, arquivo_dados);
    int diferenca = tam_registro_rem - registro_dados->tamanho_registro;

    fseek(arquivo_dados, endereco, SEEK_SET); //Reposiciona o ponteiro no início do registro a ser reaproveitado (get_tam muda)
    registro_dados->tamanho_registro = tam_registro_rem; //Atualiza o campo de tamanho do registro
    escrever_registro_dados(registro_dados, arquivo_dados); //Escreve o registro no arquivo

    printf("Diferença igual a %d\n", diferenca);
    
    //Preenche o resto do registro com '$'
    for(int i = 0; i < diferenca; i++){
        fwrite("$", sizeof(char), 1, arquivo_dados);
    }
}

void inserir_final(FILE* arquivo_dados, FILE* arquivo_index, DADOS* registro_dados, CABECALHO* registro_cabecalho_dados, DADOS_INDEX* vetor_index, DADOS_INDEX* registro_index){
    // Como não há registros logicamente removidos, inserir no fim do arquivo:
    long int endereco = getProxRegDisponivel(registro_cabecalho_dados);  
    registro_index->chave = registro_dados->id;
    registro_index->byteoffset = endereco;  
    printf("Endereço: %ld\n", endereco);

    // Uso o registro_cabecalho_dados->prox_reg_disponivel (byteoffset do final) e escreve o registro de dados lá
    fseek(arquivo_dados, endereco, SEEK_SET);   
    escrever_registro_dados(registro_dados, arquivo_dados);
    endereco = ftell(arquivo_dados);
    printf("Endereço: %ld\n", endereco);
    // endereco += registro_dados->tamanho_registro;
    // printf("Endereço: %ld\n", endereco);
    setProxRegDisponivel(registro_cabecalho_dados, endereco);

    //Incrementar o número de registros no cabeçalho
    int n_reg = getnRegDisponiveis(registro_cabecalho_dados);
    set_nRegDisponiveis(registro_cabecalho_dados, n_reg+1);

    // Inserir reg index no vetor de registros index
    int count_reg_index = incrementar_count_reg();
    inserir_ordenado(vetor_index, registro_index, count_reg_index);

    // Att o cabelçalho do arq de dados e reescrever ele(n registro depóniveis, prox_reg_disponivel)
    fseek(arquivo_dados, 0, SEEK_SET);  // Resetar o ponteiro do arquivo para o início

    printf("\nTopo: %ld\n", getTopo(registro_cabecalho_dados));
    printf("Prox: %ld\n", getProxRegDisponivel(registro_cabecalho_dados));
    printf("N Reg: %d\n", getnRegDisponiveis(registro_cabecalho_dados));
    printf("N Rem: %d\n", getnRemovidos(registro_cabecalho_dados));

    escrever_cabecalho(arquivo_dados, registro_cabecalho_dados); //Escreve o cabeçalho no arquivo de dados
}

void insercao_dinamica(FILE* arquivo_dados, FILE* arquivo_index, DADOS* registro_dados, CABECALHO* registro_cabecalho_dados, DADOS_INDEX* vetor_index, DADOS_INDEX* registro_index, long int endereco){
//Caso encontre um endereço viável, inserimos o registro no endereço encontrado
    registro_index->chave = registro_dados->id;
    registro_index->byteoffset = endereco;  
    printf("Endereço encontrado: %ld\n", endereco);

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

    printf("\nTopo: %ld\n", getTopo(registro_cabecalho_dados));
    printf("Prox: %ld\n", getProxRegDisponivel(registro_cabecalho_dados));
    printf("N Reg: %d\n", getnRegDisponiveis(registro_cabecalho_dados));
    printf("N Rem: %d\n", getnRemovidos(registro_cabecalho_dados));

    escrever_cabecalho(arquivo_dados, registro_cabecalho_dados); //Rescreve o cabeçalho no arquivo de dados
}