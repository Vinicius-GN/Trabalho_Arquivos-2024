#include "utils.h"

/* Trabalho introdutório da disciplina de Organização de Arquivos 

##############################################################
    Alunos: Vinicius Gustierrez Neves          N°USP: 14749363
            Augusto Cavalcante Barbosa Pereira N°USP: 14651531
##############################################################
*/


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