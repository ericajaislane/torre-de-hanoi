#ifndef PILHA_H
#define PILHA_H

#define MAX_TORRES 3         // Número de torres do jogo
#define MAX_DISCOS 64        // Máximo de discos permitidos

// Estrutura Pilha, que representa uma torre com discos
typedef struct {
    int discos[MAX_DISCOS];  // Array que armazena os discos (valores representando tamanho)
    int top;                 // Índice do topo da pilha (-1 quando vazia)
} Pilha;

// Protótipos das funções para manipular a pilha
void inicializa(Pilha* pilha);        // Inicializa a pilha, deixando-a vazia
int empty(Pilha pilha);                // Verifica se pilha está vazia
int full(Pilha pilha, int max_discos);// Verifica se pilha está cheia (com limite de discos)
void push(Pilha* pilha, int disco);   // Adiciona um disco no topo
int pop(Pilha* pilha);                 // Remove o disco do topo e retorna ele
int stacktop(Pilha pilha);             // Retorna o disco do topo sem remover

#endif

