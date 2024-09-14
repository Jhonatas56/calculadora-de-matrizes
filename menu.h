#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

// Define a posicao do cursor na janela do console.
void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;   // Define a coordenada X (horizontal) do cursor.
    coord.Y = y;   // Define a coordenada Y (vertical) do cursor.
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move o cursor para a coordenada especificada.
}

// Imprime o texto centralizado na tela do console na linha y.
void printCenteredText(const char* text, int screenWidth, int y) {
    int length = strlen(text); // Obtem o comprimento do texto.
    int x = (screenWidth - length) / 2; // Calcula a posicao X para centralizar o texto.
    setCursorPosition(x, y); // Move o cursor para a posicao calculada.
    printf("%s", text); // Imprime o texto na posicao atual do cursor.
}

// Imprime o menu com a opcao selecionada destacada.
void printMenu(int selectedOption, int screenWidth, int screenHeight) {
    system("cls"); // Limpa a tela do console.
    int menuStartY = (screenHeight / 2) - 5; // Calcula a posicao Y para centralizar o menu verticalmente.
    int menuPadding = 25; // Ajuste para garantir que os numeros fiquem alinhados.

    // Imprime o titulo do menu centralizado.
    printCenteredText("=== CALCULADORA DE MATRIZES ===", screenWidth, menuStartY);

    // Imprime cada opcao do menu, destacando a opcao selecionada com um '>' a esquerda.
    setCursorPosition((screenWidth - menuPadding) / 2, menuStartY + 2);
    printf((selectedOption == 1) ? "> 1.  Adicao de matrizes" : "  1.  Adicao de matrizes");

    setCursorPosition((screenWidth - menuPadding) / 2, menuStartY + 3);
    printf((selectedOption == 2) ? "> 2.  Subtracao de matrizes" : "  2.  Subtracao de matrizes");

    setCursorPosition((screenWidth - menuPadding) / 2, menuStartY + 4);
    printf((selectedOption == 3) ? "> 3.  Produto de um numero por uma matriz" : "  3.  Produto de um numero por uma matriz");

    setCursorPosition((screenWidth - menuPadding) / 2, menuStartY + 5);
    printf((selectedOption == 4) ? "> 4.  Produto de matrizes" : "  4.  Produto de matrizes");

    setCursorPosition((screenWidth - menuPadding) / 2, menuStartY + 6);
    printf((selectedOption == 5) ? "> 5.  Calculo de Determinante" : "  5.  Calculo de Determinante");

    setCursorPosition((screenWidth - menuPadding) / 2, menuStartY + 7);
    printf((selectedOption == 6) ? "> 6.  Matriz inversa" : "  6.  Matriz inversa");

    setCursorPosition((screenWidth - menuPadding) / 2, menuStartY + 8);
    printf((selectedOption == 7) ? "> 7.  Matriz transposta" : "  7.  Matriz transposta");

    setCursorPosition((screenWidth - menuPadding) / 2, menuStartY + 9);
    printf((selectedOption == 8) ? "> 8.  Sair" : "  8.  Sair");
}

// Obtem as dimensoes da tela do console.
void getConsoleSize(int *width, int *height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); // Obtem informacoes sobre o buffer da tela do console.
    *width = csbi.srWindow.Right - csbi.srWindow.Left + 1; // Calcula a largura da tela.
    *height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1; // Calcula a altura da tela.
}
