#include "funcionalidades.h"

/* Trabalho introdutório da disciplina de Organização de Arquivos 

##############################################################
    Alunos: Vinicius Gustierrez Neves          N°USP: 14749363
            Augusto Cavalcante Barbosa Pereira N°USP: 14651531
##############################################################
*/

// Interface de chamada das funcionalidades
void interface(int command){
    switch (command)
    {
    case 1:
        funcionalidade1();
        break;

    case 2:
        funcionalidade2();
        break;

    case 3:
        funcionalidade3();
        break;

    default:
        break;
    }
}


/*Passos:
- Alterar prox reg disp após cada operação e por meio de busca***

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

int main(){
    int command;
    scanf("%d", &command);
    interface(command);

    return 0;
}