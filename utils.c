#include "utils.h"

//############################################################################
/* As funções definidas neste arquivo estão explicadas no arquivo "utils.h". 
Nesse código você encontrá comentários a nível de variáveis e procedimentos.
##############################################################################*/

//Definição da estrutura do cabeçalho, seguindo a ordem recomendada nas espeficiações do trabalho
struct registro_cabecalho{
    char status;
    long long int topo;
    long long int prox_reg_disponivel;
    int n_reg_disponiveis;
    int n_reg_removidos;
};

//Esturura de dados utilizada para a busca de registro na funcionalidade 3
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


FILE* abrir_arquivo(const char* nome_arquivo, const char* modo){

    //Modularização para procedimento padrão de abertura de arquivos.
    FILE* arquivo = fopen(nome_arquivo, modo);
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return NULL;
    }
    return arquivo;
}

void escrever_cabecalho(FILE* arquivo, CABECALHO* cabecalho){

    //Escreve o cabeçalho no arquivo binário campo a campo, asssim como solicitado
    fwrite(&cabecalho->status, sizeof(char), 1, arquivo);
    fwrite(&cabecalho->topo, sizeof(long long int), 1, arquivo);
    fwrite(&cabecalho->prox_reg_disponivel, sizeof(long long int), 1, arquivo);
    fwrite(&cabecalho->n_reg_disponiveis, sizeof(int), 1, arquivo);
    fwrite(&cabecalho->n_reg_removidos, sizeof(int), 1, arquivo);
}

CABECALHO* ler_cabecalho(FILE* arquivo){

    //Lê o cabeçalho do arquivo binário campo a campo, dado que não é válida a operaçao de leitura do cabeçalho inteiro
    CABECALHO* cabecalho = (CABECALHO*) malloc(sizeof(CABECALHO));
    if(cabecalho == NULL){
        printf("Erro ao alocar memória para o cabeçalho\n");
        fclose(arquivo);
        exit(1);
    }
    fread(&cabecalho->status, sizeof(char), 1, arquivo);
    fread(&cabecalho->topo, sizeof(long long int), 1, arquivo);
    fread(&cabecalho->prox_reg_disponivel, sizeof(long long int), 1, arquivo);
    fread(&cabecalho->n_reg_disponiveis, sizeof(int), 1, arquivo);
    fread(&cabecalho->n_reg_removidos, sizeof(int), 1, arquivo);
    return cabecalho;
}

