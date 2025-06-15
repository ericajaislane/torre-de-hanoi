#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para manipulação de strings
#include "hanoi.h"  // Inclui o cabeçalho único

// Variável global para o início da lista encadeada (declarada aqui e usada nas funções de histórico)
Node* head = NULL;

// --- Implementação das Funções de Utilitário (gotoxy) ---

// Função que move o cursor para (x, y) no terminal (Windows)
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// --- Implementação das Funções da Pilha ---

// Inicializa a pilha definindo top = -1 (vazia)
void inicializa(Pilha* pilha) {
    pilha->top = -1;
}

// Retorna 1 (true) se pilha vazia, 0 caso contrário
int empty(Pilha pilha) {
    return pilha.top == -1;
}

// Empilha um disco, incrementando o topo e armazenando o disco no array
void push(Pilha* pilha, int disco) {
    if (pilha->top < MAX_DISCOS - 1) {
        pilha->discos[++(pilha->top)] = disco;
    }
}

// Desempilha um disco, retorna o disco e decrementa o topo
int pop(Pilha* pilha) {
    if (pilha->top != -1) {
        return pilha->discos[(pilha->top)--];
    }
    return 0; // Retorna 0 ou outro valor indicativo de erro se a pilha estiver vazia
}

// Retorna o disco do topo da pilha, sem remover
int stacktop(Pilha pilha) {
    if (pilha.top != -1) {
        return pilha.discos[pilha.top];
    }
    return 0; // Retorna 0 ou outro valor indicativo de erro se a pilha estiver vazia
}

// --- Implementação das Funções para a Lista Encadeada e Histórico ---

// Função para adicionar um novo registro à lista encadeada
void add_record(GameRecord new_record) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Erro de alocação de memória para o histórico!\n");
        return;
    }
    new_node->record = new_record;
    new_node->next = NULL;

    if (head == NULL) {
        head = new_node;
    } else {
        Node* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Função para salvar um registro no arquivo de texto
void save_record_to_file(GameRecord record) {
    FILE* fp = fopen(HISTORY_FILE, "a");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de histórico!\n");
        return;
    }
    fprintf(fp, "%d;%s;%d;%s\n", record.num_movimentos, record.nome_jogador, record.modo_jogo, record.data_hora_encerramento);
    fclose(fp);
}

// Função para carregar registros do arquivo para a lista encadeada
void load_records_from_file() {
    FILE* fp = fopen(HISTORY_FILE, "r");
    if (fp == NULL) {
        return;
    }

    GameRecord record;
    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%d;%49[^;];%d;%29[^\n]",
               &record.num_movimentos,
               record.nome_jogador,
               &record.modo_jogo,
               record.data_hora_encerramento);
        add_record(record);
    }
    fclose(fp);
}

// Função para liberar a memória da lista encadeada
void free_list() {
    Node* current = head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}

// Função para exibir todos os registros da lista
void print_records() {
    system("cls");
    gotoxy(20, 0);
    printf("=== HISTÓRICO DE PARTIDAS ===\n\n");

    if (head == NULL) {
        printf("Nenhum registro de partida encontrado.\n");
    } else {
        Node* current = head;
        int i = 1;
        while (current != NULL) {
            printf("--- Partida %d ---\n", i++);
            printf("Movimentos: %d\n", current->record.num_movimentos);
            printf("Jogador: %s\n", current->record.nome_jogador);
            printf("Discos: %d\n", current->record.modo_jogo);
            printf("Data/Hora: %s\n", current->record.data_hora_encerramento);
            printf("-------------------\n\n");
            current = current->next;
        }
    }
    system("pause");
}

