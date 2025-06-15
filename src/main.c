#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "gotoxy.h"
#include "pilha.h"

// Função para imprimir as torres e discos na tela
void imprime(Pilha torres[3], int num_discos) {
    system("cls");  // Limpa a tela

    char bloco = -37; // Caractere para representar o disco graficamente
    int base = num_discos + 3; // Base para o posicionamento

    gotoxy(25, 0);
    printf("=== TORRE DE HANOI ===\n\n");

    // Loop para cada torre
    for (int t = 0; t < 3; t++) {
        gotoxy(t * 25, 2);  // Posiciona o texto do título da torre
        printf("TORRE %d", t + 1);

        // Para imprimir os discos do topo para a base da pilha
        for (int i = num_discos - 1; i >= 0; i--) {
            gotoxy(t * 25, 4 + num_discos - i); // Define a linha para cada disco
            int disco = (i <= torres[t].top) ? torres[t].discos[i] : 0;

            if (disco == 0)
                printf("    |    "); // Representa um espaço vazio na torre
            else {
                // Imprime blocos representando o tamanho do disco
                for (int j = 0; j < disco; j++) printf("%c", bloco);
                printf("|");
                for (int j = 0; j < disco; j++) printf("%c", bloco);
            }
        }
    }
}

// Inicializa as torres com o número de discos na primeira torre
void iniciar(Pilha torres[3], int num_discos) {
    // Inicializa todas as torres (pilhas) como vazias
    for (int i = 0; i < 3; i++) inicializa(&torres[i]);

    // Empilha os discos da maior (num_discos) para o menor (1) na torre 0
    for (int i = num_discos; i >= 1; i--) push(&torres[0], i);
}

// Verifica se o jogador venceu: todos os discos na torre 3 na ordem correta
int venceu(Pilha torres[3], int num_discos) {
    if (torres[2].top + 1 != num_discos) return 0; // Se não tem todos discos, não venceu

    // Checa se os discos estão na ordem correta na torre 3
    for (int i = 0; i < num_discos; i++)
        if (torres[2].discos[i] != num_discos - i)
            return 0; // Se algum disco estiver fora da ordem, não venceu

    return 1; // Vitória confirmada
}

int main() {
    int num_discos, origem, destino, jogadas = 0;
    Pilha torres[3];  // As 3 torres do jogo

    printf("Informe o número de discos (3 a 10): ");
    scanf("%d", &num_discos);

    // Validação do número de discos
    if (num_discos < 3 || num_discos > 10) {
        printf("Número inválido.\n");
        return 1;
    }

    // Inicializa as torres e coloca os discos na primeira
    iniciar(torres, num_discos);

    // Loop do jogo: enquanto não venceu
    while (!venceu(torres, num_discos)) {
        imprime(torres, num_discos);
        printf("\nMovimento #%d\n", jogadas + 1);
        printf("De (1-3): ");
        scanf("%d", &origem);
        printf("Para (1-3): ");
        scanf("%d", &destino);

        origem--; destino--; // Ajusta índices para 0-based

        // Validação das torres digitadas
        if (origem < 0 || origem > 2 || destino < 0 || destino > 2) {
            printf("Torre inválida!\n");
            system("pause");
            continue;
        }

        // Valida se a torre de origem está vazia
        if (empty(torres[origem])) {
            printf("Torre de origem está vazia!\n");
            system("pause");
            continue;
        }

        int disco = stacktop(torres[origem]);

        // Valida se disco maior não está sendo colocado sobre disco menor
        if (!empty(torres[destino]) && disco > stacktop(torres[destino])) {
            printf("Não é possível colocar um disco maior sobre um menor!\n");
            system("pause");
            continue;
        }

        // Movimento válido: desempilha da origem e empilha na torre destino
        push(&torres[destino], pop(&torres[origem]));
        jogadas++;
    }

    // Impressão final de vitória
    imprime(torres, num_discos);
    printf("\nParabéns! Você completou em %d jogadas.\n", jogadas);
    return 0;
}
