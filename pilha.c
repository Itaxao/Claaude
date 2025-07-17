#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Bibliotecas/pilha.h"

void criar_pilha(Pilha *pilha) {
    pilha->topo = NULL;
}

void empilhar(Pilha *pilha, const char *nome, int id) {
    Funcao *novo = (Funcao*) malloc(sizeof(Funcao));
    if (!novo) {
        printf("Erro de alocação de memória.\n");
        return;
    }

    strncpy(novo->nome, nome, sizeof(novo->nome));
    novo->nome[sizeof(novo->nome) - 1] = '\0';
    novo->id = id;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

int desempilhar(Pilha *pilha) {
    if (pilha_vazia(pilha)) {
        printf("Pilha de funções vazia.\n");
        return 0;
    }

    Funcao *remover = pilha->topo;
    int id = remover->id;
    pilha->topo = remover->prox;

    printf("Executando função: %s (ID: %d)\n", remover->nome, remover->id);
    free(remover);
    return id;
}

int pilha_vazia(Pilha *pilha) {
    return (pilha->topo == NULL);
}

void mostrar_pilha(Pilha *pilha) {
    if (pilha_vazia(pilha)) {
        printf("Pilha de funções vazia.\n");
        return;
    }

    Funcao *aux = pilha->topo;
    printf("Chamadas na pilha:\n");
    while (aux != NULL) {
        printf("- %s (ID: %d)\n", aux->nome, aux->id);
        aux = aux->prox;
    }
}

void liberar_pilha(Pilha *pilha) {
    while (!pilha_vazia(pilha)) {
        desempilhar(pilha);
    }
}