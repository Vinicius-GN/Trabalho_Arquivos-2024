#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Trabalho introdutório da disciplina de Organização de Arquivos 

##############################################################
    Alunos: Vinicius Gustierrez Neves          N°USP: 14749363
            Augusto Cavalcante Barbosa Pereira N°USP: 14651531
##############################################################
*/

//Melhorias: modularizar a split e tirar /0 dos registros

typedef struct registro_cabecalho CABECALHO;
typedef struct registro_dados DADOS;

struct registro_cabecalho{
    char status;
    long long int topo;
    long long int prox_reg_disponivel;
    int n_reg_disponiveis;
    int n_reg_removidos;
};

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
    FILE* arquivo = fopen(nome_arquivo, modo);
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        exit(1);
    }
    return arquivo;
}

void escrever_cabecalho(FILE* arquivo, CABECALHO* cabecalho){
    fwrite(&cabecalho->status, sizeof(char), 1, arquivo);
    fwrite(&cabecalho->topo, sizeof(long long int), 1, arquivo);
    fwrite(&cabecalho->prox_reg_disponivel, sizeof(long long int), 1, arquivo);
    fwrite(&cabecalho->n_reg_disponiveis, sizeof(int), 1, arquivo);
    fwrite(&cabecalho->n_reg_removidos, sizeof(int), 1, arquivo);
}

//Void pois não preciso ter retorno, só escrever no arquivo novamente
void escrever_registro_dados(DADOS* registro, FILE* arquivo){
    //Escreve os registros no arquivo binário
    fwrite(&registro->removido, sizeof(char), 1, arquivo);
    fwrite(&registro->tamanho_registro, sizeof(int), 1, arquivo);
    fwrite(&registro->prox_reg, sizeof(long int), 1, arquivo);
    fwrite(&registro->id, sizeof(int), 1, arquivo);
    fwrite(&registro->idade, sizeof(int), 1, arquivo);
    fwrite(&registro->tam_Nome, sizeof(int), 1, arquivo);
    fwrite(registro->nome, sizeof(char), registro->tam_Nome, arquivo);
    fwrite(&registro->tam_Nacionalidade, sizeof(int), 1, arquivo);
    fwrite(registro->nacionalidade, sizeof(char), registro->tam_Nacionalidade, arquivo);
    fwrite(&registro->tam_Clube, sizeof(int), 1, arquivo);
    fwrite(registro->clube, sizeof(char), registro->tam_Clube, arquivo);
}

DADOS* init_registro_dados(){
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
}

CABECALHO* init_arquivo_binario(FILE* arquivo){
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
    
    escrever_cabecalho(arquivo, cabecalho);
    return cabecalho;
}

void apagar_registro(DADOS** registro){
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

    //O restante dos campos são de tamanho fixo, então não precisam ser liberados pois não foram alocados dinamicamente

    if(*registro != NULL){
        free(*registro);
        *registro = NULL;
    }

}

