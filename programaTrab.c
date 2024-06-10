#include "funcionalidades_intr.h"
#include "funcionalidades_trab1.h"
#include "funcionalidades_arvB.h"

/* Trabalho 1 da disciplina de Organização de Arquivos 

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

    case 4:
        funcionalidade4();
        break;

    case 5:
        funcionalidade5();
        break;

    case 6:
        funcionalidade6();
        break;

    case 7:
        funcionalidade7();
        break;

    case 8:
        funcionalidade8();
        break;

    case 9:
        funcionalidade9();
        break;

    case 10:
        funcionalidade10();
        break;
        
    default:
        break;
    }
}



// Função principal para chamada da interface
int main(){
    int command;
    scanf("%d", &command);
    interface(command);

    return 0;
}