#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define SIZE 3

//Fun��o imprimir novo estado conforme movimento do jogador.
void printMatriz(int matriz[SIZE][SIZE]) {
    system(CLEAR); // Limpa a tela antes de imprimir.
    printf("\n  8-PUZZLE \n");
    printf("\n");
    for (int i = 0; i < SIZE; i++) {

        for (int j = 0; j < SIZE; j++) {
            if ((i + j) % 2 == 0) {
                printf("\x1B[48;2;50;50;50m\x1B[38;2;255;255;255m"); // Fundo cinza escuro e texto branco
            } else {
                printf("\x1B[48;2;0;0;0m\x1B[38;2;255;255;255m"); // Fundo preto e texto branco
            }
            int num = matriz[i][j];
            int espacos = 3 - 1; // N�mero de espa�os para centralizar (3 � o tamanho do n�mero m�ximo 9)
            printf("%*d%*s", espacos, num, espacos, ""); // Imprime n�mero centralizado com espa�os
        }
        printf("\x1B[0m\n"); // Reset de formata��o de cor
    }
}

//Fun��o para ler movimento do usu�rio e modifica o estado do puzzle.
void ler(int matriz[SIZE][SIZE], int input) {
    int row_9, col_9, row_input, col_input;
    int distanciaMaxima = 1; // M�xima dist�ncia permitida.

    // Encontre as posi��es do n�mero 9 e do n�mero de entrada.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matriz[i][j] == 9) {
                row_9 = i;
                col_9 = j;
            }
            if (matriz[i][j] == input) {
                row_input = i;
                col_input = j;
            }
        }
    }

    // Verifique se a dist�ncia entre os n�meros � menor ou igual � dist�ncia m�xima permitida.
    int distancia = abs(row_input - row_9) + abs(col_input - col_9);
    if (distancia <= distanciaMaxima) {
        matriz[row_9][col_9] = input;
        matriz[row_input][col_input] = 9;
    }
}

//Fun��o para indicar se o puzzle foi resolvido ou n�o.
int PuzzleCompleto(int matriz[SIZE][SIZE]) {
    int mat[SIZE][SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, i, j, cont = 0;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (mat[i][j] == matriz[i][j]) {
                cont++;
            }
        }
    }
    if (cont == SIZE * SIZE) {

    char l=3,
    b= 1;

    // frequ�ncia e dura��o
    Beep(2000,200);
    Beep(2500,250);
    Beep(3000,1000);

        printf("\n");
        printf("\n  !! JOGO CONCLU�DO !! %c %c ", l, b);
        printf("\n");
        return 1;
    }
    return 0;
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    int matriz[SIZE][SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 9, 8}};
    int used[9] = {0};
    srand(time(0));
    int i, j, num;

    // Preenchendo a matriz 3x3 com valores de 1 a 9 sem repeti��o.
     for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            do {
                num = rand() % 9 + 1;
            } while (used[num - 1]);
            used[num - 1] = 1;
            matriz[i][j] = num;
        }
    }



    printMatriz(matriz);

    int passos = 0, Resposta;
    do {
        int input;
        printf("\n");
        printf("Mova a pe�a: ");
        scanf("%d", &input);

        ler(matriz, input);
        printMatriz(matriz);

        passos++;
        Resposta=PuzzleCompleto(matriz);
    } while (Resposta!=1);

    return 0;
}
