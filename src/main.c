#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "gotoxy.h"
#include "pilha.h"

#define TORRES 3
#define MAX 10

void imprimir(Pilha torres[], int n) {
    system("cls");
    int i, j;
    char bloco = -37;
    gotoxy(30, 0);
    printf("TORRE DE HANOI - %d discos\n", n);

    for (i = 0; i < TORRES; i++) {
        gotoxy(20 * i, 2);
        printf("PILHA %d", i + 1);
        int y = 3;
        for (j = torres[i].top; j >= 0; j--) {
            gotoxy(20 * i, y++);
            int tamanho = torres[i].discos[j];
            int espacos = n - tamanho;
            for (int e = 0; e < espacos; e++) printf(" ");
            for (int b = 0; b < tamanho * 2 - 1; b++) printf("%c", bloco);
            printf("\n");
        }
    }
}

void iniciar(Pilha torres[], int n) {
    for (int i = 0; i < TORRES; i++) {
        inicializa(&torres[i], n);
    }

    for (int i = n; i >= 1; i--) {
        push(&torres[0], i);
    }
}

int vitoria(Pilha torres[], int n) {
    if (torres[2].top != n - 1) return 0;
    for (int i = 0; i < n; i++) {
        if (torres[2].discos[i] != n - i) return 0;
    }
    return 1;
}

int main() {
    int n;
    Pilha torres[TORRES];
    int origem, destino, jogadas;
    char repetir;

    do {
        system("cls");
        printf("Informe o numero de discos (3 a 10): ");
        scanf("%d", &n);
        if (n < 3 || n > MAX) {
            printf("Valor invalido.\n");
            continue;
        }

        iniciar(torres, n);
        jogadas = 0;

        while (!vitoria(torres, n)) {
            imprimir(torres, n);
            gotoxy(0, 15);
            printf("Jogada %d\n", jogadas + 1);
            printf("Mover de (1 a 3): ");
            scanf("%d", &origem);
            printf("Para (1 a 3): ");
            scanf("%d", &destino);

            if (origem < 1 || origem > 3 || destino < 1 || destino > 3) {
                printf("Pilha invalida!\n");
                system("pause");
                continue;
            }

            origem--; destino--;

            if (empty(torres[origem])) {
                printf("Pilha de origem vazia!\n");
                system("pause");
                continue;
            }

            int disco = stacktop(torres[origem]);
            if (!empty(torres[destino]) && disco > stacktop(torres[destino])) {
                printf("Movimento invalido: disco maior sobre menor!\n");
                system("pause");
                continue;
            }

            push(&torres[destino], pop(&torres[origem]));
            jogadas++;
        }

        imprimir(torres, n);
        gotoxy(0, 20);
        printf("Parabens! Voce venceu em %d jogadas.\n", jogadas);

        printf("Deseja jogar novamente? (s/n): ");
        scanf(" %c", &repetir);

        for (int i = 0; i < TORRES; i++) {
            liberar(&torres[i]);
        }

    } while (repetir == 's' || repetir == 'S');

    return 0;
}
