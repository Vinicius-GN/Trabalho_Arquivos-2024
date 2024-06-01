//############################################################################
/* As funções definidas neste arquivo estão explicadas no arquivo "vetorIndex.h". 
Nesse código você encontrá comentários a nível de variáveis e procedimentos.
##############################################################################*/

#include "vetorIndex.h"

//Tamanho inicial do vetor de índices (aumentado se necessário com realloc)
int TAMANHO_VETOR_INDEX = 1050; //Tamanho do vetor de índices (1050 registros)


//Permitir acesso direto aos dados da struct
struct registro_dados_index {
    int chave;
    long long int byteoffset;
};

//Definição da estrutura do registro de cabeçalho do arquivo de índice
struct registro_cabecalho_index{
    char status;
};

DADOS_INDEX* criar_vetor(){
    //Aloca o vetor e inicializa os seus campos.
    DADOS_INDEX* vetor = (DADOS_INDEX*)malloc(sizeof(DADOS_INDEX)*TAMANHO_VETOR_INDEX);

    /*Obs: Nesse caso, optamos por inicializar o vetor com um tamanho pre-definido e realocar memória caso necessário, pois 
      utilizar realloc para aumentar o tamanho do vetor a cada inserção seria computacionalmente mais custoso.*/

    for(int i = 0; i < TAMANHO_VETOR_INDEX; i++){
        vetor[i].chave = -1;
        vetor[i].byteoffset = -1;
    }
    return vetor;
}

void inserir_ordenado(DADOS_INDEX* vetor, DADOS_INDEX* registro, int tamanho){
    if(tamanho > TAMANHO_VETOR_INDEX){
        DADOS_INDEX* temp = realloc(vetor, sizeof(DADOS_INDEX) * tamanho * 2);
        if (temp == NULL) {
            // Nesse caso, houve falha na realocação do vetor
            printf("Erro: não foi possível alocar memória suficiente.\n");

        
        } else {
            // Realocação bem-sucedida!
            vetor = temp;
            // Atualiza o valor de TAMANHO_VETOR_INDEX se estiver mantendo controle do tamanho atual
            TAMANHO_VETOR_INDEX = tamanho * 2;
        }
    }
    
    for(int i = 0; i < tamanho;i++){
        //Insere o registro de forma ordenada no vetor
        if(vetor[i].chave == -1){
            //Insere no final
            vetor[i].chave = registro->chave;
            vetor[i].byteoffset = registro->byteoffset;
            break;
        }
        else{
            //Insere no meio e reorganiza o vetor
            if(vetor[i].chave > registro->chave){
                for(int j = tamanho-1; j > i; j--){
                    vetor[j].chave = vetor[j-1].chave;
                    vetor[j].byteoffset = vetor[j-1].byteoffset;
                }
                vetor[i].chave = registro->chave;
                vetor[i].byteoffset = registro->byteoffset;
                break;
            }
        }
    }
}

void remover_ordenado(DADOS_INDEX* vetor, int chave, int inicio, int fim, int tamanho){ 
    int pos = fim+inicio/2; //Cálculo da posição do meio para a busca binária
   
    if(inicio <= fim){ //Verificação de condição base da recursão em busca binária

        //Se achar o registro, remove ele e reorganiza o vetor
        if(vetor[pos].chave == chave){

            //Remoção do registro
            vetor[pos].chave = -1; 
            vetor[pos].byteoffset = -1;

            //Shift dos dados para preencher o espaço vazio
            for(int i = pos; i < tamanho-1; i++){
                vetor[i].chave = vetor[i+1].chave;
                vetor[i].byteoffset = vetor[i+1].byteoffset;
            }

            return;
        }

        //Se a chave do registro for maior que a chave do registro na posição pos, chama a função recursivamente para a metade da direita
        else if(vetor[pos].chave > chave){
            remover_ordenado(vetor, chave, inicio, pos-1, tamanho);
        }
        //Se a chave do registro for menor que a chave do registro na posição pos, chama a função recursivamente para a metade da esquerda
        else if(vetor[pos].chave < chave){
            remover_ordenado(vetor, chave, pos+1, fim, tamanho);
        }
    }
}

void apagar_vetor(DADOS_INDEX**vetor){
    free(*vetor); //Libera a memória alocada para o vetor
}

void imprimir_vetor(DADOS_INDEX* vetor, int tamanho){

    //Percorre o vetor e imprime os valores de chave e byteoffset
    for(int i = 0; i < tamanho; i++){ 
        printf("[%d, %lld]\n", vetor[i].chave, vetor[i].byteoffset);
    }
}

// Função auxiliar para escrever um registro de index no arquivo
void escrever_registro_index(DADOS_INDEX *registro, FILE *arquivo){
    fwrite(&registro->chave, sizeof(int), 1, arquivo);
    fwrite(&registro->byteoffset, sizeof(long long int), 1, arquivo);
}

void escrever_vetor_index(DADOS_INDEX* vetor_index, FILE* arquivo_index){
    for (int i = 0; i < get_count_reg(); i++)//Escreve todos os registros do vetor no arquivo
    {
        escrever_registro_index(&vetor_index[i], arquivo_index);
    }
}

void set_arquivo_index(char status, CABECALHO_INDEX *cabecalho, FILE *arquivo){
    //Atualiza o status do arquivo de índice
    cabecalho->status = status;
    fwrite(&cabecalho->status, sizeof(char), 1, arquivo);
}

long int busca_binaria_index(DADOS_INDEX* vetor, int chave, int inicio, int fim){
    if(vetor == NULL){
        return -1;
    }
    int pos = (inicio+fim)/2; //Cálculo de posição do meio para a busca binária
    if(inicio <= fim){ //Condição para continuação da busca binária
        if(vetor[pos].chave == chave){
            //Encontrou a chave buscada
            return vetor[pos].byteoffset;
        }
        else if(vetor[pos].chave > chave){
            //Chave buscada está à esquerda (no vetor)
            return busca_binaria_index(vetor, chave, inicio, pos-1);
        }
        else if(vetor[pos].chave < chave){
            //Chave buscada está à direita (no vetor)
            return busca_binaria_index(vetor, chave, pos+1, fim);
        }
    }
    return -1;
}

// Função para liberar a memória alocada para os registros de index e dados
void liberar_memoria(CABECALHO_INDEX **registro_cabecalho_index, DADOS_INDEX **registro_index, DADOS **registro_dados){
    if(*registro_cabecalho_index != NULL)
        free(*registro_cabecalho_index);

    if(*registro_index != NULL)
        free(*registro_index);

    apagar_registro(registro_dados);
}
