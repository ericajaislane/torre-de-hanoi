#include <windows.h>
#include "gotoxy.h"

// Função que move o cursor para (x, y) no terminal (Windows)
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;   // Coordenada X (coluna)
    coord.Y = y;   // Coordenada Y (linha)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