void ler_registro(FILE* arquivo_bin, DADOS* registro){
    //lê os campos fixos do registro
    fread(&(registro->prox_reg), sizeof(long int), 1, arquivo_bin);

    fread(&(registro->id), sizeof(int), 1, arquivo_bin);

    fread(&(registro->idade), sizeof(int), 1, arquivo_bin);
        
    fread(&(registro->tam_Nome), sizeof(int), 1, arquivo_bin);

    //Tratamos os campos nulos de dados
    if(registro->tam_Nome != 0){
        //Aloca memória para o nome (tamanho variável)
        registro->nome = (char*) malloc((registro->tam_Nome+1) * sizeof(char)); 
        fread(registro->nome, sizeof(char), registro->tam_Nome, arquivo_bin);
        registro->nome[registro->tam_Nome] = '\0'; //Adição do \0 no final da string para evitar lixo
    }

    fread(&(registro->tam_Nacionalidade), sizeof(int), 1, arquivo_bin);

    //Tratamos os campos nulos de dados
    if(registro->tam_Nacionalidade != 0){
        registro->nacionalidade = (char*) malloc((registro->tam_Nacionalidade+1) * sizeof(char)); 
        fread(registro->nacionalidade, sizeof(char), registro->tam_Nacionalidade, arquivo_bin);
        registro->nacionalidade[registro->tam_Nacionalidade]='\0'; //Adição do \0 no final da string para evitar lixo
    }

        fread(&(registro->tam_Clube), sizeof(int), 1, arquivo_bin);

        //Tratamos os campos nulos de dados
    if(registro->tam_Clube != 0){
        registro->clube = (char*) malloc((registro->tam_Clube+1) * sizeof(char)); 
        fread(registro->clube, sizeof(char), registro->tam_Clube, arquivo_bin);
        registro->clube[registro->tam_Clube] = '\0'; //Adição do \0 no final da string para evitar lixo
 
        //Os campos de tamanho variavel são alocados, mas são liberados no final da execução da função "print registro"
    }
}
void print_registro(DADOS* registro){
    //printa os campos requisitados do registro e trata os campos nulos de dados
    if(registro->tam_Nome == 0){
                printf("Nome do Jogador: SEM DADO\n");
            }
            else{
                printf("Nome do Jogador: %s\n", registro->nome);
                if(registro->nome != NULL){
                    free(registro->nome);
                    registro->nome = NULL;
                }
                
            }
            if(registro->tam_Nacionalidade == 0){
                printf("Nacionalidade do Jogador: SEM DADO\n");
            }
            else{
                printf("Nacionalidade do Jogador: %s\n", registro->nacionalidade);
                if(registro->nacionalidade != NULL){
                    free(registro->nacionalidade);
                    registro->nacionalidade = NULL;
                }
            }
            if(registro->tam_Clube == 0){
                printf("Clube do Jogador: SEM DADO\n");
            }
            else{
                printf("Clube do Jogador: %s\n", registro->clube);
                if(registro->clube != NULL){
                    free(registro->clube);
                    registro->clube = NULL;
                }
            }
            printf("\n");
}

void add_lista(BL* lista, DADOS* registro){
    //aloca um novo registro e copia os dados do registro auxiliar pra ele
    BN* no = (BN*) malloc(sizeof(BN));
    no->prox=NULL;
    no->registro= (DADOS*) malloc(sizeof(DADOS));
    no->registro->id = registro->id;
    no->registro->idade = registro->idade;
    no->registro->tam_Nome = registro->tam_Nome;
    no->registro->tam_Nacionalidade = registro->tam_Nacionalidade;
    no->registro->tam_Clube = registro->tam_Clube;
    //checa se as strings não estam vazias antes de alocar e copiar
    if(registro->tam_Nome!=0){
        no->registro->nome = (char*) malloc(30*sizeof(char));
        strcpy(no->registro->nome,registro->nome);
    }
    if(registro->tam_Nacionalidade!=0){
        no->registro->nacionalidade = (char*) malloc(30*sizeof(char));
        strcpy(no->registro->nacionalidade,registro->nacionalidade);
    }
    if(registro->tam_Clube!=0){
        no->registro->clube = (char*) malloc(30*sizeof(char));
        strcpy(no->registro->clube,registro->clube);
    }
    //checa se a lista está vazia e realiza a inserção do registro
    if(lista->ini==NULL){
        lista->ini = no;
        lista->fim = no;
    }
    else{
        lista->fim->prox = no;
        lista->fim = no;
    }
}
void apagar_lista(BL** lista){
    //inicializo as variavéis usadas para percorrer a lista
    BN *node, *ant;
    ant = (*lista)->ini;
    //se assegura de que a lista não está vazia para evitar segfault
    if(ant!=NULL){
        node=ant->prox;
    }
    //percorre a lista liberando o nó e o registro anterior
    while(ant!=NULL){
        apagar_registro(&(ant->registro));
        ant->prox=NULL;
        free(ant);
        ant=node;
        if(node!=NULL)
            node=node->prox;
    }
    //libera a lista em si
    (*lista)->ini=NULL;
    (*lista)->fim=NULL;
    free(*lista);
    lista=NULL;
}

