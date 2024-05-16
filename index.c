#include "index.h"
int count_reg = 0;

struct registro_cabecalho_index
{
    char status;
};

struct registro_dados_index
{
    int chave;
    long long int byteoffset;
};

// Função para setar o status do arquivo de index
void set_arquivo_index(char status, CABECALHO_INDEX *cabecalho, FILE *arquivo)
{
    cabecalho->status = status;
    fwrite(&cabecalho->status, sizeof(char), 1, arquivo);
}

// Verificar na inserção e remoção se o arquivo de index está comprometido
void check_arquivo_index(CABECALHO_INDEX *cabecalho, FILE *arquivo)
{
    fseek(arquivo, 0, SEEK_SET);
    fread(&cabecalho->status, sizeof(char), 1, arquivo);
}

// Função para escrever um registro de index no arquivo
void escrever_registro_index(DADOS_INDEX *registro, FILE *arquivo)
{
    fwrite(&registro->chave, sizeof(int), 1, arquivo);
    fwrite(&registro->byteoffset, sizeof(long long int), 1, arquivo);
}

// Função para criar um registro de index do arquivo de dados
DADOS_INDEX* create_index(FILE *arquivo_index, FILE *arquivo_dados)
{
    char status = '0';
    int tamanho_reg = 0;

    // Inicializa o status do registro de index como 0 na abertura ("corropido")
    CABECALHO_INDEX *registro_cabecalho_index = (CABECALHO_INDEX *)malloc(sizeof(CABECALHO_INDEX));
    set_arquivo_index('0', registro_cabecalho_index, arquivo_index);

    // Inicializa o registro de dados e index
    DADOS_INDEX *registro_index = (DADOS_INDEX *)malloc(sizeof(DADOS_INDEX));
    DADOS *registro_dados = init_registro_dados();

    DADOS_INDEX *vetor_index = criar_vetor(TAMANHO_VETOR_INDEX);

    /*For para pegar dados, pular o numero de bytes do registro, escreve apaga registrom de index*/
    while (fread(&status, sizeof(char), 1, arquivo_dados) != 0)
    {

        fread(&tamanho_reg, sizeof(int), 1, arquivo_dados);

        // Se o registro não foi removido, lemos os campos restantes e imprimimos na tela
        if (status != '1')
        {
            registro_index->byteoffset = (ftell(arquivo_dados) - 5); //Lógica do fteell errada (pegar o primeio bayte, nao ler e pegar dps)
            ler_registro(arquivo_dados, registro_dados);
            registro_index->chave = getID(registro_dados);

            count_reg++;

            inserir_ordenado(vetor_index, registro_index, count_reg);
        }
        else
        {
            // Se o registro foi removido, pulamos para o próximo registro (tamanho deo registro - 5 bytes [campos removido e tamanho do registro])
            fseek(arquivo_dados, (tamanho_reg - 5), SEEK_CUR);
        }
    }

    for (int i = 0; i < count_reg; i++)
    {
        if (registro_index->chave == -1)
        {
            printf("Registro não existe\n");
            continue;
        }
        else
        {
            escrever_registro_index(&vetor_index[i], arquivo_index);
        }
    }

    // Libera a memória alocada para os registros
    free(registro_cabecalho_index);
    free(registro_index);
    apagar_registro(&registro_dados); // Libera os campos de tamanho variavel alocados

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
    int num_remover = 0;
    scanf("%d", &num_remover);

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

    // Criação do arquivo de index 
    DADOS_INDEX* vetor_index = create_index(arquivo_index, arquivo_dados); // Puxa o arquivo de index para a memória principal por meio de um vetor de registros

    for (int i = 0; i < num_remover; i++)
    {
        // Alocar e ler o registro de dados do input
        //Fazer count--

        //O resto é com o mano augusto
        
    }

    fseek(arquivo_index, 0, SEEK_SET); // Resetar o ponteiro do arquivo para o início
    CABECALHO_INDEX *registro_cabecalho_index = (CABECALHO_INDEX *)malloc(sizeof(CABECALHO_INDEX)); //Não é necessario alocar e passar o registro,
    //mas fica mais claro o que estamos fazendo do que só escrever um char no arquivo de indice.
    set_arquivo_index('1', registro_cabecalho_index, arquivo_index);
    
    //Libera memória
    apagar_vetor(&vetor_index);
    free(registro_cabecalho_dados);
    fclose(arquivo_dados);
    fclose(arquivo_index);

    // Impressão do arquivo de index e de dados na tela
    binarioNaTela(arquivo_dados_name);
    binarioNaTela(arquivo_index_name);
}

