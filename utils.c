#include "utils.h"

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

FILE* abrir_arquivo(const char* nome_arquivo, const char* modo){

    //Modularização para procedimento padrão de abertura de arquivos.
    FILE* arquivo = fopen(nome_arquivo, modo);
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        exit(1);
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
    fread(&cabecalho->status, sizeof(char), 1, arquivo);
    fread(&cabecalho->topo, sizeof(long long int), 1, arquivo);
    fread(&cabecalho->prox_reg_disponivel, sizeof(long long int), 1, arquivo);
    fread(&cabecalho->n_reg_disponiveis, sizeof(int), 1, arquivo);
    fread(&cabecalho->n_reg_removidos, sizeof(int), 1, arquivo);
    return cabecalho;
}

DADOS* ler_registro(FILE* arquivo_bin, DADOS* registro){
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
        registro->nome[registro->tam_Nome] = '\0';
    }

    fread(&(registro->tam_Nacionalidade), sizeof(int), 1, arquivo_bin);

    //Tratamos os campos nulos de dados
    if(registro->tam_Nacionalidade != 0){
        registro->nacionalidade = (char*) malloc((registro->tam_Nacionalidade+1) * sizeof(char)); 
        fread(registro->nacionalidade, sizeof(char), registro->tam_Nacionalidade, arquivo_bin);
        registro->nacionalidade[registro->tam_Nacionalidade]='\0';
    }

        fread(&(registro->tam_Clube), sizeof(int), 1, arquivo_bin);

        //Tratamos os campos nulos de dados
    if(registro->tam_Clube != 0){
        registro->clube = (char*) malloc((registro->tam_Clube+1) * sizeof(char)); 
        fread(registro->clube, sizeof(char), registro->tam_Clube, arquivo_bin);
        registro->clube[registro->tam_Clube] = '\0';
    }


        

}
void print_registro(DADOS* registro){
    //printa os campos requisitados do registro, caso não forem nulos
    if(registro->tam_Nome == 0){
                printf("Nome do Jogador: SEM DADO\n");
            }
            else{
                printf("Nome do Jogador: %s\n", registro->nome);
                free(registro->nome);
                registro->nome = NULL;
            }
            if(registro->tam_Nacionalidade == 0){
                printf("Nacionalidade do Jogador: SEM DADO\n");
            }
            else{
                printf("Nacionalidade do Jogador: %s\n", registro->nacionalidade);
                free(registro->nacionalidade);
                registro->nacionalidade = NULL;
            }
            if(registro->tam_Clube == 0){
                printf("Clube do Jogador: SEM DADO\n");
            }
            else{
                printf("Clube do Jogador: %s\n", registro->clube);
                free(registro->clube);
                registro->clube = NULL;
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
    //se assegura de que a lista não está vazia para evitar segfaukt
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

    //Leberação da memória alocada para os campos de tamanho variável e para o registro em si
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

        printf("%s\n", linha);

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

        //Separação dos campos de tam variável:

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


void funcionalidade1(void){
    //Contador do número de registros lidos
    int count_registros = 0;

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
    printf("%s\n", linha);

//// PEGAR LINHA A LINHA E ESCREVER NO ARQUIVO BINÁRIO ////
//A função fgets lê até o fim da linha ou até que o número máximo de caracteres seja lido, o que ocorrer primeiro
   while((fgets(linha, 256, arquivo_in)) != NULL){
        DADOS* registro = split_linha(arquivo_in, linha); //Função que separa os campos da linha e retorna um registro com os campos preenchidos

        //Printar para conferência
        printf("Removido: %c\n", registro->removido);
        printf("Prox reg: %ld\n", registro->prox_reg);
        printf("Id: %d\n", registro->id);
        printf("Idade: %d\n", registro->idade);
        printf("TAM Nome: %d\n", registro->tam_Nome);
        printf("Nome: %s\n", registro->nome);
        printf("TAM nacionalidade: %d\n", registro->tam_Nacionalidade);
        printf("Nacionalidade: %s\n", registro->nacionalidade);
        printf("TAM clube: %d\n", registro->tam_Clube);
        printf("Clube: %s\n", registro->clube);
        printf("Tamanho registro: %d\n\n", registro->tamanho_registro);
        
        escrever_registro_dados(registro, arquivo_out);

        //Libera a memória alocada para o registro
        apagar_registro(&registro);

        count_registros++;

    }
    //Fecha o arquivo de entrada
    fclose(arquivo_in);

    //Atualiza o cabeçalho do arquivo binário (status e numero de registros disponíveis)
    cabecalho->n_reg_disponiveis = count_registros;
    cabecalho->status = '1';

    fseek(arquivo_out, 0, SEEK_SET);
    escrever_cabecalho(arquivo_out, cabecalho);

    //Printar cabeçalho para conferência
    printf("Staus: %c\n", cabecalho->status);
    printf("Reg disp: %d\n", cabecalho->n_reg_disponiveis);
    printf("Reg disp: %d\n", cabecalho->n_reg_removidos);
    printf("Topo: %lld\n", cabecalho->topo);
    printf("Prox reg disp: %lld\n", cabecalho->prox_reg_disponivel);

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

    //Lemos os campos do cabeçalho para passar pelos dados (outra opção seria usar o fseek)
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

    //percorre pelas buscas
    for(int i=0;i<n_buscas;i++){
        printf("busca %d\n\n",i+1);
        BN* aux=listas[i]->ini;
        //percorre e printa as listas com os resultados das buscas
        while(aux!=NULL){
            print_registro(aux->registro);
            aux=aux->prox;
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