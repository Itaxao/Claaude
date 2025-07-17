#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Bibliotecas/fila.h"

// =================================================================================================================================
// Cria uma fila vazia e retorna seu endereco
Fila* criar_fila() {
    Fila *f = (Fila*) malloc(sizeof(Fila)); // Aloca memoria para a fila

    if (f == NULL) { // Verifica se a alocacao foi bem sucedida
        printf("Erro na alocação de memória.\n");
        exit(1);
    }

    f->inicio = NULL; // Inicializa o inicio da fila como NULL
    f->fim = NULL; // Inicializa o fim da fila como NULL
    return f; // Retorna o endereco da fila criada
}

// =================================================================================================================================
// Insere um dado no fim da fila
void enfileirar(Fila *f, TipoDado dado) {
    if (f == NULL) return;

    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }

    novo->dado = dado;
    novo->prox = NULL;

    // Inserir no início se a fila estiver vazia ou se o novo tem maior prioridade.
    if (fila_vazia(f) || dado.prioridade < f->inicio->dado.prioridade) {
        novo->prox = f->inicio;
        f->inicio = novo;
        if (f->fim == NULL)
            f->fim = novo;
    } 
    else {
        // Inserção ordenada no meio ou fim baseando-se na prioridade.
        No *atual = f->inicio;
        while (atual->prox != NULL && atual->prox->dado.prioridade <= dado.prioridade) {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
        if (novo->prox == NULL)
            f->fim = novo;
    }
}

// =================================================================================================================================
// Remove um dado do início da fila e retorna seu valor
TipoDado desenfileirar(Fila *f) {
    if (f != NULL && !fila_vazia(f)) { // Verifica se a fila existe e não está vazia

        No *aux = f->inicio; // Guarda o endereço do início da fila em aux
        TipoDado dado = aux->dado; // Guarda o dado do início da fila em dado 
        f->inicio = f->inicio->prox; // Atualiza o início da fila para o próximo nó
        free(aux); // Libera a memória do nó apontado por aux

        if (fila_vazia(f)) { // Se a fila ficou vazia, o fim da fila também deve ser NULL
            f->fim = NULL; 
        }
        return dado; // Retorna o dado removido
    } 
    else { // Se a fila não existe ou está vazia, retorna um valor inválido
        printf("Fila inexistente ou vazia.\n");
        
        // Para evitar erro com o TipoDado sendo uma struct, a verificação foi alterada para garantir que funcionará
        TipoDado invalido;
        invalido.pid = -1;
        invalido.prioridade = -1;
        strcpy(invalido.nome, "NULL");
        strcpy(invalido.estado, "NULL");
        invalido.num_chamadas = -1;
        criar_pilha(&invalido.pilha_funcoes);  // Inicializa a pilha vazia
        
        return invalido;
    }
}

// =================================================================================================================================
// Imprime os dados da fila na ordem do início ao fim
void mostrar_fila(Fila *f) {
    if (f != NULL && !fila_vazia(f)) { // Verifica se a fila existe e não está vazia

        No *aux = f->inicio; // Cria um ponteiro auxiliar para percorrer a fila
        printf("\x1b[36m Fila prioritaria:\x1b[0m \n");
        while (aux != NULL) { // Enquanto o auxiliar não for NULL
            printf("| \x1b[35mPID: \x1b[0m \x1b[34m %d \x1b[0m |\x1b[35m Nome:\x1b[0m \x1b[34m %s \x1b[0m | \x1b[35m Prioridade:\x1b[0m  \x1b[34m %d \x1b[0m | \x1b[35m Estado:\x1b[0m \x1b[34m %s \x1b[0m | \x1b[35m Nº de Chamadas: \x1b[0m \x1b[34m %d \x1b[0m |\n", 
                   aux->dado.pid, aux->dado.nome, aux->dado.prioridade, aux->dado.estado, aux->dado.num_chamadas);
            aux = aux->prox;
        }
        printf("\n");
    } 
    else { // Se a fila não existe ou está vazia, imprime uma mensagem de erro
        printf("Fila inexistente ou vazia.\n");
    }
}

// =================================================================================================================================
// Verifica se a fila está vazia e retorna 1 se sim, 0 se não
int fila_vazia(Fila *f) {
    if (f != NULL) { // Verifica se a fila existe
        return f->inicio == NULL; // Retorna 1 se o início da fila for NULL, 0 caso contrário
    } 
    else { // Se a fila não existe, retorna -1
        return -1;
    }
}

// =================================================================================================================================
// Libera a memória de uma fila e seus nós
void liberar_fila(Fila *f) {
    if (f != NULL) { // Verifica se a fila existe
        No *aux; // Cria um ponteiro auxiliar para percorrer a fila
        while (f->inicio != NULL) { // Enquanto o início da fila não for NULL
            aux = f->inicio; // Guarda o endereço do início da fila em aux
            f->inicio = f->inicio->prox; // Atualiza o início da fila para o próximo nó
            // Libera a pilha do processo antes de liberar o nó
            liberar_pilha(&aux->dado.pilha_funcoes);
            free(aux); // Libera a memória do nó apontado por aux
        }
        free(f); // Libera a memória da fila
    }
}