void escrever_registro_dados(DADOS* registro, FILE* arquivo){

    //Escreve os registros de dados no arquivo binário campo a campo, assim como solicitado
    fwrite(&registro->removido, sizeof(char), 1, arquivo);
    fwrite(&registro->tamanho_registro, sizeof(int), 1, arquivo);
    fwrite(&registro->prox_reg, sizeof(long int), 1, arquivo);
    fwrite(&registro->id, sizeof(int), 1, arquivo);
    fwrite(&registro->idade, sizeof(int), 1, arquivo);
    
    //Tratamento de campos de tamanho variável nulos (não imprime nada)
    fwrite(&registro->tam_Nome, sizeof(int), 1, arquivo);
    if (registro->tam_Nome > 0) {
        fwrite(registro->nome, sizeof(char), registro->tam_Nome, arquivo);
    }

    fwrite(&registro->tam_Nacionalidade, sizeof(int), 1, arquivo);
    if (registro->tam_Nacionalidade > 0) {
        fwrite(registro->nacionalidade, sizeof(char), registro->tam_Nacionalidade, arquivo);
    }

    fwrite(&registro->tam_Clube, sizeof(int), 1, arquivo);
    if (registro->tam_Clube > 0) {
        fwrite(registro->clube, sizeof(char), registro->tam_Clube, arquivo);
    }
}

DADOS* init_registro_dados(){

    //Inicializa um registro de dados com os campos preenchidos assim como recomendado nas especificações 
    DADOS* registro = (DADOS*)malloc(sizeof(DADOS));
    registro->removido = '0';
    registro->tamanho_registro = 0;
    registro->prox_reg = -1;
    registro->id = 0;
    registro->idade = 0;
    registro->tam_Nome = 0;
    registro->nome = NULL;
    registro->tam_Nacionalidade = 0;
    registro->nacionalidade = NULL;
    registro->tam_Clube = 0;
    registro->clube = NULL;

    return registro;
}

CABECALHO* init_arquivo_binario(FILE* arquivo){

    //Inicialização do registro de dados
    CABECALHO* cabecalho = (CABECALHO*)malloc(sizeof(CABECALHO));

    if(cabecalho == NULL){
        printf("Erro ao alocar memória para o cabeçalho\n");
        fclose(arquivo);
        exit(1);
    }

    (cabecalho)->status = '0';
    (cabecalho)->topo = -1;
    (cabecalho)->prox_reg_disponivel = 0;
    (cabecalho)->n_reg_disponiveis = 0;
    (cabecalho)->n_reg_removidos = 0;
    
    //Escreve o cabeçalho no arquivo binário campo a campo
    escrever_cabecalho(arquivo, cabecalho);

    //Retorna um ponteiro para o cabeçalho incializado e escrito no arquivo binário
    return cabecalho;
}

void apagar_registro(DADOS** registro){

    //Liberação da memória alocada para os campos de tamanho variável e para o registro em si
    //O restante dos campos são de tamanho fixo, então são liberados junto com o registro
    if((*registro)->nome != NULL){
        free((*registro)->nome);
        (*registro)->nome = NULL;
    }
    if((*registro)->nacionalidade != NULL){
        free((*registro)->nacionalidade);
        (*registro)->nacionalidade = NULL;
    }
    if((*registro)->clube != NULL){
        free((*registro)->clube);
        (*registro)->clube = NULL;
    }


    if(*registro != NULL){
        free(*registro);
        *registro = NULL;
    }

}

void apagar_cabecalho(CABECALHO** cabecalho){
    //Libera a memória alocada para o cabeçalho
    if(*cabecalho != NULL){
        free(*cabecalho);
        *cabecalho = NULL;
    }
}

void binarioNaTela(char *nomeArquivoBinario) {

    //Essa função foi disponibilizada pela professora e serve para imprimir o arquivo binário na tela
	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}

void scan_quote_string(char *str) {

	/*
	*	Use essa função para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo.
    */

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
		str[0] = R;
		scanf("%s", &str[1]);
	} else { // EOF
		strcpy(str, "");
	}
}

