#include "funcionalidades_arvB.h"

//Definição da struct da árvore B
struct arvB{
    char status;
    int noRaiz;
    int proxRRN;
    int nroNiveis;
    char lixo[47]; //Caracteres para preenchimento "$" dos 60bytes de cada nó
};

//Definição da struct dos nós dessa árvore que conterão as informações dos registros de dados disponíveis 
struct no_Arvb{
    //Informações do nó
    int altura_No;
    int nroChaves;

    //Informações dos registros de indíce na árvore
    int chave1;
    long int boffset1;
    int chave2;
    long int boffset2;
    int chave3;
    long int boffset3;

    //Informações dos nós filhos em nível inferior
    int filho1;
    int filho2;
    int filho3;
    int filho4;
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

void funcionalidade7 (void){
    // Pega o input dos nomes dos arquivos de dados e index
    char arquivo_dados_name[50];
    char arquivo_index_name[50];
    scanf("%s", arquivo_dados_name);
    scanf("%s", arquivo_index_name);

    // Cria o arquivo de index no modo escrita binária
    FILE *arquivo_index = abrir_arquivo(arquivo_index_name, "w+b");
    if (arquivo_index == NULL) //Verifica se a abertura do arquivo foi bem-sucedida
    {
        printf("Indice");
        return;
    }

    // Abertura do arquivo de dados para leitura dos registros no modo binário
    FILE *arquivo_dados = abrir_arquivo(arquivo_dados_name, "rb");
    if (arquivo_dados == NULL)
    {
        fclose(arquivo_index);
        return;
    }

    // Ler o primeiro byte do arquivo de dados (status) para verificar se está corrompido ou não 
    CABECALHO *registro_cabecalho_dados = ler_cabecalho(arquivo_dados);
    char status = get_status(registro_cabecalho_dados);
    if (status == '0')
    {
        fclose(arquivo_dados);
        fclose(arquivo_index);
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Construção do arquivo de index por meio de uma estrutura de arvore 
    
    //Todo o processo de contrução da arvore acontece aqui (alocação das estruturas, leitura do arquivo de dados, 
    //inserção e escrita no arquivo de index, liberação da memória e reescrita do status do arquivo de indice para "0" e "1" quando finalizar)
    construcao_arvB(arquivo_dados, arquivo_index, registro_cabecalho_dados);

    // Libera a memória alocada para as estruturas utilizadas
    free(registro_cabecalho_dados);

    // Fecha os arquivos
    fclose(arquivo_dados);
    fclose(arquivo_index);

    // Impressão do arquivo de index e de dados na tela
    binarioNaTela(arquivo_index_name);
}

void funcionalidade8 (void){
    int n, id;
    long int alvo;
    

    // Pega o input dos nomes dos arquivos de dados e index
    char arquivo_dados_name[50];
    char arquivo_index_name[50];
    scanf("%s", arquivo_dados_name);
    scanf("%s", arquivo_index_name);
    

    // Cria o arquivo de index no modo escrita binária
    FILE *arquivo_index = abrir_arquivo(arquivo_index_name, "w+b");
    if (arquivo_index == NULL) //Verifica se a abertura do arquivo foi bem-sucedida
    {
        return;
    }

    // Abertura do arquivo de dados para leitura dos registros no modo binário
    FILE *arquivo_dados = abrir_arquivo(arquivo_dados_name, "rb");
    if (arquivo_dados == NULL)
    {
        fclose(arquivo_index);
        return;
    }

    CABECALHO *registro_cabecalho_dados = ler_cabecalho(arquivo_dados);
    char status = get_status(registro_cabecalho_dados);
    if (status == '0')
    {
        fclose(arquivo_dados);
        fclose(arquivo_index);
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    DADOS* aux = malloc(sizeof(DADOS));
    scanf(" %d",&n);

    for(int i = 0; i<n;i++){
        scanf(" %d");
        scanf(" %s");
        scanf(" %d",&id);
        rewind(arquivo_index);
        printf("busca %d\n\n", i+1);
        alvo = busca_arvB(arquivo_index,id);
        if(alvo != -1){
            fseek(arquivo_dados, alvo, SEEK_SET);
            ler_registro(arquivo_dados,aux);
            print_registro(aux);
        }
        else{
            printf("Registro inexistente.\n\n");
        }
    }

    //libera a memória
    free(registro_cabecalho_dados);
    free(aux);

    // Fecha os arquivos
    fclose(arquivo_dados);
    fclose(arquivo_index);

}

void funcionalidade9 (void){
    //declaração de variáveis usadas na busca
    int num_buscas = 0, num_campos = 0, comp, existente;
    long int alvo;
    char campo[15];

    // Pega o input dos nomes dos arquivos de dados e index
    char arquivo_dados_name[50];
    char arquivo_index_name[50];
    scanf("%s", arquivo_dados_name);
    scanf("%s", arquivo_index_name);

    // Cria o arquivo de index no modo escrita binária
    FILE *arquivo_index = abrir_arquivo(arquivo_index_name, "w+b");
    if (arquivo_index == NULL) //Verifica se a abertura do arquivo foi bem-sucedida
    {
        return;
    }

    // Abertura do arquivo de dados para leitura dos registros no modo binário
    FILE *arquivo_dados = abrir_arquivo(arquivo_dados_name, "rb");
    if (arquivo_dados == NULL)
    {
        fclose(arquivo_index);
        return;
    }

    CABECALHO *registro_cabecalho_dados = ler_cabecalho(arquivo_dados);
    char status = get_status(registro_cabecalho_dados);
    if (status == '0')
    {
        fclose(arquivo_dados);
        fclose(arquivo_index);
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    //construção do arquivo de index
    construcao_arvB(arquivo_dados, arquivo_index, registro_cabecalho_dados);

    //alocação dos vedores utilizados para comparação
    DADOS* parametros = (DADOS*) malloc(sizeof(DADOS));
    DADOS* aux = (DADOS*) malloc(sizeof(DADOS));

    //alocação dos campos variáveis do registro que guarda os parâmetros
    parametros->nome = (char*) malloc(sizeof(char)*30);
    parametros->nacionalidade = (char*) malloc(sizeof(char)*30);
    parametros->clube = (char*) malloc(sizeof(char)*30);
    
    for (int i = 0; i < num_buscas; i++)
    {
        existente = 0;
        scanf(" %d",&num_campos);
        //inicialização dos campos do registro que guarda os parâmetros
        parametros->id=-1;
        parametros->idade= -1;
        strcpy(parametros->nome,"$");
        strcpy(parametros->nacionalidade,"$");
        strcpy(parametros->clube,"$");
        //preenche os parâmetros que seram comparados do registro
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

        printf("busca %d\n\n", i+1);

        //checa se deve realizar a busca pelo index ou a busca sequencial
        if(parametros->id != -1){
            //realiza a busca sequencial
            alvo = busca_arvB(arquivo_index,parametros->id);
            if(alvo!=-1){
                //se o registro foi encontrado no indice, le o registro e procede a remoção
                fseek(arquivo_dados,alvo,SEEK_SET);
                fread(&(aux->removido), sizeof(char), 1, arquivo_dados);
                fread(&(aux->tamanho_registro), sizeof(int), 1, arquivo_dados);
                ler_registro(arquivo_dados,aux);

                //checa se o registro que acabou de ser lido deve ser removido com base nos outros possíveis parâmetros
                comp = comparar_registros(parametros,aux);
                    
                if(comp == 1){
                    print_registro(aux);
                    existente = 1;
                }
                //libera os campos variaveis do registro auxiliar caso tiverem sido alocados e não impressos
                if(aux->nome!=NULL){
                    free(aux->nome);
                    aux->nome=NULL;
                }
                if(aux->nacionalidade!=NULL){
                    free(aux->nacionalidade);
                    aux->nacionalidade=NULL;
                }
                if(aux->clube=NULL){
                    free(aux->clube);
                    aux->clube=NULL;
                }
                    

            }

        }
        else{
            //corrige a posição do arquivo de dados
            fseek(arquivo_dados,25,SEEK_SET);
            //percorre o arquivo de dados inteiramente
            while(fread(&(aux->removido), sizeof(char), 1, arquivo_dados) != 0){
                fread(&(aux->tamanho_registro), sizeof(int), 1, arquivo_dados);
                if(aux->removido!='1'){
                    //caso o registro não esteja já marcado como removido, lê o registro e checa se ele deve ser removido
                    ler_registro(arquivo_dados,aux);
                    comp = comparar_registros(parametros,aux);
                    
                    if(comp == 1){
                        existente = 1;
                        print_registro(aux);
                    }
                    //libera os campos variaveis do registro auxiliar caso tiverem sido alocados e não impressos
                    if(aux->nome!=NULL){
                        free(aux->nome);
                        aux->nome=NULL;
                    }
                    if(aux->nacionalidade!=NULL){
                        free(aux->nacionalidade);
                        aux->nacionalidade=NULL;
                    }
                    if(aux->clube=NULL){
                        free(aux->clube);
                        aux->clube=NULL;
                    }

                }
                else{
                //caso o registro já tenha sido removido
                fseek(arquivo_dados, (aux->tamanho_registro)-5, SEEK_CUR);
                }
            }
        }
        if(existente == 0){
            printf("Registro inexistente.\n\n");
        }
    }  

    free(registro_cabecalho_dados);
    free(aux);
    apagar_registro(&parametros);

     // Fecha os arquivos
    fclose(arquivo_dados);
    fclose(arquivo_index);

}
    

void funcionalidade10(void){
// Pega o input dos nomes dos arquivos de dados e index
    char arquivo_dados_name[50];
    char arquivo_index_name[50];
    scanf("%s", arquivo_dados_name);
    scanf("%s", arquivo_index_name);

    // Cria o arquivo de index no modo escrita binária
    FILE *arquivo_index = abrir_arquivo(arquivo_index_name, "w+b");
    if (arquivo_index == NULL) //Verifica se a abertura do arquivo foi bem-sucedida
    {
        return;
    }

    // Abertura do arquivo de dados para leitura dos registros no modo binário
    FILE *arquivo_dados = abrir_arquivo(arquivo_dados_name, "w+b");
    if (arquivo_dados == NULL)
    {
        fclose(arquivo_index);
        return;
    }

      // Fecha os arquivos
    fclose(arquivo_dados);
    fclose(arquivo_index);
}