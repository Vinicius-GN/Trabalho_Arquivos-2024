#include "funcionalidades.h"

/* As funções definidas neste arquivo estão explicadas no arquivo "utils.h". 
Nesse código você encontrá comentários a nível de variáveis e procedimentos.*/

//Definição da estrutura do cabeçalho, seguindo a ordem recomendada nas espeficiações do trabalho
struct registro_cabecalho{
    char status;
    long long int topo;
    long long int prox_reg_disponivel;
    int n_reg_disponiveis;
    int n_reg_removidos;
};

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

void funcionalidade1(void){
    //Contador do número de registros lidos
    int count_registros = 0;
    long int prox_reg = 0;

    //Leitura dos nomes dos arquivos
    char arquivo_in_name[50];
    char arquivo_out_name[50];
    scanf("%s", arquivo_in_name);
    scanf("%s", arquivo_out_name);

    //Inicialização do arquivo binário
    FILE* arquivo_out = abrir_arquivo(arquivo_out_name, "wb");

    //Iniciliza o cabeçalho do arquivo binário e escreve no arquivo o cabeçalho
    CABECALHO* cabecalho = init_arquivo_binario(arquivo_out);

    //Inicializando o arquivo de entrada
    FILE* arquivo_in = abrir_arquivo(arquivo_in_name, "r");

    /*Inicio de leitura e escrita dos dados no arquivo binário*/
    fseek(arquivo_in, 0, SEEK_SET);//Resetar o ponteiro do arquivo para o início (precaução)

    //Inicilaização de um buffer para leitura de cada linha
    char linha[256];

    //Tira a primeira linha da entrada
    fgets(linha, 256, arquivo_in); 
    linha[strcspn(linha, "\n")] = 0; //Remove o \n da string (poderia ficar salva no ultimo campo do registro)

//// PEGAR LINHA A LINHA E ESCREVER NO ARQUIVO BINÁRIO ////
//A função fgets lê até o fim da linha ou até que o número máximo de caracteres seja lido, o que ocorrer primeiro
   while((fgets(linha, 256, arquivo_in)) != NULL){
        DADOS* registro = split_linha(arquivo_in, linha); //Função que separa os campos da linha e retorna um registro com os campos preenchidos

        //Printar para conferência
        // printf("Removido: %c\n", registro->removido);
        // printf("Prox reg: %ld\n", registro->prox_reg);
        // printf("Id: %d\n", registro->id);
        // printf("Idade: %d\n", registro->idade);
        // printf("TAM Nome: %d\n", registro->tam_Nome);
        // printf("Nome: %s\n", registro->nome);
        // printf("TAM nacionalidade: %d\n", registro->tam_Nacionalidade);
        // printf("Nacionalidade: %s\n", registro->nacionalidade);
        // printf("TAM clube: %d\n", registro->tam_Clube);
        // printf("Clube: %s\n", registro->clube);
        // printf("Tamanho registro: %d\n\n", registro->tamanho_registro);
        
        escrever_registro_dados(registro, arquivo_out);
        //Contador para o próximo byteoffset
        prox_reg += registro->tamanho_registro;

        //Libera a memória alocada para o registro
        apagar_registro(&registro);

        count_registros++;

        

    }
    //Fecha o arquivo de entrada
    fclose(arquivo_in);

    //Atualiza o cabeçalho do arquivo binário (status e numero de registros disponíveis)
    cabecalho->n_reg_disponiveis = count_registros;
    cabecalho->status = '1';
    cabecalho->prox_reg_disponivel = prox_reg;

    fseek(arquivo_out, 0, SEEK_SET);
    escrever_cabecalho(arquivo_out, cabecalho);
    apagar_cabecalho(&cabecalho);

    // //Printar cabeçalho para conferência
    // printf("Staus: %c\n", cabecalho->status);
    // printf("Reg disp: %d\n", cabecalho->n_reg_disponiveis);
    // printf("Reg indisp: %d\n", cabecalho->n_reg_removidos);
    // printf("Topo: %lld\n", cabecalho->topo);
    // printf("Prox reg disp: %lld\n", cabecalho->prox_reg_disponivel);

    //Fecha o arquivo binário
    fclose(arquivo_out);

    //Exigência do trabalho
    binarioNaTela(arquivo_out_name);
    return;
}

