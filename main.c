#include <stdio.h>
#include <windows.h>
#include <conio.h> // Para _getch() e _kbhit()
#include "menu.h"
#include "funcoes.h"

#define UP_ARROW 72
#define DOWN_ARROW 80
#define ENTER_KEY 13

int main() {
    int selectedOption = 1;
    int keyPressed = 0;
    int screenWidth, screenHeight;
    int linhas, colunas, linhasB, colunasB;
    float **matrizA, **matrizB, **resultado;

    // obtem o tamanho do console
    getConsoleSize(&screenWidth, &screenHeight);

    do {
        printMenu(selectedOption, screenWidth, screenHeight);

        keyPressed = _getch();

        // navega com as setas ou numeros
        if (keyPressed == 0 || keyPressed == 224) { // Seta detectada
            keyPressed = _getch(); // Le a tecla pressionada
            if (keyPressed == UP_ARROW && selectedOption > 1) {
                selectedOption--;
            } else if (keyPressed == DOWN_ARROW && selectedOption < 8) {
                selectedOption++;
            }
        } else if (keyPressed >= '1' && keyPressed <= '8') {
            selectedOption = keyPressed - '0';
        }

        if (keyPressed == ENTER_KEY) {
            system("cls");

            if (selectedOption >= 1 && selectedOption <= 7) {
                printf("Digite o numero de linhas e colunas da matriz A: ");
                scanf("%d %d", &linhas, &colunas);
                alocaMatriz(&matrizA, linhas, colunas);
                printf("Leitura da matriz A:\n");
                leMatriz(matrizA, linhas, colunas);
            }

            if (selectedOption == 1 || selectedOption == 2 || selectedOption == 4) {
                printf("Digite o numero de linhas e colunas da matriz B: ");
                scanf("%d %d", &linhasB, &colunasB);
                alocaMatriz(&matrizB, linhasB, colunasB);
                printf("Leitura da matriz B:\n");
                leMatriz(matrizB, linhasB, colunasB);
            }

            switch (selectedOption) {
                case 1:
                    if (linhas != linhasB || colunas != colunasB) {
                        printf("As matrizes devem ter o mesmo tamanho para adicao!\n");
                    } else {
                        alocaMatriz(&resultado, linhas, colunas);
                        adicaoMatrizes(matrizA, matrizB, resultado, linhas, colunas);
                        printf("\nResultado da Adicao:\n");
                        imprimeMatriz(resultado, linhas, colunas);
                        liberaMatriz(resultado, linhas);
                    }
                    break;
                case 2:
                    if (linhas != linhasB || colunas != colunasB) {
                        printf("As matrizes devem ter o mesmo tamanho para subtracao!\n");
                    } else {
                        alocaMatriz(&resultado, linhas, colunas);
                        subtracaoMatrizes(matrizA, matrizB, resultado, linhas, colunas);
                        printf("\nResultado da Subtracao:\n");
                        imprimeMatriz(resultado, linhas, colunas);
                        liberaMatriz(resultado, linhas);
                    }
                    break;
                case 3:
                    alocaMatriz(&resultado, linhas, colunas);
                    float escalar;
                    printf("Digite o escalar: ");
                    scanf("%f", &escalar);
                    produtoPorEscalar(matrizA, escalar, resultado, linhas, colunas);
                    printf("\nResultado do Produto por Escalar:\n");
                    imprimeMatriz(resultado, linhas, colunas);
                    liberaMatriz(resultado, linhas);
                    break;
                case 4:
                    if (colunas != linhasB) {
                        printf("O numero de colunas da matriz A deve ser igual ao numero de linhas da matriz B!\n");
                    } else {
                        alocaMatriz(&resultado, linhas, colunasB);
                        produtoMatrizes(matrizA, matrizB, resultado, linhas, colunas, colunasB);
                        printf("\nResultado do Produto de Matrizes:\n");
                        imprimeMatriz(resultado, linhas, colunasB);
                        liberaMatriz(resultado, linhas);
                    }
                    break;
                case 5:
                    if (linhas != colunas) {
                        printf("A matriz deve ser quadrada para calcular o determinante!\n");
                    } else {
                        float det = determinante(matrizA, linhas);
                        printf("\nDeterminante da Matriz: %.2f\n", det);
                    }
                    break;
                case 6:
                    if (linhas != colunas) {
                        printf("A matriz deve ser quadrada para calcular a inversa!\n");
                    } else {
                        alocaMatriz(&resultado, linhas, colunas);
                        if (inversaMatriz(matrizA, resultado, linhas)) {
                            printf("\nMatriz Inversa:\n");
                            imprimeMatriz(resultado, linhas, colunas);
                        }
                        liberaMatriz(resultado, linhas);
                    }
                    break;
                case 7:
                    alocaMatriz(&resultado, colunas, linhas);
                    transposta(matrizA, resultado, linhas, colunas);
                    printf("\nMatriz Transposta:\n");
                    imprimeMatriz(resultado, colunas, linhas);
                    liberaMatriz(resultado, colunas);
                    break;
                case 8:
                    printCenteredText("Saindo...", screenWidth, screenHeight / 2);
                    return 0;
            }
            printf("\nPressione qualquer tecla para continuar...");
            _getch(); // Pausa para ver o resultado
        }

    } while (1);

    return 0;
}