void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

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
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada está da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
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
        DADOS* registro = (DADOS*) malloc(sizeof(DADOS));

        if(registro == NULL){
            printf("Erro ao alocar memória para o registro\n");
            fclose(arquivo_in);
            exit(1);
        }

        int contador_tamanho = 28; //Ao todo, temos que cada registro incialmente tem 33 bytes de tamanho fixo. Contudo, para pular para o pŕoximo registro, precisamos de 5 bytes a menos
        //Dado que o campo removido tem 1 byte e tam_registro 4 bytes. Dessa forma, o tamanho inicial é 28 bytes e conseguimos pular para o próximo registro de forma correta. 
        int contador_campo_var = 0;

        //Inicializa o registro e verifica se a alocação foi bem sucedida
        if(init_registro_dados(registro) == NULL){
            printf("Erro ao alocar memória para o registro\n");
            fclose(arquivo_in);
            exit(1);
        }

        int idade = 0, id = 0, pos = 0;
        char nome[100] = "\0";
        char nacionalidade[100] = "\0";
        char clube[100] = "\0";

        // fgets em C lê até o fim da linha ou até que o número máximo de caracteres seja lido, o que ocorrer primeir
        printf("%s\n", linha);

        //Separação dos campos de tam fixo:
        for(;linha[pos] != ','; pos++){
            id = id * 10 + (linha[pos] - '0');
        }
        registro->id = id;
        pos++;

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
        pos++;

        //Separação dos campos de tam variável:
        //LER NOME
        for(; linha[pos] != ','; pos++){
            nome[contador_campo_var] = linha[pos];
            contador_campo_var++;
        }
        if(contador_campo_var == 0){
            registro->tam_Nome = 0;
        }
        else{
            registro->tam_Nome = contador_campo_var + 1;//////////////////////////////////////Alterar depois
            registro->nome = (char*) malloc((contador_campo_var + 1) * sizeof(char));
            strcpy(registro->nome, nome);
            contador_tamanho += contador_campo_var;
            contador_campo_var = 0;

            //Lógica para eliminar o /0
            // registro->tam_Nome = contador_campo_var;
            // registro->nome = (char*) malloc((contador_campo_var + 1) * sizeof(char));
            // if(registro->nome != NULL){
            //     strncpy(registro->nome, nome, contador_campo_var);//Copia a string nome sem o ultimo caractere que é um \0
            //     contador_tamanho += contador_campo_var;
            //     contador_campo_var = 0;
            // }
            // else{s
            //     printf("Erro ao alocar memória para o nome\n");
            //     //Ao final, os campos não alocados terão valores nullos e tamanho 0
            // }


        }
        pos++;
        
        //LER NACIONALIDADE
        for(; linha[pos] != ','; pos++){
            nacionalidade[contador_campo_var] = linha[pos];
            contador_campo_var++;
        }
        if(contador_campo_var == 0){
            registro->tam_Nacionalidade = 0;
        }
        else{
            registro->tam_Nacionalidade = contador_campo_var + 1;//////////////////////////////////////Alterar depois
            registro->nacionalidade = (char*) malloc((contador_campo_var + 1) * sizeof(char));
            strcpy(registro->nacionalidade, nacionalidade);
            contador_tamanho += contador_campo_var;
            contador_campo_var = 0;
        }
        pos++;

        //LER CLUBE
        for(; linha[pos] != '\n'; pos++){
            clube[contador_campo_var] = linha[pos];
            contador_campo_var++;
        }
        if(contador_campo_var == 0){
           registro->tam_Clube = 0;
        }
        else{
            registro->tam_Clube = contador_campo_var + 1;//////////////////////////////////////Alterar depois
            registro->clube = (char*) malloc((contador_campo_var + 1) * sizeof(char));
            strcpy(registro->clube, clube);
            contador_tamanho += contador_campo_var;
            contador_campo_var = 0;
        }
        registro->tamanho_registro = contador_tamanho;   
        return registro;
    }


