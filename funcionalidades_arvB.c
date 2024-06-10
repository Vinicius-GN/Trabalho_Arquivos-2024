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
    FILE *arquivo_index = abrir_arquivo(arquivo_index_name, "wb");
    if (arquivo_index == NULL) //Verifica se a abertura do arquivo foi bem-sucedida
    {
        return;
    }

    // Abertura do arquivo de dados para leitura dos registros no modo binário
    FILE *arquivo_dados = abrir_arquivo(arquivo_dados_name, "r+b");
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
    //Recuperação de dados na árvore B utilizando ID (simples)
}

void funcionalidade9 (void){
    //Recuperação dos DADOS de registros que satisfaçam os campos solicitados (parece ser simples)
}

void funcionalidade10 (void){
    //Inserção de novos registros na arv_B e arquivo de dados (A função de inserção com reaporveitamento 
    //de espaço já esta pronta e a de inserção na árvore B provavelmente vai estar)
}