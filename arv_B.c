#include "arv_B.h"

//Trabalho prático 2 da disciplina de Organização de Arquivos

//############################################################################
/* As funções definidas neste arquivo estão explicadas no arquivo "arv_B.h". 
Nesse código você encontrá comentários a nível de variáveis e procedimentos.*/
//############################################################################

/*
##############################################################
    Alunos: Vinicius Gustierrez Neves          N°USP: 14749363
            Augusto Cavalcante Barbosa Pereira N°USP: 14651531
##############################################################
*/

//Definição da estrutura de cabeçalho da árvore B
struct arvB{
    char status; //Atualizado no inicio e no final da execução de "contrucao_arvB"
    int noRaiz; // Atualizado quando há promoção na raiz
    int proxRRN; //Atualizado quando há split de nó ou com a criação da raiz
    int nroChaves; //Atualizado a cada inserção de registros
    char lixo[47]; //Caracteres para preenchimento "$" dos 60bytes de cada nó
};

//Definição da estrutura dos nós dessa árvore que conterão as informações dos registros de dados disponíveis 
struct no_Arvb{
    //Informações do nó
    int altura_No;
    int nroChaves;

    //Informações dos registros de indíce na árvore
    int C1;
    long int PR1;
    int C2;
    long int PR2;
    int C3;
    long int PR3;

