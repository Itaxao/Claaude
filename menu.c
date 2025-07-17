#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// BIBLIOTECAS QUE ADCIONA O SLEEP
#include <unistd.h>


// Bibliotecas próprias.
#include "Bibliotecas/fila.h" 
#include "Bibliotecas/pilha.h" 

// =================================================================================================

// VARIAVEIS E FUNÇÕES GLOBAIS (DEFINIMOS ALGUMAS VARIAVEIS GLOBAIS)

int opcaomenu;
int contador_PID = 1; // PID inicial.
Fila *fila; // Chamando a fila globalmente.


// =================================================================================================
int main(){

    fila = criar_fila();
    printf("\n\x1b[32m=====\x1b[0m BEM VINDO AO \x1b[31mIcarOS\x1b[0m! \x1b[32m=====\x1b[0m\n\n");

    do{
        //INTERFACE DO USUÁRIO (CRIAMOS O MENU ACESSÁVEL)
        fflush(stdout); // SLEEP PARA FINS ESTÉTICOS
        sleep(2);
        printf("\x1b[32m=====\x1b[0m DIGITE A OPCAO DESEJADA! \x1b[32m=====\x1b[0m\n\n");
        printf("\x1b[32m===========================================================\x1b[0m\n");
        printf("1\x1b[32m .................... \x1b[0mCRIAR NOVO PROCESSO\n");
        printf("2\x1b[32m .................... \x1b[0mEXECUTAR PROCESSO\n");
        printf("3\x1b[32m .................... \x1b[0mIMPRIMIR ESTADO ATUAL DO SISTEMA\n");
        printf("4\x1b[32m .................... \x1b[0mCANCELAR PROCESSO\n\n");

        printf("\x1b[31m0\x1b[0m\x1b[32m .................... \x1b[0m\x1b[31mSAIR DO SISTEMA\x1b[0m\n");
        printf("\x1b[32m===========================================================\x1b[0m\n\n");

        printf("OPCAO: ");
        scanf("%d", &opcaomenu);
        getchar();

// =================================================================================================        

    switch (opcaomenu){

        case 1:{
            TipoDado processo;

            processo.pid = contador_PID++;
        
            printf("\x1b[36m Nome do Processo\x1b[0m: ");
            fgets(processo.nome,sizeof(processo.nome),stdin);
            processo.nome[strcspn(processo.nome, "\n")] = '\0';

            printf("\x1b[36m Prioridade \x1b[0m \x1b[31m(1: Alta)\x1b[0m \x1b[33m(2: Media)\x1b[0m \x1b[32m(3: Baixa)\x1b[0m: ");
            scanf("%d", &processo.prioridade);
            getchar(); // Limpa o buffer do scanf,

            printf("\x1b[36m Número de Chamadas desejadas\x1b[0m: ");
            scanf("%d",&processo.num_chamadas);
            getchar(); // Limpador de buffer portátil.

            strcpy(processo.estado, "Pronto");
            criar_pilha(&processo.pilha_funcoes);

            enfileirar(fila,processo);

            printf("\x1b[32m Processo criado com sucesso. \x1b[0m");
        
        break;
        }

    case 2: {

if(fila_vazia(fila)){ // VERIFICA SE A FILA ESTÁ VAZIA

printf("\x1b[31mNenhum processo encontrado.\x1b[0m\n");

}

TipoDado processo = desenfileirar(fila); // TIRA O PROCESSO DA FILA
strcpy(processo.estado, "Executando"); // MARCA EXECUTANDO

for (int i = 1; i <= processo.num_chamadas; i++) { // VAI REPETIR ATÉ O NÚMERO MÁXIMO DE CHAMADAS
    char nomefuncao[50];
    sprintf(nomefuncao, "Funcao_%d",i);
    empilhar(&processo.pilha_funcoes, nomefuncao, i); // EMPILHA A CHAMADA 
}

printf("n\x1b[33mExecutando processo PID %d: %s\x1b[om\n", processo.pid, processo.nome); //EXIBE O PROCESSO SENDO EXECUTADO

while(!pilha_vazia(&processo.pilha_funcoes)){ // SIMULA A EXECUÇÃO

int chamada = desempilhar(&processo.pilha_funcoes);
printf("-> Executando chamada %d o processo %s\n", chamada, processo.nome);
sleep(1);

}

strcpy(processo.estado, "Finalizado"); // MUDA O ESTADO PARA DE EXECUTANDO PARA FINALIZADO
printf("\n\x1b[32mProcesso %d finalizado com sucesso. \x1b[0m\n", processo.pid);
     
    break;
    }

    case 3:
        mostrar_fila(fila);
    break;

    case 4:
    printf("PROCESSO CANCELADO!");
    break;

    case 0:
        printf("\x1b[31m Sistema Finalizando.......\x1b[0m");
        liberar_fila(fila);
    break;

    default:
    printf("OPCAO NAO ENCONTRADA!");
    }

} while (opcaomenu != 0);

    return 0;
}



