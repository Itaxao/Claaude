#ifndef PILHA_H
#define PILHA_H

// Empilhamento da chamada de função.
typedef struct Funcao{
    char nome[50];
    int id;
    struct Funcao *prox;
} Funcao;

typedef struct{
    Funcao *topo;
} Pilha;

void criar_pilha(Pilha *pilha);
void empilhar(Pilha *pilha, const char *nome, int id);
int desempilhar(Pilha *pilha);
int pilha_vazia(Pilha *pilha);
void mostrar_pilha(Pilha *pilha);
void liberar_pilha(Pilha *pilha);

#endif