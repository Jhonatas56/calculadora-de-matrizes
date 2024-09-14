#include <stdio.h>
#include <stdlib.h>

// Aloca memoria para uma matriz de floats com o numero de linhas e colunas especificado.
void alocaMatriz(float ***matriz, int linhas, int colunas) {
    int i;
    *matriz = (float **)malloc(linhas * sizeof(float *)); // Aloca memoria para as linhas da matriz.
    for (i = 0; i < linhas; i++) {
        (*matriz)[i] = (float *)malloc(colunas * sizeof(float)); // Aloca memoria para as colunas de cada linha.
    }
}

// Libera a memoria alocada para uma matriz.
void liberaMatriz(float **matriz, int linhas) {
    int i;
    for (i = 0; i < linhas; i++) {
        free(matriz[i]); // Libera a memoria de cada linha.
    }
    free(matriz); // Libera a memoria para o array de ponteiros de linhas.
}

// Le os elementos de uma matriz a partir da entrada padrao.
void leMatriz(float **matriz, int linhas, int colunas) {
    int i, j;
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            printf("Elemento [%d][%d]: ", i + 1, j + 1); // Solicita o elemento na posicao [i][j].
            scanf("%f", &matriz[i][j]); // Le o elemento e armazena na matriz.
        }
    }
}

// Imprime os elementos de uma matriz formatados com duas casas decimais.
void imprimeMatriz(float **matriz, int linhas, int colunas) {
    int i, j;
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            printf("%.2f ", matriz[i][j]); // Imprime o elemento com duas casas decimais.
        }
        printf("\n"); // Move para a proxima linha apos imprimir uma linha da matriz.
    }
}

// Troca duas linhas em uma matriz.
void trocaLinhas(float **matriz, int linha1, int linha2, int colunas) {
    int i;
    for (i = 0; i < colunas; i++) {
        float temp = matriz[linha1][i]; // Armazena o elemento da linha1.
        matriz[linha1][i] = matriz[linha2][i]; // Substitui o elemento da linha1 pelo da linha2.
        matriz[linha2][i] = temp; // Substitui o elemento da linha2 pelo original da linha1.
    }
}

// Calcula a matriz inversa usando o metodo de Gauss-Jordan.
int inversaMatriz(float **matriz, float **inversa, int n) {
    int i, j, k;

    // Inicializa a matriz inversa como a matriz identidade.
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j) {
                inversa[i][j] = 1;
            } else {
                inversa[i][j] = 0;
            }
        }
    }

    // Aplica o metodo de Gauss-Jordan para encontrar a matriz inversa.
    for (i = 0; i < n; i++) {
        if (matriz[i][i] == 0) {
            int trocou = 0;
            for (j = i + 1; j < n; j++) {
                if (matriz[j][i] != 0) {
                    trocaLinhas(matriz, i, j, n); // Troca as linhas na matriz original.
                    trocaLinhas(inversa, i, j, n); // Troca as linhas na matriz inversa.
                    trocou = 1;
                    break;
                }
            }
            if (!trocou) {
                printf("A matriz nao tem inversa.\n");
                return 0; // A matriz nao tem inversa.
            }
        }

        float pivo = matriz[i][i];
        for (j = 0; j < n; j++) {
            matriz[i][j] /= pivo; // Normaliza a linha da matriz original.
            inversa[i][j] /= pivo; // Normaliza a linha da matriz inversa.
        }

        for (j = 0; j < n; j++) {
            if (i != j) {
                float fator = matriz[j][i];
                for (k = 0; k < n; k++) {
                    matriz[j][k] -= fator * matriz[i][k]; // Elimina o termo na linha j.
                    inversa[j][k] -= fator * inversa[i][k]; // Elimina o termo correspondente na inversa.
                }
            }
        }
    }
    return 1; // Retorna 1 se a inversa foi calculada com sucesso.
}

// Realiza a adicao de duas matrizes e armazena o resultado na matriz resultado.
void adicaoMatrizes(float **a, float **b, float **resultado, int linhas, int colunas) {
    int i, j;
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            resultado[i][j] = a[i][j] + b[i][j]; // Adiciona os elementos correspondentes das duas matrizes.
        }
    }
}

// Realiza a subtracao de duas matrizes e armazena o resultado na matriz resultado.
void subtracaoMatrizes(float **a, float **b, float **resultado, int linhas, int colunas) {
    int i, j;
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            resultado[i][j] = a[i][j] - b[i][j]; // Subtrai os elementos correspondentes das duas matrizes.
        }
    }
}

// Realiza a multiplicacao de uma matriz por um escalar e armazena o resultado na matriz resultado.
void produtoPorEscalar(float **a, float escalar, float **resultado, int linhas, int colunas) {
    int i, j;
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            resultado[i][j] = a[i][j] * escalar; // Multiplica cada elemento da matriz pelo escalar.
        }
    }
}

// Realiza a multiplicacao de duas matrizes e armazena o resultado na matriz resultado.
void produtoMatrizes(float **a, float **b, float **resultado, int linhasA, int colunasA, int colunasB) {
    int i, j, k;
    for (i = 0; i < linhasA; i++) {
        for (j = 0; j < colunasB; j++) {
            resultado[i][j] = 0;
            for (k = 0; k < colunasA; k++) {
                resultado[i][j] += a[i][k] * b[k][j]; // Calcula o produto matricial.
            }
        }
    }
}

// Calcula o determinante de uma matriz quadrada.
float determinante(float **matriz, int n) {
    if (n == 1) {
        return matriz[0][0]; // Determinante de uma matriz 1x1.
    } else if (n == 2) {
        return matriz[0][0] * matriz[1][1] - matriz[0][1] * matriz[1][0]; // Determinante de uma matriz 2x2.
    } else {
        float det = 0;
        int i, j, k;
        for (i = 0; i < n; i++) {
            float **submatriz;
            alocaMatriz(&submatriz, n - 1, n - 1); // Aloca memoria para a submatriz.
            for (j = 1; j < n; j++) {
                for (k = 0; k < n; k++) {
                    if (k < i) {
                        submatriz[j - 1][k] = matriz[j][k];
                    } else if (k > i) {
                        submatriz[j - 1][k - 1] = matriz[j][k];
                    }
                }
            }
            det += matriz[0][i] * determinante(submatriz, n - 1) * (i % 2 == 0 ? 1 : -1); // Calcula o determinante usando a expansao de Laplace.
            liberaMatriz(submatriz, n - 1); // Libera a memoria da submatriz.
        }
        return det;
    }
}

// Calcula a matriz transposta de uma matriz.
void transposta(float **a, float **resultado, int linhas, int colunas) {
    int i, j;
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            resultado[j][i] = a[i][j]; // Transpoe os elementos da matriz.
        }
    }
}