bool funcionalidade1(void){
    //Contador do número de registros
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
   while((fgets(linha, 256, arquivo_in)) != NULL){
        DADOS* registro = split_linha(arquivo_in, linha); //Função que separa os campos da linha e retorna um registro com os campos preenchidos

        //Printar para conferência
        printf("Removido: %c", registro->removido);
        printf("Prox reg: %ld", registro->prox_reg);
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

    return true;
}

bool funcionalidade2(void){
    //Aqui temos que fazer a leitura dos registros do arquivo binário e imprimir na tela
    char nome_arquivo_binario[50];
    scanf("%s", nome_arquivo_binario);
    FILE* arquivo_bin = abrir_arquivo(nome_arquivo_binario, "rb");

    //Pulamos a leitura do cabeçalho (não nos interessa)
    fseek(arquivo_bin, 0, SEEK_SET);/////////////////////////////////

    CABECALHO* cabecalho = (CABECALHO*) malloc(sizeof(CABECALHO));

    fread(cabecalho, sizeof(CABECALHO), 1, arquivo_bin);
    printf("Status: %c\n", cabecalho->status);
    printf("Topo: %lld\n", cabecalho->topo);
    printf("Prox reg disp: %lld\n", cabecalho->prox_reg_disponivel);
    printf("N reg disp: %d\n", cabecalho->n_reg_disponiveis);
    printf("N reg removidos: %d\n", cabecalho->n_reg_removidos);


    //Leitura e impressão dos registros
    DADOS* registro = (DADOS*) malloc(sizeof(DADOS));
    if (registro == NULL){
        printf("Erro ao alocar memória para o registro\n");
        fclose(arquivo_bin);
        exit(1);
    }

    //alocar memoria para as strings ao decorrer da leitura

    while(feof(arquivo_bin) == 0){

        //Leitura dos campos iniciais do registro (removido e tamanho do registro)
        fread(&(registro->removido), sizeof(char), 1, arquivo_bin);
        printf("Removido: %c\n", registro->removido);

        fread(&(registro->tamanho_registro), sizeof(int), 1, arquivo_bin);
        printf("Tamanho registro: %d\n", registro->tamanho_registro);

        //Se o registro não foi removido, lemos os campos restantes e imprimimos na tela
        //NA EXECUÇÃO OFICIAL, SO IMPRIMIMOS NOME, NACIONALIDADE E CLUBE
        if(registro->removido != '1'){
            fread(&(registro->prox_reg), sizeof(long int), 1, arquivo_bin);
            printf("Prox reg: %ld\n", registro->prox_reg);

            fread(&(registro->id), sizeof(int), 1, arquivo_bin);
            printf("Id: %d\n", registro->id);

            fread(&(registro->idade), sizeof(int), 1, arquivo_bin);
            printf("Idade: %d\n", registro->idade);
        
            fread(&(registro->tam_Nome), sizeof(int), 1, arquivo_bin);
            printf("TAM Nome: %d\n", registro->tam_Nome);

            //Tratamos os campos nulos de dados
            if(registro->tam_Nome == 0){
                printf("Nome do Jogador: SEM DADO\n");
                //Nao sei se preciso pular aqui ou não
            }
            else{
                //Aloca memória para o nome (tamanho variável)
                registro->nome = (char*) malloc((registro->tam_Nome) * sizeof(char)); 
                fread(registro->nome, sizeof(char), registro->tam_Nome, arquivo_bin);
                printf("Nome: %s\n", registro->nome);
            }

            fread(&(registro->tam_Nacionalidade), sizeof(int), 1, arquivo_bin);
            printf("TAM nacionalidade: %d\n", registro->tam_Nacionalidade);

            //Tratamos os campos nulos de dados
            if(registro->tam_Nacionalidade == 0){
                printf("Nacionalidade: SEM DADO\n");
                //Nao sei se preciso pular aqui ou não
            }
            else{
                registro->nacionalidade = (char*) malloc((registro->tam_Nacionalidade) * sizeof(char)); 
                fread(registro->nacionalidade, sizeof(char), registro->tam_Nacionalidade, arquivo_bin);
                printf("Nacionalidade: %s\n", registro->nacionalidade);
            }

            fread(&(registro->tam_Clube), sizeof(int), 1, arquivo_bin);
            printf("TAM clube: %d\n", registro->tam_Clube);

            //Tratamos os campos nulos de dados
            if(registro->tam_Clube == 0){
                printf("Clube: SEM DADO\n");
                //Nao sei se preciso pular aqui ou não
            }
            else{
                registro->clube = (char*) malloc(registro->tam_Clube * sizeof(char)); 
                fread(registro->clube, sizeof(char), registro->tam_Clube, arquivo_bin);
                printf("Clube: %s\n", registro->clube);
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

    fclose(arquivo_bin);
    apagar_registro(&registro);
    return true;
}

bool funcionalidade3(void){
    //Aqui temos que fazer a busca de um ou mais campos
    //Lembrar de tratar as aspas duplas
    //Lembrar de não exibir registros removidos

    return true;
}


void interface(int command){
    switch (command)
    {
    case 1:
        if(funcionalidade1()){
            printf("Arquivo binario gerado com sucesso!\n");
        }  
        else{
            printf("Falha no processamento do arquivo.\n");
        }
        break;

    case 2:
        if(funcionalidade2()){
            printf("Arquivo binario gerado com sucesso!\n");
        }  
        else{
            printf("Falha no processamento do arquivo.\n");
        }
        break;

    case 3:
        funcionalidade3();
        break;

    default:
        break;
    }
}


/*Passos:
*Inicializar o registro de cabeçalho (status = 0, topo = -1, prox_reg_disponivel = 0, n_reg_disponiveis = 0, n_reg_removidos = 0)
- AlteraR status ao abrir e fechar o arquivo
- Alterar numeros de registros ao inserir e remover
- Alterar prox reg disp após cada operação e por meio de busca***

*Inserir registros:
- Alocar struct registro_dados
- Inserir dados na struct
- Inserir struct no arquivo de fora binária

*Operações:
1 - Pegar o arquivo csv e transformar em binário pra saída (acredito que é só ler e escrever) -> NAO PODE TER /0
2 - Interpretar um aquivo binário de entrada, tratar campos nulos e imprimir na saída os dados formatados
* SEM DADO caso nulo (mas escreve como $), pular uma linha apos cada registro
3 - Permitir uma busca nos registros dos jogadores baseados em um ou mais campos especificos. A função pode retornar 0 registros 
Os valores dos campos do tipo string devem ser
especificados entre aspas duplas ("). Para a manipulação de strings com aspas duplas,
pode-se usar a função scan_quote_string disponibilizada na página do projeto da
disciplina.
Registros marcados como logicamente removidos não devem ser exibidos.

*/

// FINS de teste de escrita
    /*FILE* arquivo = fopen("jogador.bin", "rb");

    if (arquivo == NULL){
        printf("Erro! Impossivel abrir o arquivo!\n");
        exit(1);
    }

    CABECALHO cabecalho;

    fread(&cabecalho, sizeof(CABECALHO), 1, arquivo);
    printf("Status: %c\n", cabecalho.status);
    printf("Topo: %lld\n", cabecalho.topo);
    printf("Prox reg disp: %lld\n", cabecalho.prox_reg_disponivel);
    printf("N reg disp: %d\n", cabecalho.n_reg_disponiveis);
    printf("N reg removidos: %d\n", cabecalho.n_reg_removidos);
    */


int main(){
    printf("Inicio de execução\n");
    int command;
    scanf("%d", &command);
    interface(command);

    return 0;
}