#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5

// Símbolos:
// ~ = água, # = navio, X = acerto, o = erro

void inicializar(char tabuleiro[SIZE][SIZE], char valor) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            tabuleiro[i][j] = valor;
}

void mostrar(char tabuleiro[SIZE][SIZE], int revelar) {
    printf("   ");
    for (int j = 0; j < SIZE; j++) printf("%d ", j+1);
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%c  ", 'A' + i);
        for (int j = 0; j < SIZE; j++) {
            char c = tabuleiro[i][j];
            if (!revelar && c == '#') c = '~';
            printf("%c ", c);
        }
        printf("\n");
    }
}

void posicionarNavio(char tabuleiro[SIZE][SIZE]) {
    int linha = rand() % SIZE;
    int coluna = rand() % SIZE;
    tabuleiro[linha][coluna] = '#';
}

int jogar(char oculto[SIZE][SIZE], char visivel[SIZE][SIZE], int linha, int coluna) {
    if (visivel[linha][coluna] == 'X' || visivel[linha][coluna] == 'o')
        return -1; // já jogado

    if (oculto[linha][coluna] == '#') {
        visivel[linha][coluna] = 'X';
        return 1; // acerto
    } else {
        visivel[linha][coluna] = 'o';
        return 0; // erro
    }
}

int main() {
    srand(time(NULL));

    char jogador[SIZE][SIZE], computador[SIZE][SIZE];
    char visivel[SIZE][SIZE];

    inicializar(jogador, '~');
    inicializar(computador, '~');
    inicializar(visivel, '~');

    // Um navio para cada lado
    posicionarNavio(jogador);
    posicionarNavio(computador);

    printf("===== BATALHA NAVAL SIMPLES =====\n");
    printf("Tabuleiro %dx%d, cada lado tem 1 navio escondido.\n", SIZE, SIZE);
    printf("Digite jogadas como A1, B3, etc.\n\n");

    int fim = 0;
    while (!fim) {
        mostrar(visivel, 0);
        char letra;
        int num;
        printf("\nSua jogada: ");
        scanf(" %c%d", &letra, &num);
        int linha = letra - 'A';
        int coluna = num - 1;

        if (linha < 0 || linha >= SIZE || coluna < 0 || coluna >= SIZE) {
            printf("Coordenada inválida!\n");
            continue;
        }

        int res = jogar(computador, visivel, linha, coluna);
        if (res == -1) {
            printf("Você já jogou aqui! Tente outra posição.\n");
            continue;
        } else if (res == 1) {
            printf("ACERTOU! Você venceu!\n");
            fim = 1;
        } else {
            printf("Água! Agora é a vez do computador...\n");
            // Jogada simples do computador
            int lr, cr, r;
            do {
                lr = rand() % SIZE;
                cr = rand() % SIZE;
                r = jogar(jogador, jogador, lr, cr);
            } while (r == -1);

            printf("Computador jogou em %c%d -> ", 'A'+lr, cr+1);
            if (r == 1) {
                printf("acertou seu navio! Você perdeu...\n");
                fim = 1;
            } else {
                printf("errou.\n");
            }
        }
    }

    printf("\nTabuleiro do computador (revelado):\n");
    mostrar(computador, 1);

    return 0;
}