void funcionalidade2(void){
    //Tentativa de abrir o arquivo binário solicitado pelo usuário
    char nome_arquivo_binario[50];
    scanf("%s", nome_arquivo_binario);
    FILE* arquivo_bin = abrir_arquivo(nome_arquivo_binario, "rb");
    if(arquivo_bin == NULL){
        return;
    }

    //Lemos os campos do cabeçalho para passar pelos dados (outra opção seria usar o fseek com o tamanho do registro de cabeçalho)
    fseek(arquivo_bin, 0, SEEK_SET);

    CABECALHO* cabecalho = ler_cabecalho(arquivo_bin);

    //Alocação do registro de dados
    DADOS* registro = (DADOS*) malloc(sizeof(DADOS));
    if (registro == NULL){
        printf("Erro ao alocar memória para o registro\n");
        fclose(arquivo_bin);
        exit(1);
    }

    ////////// LEITURA DOS REGISTROS DO ARQUIVO BINÀRIO E IMPRESSÃO//////////
    while(fread(&(registro->removido), sizeof(char), 1, arquivo_bin) != 0){

        fread(&(registro->tamanho_registro), sizeof(int), 1, arquivo_bin);

        //Se o registro não foi removido, lemos os campos restantes e imprimimos na tela
        if(registro->removido != '1'){
            ler_registro(arquivo_bin,registro);
            print_registro(registro);
        }
        else{
            //Se o registro foi removido, pulamos para o próximo registro
            fseek(arquivo_bin, registro->tamanho_registro, SEEK_CUR);
            }

        if(feof(arquivo_bin)){
            break;
        }

    }

    //Fechamento do registro binário e liberação da memória alocada para o registro
    fclose(arquivo_bin);
    apagar_registro(&registro);
    apagar_cabecalho(&cabecalho);
    return;
}