// Função para buscar por nome de jogador
void search_by_player_name() {
    system("cls");
    gotoxy(20, 0);
    printf("=== BUSCAR POR JOGADOR ===\n\n");

    char search_name[50];
    printf("Digite o nome do jogador para buscar: ");
    scanf("%49s", search_name);
    while (getchar() != '\n'); // Limpar o buffer do teclado

    Node* current = head;
    int found = 0;
    while (current != NULL) {
        if (strcmp(current->record.nome_jogador, search_name) == 0) {
            printf("\n--- Partida Encontrada ---\n");
            printf("Movimentos: %d\n", current->record.num_movimentos);
            printf("Jogador: %s\n", current->record.nome_jogador);
            printf("Discos: %d\n", current->record.modo_jogo);
            printf("Data/Hora: %s\n", current->record.data_hora_encerramento);
            printf("--------------------------\n");
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("\nNenhum registro encontrado para o jogador '%s'.\n", search_name);
    }
    system("pause");
}

// Função para buscar por data (apenas a data, não a hora)
void search_by_date() {
    system("cls");
    gotoxy(20, 0);
    printf("=== BUSCAR POR DATA ===\n\n");

    char search_date[11];
    printf("Digite a data para buscar (YYYY-MM-DD): ");
    scanf("%10s", search_date);
    while (getchar() != '\n'); // Limpar o buffer do teclado

    Node* current = head;
    int found = 0;
    while (current != NULL) {
        if (strncmp(current->record.data_hora_encerramento, search_date, 10) == 0) {
            printf("\n--- Partida Encontrada ---\n");
            printf("Movimentos: %d\n", current->record.num_movimentos);
            printf("Jogador: %s\n", current->record.nome_jogador);
            printf("Discos: %d\n", current->record.modo_jogo);
            printf("Data/Hora: %s\n", current->record.data_hora_encerramento);
            printf("--------------------------\n");
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("\nNenhum registro encontrado para a data '%s'.\n", search_date);
    }
    system("pause");
}


// --- Implementação das Funções do Jogo Torre de Hanói ---

// Função para imprimir as torres e discos na tela
void imprime(Pilha torres[3], int num_discos) {
    system("cls");

    char bloco = (char)219;

    gotoxy(25, 0);
    printf("=== TORRE DE HANOI ===\n\n");

    for (int t = 0; t < 3; t++) {
        gotoxy(t * 25 + 5, 2);
        printf("TORRE %d", t + 1);

        gotoxy(t * 25, num_discos + 4);
        for(int k = 0; k < num_discos * 2 + 3; k++) printf("=");

        for(int k = 0; k < num_discos + 1; k++) {
            gotoxy(t * 25 + num_discos + 1, 3 + k);
            printf("|");
        }

        for (int i = num_discos - 1; i >= 0; i--) {
            int disco_val = (i <= torres[t].top) ? torres[t].discos[i] : 0;
            int current_disk_pos_on_tower = (torres[t].top - i);
            gotoxy(t * 25 + num_discos + 1 - disco_val, num_discos + 3 - current_disk_pos_on_tower);

            if (disco_val == 0) {
                 for (int j = 0; j < num_discos * 2 + 1; j++) printf(" ");
            }
            else {
                for (int j = 0; j < num_discos - disco_val; j++) printf(" ");
                for (int j = 0; j < disco_val; j++) printf("%c", bloco);
                printf("%c", bloco);
                for (int j = 0; j < disco_val; j++) printf("%c", bloco);
                for (int j = 0; j < num_discos - disco_val; j++) printf(" ");
            }
        }
    }
}

// Inicializa as torres com o número de discos na primeira torre
void iniciar(Pilha torres[3], int num_discos) {
    for (int i = 0; i < 3; i++) inicializa(&torres[i]);
    for (int i = num_discos; i >= 1; i--) push(&torres[0], i);
}

// Verifica se o jogador venceu
int venceu(Pilha torres[3], int num_discos) {
    if (torres[2].top + 1 != num_discos) return 0;
    for (int i = 0; i < num_discos; i++)
        if (torres[2].discos[i] != num_discos - i)
            return 0;
    return 1;
}

// Função principal do jogo da Torre de Hanói
void play_game() {
    int num_discos, origem, destino, jogadas = 0;
    Pilha torres[3];

    system("cls");
    printf("Informe o número de discos (3 a 10): ");
    scanf("%d", &num_discos);
    while (getchar() != '\n');

    if (num_discos < 3 || num_discos > 10) {
        printf("Número de discos inválido. O jogo será encerrado.\n");
        system("pause");
        return;
    }

    iniciar(torres, num_discos);

    while (!venceu(torres, num_discos)) {
        imprime(torres, num_discos);
        printf("\nMovimento #%d\n", jogadas + 1);
        printf("De (1-3): ");
        scanf("%d", &origem);
        printf("Para (1-3): ");
        scanf("%d", &destino);
        while (getchar() != '\n');

        origem--; destino--;

        if (origem < 0 || origem > 2 || destino < 0 || destino > 2) {
            printf("Torre inválida!\n");
            system("pause");
            continue;
        }

        if (empty(torres[origem])) {
            printf("Torre de origem está vazia!\n");
            system("pause");
            continue;
        }

        int disco_origem = stacktop(torres[origem]);

        if (!empty(torres[destino]) && disco_origem > stacktop(torres[destino])) {
            printf("Não é possível colocar um disco maior sobre um menor!\n");
            system("pause");
            continue;
        }

        push(&torres[destino], pop(&torres[origem]));
        jogadas++;
    }

    imprime(torres, num_discos);
    printf("\nParabéns! Você completou em %d jogadas.\n", jogadas);

    GameRecord new_record;
    new_record.num_movimentos = jogadas;
    new_record.modo_jogo = num_discos;

    printf("Digite seu nome (até 49 caracteres): ");
    scanf("%49s", new_record.nome_jogador);
    while (getchar() != '\n');

    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(new_record.data_hora_encerramento, sizeof(new_record.data_hora_encerramento), "%Y-%m-%d %H:%M:%S", info);

    add_record(new_record);
    save_record_to_file(new_record);

    printf("\nPartida registrada com sucesso!\n");
    system("pause");
}

// Função para exibir o menu principal
void display_menu() {
    system("cls");
    gotoxy(20, 0);
    printf("=== MENU PRINCIPAL - TORRE DE HANÓI ===\n\n");
    printf("1. Iniciar Novo Jogo\n");
    printf("2. Ver Histórico de Partidas\n");
    printf("3. Buscar Partida por Jogador\n");
    printf("4. Buscar Partida por Data\n");
    printf("5. Sair\n");
    printf("\nEscolha uma opção: ");
}

// --- Função main (única no arquivo de implementação) ---

int main() {
    load_records_from_file();

    int choice;
    do {
        display_menu();
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                play_game();
                break;
            case 2:
                print_records();
                break;
            case 3:
                search_by_player_name();
                break;
            case 4:
                search_by_date();
                break;
            case 5:
                printf("Saindo do jogo. Até mais!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                system("pause");
                break;
        }
    } while (choice != 5);

    free_list();
    return 0;
}