    //Informações dos nós filhos em nível inferior
    int P1;
    int P2;
    int P3;
    int P4;
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

//Definição da estrutura de cabeçalho do arquivo de dados
struct registro_cabecalho{
    char status;
    long int topo;
    long int prox_reg_disponivel;
    int n_reg_disponiveis;
    int n_reg_removidos;
};

//Estrutura de dados auxiliar 
struct promocao_no{
    int chavePromovida;
    long int byteOffsetPromovido;
    int novoNo; //RRN do novo nó (preciso já ter escrito ele no arquivo para saber o RRN dele)
    bool houvePromocao; //Flag para marcar se houve promoção ou não recursivamente
};


ARVB * init_arvB(void){
    //Inicializa a árvore B
    ARVB* arv = (ARVB*)malloc(sizeof(ARVB));

    //Inicializa os campos da árvore B
    arv->status = '0';
    arv->noRaiz = -1;
    arv->proxRRN = 0;
    arv->nroChaves = 0;
    for(int i = 0; i < 47; i++){       //Completa o restante dos 60 bytes do nó com '$'  
        arv->lixo[i] = '$';            //Já que o arquivo de índice é composto por páginas de disco de 60 bytes cada
    }

    return arv;
}

NO_ARVB * init_no(void){
    //Inicializa um nó da árvore B
    NO_ARVB* no = (NO_ARVB*)malloc(sizeof(NO_ARVB));

    //Inicializa os campos do nó inicialmente
    no->altura_No = -1; 
    no->nroChaves = 0;
    no->C1 = -1;
    no->PR1 = -1;
    no->C2 = -1;
    no->PR2 = -1;
    no->C3 = -1;
    no->PR3 = -1;
    no->P1 = -1;
    no->P2 = -1;
    no->P3 = -1;
    no->P4 = -1;

    //Retorna o nó inicializado
    return no;
}


ARVB* ler_cabecalho_arvB(FILE* arquivo){
    //Aloca memória para o cabeçalho da árvore B
    ARVB* cabecalho = (ARVB*)malloc(sizeof(ARVB));

    //Lê o cabeçalho da árvore B
    fread(&(cabecalho->status), sizeof(char), 1, arquivo);
    fread(&(cabecalho->noRaiz), sizeof(int), 1, arquivo);
    fread(&(cabecalho->proxRRN), sizeof(int), 1, arquivo);
    fread(&(cabecalho->nroChaves), sizeof(int), 1, arquivo);
    //Lê o lixo de preenchimento do cabeçalho
    //fread(&(cabecalho->lixo), sizeof(char), 47, arquivo);

    //Retorna o cabeçalho lido
    return cabecalho;
}

void escrever_cabecalho_arvB(FILE* arquivo, ARVB* arvore){
    //Escreve o cabeçalho da árvore B
    fwrite(&(arvore->status), sizeof(char), 1, arquivo);
    fwrite(&(arvore->noRaiz), sizeof(int), 1, arquivo);
    fwrite(&(arvore->proxRRN), sizeof(int), 1, arquivo);
    fwrite(&(arvore->nroChaves), sizeof(int), 1, arquivo);
    fwrite(&(arvore->lixo), sizeof(char), 47, arquivo);
}

void set_status_arvB(FILE *arquivo, char status, ARVB *arv){
    //Altera o status do arquivo de índices
    arv->status = status;
    fseek(arquivo, 0, SEEK_SET);

    //Reescreve o cabeçalho no arquivo de índices
    escrever_cabecalho_arvB(arquivo, arv);
}

PROMOCAO split_no(FILE* arquivo, ARVB* arvore, NO_ARVB* no_atual, int RRN, int chave, int pos, long int byteoffset, PROMOCAO promocao_recursiva){

    //Inicialização do novo nó a ser criado
    NO_ARVB* no_novo = init_no();

    //Determinação do RRN do novo nó
    int RRN_novo = arvore->proxRRN; //RRN do novo nó
    arvore->proxRRN = arvore->proxRRN + 1; //Incrementa o próximo RRN disponível

    //Preenchimento do novo nó
    no_novo-> altura_No = no_atual->altura_No; //A altura do novo nó é a mesma do nó atual
    no_novo->nroChaves = 1; //O novo nó (à direita) terá apenas uma chave no split, seguindo o algoritmo desejado

    //Estrutura de promoção do nó para retorno
    PROMOCAO promocao_de_no; 
    promocao_de_no.houvePromocao = true; //Houve promoção no nó (resultante do Split)

    //Tratando as possibilidades de split por meio do valor de "pos"
    //Se pos = 1, a chave a ser inserida é a menor de todas e o nó está cheio (tem quue shifitar e splitar)
    if(pos == 1){

        //Inserção da chave do novo nó (antiga chave 3 do nó splitado)
        no_novo->C1 = no_atual->C2;
        no_novo->PR1 = no_atual->PR2;
        no_novo->C2 = no_atual->C3;
        no_novo->PR2 = no_atual->PR3;
        //Passa as chaves para a direita também
        no_novo->P1 = no_atual->P2;
        no_novo->P2 = no_atual->P3;
        no_novo->P3 = no_atual->P4;

        //Dados do registro de indice a serem promovidos
        promocao_de_no.chavePromovida = no_atual->C1;
        promocao_de_no.byteOffsetPromovido = no_atual->PR1;

        //Shift de chave, boffset e filhos para a direita
        no_atual->C1 = chave; //Nova chave inserida
        no_atual->PR1 = byteoffset; //Novo byteoffset da chave inserida
        no_atual->P2 = promocao_recursiva.novoNo; //O filho mais à direita do nó atual é o novo nó criado na promoção de níveis inferirores
        //P1 fica igual
    }
    //Se pos = 2, a chave a ser inserida é a do meio e o nó está cheio (tem que shifitar e splitar)
    else if(pos == 2){

        //Inserção da chave do novo nó 
        no_novo->C1 = no_atual->C2;
        no_novo->PR1 = no_atual->PR2;
        no_novo->C2 = no_atual->C3;
        no_novo->PR2 = no_atual->PR3;
        //Passa as chaves para a direita também
        no_novo->P1 = promocao_recursiva.novoNo; //Novo nó produzido pelo split recursivo do nivel inferior
        no_novo->P2 = no_atual->P3;
        no_novo->P3 = no_atual->P4;

        //A chave inserida é promovida (ocuparia a posição 2, que é promovida)
        promocao_de_no.chavePromovida = chave;
        promocao_de_no.byteOffsetPromovido = byteoffset;
        //P1, P2 e C1 ficam iguais
    }
    //Se pos = 3, a chave a ser inserida é a penútima de todas e o nó está cheio (tem que shifitar e splitar)
    else if(pos == 3){

        //Inserção da chave do novo nó
        no_novo->C1 = chave;
        no_novo->PR1 = byteoffset;
        no_novo->C2 = no_atual->C3;
        no_novo->PR2 = no_atual->PR3;
        //Passa as chaves para a direita também
        no_novo->P1 = no_atual->P3;
        no_novo->P2 = promocao_recursiva.novoNo;
        no_novo->P3 = no_atual->P4;

        //Dados do registro de indice a serem promovidos
        promocao_de_no.chavePromovida = no_atual->C2;
        promocao_de_no.byteOffsetPromovido = no_atual->PR2;

        //P1, P2, C1 ficam iguais

    }
    //Se pos = 4, a chave a ser inserida é a maior de todas e o nó está cheio 
    else if(pos == 4){

        //Inserção da chave do novo nó
        no_novo->C1 = no_atual->C3;
        no_novo->PR1 = no_atual->PR3;
        no_novo->C2 = chave;
        no_novo->PR2 = byteoffset;
        //Passa as chaves para a direita também
        no_novo->P1 = no_atual->P3;
        no_novo->P2 = no_atual->P4;
        no_novo->P3 = promocao_recursiva.novoNo;

        //Dados do registro de indice a serem promovidos
        promocao_de_no.chavePromovida = no_atual->C2;
        promocao_de_no.byteOffsetPromovido = no_atual->PR2;

        //P1, P2, C1 ficam iguais
        
    }
    
   //Operações que sempre ocorrem para todos os casos (escolhendo a maior chave da direita para promoção)
    no_atual->C3 = -1; //Apaga a chave da pos3
    no_atual->PR3 = -1; //Apaga o byteoffset da chave de posição 3
    no_atual->C2 = -1; //Apaga a chave da pos2
    no_atual->PR2 = -1; //Apaga o byteoffset da chave de posição 2
    no_atual->P3 = -1; //O último filho do nó atual é sempre nulo no split
    no_atual->P4 = -1; //O último filho do nó atual é sempre nulo no split
    promocao_de_no.novoNo = RRN_novo; //RRN do novo nó alocado será colocado na recursão

    //Atualização do número de chaves dos nós
    no_novo->nroChaves = 2; //Incrementa o número de chaves do nó (normalmente 2)
    no_atual->nroChaves = 1; //Decrementa o número de chaves do nó 

    //Escreve os nós no arquivo de índices
    fseek(arquivo, RRN*TAMANHO_NO + TAMANHO_CABECALHO, SEEK_SET); //Vai até a página de disco correspondente ao RRN
    escrever_no_arvB(arquivo, no_atual); //Reescreve o nó atual
    fseek(arquivo, RRN_novo*TAMANHO_NO + TAMANHO_CABECALHO, SEEK_SET); //Vai até a página de disco correspondente ao RRN do novo nó
    escrever_no_arvB(arquivo, no_novo); //Escreve o novo nó

    //Libera a memória alocada para os nós
    apagar_no(&no_atual);
    apagar_no(&no_novo);
    return promocao_de_no;
}

void inserir_noInterno(FILE* arquivo, NO_ARVB* no, int RRN, int pos, int chave, long int byteoffset, int filho){
    //Insere a chave e o byteoffset na posição correta

    //Tratamento dos casos de inserção baseada na posição correta de inserção da chave
    if(pos == 1){
        //Shifta as chaves e byteoffset dos registros para a direita
        no->C3 = no->C2;
        no->PR3 = no->PR2;
        no->C2 = no->C1;
        no->PR2 = no->PR1;

        //Insere a chave e o byteoffset na posição correta
        no->C1 = chave;
        no->PR1 = byteoffset;

        //Shifta os filhos para a direita e salva o novo nó resultante do split da recursão
        no->P4 = no->P3;
        no->P3 = no->P2;
        no->P2 = filho;
    }
    else if(pos == 2){

        //Shifta as chaves e byteoffset dos registros para a direita
        no->C3 = no->C2;
        no->PR3 = no->PR2;

        //Insere a chave e o byteoffset na posição correta
        no->C2 = chave;
        no->PR2 = byteoffset;

        //Shifta os filhos para a direita e salva o novo nó resultante do split da recursão
        no->P4 = no->P3;
        no->P3 = filho;
    }
    else if(pos == 3){

        //Insere a chave e o byteoffset na posição correta e não precisa shiftar
        no->C3 = chave;
        no->PR3 = byteoffset;

        //Salva o novo nó resultante do split da recursão
        no->P4 = filho;
    }

    //Incrementa o número de chaves do nó
    no->nroChaves = no->nroChaves + 1;

    //Escreve o nó no arquivo de índices
    fseek(arquivo, RRN*TAMANHO_NO + TAMANHO_CABECALHO, SEEK_SET); //Vai até a página de disco correspondente ao RRN
    escrever_no_arvB(arquivo, no); //Escreve o nó no arquivo de índices
    apagar_no(&no); //Libera a memória alocada para o nó
    return;
}

void insercao_noFolha(FILE* arquivo, NO_ARVB* no, int RRN, int pos, int chave, long int byteoffset){
    //Insere a chave e o byteoffset na posição correta
    if(pos == 1){
        //Shifta os as chaves e byteoffset para a direita
        no->C3 = no->C2;
        no->PR3 = no->PR2;
        no->C2 = no->C1;
        no->PR2 = no->PR1;

        //Insere a chave e o byteoffset na posição correta
        no->C1 = chave;
        no->PR1 = byteoffset;
    }
    else if(pos == 2){

        //Shifta os as chaves e boff para a direita
        no->C3 = no->C2;
        no->PR3 = no->PR2;

        //Insere a chave e o byteoffset na posição correta
        no->C2 = chave;
        no->PR2 = byteoffset;
    }
    else if(pos == 3){

        //Insere a chave e o byteoffset na posição correta e não precisa shiftar
        no->C3 = chave;
        no->PR3 = byteoffset;
    }

    //Não precisa shiftar os filhos e nem inserir o nó criado em um split e passado recursivamente, pois é um nó folha.

    //Incrementa o número de chaves do nó
    no->nroChaves = no->nroChaves + 1;

    //Escreve o nó no arquivo de índices
    fseek(arquivo, RRN*TAMANHO_NO + TAMANHO_CABECALHO, SEEK_SET); //Vai até a página de disco correspondente ao RRN
    escrever_no_arvB(arquivo, no);

    //Libera a memória alocada para o nó
    apagar_no(&no);
    return;
}

PROMOCAO inserir_arvB_recursivo(FILE* arquivo_index, ARVB* arvore, int RRN, int chave, long int byteoffset){
    //Função recursiva para inserção de registros na árvore B

    //Verifica se o RRN é válido
    if(RRN == -1){
        printf("Algo deu errado\n");
        return (PROMOCAO){.houvePromocao = false};
    }

    //Lê o nó atual
    NO_ARVB* no = init_no();
    ler_no_arvB(arquivo_index, RRN, no);
    // imprimir_no_arvB(no); //Caso deseje imprimir o nó atual, descomente essa linha

    //Encontra a posição correta para inserir a chave
    //Se pos =  4, a chave é maior que todas as chaves do nó e o nó está cheio
    int pos = 1;
    for(; pos <= no->nroChaves && chave > get_chave(no, pos); pos++){} 

    //Verificação se a chave já existe para evitar inserção repetida
    if (pos <= no->nroChaves && chave == get_chave(no, pos)) {
        // Chave já existe e sai da função
        apagar_no(&no);
        return (PROMOCAO){.houvePromocao = false};
    }
    
    //Encontamos o nó raiz e devemos inserir nele
    if(no->altura_No == 0){

        ///Verificaçaõ se o nó folha encontrado para inserção está cheio
        if(no->nroChaves == MAX_NRO){

            /*Como a função split_no leva em consideração resultados de splits de níveis inferiores que
            foram propagados por meio da estrutura "PROMOCAO", precisamos criar uma estrutura de promoção "falsa" 
            para splitar corretamente o nó folha:*/

            PROMOCAO promocao_falsa;
            promocao_falsa.houvePromocao = false;
            promocao_falsa.chavePromovida = -1;
            promocao_falsa.byteOffsetPromovido = -1;
            promocao_falsa.novoNo = -1; //Esse é essencial para o split_no

            //Lógica para split dos nós e retorno da promoção (libera a memória internamente)
            PROMOCAO promover_no = split_no(arquivo_index, arvore, no, RRN, chave, pos, byteoffset, promocao_falsa);
            //Retornar a promoção recursivamente
            return promover_no; 
        }

        else{
            //Nó folha não está cheio, então podemos inserir a chave e o byteoffset normal

            //Esta função insere a chave e o byteoffset no nó folha e o reescreve no arquivo de indices baseando-se no valor do RRN
            insercao_noFolha(arquivo_index, no, RRN, pos, chave, byteoffset);
            return (PROMOCAO){.houvePromocao = false};
        }

    }
    //Caso contrário, temos que chamar recursivamente para encontrar o nó folha para inserção
    else{
        //A função "get_filho" retorna o RRN do nó filho para o qual a busca pelo nó folha deve continuar
        PROMOCAO promocao_de_no = inserir_arvB_recursivo(arquivo_index, arvore, get_filho(no, pos), chave, byteoffset);
        
        //Verifica se houve promoção no nó filho
        if(promocao_de_no.houvePromocao){

            //Lógica para encontrar a posição correta para inserir a chave e o byteoffset promovidos na recursão
            pos = 1;
            for(; pos <= no->nroChaves && promocao_de_no.chavePromovida > get_chave(no, pos); pos++){} 

            //Verifica se o nó atual está cheio
            if(no->nroChaves < MAX_NRO){

                //Essa função insere o registro de indice no nó interno e salva o novo filho criado no split, ainda reescreve o nó no arquivo de indices
                inserir_noInterno(arquivo_index, no, RRN, pos, promocao_de_no.chavePromovida, promocao_de_no.byteOffsetPromovido, promocao_de_no.novoNo);
                //apagar_no(&no);
                return (PROMOCAO){.houvePromocao = false};
            }
            else{
                //Nó interno está cheio, então precisamos splitar o nó

                //Já com o valor de pos, chamamos o split
                //Split: Insere o nó promovido pela recursão, aloca o novo nó do split atual e retorna a promoção para o nível superior (chave, boffset e RRN do novo nó)
                PROMOCAO promover_no = split_no(arquivo_index, arvore, no, RRN, promocao_de_no.chavePromovida, pos, promocao_de_no.byteOffsetPromovido, promocao_de_no);
                //Retornar a promoção
                return promover_no; 
            }
        }   
    }

    //Caso não haja promoção, liberamos a memória alocada para o nó e retornamos que não houve promoção
    apagar_no(&no);
    return (PROMOCAO){.houvePromocao = false};
}

void inserir_arvB(FILE* arquivo_index, ARVB* arvore, int chave, long int byteoffset){
    //Verifica se a árvore está vazia
    if(arvore->noRaiz == -1){
        //Cria um novo nó com a chave e o byteoffset
        NO_ARVB* no = init_no();
        no->nroChaves = 1;
        no->C1 = chave;
        no->PR1 = byteoffset;
        no->altura_No = 0;

        //Atualiza os campos do cabeçalho da arvoreB
        arvore->noRaiz = arvore->proxRRN;
        arvore->proxRRN = 1;        
        //Número de chaves totais é atualizado ao final da construção da árvore

        //Vai para o RRN do nó raiz
        fseek(arquivo_index, arvore->noRaiz*TAMANHO_NO + TAMANHO_CABECALHO, SEEK_SET); //Somamos o + TAMANHO_CABECALHO para pular o cabeçalho  e tratar corretamente os bytesoffset dos RRNs
        escrever_no_arvB(arquivo_index, no);

        //Libera a memória alocada para o nó
        apagar_no(&no);
    }
    else{
        //Caso a árvore não esteja vazia, chama a função de inserção recursiva
        PROMOCAO promocao_de_no = inserir_arvB_recursivo(arquivo_index, arvore, arvore->noRaiz, chave, byteoffset);

        //Verfica se houve promoção na raiz (nesse caso, a raiz é atualizada)
        if(promocao_de_no.houvePromocao){

            //Lemos a raiz atual para pegar a sua altura
            NO_ARVB* raiz = init_no();
            ler_no_arvB(arquivo_index, arvore->noRaiz, raiz);

            //A inserir recursivo já faz o split e insire na raiz. Caso a raiz lá na função esteja cheia, a promoção é feita e a raiz é atualizada (criamos um novo nível nesse caso)
            NO_ARVB* nova_raiz = init_no();

            //Usa uma nova página de disco para a nova raiz
            int RRN_nova_raiz = arvore->proxRRN;
            arvore->proxRRN = arvore->proxRRN + 1; //Att a próxima RRN disponível

            //Inicialização da nova raiz
            nova_raiz->nroChaves = 1;
            nova_raiz->C1 = promocao_de_no.chavePromovida;
            nova_raiz->PR1 = promocao_de_no.byteOffsetPromovido;
            nova_raiz->P1 = arvore->noRaiz; //A antiga raiz é o filho mais à esquerda da nova raiz
            nova_raiz->P2 = promocao_de_no.novoNo; //O novo nó criado é o filho mais à direita da nova raiz
            nova_raiz->altura_No = raiz->altura_No+1; //A altura da nova raiz é a altra da antiga, acrescida de 1

            arvore->noRaiz = RRN_nova_raiz; //Atualiza o RRN da raiz da árvore

            //Reescreve a nova raiz no arquivo de índices
            fseek(arquivo_index, RRN_nova_raiz*TAMANHO_NO + TAMANHO_CABECALHO, SEEK_SET); //Vai até a página de disco correspondente ao RRN da nova raiz
            escrever_no_arvB(arquivo_index, nova_raiz); //Escreve a nova raiz no arquivo de índices (na posição do RRN da nova raiz)

            free(raiz);
            free(nova_raiz);
            return;
        }
        return;
    }
    
    return;
}

void construcao_arvB(FILE *arquivo_dados, FILE *arquivo_index, CABECALHO *registro_cabecalho_dados){
    //Variaveis auxiliares para a leitura dos registros de dados
    char status;
    int tamanho_reg, chave;
    long int byteoffset;
    int count_registros = 0;

    //Verifica se há registros disponíveis no arquivo de dados para a construção da arvoreB
    if(registro_cabecalho_dados->n_reg_disponiveis == 0){
        return;
    }

    //Alocação e inicializaçao das estruturas auxiliares 
    ARVB* arvore = init_arvB();
    DADOS* registro_dados = init_registro_dados();

    //Inicializa o arquivo como inconsistente (primeira ação neste arquivo)
    set_status_arvB(arquivo_index, '0', arvore);

    /*Loop para pegar os registros do arquivo de dados e escrever no arquivo de índices aqueles que não estão lógicamente removidos*/
    while (fread(&status, sizeof(char), 1, arquivo_dados) != 0)
    {
        //Ler o tamanho do registro atual (para puilá-lo, caso necessário)
        fread(&tamanho_reg, sizeof(int), 1, arquivo_dados);

        // Se o registro não foi removido, o inserimos na árvore binária
        if (status != '1')
        {
            byteoffset = (ftell(arquivo_dados) - 5); //Lê o byteoffset do registro de dados (-5 pois já lemos o status e o tamanho do registro)
            fread(&(registro_dados->prox_reg), sizeof(long int), 1, arquivo_dados); //Lê o campo de proximo registro (não usa, apenas para mover o ponteiro)
            fread(&(registro_dados->id), sizeof(int), 1, arquivo_dados); 
            chave = registro_dados->id;

            //Vai para o final do registro atual (já leu as informações necessárias)
            //17 bytes é a soma dos campos status, tamanho do registro, do proximo registro e do id (1 + 4 + 8 + 4 = 17)
            fseek(arquivo_dados, tamanho_reg - 17, SEEK_CUR);

            //Atualiza a contagem dos registros inseridos
            count_registros++;

            //Insere o registro na arvore B
            inserir_arvB(arquivo_index, arvore, chave, byteoffset); 
        }
        else
        {
            // Se o registro foi removido, pulamos para o próximo registro (tamanho deo registro - 5 bytes [campos removido e tamanho do registro])
            fseek(arquivo_dados, (tamanho_reg - 5), SEEK_CUR);
        }
    }

    //Atualiza o número de chaves da árvore baseado no número de registros inseridos
    arvore->nroChaves = count_registros;    

    //Reescreve o status do arquivo de indices para consistente ao final da construção
    set_status_arvB(arquivo_index, '1', arvore); //Reescreve o cabeçalho todo, mudando o status para consistente

    // Libera a memória alocada para os registros
    free(arvore);
    arvore = NULL;
    apagar_registro(&registro_dados);
    
    return;
}

long int busca_rec_arvB(FILE *index, int id, int RRN, NO_ARVB* aux){
    if(RRN==-1){
        return -1;
    }
    else{
        ler_no_arvB(index,RRN,aux);
        int i = 0, chave;
        for(; i<aux->nroChaves; i++){
            chave = get_chave(aux,i+1);
            if(id<chave){
                return busca_rec_arvB(index,id,get_filho(aux,i+1),aux);
            }
            else if(id == chave){
                return get_valor(aux, i+1);
            }
        }
        return busca_rec_arvB(index,id,get_filho(aux,i+1),aux);
    }

}

long int busca_arvB(FILE *index, int id,ARVB *cabecalho){
    rewind(index);
    NO_ARVB *aux = (NO_ARVB*)malloc(sizeof(NO_ARVB));
    long int byte_offset = busca_rec_arvB(index,id,cabecalho->noRaiz,aux);
    free(aux);
    return byte_offset;

}