void funcionalidade3(){
    char nome_arquivo_binario[50],campo[20];
    int  n_buscas,n_campos,add = 1;
    //recebe o nome e abre o aquivo
    scanf("%s", nome_arquivo_binario);
    FILE* arquivo_bin = abrir_arquivo(nome_arquivo_binario, "rb");
    //recebe o número de buscas que serão realizadas
    scanf(" %d",&n_buscas);
    //aloca e testa o registro auxiliar
    DADOS* registro = (DADOS*) malloc(sizeof(DADOS));
    if (registro == NULL){
        printf("Erro ao alocar memória para o registro\n");
        fclose(arquivo_bin);
        exit(1);
    }
    //lê o cabeçalho para corrigir a posição do ponteiro do arquivo
    CABECALHO* cabecalho = ler_cabecalho(arquivo_bin);
    //aloca o vetor de registros de parâmetros das buscas
    DADOS** buscas = (DADOS**) malloc(n_buscas*sizeof(DADOS*));
    //aloca o vetor de listas de resultados das buscas
    BL** listas = (BL**) malloc(n_buscas*sizeof(BL*));
    for(int i=0;i<n_buscas;i++){
        //aloca os registros com os parâmetros da buscas
        buscas[i] = (DADOS*) malloc(sizeof(DADOS));
        //aloca listas para guardar os resultados das buscas
        listas[i] = (BL*) malloc(n_buscas*sizeof(BL));
        //inicializa as listas
        listas[i]->ini=NULL;
        listas[i]->fim=NULL;
        //inicializa os registros
        buscas[i]->id=-1;
        buscas[i]->idade= -1;
        buscas[i]->nome = (char*) malloc(sizeof(char)*30);
        strcpy(buscas[i]->nome,"$");
        buscas[i]->nacionalidade = (char*) malloc(sizeof(char)*30);
        strcpy(buscas[i]->nacionalidade,"$");
        buscas[i]->clube = (char*) malloc(sizeof(char)*30);
        strcpy(buscas[i]->clube,"$");
    }
    //percorre as buscas
    for(int i=0;i<n_buscas;i++){
        //recebe o número de parâmetros que essa busca terá
        scanf("%d",&n_campos);
        //preenche os parâmetros do registro
        for(int j=0;j<n_campos;j++){
            scanf("%s",campo);
            if(strcmp(campo,"id")==0){
                scanf(" %d",&buscas[i]->id);
            }
            else if(strcmp(campo,"idade")==0){
                scanf(" %d",&buscas[i]->idade);
            }
            else if(strcmp(campo,"nome")==0){
                scan_quote_string(buscas[i]->nome);
            }
            else if(strcmp(campo,"nacionalidade")==0){
                scan_quote_string(buscas[i]->nacionalidade);
            }
            else if(strcmp(campo,"clube")==0){
                scan_quote_string(buscas[i]->clube);
            }
        }
    }
    //percorre todos os registros do arquivo pulando os que estão marcados para remoção
    while(fread(&(registro->removido), sizeof(char), 1, arquivo_bin) != 0){
        fread(&(registro->tamanho_registro), sizeof(int), 1, arquivo_bin);
        if(registro->removido != '1'){
            ler_registro(arquivo_bin,registro);
            for(int i=0;i<n_buscas;i++){
                add=1;
                //desclassifica o registro se ele não cumprir os parâmetros da busca
                //o parâmetro só é levado em conta se ele não estiver vazio
                if(buscas[i]->id!=-1){
                    if(registro->id != buscas[i]->id){
                        add=0;
                    }
                }
                if(buscas[i]->idade!=-1){
                    if(registro->idade != buscas[i]->idade){
                        add=0;
                    }
                }
                if(strcmp(buscas[i]->nome,"$")!=0){
                    if(registro->tam_Nome == 0 || strcmp(buscas[i]->nome,registro->nome)!=0){
                        add=0;
                    }

                }
                if(strcmp(buscas[i]->nacionalidade,"$")!=0){
                    if(registro->tam_Nacionalidade == 0 ||strcmp(buscas[i]->nacionalidade,registro->nacionalidade)!=0){
                        add=0;
                    }
                    
                }
                if(strcmp(buscas[i]->clube,"$")!=0){
                    if(registro->tam_Clube == 0 ||strcmp(buscas[i]->clube,registro->clube)!=0){
                        add=0;
                    }
                    
                }
                //caso satisfaça os parâmetros insere uma cópia do registro auxiliar na lista de resultados
                if(add==1){
                    add_lista(listas[i],registro);
                }
               
            }
            //libera as strings utilizadas no registro auxiliar
            if(registro->tam_Nome!=0){
                    free(registro->nome);
                    registro->nome = NULL;
                }
                if(registro->tam_Nome!=0){
                    free(registro->nome);
                    registro->nome = NULL;
                }
                if(registro->tam_Nome!=0){
                    free(registro->nome);
                    registro->nome = NULL;
                }   
        }
        else{
        //Se o registro foi removido, pulamos para o próximo registro
            fseek(arquivo_bin, registro->tamanho_registro, SEEK_CUR);
        }

        if(feof(arquivo_bin)){
            break;
        }
    }
    //fecha o arquivo e libera o registro auxiliar
    fclose(arquivo_bin);
    apagar_registro(&registro);

    int count=0;
    //percorre pelas buscas
    for(int i=0;i<n_buscas;i++){
        printf("Busca %d\n\n",i+1);
        BN* aux=listas[i]->ini;
        //percorre e printa as listas com os resultados das buscas
        while(aux!=NULL){
            print_registro(aux->registro);
            aux=aux->prox;
            count++;   
        }
        if (count == 0){
            printf("Registro inexistente.\n\n");
        }
        //libera o registro dos parâmetros da busca e a lista dos resultados
        apagar_registro(&(buscas[i]));
        apagar_lista(&(listas[i]));
    }
    //libera os dois vetores utilizaos na busca
    free(buscas);
    buscas=NULL;
    free(listas);
    listas=NULL;

    return;
}