#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

void inicializa(Pilha* pilha, int tamanho) {
    pilha->top = -1;
    pilha->max = tamanho;
    pilha->discos = (int*)malloc(tamanho * sizeof(int));
}

void liberar(Pilha* pilha) {
    free(pilha->discos);
}

int empty(Pilha pilha) {
    return pilha.top == -1;
}

int full(Pilha pilha) {
    return pilha.top == pilha.max - 1;
}

void push(Pilha* pilha, int valor) {
    if (!full(*pilha)) {
        pilha->discos[++pilha->top] = valor;
    }
}

int pop(Pilha* pilha) {
    if (!empty(*pilha)) {
        return pilha->discos[pilha->top--];
    }
    return -1;
}

int stacktop(Pilha pilha) {
    if (!empty(pilha)) {
        return pilha.discos[pilha.top];
    }
    return -1;
}