DADOS* split_linha(FILE* arquivo_in, const char* linha){
        //Inicializa o registro e verifica se a alocação foi bem sucedida
        DADOS* registro = init_registro_dados();

        if(registro == NULL){
            printf("Erro ao alocar memória para o registro\n");
            fclose(arquivo_in);
            exit(1);
        }

        //Ao todo, temos que cada registro incialmente tem 33 bytes de tamanho fixo. 
        int contador_tamanho = 33; 

        //Variável que acumulará o tamanho dos campos de tamanho variável para a alocação e contagem do tamanho do registro
        int contador_campo_var = 0;


        int idade = 0, id = 0, pos = 0;

        //Inicialização de strings auxiliares para armazenar os campos de tamanho variável
        char nome[100] = "\0";
        char nacionalidade[100] = "\0";
        char clube[100] = "\0";

        //Separação dos campos de tamanho fixo (estratégia byte a byte):
        for(;linha[pos] != ','; pos++){
            id = id * 10 + (linha[pos] - '0');
        }
        registro->id = id;
        pos++;//Passa pela vírgula

        for(;linha[pos] != ','; pos++){
            idade = idade * 10 + (linha[pos] - '0');
            contador_campo_var++;
        }
        if(contador_campo_var == 0){
            registro->idade = -1;
        }
        else{
            registro->idade = idade;}
            contador_campo_var = 0;
        pos++;//Passa pela vírgula

        //Separação dos campos de tamanho variável:

        //Leitura do nome do jogador usando a string auxiliar
        for(; linha[pos] != ','; pos++){
            nome[contador_campo_var] = linha[pos];
            contador_campo_var++;
        }
        if(contador_campo_var == 0){
            registro->tam_Nome = 0;
        }
        else{
            registro->tam_Nome = contador_campo_var;
            registro->nome = (char*) malloc((contador_campo_var) * sizeof(char));
            if(registro->nome != NULL){
                //A função strncpy possibilita determianar a quantidade de bytes a serem copiados para eliminar o /0 do final da string
                strncpy(registro->nome, nome, contador_campo_var);
                contador_tamanho += contador_campo_var; //Atualiza o tamanho do registro
                contador_campo_var = 0;
            }
            else{
                //Não preciso definir os campos de tamanho variável como nulos pois eles ja são inciailizados assim
                printf("Erro ao alocar memória para o nome\n");
            }

        }
        pos++;
        
        //Ler nacionalidade dos jogadores
        for(; linha[pos] != ','; pos++){
            nacionalidade[contador_campo_var] = linha[pos];
            contador_campo_var++;
        }
        if(contador_campo_var == 0){
            registro->tam_Nacionalidade = 0;
        }
        else{
            //Lógica para eliminar o /0
            registro->tam_Nacionalidade = contador_campo_var;
            registro->nacionalidade = (char*) malloc((contador_campo_var) * sizeof(char));
            if(registro->nome != NULL){
                strncpy(registro->nacionalidade, nacionalidade, contador_campo_var);//Copia a string nome sem o ultimo caractere que é um \0
                contador_tamanho += contador_campo_var;
                contador_campo_var = 0;
            }
            else{
                printf("Erro ao alocar memória para o nome\n");
            }
        }
        pos++;

        //Ler o clube dos jogadores
        for(;linha[pos] != '\n' && linha[pos] != '\r'; pos++){
            clube[contador_campo_var] = linha[pos];
            contador_campo_var++;
        }

        if(contador_campo_var == 0){
           registro->tam_Clube = 0;
        }
        else{
            //Lógica para eliminar o /0
            registro->tam_Clube = contador_campo_var;
            registro->clube = (char*) malloc((contador_campo_var) * sizeof(char));
            if(registro->clube != NULL){
                strncpy(registro->clube, clube, contador_campo_var);//Copia a string nome sem o ultimo caractere que é um \0
                contador_tamanho += contador_campo_var;
                contador_campo_var = 0;
            }
            else{
                printf("Erro ao alocar memória para o nome\n");
            }
        }
        registro->tamanho_registro = contador_tamanho;   
        return registro;
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