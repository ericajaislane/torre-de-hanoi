#include "pilha.h"

// Inicializa a pilha definindo top = -1 (vazia)
void inicializa(Pilha* pilha) {
    pilha->top = -1;
}

// Retorna 1 (true) se pilha vazia, 0 caso contrário
int empty(Pilha pilha) {
    return pilha.top == -1;
}

// Retorna 1 (true) se pilha cheia (top == max_discos - 1), 0 caso contrário
int full(Pilha pilha, int max_discos) {
    return pilha.top == max_discos - 1;
}

// Empilha um disco, incrementando o topo e armazenando o disco no array
void push(Pilha* pilha, int disco) {
    pilha->discos[++(pilha->top)] = disco;
}

// Desempilha um disco, retorna o disco e decrementa o topo
int pop(Pilha* pilha) {
    return pilha->discos[(pilha->top)--];
}

// Retorna o disco do topo da pilha, sem remover
int stacktop(Pilha pilha) {
    return pilha.discos[pilha.top];
}