void funcionalidade6(void)
{
    int num_insertons = 0;
    scanf("%d", &num_insertons);

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

    // Criação do arquivo de index
    DADOS_INDEX* vetor_index = create_index(arquivo_index, arquivo_dados); // Puxa o arquivo de index para a memória principal por meio de um vetor de registros
    
    imprimir_vetor(vetor_index, count_reg);
    DADOS_INDEX* registro_index = (DADOS_INDEX*)malloc(sizeof(DADOS_INDEX));
    DADOS* registro_dados = (DADOS*)malloc(sizeof(DADOS_INDEX));

    for (int i = 0; i < num_insertons; i++)
    {
        // Alocar e ler o registro de dados do input

        // LÓGICA DE REAPROVEITAMENTO DE ESPAÇO
        if (1)
        { // get_nRemovidos(registro_cabecalho_dados) == 0 ){ //oU TOPO == -1
            // Se não houver registros logicamente removidos, inserir no fim do arquivo:

            // Inserir reg index no vetor de registros (provavelmten vai ter que shiftar o vetor pra inserir ordenado) -> VERIFICAR SE ESSE CARA JÁ EXISTE NO VETOR E, SE SIM, NÃO INSERIR

            // Uso o registro_cabecalho_dados->prox_reg_disponivel (byteoffset do final) e escreve o registro de dados lá
            // Att esse cara

            // Att o cabelçalho do arq de dados e reescrever ele(n registro depóniveis, prox_reg_disponivel)
            //Fazer count++
        }
        else
        {
            // Se houver registros logicamente removidos, inserir no bestfit

            // Bestfit: Percorre os registros lógicamnet eremovidos a partir do topo da lista, procurando o primeiro registro que caiba o novo registro (vai salvando o byteoffset do registro anterior para quando achar
            // o registro que caiba, inserir o novo registro no lugar do registro removido e atualizar o ponteiro do registro removido para o próximo registro removido)

            // Se achar o best-fit nas busca sequencial =
            // Inserir reg index no vetor de registros (provavelmte vai ter que shiftar o vetor pra inserir ordenado) -> VERIFICAR SE ESSE CARA JÁ EXISTE NO VETOR E, SE SIM, NÃO INSERIR
            //(Byteoffset é o byte atual e busca binária?)

            // Corrige o endereçamento dos registros lógicamente removidos no arquivo de dados(reescreve o proximo do reg anterior para o proximo do reg atual) -> TALVEZ O TOPO DA LISTA DE REMOVIDOS TENHA QUE SER ATUALIZADO
            // Insere os dados no endereço encontrado e seta para "$" os bytes restantes

            // Att o cabeçalho do arq de dados e reescrever ele(n registro depóniveis, n registro removidos)

            // Se não achar um que caiba: Insere no fim seguindo o algoritmo acima definido
        }
    }

    fseek(arquivo_index, 0, SEEK_SET); // Resetar o ponteiro do arquivo para o início
    CABECALHO_INDEX *registro_cabecalho_index = (CABECALHO_INDEX *)malloc(sizeof(CABECALHO_INDEX));
    set_arquivo_index('1', registro_cabecalho_index, arquivo_index);

    // Liberar memória
    apagar_vetor(&vetor_index);
    free(registro_cabecalho_dados);
    free(registro_dados);
    free(registro_index);
    fclose(arquivo_dados);
    fclose(arquivo_index);

    // Impressão do arquivo de index e dados na tela
    binarioNaTela(arquivo_dados_name);
    binarioNaTela(arquivo_index_name);
}

void teste_vetor()
{
    int command, tamanho = 0;
    int id;
    long long int boff;
    scanf("%d", &command);
    DADOS_INDEX *registro = (DADOS_INDEX *)malloc(sizeof(DADOS_INDEX));
    // interface(command);
    DADOS_INDEX *vetor = criar_vetor(500);
    for (int i = 0; i < command; i++)
    {
        scanf("%d %lld", &id, &boff);
        registro->chave = id;
        registro->byteoffset = boff;
        tamanho++;
        inserir_ordenado(vetor, registro, tamanho);
    }
    imprimir_vetor(vetor, tamanho);
}


/*MODULARIZAR: TODO o inicio de abertura de arquivo e final na liveração de memória, criação e cópia do vetor de index
  Melhorar: TIrar a variavel global para pegar o tamanho*/
