//############################################################################
/* As funções definidas neste arquivo estão explicadas no arquivo "funcionalidades-trab1.h". 
Nesse código você encontrá comentários a nível de variáveis e procedimentos.
##############################################################################*/

/*MODULARIZAR: TODO o inicio de abertura de arquivo e final na liveração de memória, criação e cópia do vetor de index
  Melhorar: TIRAR REPETIÇÃO DAS STRUCTS DEFINIDAS*/

#include "funcionalidades_trab1.h"

// Variável de controle do número de registros no vetor de index
int count_reg = 0;

//Definição da estrutura do registro de cabeçalho do arquivo de índice
struct registro_cabecalho_index{
    char status;
};

//Definição da estrutura do registro de dados do arquivo de índice
struct registro_dados_index{
    int chave;
    long int byteoffset;
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

struct registro_cabecalho{
    char status;
    long int topo;
    long int prox_reg_disponivel;
    int n_reg_disponiveis;
    int n_reg_removidos;
};

// Incrementar a variável de controle do número de registros no vetor de index
int incrementar_count_reg(){
    count_reg++;
    return count_reg;
}

// Pegar o número de registros no vetor de index
int get_count_reg(){
    return count_reg;
}

// Função para liberar a memória alocada para os registros de index e dados
void liberar_memoria(CABECALHO_INDEX **registro_cabecalho_index, DADOS_INDEX **registro_index, DADOS **registro_dados){
    if(*registro_cabecalho_index != NULL)
        free(*registro_cabecalho_index);

    if(*registro_index != NULL)
        free(*registro_index);

    apagar_registro(registro_dados);
}

// Função para criar um registro de index do arquivo de dados
DADOS_INDEX* create_index(FILE *arquivo_index, FILE *arquivo_dados)
{
    char status = '0';
    int tamanho_reg = 0;
    count_reg = 0; //Reseta o tamanho do vetor de index

    // Inicializa o status do registro de index como 0 na abertura ("corropido")
    CABECALHO_INDEX *registro_cabecalho_index = (CABECALHO_INDEX *)malloc(sizeof(CABECALHO_INDEX));
    set_arquivo_index('0', registro_cabecalho_index, arquivo_index);

    // Inicializa o registro de dados e index
    DADOS_INDEX *registro_index = (DADOS_INDEX *)malloc(sizeof(DADOS_INDEX));
    DADOS *registro_dados = init_registro_dados();

    //Alocação e inicialização do vetor de indices
    DADOS_INDEX *vetor_index = criar_vetor(TAMANHO_VETOR_INDEX);

    /*Loop para pegar os registros do arquivo de dados e escrever no arquivo de índices aqueles que não estão lógicamente removidos*/
    while (fread(&status, sizeof(char), 1, arquivo_dados) != 0)
    {
        //
        fread(&tamanho_reg, sizeof(int), 1, arquivo_dados);

        // Se o registro não foi removido, lemos os campos restantes e imprimimos na tela
        if (status != '1')
        {
            registro_index->byteoffset = (ftell(arquivo_dados) - 5); 
            fread(&(registro_dados->prox_reg), sizeof(long int), 1, arquivo_dados);
            fread(&(registro_dados->id), sizeof(int), 1, arquivo_dados);
            registro_index->chave = getID(registro_dados);

            fseek(arquivo_dados, tamanho_reg - 17, SEEK_CUR);

            count_reg++;

            inserir_ordenado(vetor_index, registro_index, count_reg);
        }
        else
        {
            // Se o registro foi removido, pulamos para o próximo registro (tamanho deo registro - 5 bytes [campos removido e tamanho do registro])
            fseek(arquivo_dados, (tamanho_reg - 5), SEEK_CUR);
        }
    }

    // Libera a memória alocada para os registros
    liberar_memoria(&registro_cabecalho_index, &registro_index, &registro_dados);

    return vetor_index;
}

// Create index file
// Para ordenar: Podemos inserir tudo em uma lista ordenada e depois escrever no arquivo
void funcionalidade4()
{
    // Auxiliador para pegar o tamanho do registro de dados que está sendo lido
    int tam = 0;

    // Pega o input dos nomes dos arquivos de dados e index
    char arquivo_dados_name[50];
    char arquivo_index_name[50];
    scanf("%s", arquivo_dados_name);
    scanf("%s", arquivo_index_name);

    // Cria o arquivo de index no modo escrita binária
    FILE *arquivo_index = abrir_arquivo(arquivo_index_name, "wb");
    if (arquivo_index == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Abertura do arquivo de dados para leitura dos registros
    FILE *arquivo_dados = abrir_arquivo(arquivo_dados_name, "rb");
    if (arquivo_dados == NULL)
    {
        fclose(arquivo_index);
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Ler o primeiro byte do arquivo de dados para verificar se está corrompido
    CABECALHO *registro_cabecalho_dados = ler_cabecalho(arquivo_dados);
    char status = get_status(registro_cabecalho_dados);
    if (status == '0')
    {
        fclose(arquivo_dados);
        fclose(arquivo_index);
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Construção do arquivo de index
    DADOS_INDEX* vetor_index = create_index(arquivo_index, arquivo_dados); //A função create index retorna um vetor de registros de index para que possamos utilizada em outras funcionalidades (5 e 6)
    escrever_vetor_index(vetor_index, arquivo_index);

    // Reescrever status do arquivo de index para 1
    fseek(arquivo_index, 0, SEEK_SET); // Resetar o ponteiro do arquivo para o início

    // Reescrita do status do arquivo de index para 1 (não corrompido)
    // Colocamos aqui e não em create_index pois a função é reutilizada em outras funcionalidades e não podemos reescrever até inserir/remover todos os indices necessários
    CABECALHO_INDEX *registro_cabecalho_index = (CABECALHO_INDEX *)malloc(sizeof(CABECALHO_INDEX));
    set_arquivo_index('1', registro_cabecalho_index, arquivo_index);

    apagar_vetor(&vetor_index);
    free(registro_cabecalho_dados);
    free(registro_cabecalho_index);
    fclose(arquivo_dados);
    fclose(arquivo_index);

    binarioNaTela(arquivo_index_name);
}

void funcionalidade5(void)
{
    int num_remover = 0, num_campos = 0, rem;
    long int cur_byte_offset = 0;
    char campo[15];
    

    // Pega o input dos nomes dos arquivos de dados e index
    char arquivo_dados_name[50];
    char arquivo_index_name[50];
    scanf("%s", arquivo_dados_name);
    scanf("%s", arquivo_index_name);

    scanf("%d", &num_remover);

    // Cria o arquivo de index no modo escrita binária
    FILE *arquivo_index = abrir_arquivo(arquivo_index_name, "wb");
    if (arquivo_index == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Abertura do arquivo de dados para leitura dos registros
    FILE *arquivo_dados = abrir_arquivo(arquivo_dados_name, "r+b"); //ABre arq binario para leitura e escrita
    if (arquivo_dados == NULL)
    {
        fclose(arquivo_index);
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Ler o primeiro byte do arquivo de dados para verificar se está corrompido
    CABECALHO *registro_cabecalho_dados = ler_cabecalho(arquivo_dados);
    char status = get_status(registro_cabecalho_dados);
    if (status == '0')
    {
        fclose(arquivo_dados);
        fclose(arquivo_index);
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Criação do arquivo de index (não escreve na memória ainda)
    DADOS_INDEX* vetor_index = create_index(arquivo_index, arquivo_dados); // Puxa o arquivo de index para a memória principal por meio de um vetor de registros


    DADOS* parametros = (DADOS*) malloc(sizeof(DADOS));
    DADOS* aux = (DADOS*) malloc(sizeof(DADOS));

    parametros->id=-1;
    parametros->idade= -1;
    parametros->nome = (char*) malloc(sizeof(char)*30);
    strcpy(parametros->nome,"$");
    parametros->nacionalidade = (char*) malloc(sizeof(char)*30);
    strcpy(parametros->nacionalidade,"$");
    parametros->clube = (char*) malloc(sizeof(char)*30);
    strcpy(parametros->clube,"$");
    
    for (int i = 0; i < num_remover; i++)
    {
        scanf(" %d",&num_campos);
        parametros->id=-1;
        parametros->idade= -1;
        strcpy(parametros->nome,"$");
        strcpy(parametros->nacionalidade,"$");
        strcpy(parametros->clube,"$");
        //preenche os parâmetros do registro
        for(int j=0;j<num_campos;j++){
            scanf(" %s",campo);
            if(strcmp(campo,"id")==0){
                scanf(" %d",&parametros->id);
            }
            else if(strcmp(campo,"idade")==0){
                scanf(" %d",&parametros->idade);
            }
            else if(strcmp(campo,"nomeJogador")==0){
                scan_quote_string(parametros->nome);
            }
            else if(strcmp(campo,"nacionalidade")==0){
                scan_quote_string(parametros->nacionalidade);
            }
            else if(strcmp(campo,"nomeClube")==0){
                scan_quote_string(parametros->clube);
            }
        }
        if(parametros->id != -1){
            cur_byte_offset = busca_binaria_index(vetor_index,parametros->id,0,count_reg-1);
            if(cur_byte_offset!=-1){
                fseek(arquivo_dados,cur_byte_offset,SEEK_SET);
                fread(&(aux->removido), sizeof(char), 1, arquivo_dados);
                fread(&(aux->tamanho_registro), sizeof(int), 1, arquivo_dados);
                ler_registro(arquivo_dados,aux);
                rem = 1;
                if(parametros->idade !=-1){
                    if(parametros->idade != aux->idade){
                        rem=0;
                    }
                }
                if(strcmp(parametros->nome,"$")!=0){
                    if((aux->tam_Nome==0)||(strcmp(parametros->nome,aux->nome)!=0)){
                        rem=0;
                    }
                }
                if(strcmp(parametros->nacionalidade,"$")!=0){
                    if((aux->tam_Nacionalidade==0)||(strcmp(parametros->nacionalidade,aux->nacionalidade)!=0)){
                    rem=0;
                    }
                }
                if(strcmp(parametros->clube,"$")!=0){
                    if((aux->tam_Clube==0)||strcmp(parametros->clube,aux->clube)!=0){
                    rem=0;
                    }
                }
                    
                if(rem == 1){
                    remover_dados(aux,arquivo_dados,registro_cabecalho_dados,cur_byte_offset);
                    remover_ordenado(vetor_index,aux->id,0,count_reg-1,count_reg);
                    count_reg--;

                }
                if(aux->tam_Nome!=0){
                    free(aux->nome);
                    aux->nacionalidade=NULL;
                }
                if(aux->tam_Nacionalidade!=0){
                    free(aux->nacionalidade);
                    aux->nacionalidade=NULL;
                }
                if(aux->tam_Clube!=0){
                    free(aux->clube);
                    aux->clube=NULL;
                }
                    

            }

        }
        else{
            fseek(arquivo_dados,25,SEEK_SET);
            cur_byte_offset = 25;
            while(fread(&(aux->removido), sizeof(char), 1, arquivo_dados) != 0){
                fread(&(aux->tamanho_registro), sizeof(int), 1, arquivo_dados);
                if(aux->removido!='1'){
                    ler_registro(arquivo_dados,aux);
                    rem = 1;
                    if(parametros->idade !=-1){
                        if(parametros->idade != aux->idade){
                            rem=0;
                        }
                    }
                    if(strcmp(parametros->nome,"$")!=0){
                        if((aux->tam_Nome==0)||(strcmp(parametros->nome,aux->nome)!=0)){
                            rem=0;
                        }
                    }
                    if(strcmp(parametros->nacionalidade,"$")!=0){
                        if((aux->tam_Nacionalidade==0)||(strcmp(parametros->nacionalidade,aux->nacionalidade)!=0)){
                        rem=0;
                        }
                    }
                    if(strcmp(parametros->clube,"$")!=0){
                        if((aux->tam_Clube==0)||strcmp(parametros->clube,aux->clube)!=0){
                        rem=0;
                        }
                    }
                    
                    if(rem == 1){
                        remover_dados(aux,arquivo_dados,registro_cabecalho_dados,cur_byte_offset);
                        remover_ordenado(vetor_index,aux->id,0,count_reg-1,count_reg);
                        count_reg--;

                    }
                     if(aux->tam_Nome!=0){
                        //free(aux->nome);
                        aux->nacionalidade=NULL;
                    }
                    if(aux->tam_Nacionalidade!=0){
                        //free(aux->nacionalidade);
                        aux->nacionalidade=NULL;
                    }
                    if(aux->tam_Clube!=0){
                        //free(aux->clube);
                        aux->clube=NULL;
                    }

                }
                else{
                fseek(arquivo_dados, (aux->tamanho_registro)-5, SEEK_CUR);
                }
                cur_byte_offset += aux->tamanho_registro;
            }
        }  

        
        
    }
    //rescrever cabecalho
    fseek(arquivo_dados,0,SEEK_SET);
    escrever_cabecalho(arquivo_dados,registro_cabecalho_dados);

    //Escrever os registros no arquivo de indice
    escrever_vetor_index(vetor_index, arquivo_index);

    //Reescrever status do arquivo de indice aqui
    fseek(arquivo_index, 0, SEEK_SET); // Resetar o ponteiro do arquivo para o início
    CABECALHO_INDEX *registro_cabecalho_index = (CABECALHO_INDEX *)malloc(sizeof(CABECALHO_INDEX)); //Não é necessario alocar e passar o registro,
    //mas fica mais claro o que estamos fazendo do que só escrever um char no arquivo de indice.
    set_arquivo_index('1', registro_cabecalho_index, arquivo_index);
    
    //Libera memória
    apagar_vetor(&vetor_index);
    free(registro_cabecalho_dados);
    //apagar_registro(&aux);
    apagar_registro(&parametros);
    fclose(arquivo_dados);
    fclose(arquivo_index);

    // Impressão do arquivo de index e de dados na tela
    binarioNaTela(arquivo_dados_name);
    binarioNaTela(arquivo_index_name);
}

void funcionalidade6(void)
{
    int num_insertons = 0;

    // Pega o input dos nomes dos arquivos de dados e index
    char arquivo_dados_name[50];
    char arquivo_index_name[50];
    scanf("%s", arquivo_dados_name);
    scanf("%s", arquivo_index_name);

    scanf("%d", &num_insertons);

    // Cria o arquivo de index no modo escrita binária
    FILE *arquivo_index = abrir_arquivo(arquivo_index_name, "wb");
    if (arquivo_index == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Abertura do arquivo de dados para leitura dos registros
    FILE *arquivo_dados = abrir_arquivo(arquivo_dados_name, "r+b"); //ABre arq binario para leitura e escrita
    if (arquivo_dados == NULL)
    {
        fclose(arquivo_index);
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Ler o primeiro byte do arquivo de dados para verificar se está corrompido
    fseek(arquivo_dados, 0, SEEK_SET);
    CABECALHO *registro_cabecalho_dados = ler_cabecalho(arquivo_dados);
    char status = get_status(registro_cabecalho_dados);
    if (status == '0')
    {
        fclose(arquivo_dados);
        fclose(arquivo_index);
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Criação do arquivo de index (não escreve no arquivo ainda)
    DADOS_INDEX* vetor_index = create_index(arquivo_index, arquivo_dados); // Puxa o arquivo de index para a memória principal por meio de um vetor de registros
    
    //Alocando as estruturas de dados a serem utilizadas.
    DADOS_INDEX* registro_index = (DADOS_INDEX*)malloc(sizeof(DADOS_INDEX));

    for (int i = 0; i < num_insertons; i++)
    {
        // Alocar e ler o registro de dados do input
        DADOS* registro_dados = ler_input_dados();

        printf("\nRegistro lido: %d\n", registro_dados->id);
        printf("Registro lido: %d\n", registro_dados->idade);
        printf("Registro lido: %s\n", registro_dados->nome);
        printf("Registro lido: %s\n", registro_dados->nacionalidade);
        printf("Registro lido: %s\n", registro_dados->clube);
        printf("Tam registro: %d\n", registro_dados->tamanho_registro);
        printf("Prox reg: %ld\n", registro_dados->prox_reg);

        printf("\nTopo: %ld\n", getTopo(registro_cabecalho_dados));
        printf("Prox: %ld\n", getProxRegDisponivel(registro_cabecalho_dados));
        printf("N Reg: %d\n", getnRegDisponiveis(registro_cabecalho_dados));
        printf("N Rem: %d\n", getnRemovidos(registro_cabecalho_dados));

        // LÓGICA DE REAPROVEITAMENTO DE ESPAÇO
        if (getTopo(registro_cabecalho_dados) == -1 && getnRemovidos(registro_cabecalho_dados) == 0) 
        {
            //Verefica que o item que está sendo ordenado já existe no arquivo de indice
            if(busca_binaria_index(vetor_index, registro_dados->id, 0, count_reg-1)==-1){
                printf("Registro ainda não inserido!\n");
                inserir_final(arquivo_dados, arquivo_index, registro_dados, registro_cabecalho_dados, vetor_index, registro_index);
            }
            else{
                printf("Registro já inserido!\n");
            }
        }
        else
        {
            printf("Tenho reaproveitamento de espaço\n");
            //Verifica se o item que está sendo ordenado já existe no arquivo de indice
            if(busca_binaria_index(vetor_index, registro_dados->id, 0, count_reg-1)==-1){
                printf("Registro ainda não inserido!\n");

                // Como há registros logicamente removidos, temos que encontrar o endreço para inserção seguindo a estratégia best-fit:
                long int endereco = best_fit(arquivo_dados, registro_dados, registro_cabecalho_dados, getTopo(registro_cabecalho_dados)); 

                //Best-fit pode não encontrar nenhum endereço viável de inserção. Nesse caso, inserimos no final mesmo:
                if(endereco == -1){
                    inserir_final(arquivo_dados, arquivo_index, registro_dados, registro_cabecalho_dados, vetor_index, registro_index);
                }
                else{
                    insercao_dinamica(arquivo_dados, arquivo_index, registro_dados, registro_cabecalho_dados, vetor_index, registro_index, endereco);
                }
            }
            else{
                printf("Registro já inserido!\n");
            }
        }
        //apagar_registro(&registro_dados); //Arrumar essa função
    }

    //Escrever os registros no arquivo de indice
    escrever_vetor_index(vetor_index, arquivo_index);

    //Reescrever status do arquivo de indice aqui
    fseek(arquivo_index, 0, SEEK_SET); // Resetar o ponteiro do arquivo para o início
    CABECALHO_INDEX *registro_cabecalho_index = (CABECALHO_INDEX *)malloc(sizeof(CABECALHO_INDEX)); //Não é necessario alocar e passar o registro,
    //mas fica mais claro o que estamos fazendo do que só escrever um char no arquivo de indice.
    set_arquivo_index('1', registro_cabecalho_index, arquivo_index);

    // Liberar memória
    apagar_vetor(&vetor_index);
    free(registro_cabecalho_dados);
    free(registro_index);
    fclose(arquivo_dados);
    fclose(arquivo_index);

    // Impressão do arquivo de index e dados na tela
    binarioNaTela(arquivo_dados_name);
    binarioNaTela(arquivo_index_name);
}


