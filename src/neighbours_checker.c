// Принимает на вход указатель на массив и координаты проверяемой точки
// На выходе 0, 1 или 2, где 0 - клетка мертвая , 1 - клетка
// продолжает жить, 2 - в клетке зарождается жизнь

#include <stdio.h>
#define LEN 3
#define WIDTH 3

int neighbours_checker(int *matrix, int row, int col);

int main(void) {
    int matrix[3][3] = {{0, 1, 0}, {1, 0, 1}, {0, 0, 0}};
    printf("\n%d", neighbours_checker(&matrix[0][0], 1, 1));
    return 0;
}

int neighbours_checker(int *matrix, int row, int col) {
    int nhb_counter = 0;
    if (*(matrix + row * LEN + col) == 1) nhb_counter--;
    for (int rows = row - 1; rows < row + 2; rows++) {
        for (int cols = col - 1; cols < col + 2; cols++) {
            if (*(matrix + rows * LEN + cols) == 1) {
                nhb_counter++;
            }
        }
    }
    int flag = 0;
    if (nhb_counter >= 2 && nhb_counter <= 3) {
        flag = 1;
        if (nhb_counter == 3) flag = 2;
    }
    return flag;
}
