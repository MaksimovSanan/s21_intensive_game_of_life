#include <ncurses.h>
#include <stdio.h>

//ДЛЯ КОМПИЛЯТОРА
// gcc -Wall -Werror -Wextra -Xlinker -lncurses

void draw(int *matrix);
int neighbours_checker(int *matrix, int row, int col);
int proverka(int *matrix, int *matrix2);
void privet(void);
void POKAPOKA(int flag);

int main() {
    int arr[25][80];
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    if (freopen("/dev/tty", "r", stdin) != NULL) {
        initscr();
        int speed;
        privet();
        scanw("%d", &speed);
        halfdelay(1);

        int tmp[25][80] = {0};
        int flag;
        int ULTRAflag = 0;
        char ch;

        while (ULTRAflag == 0) {
            for (int i = 0; i < 25; i++) {
                for (int j = 0; j < 80; j++) {
                    flag = neighbours_checker(&arr[0][0], i, j);
                    switch (flag) {
                        case 0:
                            tmp[i][j] = 0;
                            break;
                        case 1:
                            tmp[i][j] = (arr[i][j] == 1) ? 1 : 0;
                            break;
                        case 2:
                            tmp[i][j] = 1;
                    }
                }
            }
            if (proverka(&arr[0][0], &tmp[0][0]) == 0) {
                ch = getch();
                if (ch == '+') {
                    speed = speed / 2.0;
                } else if (ch == '-')
                    speed = speed * 2.0;
                else if (ch == 'q')
                    ULTRAflag = 2;
                napms(speed);
                draw(&tmp[0][0]);

                for (int i = 0; i < 25; i++) {
                    for (int j = 0; j < 80; j++) {
                        arr[i][j] = tmp[i][j];
                    }
                }
            } else
                ULTRAflag = 1;
        }
        POKAPOKA(ULTRAflag);
        endwin();
        return 0;
    }
}

void draw(int *matrix) {
    clear();
    int width = 26;
    int length = 81;

    for (int i = -1; i < width; i++) {
        for (int j = -1; j < length; j++) {
            if (i == -1 || i == 25 || j == -1 || j == 80) {
                printw("#");
            } else {
                if ((i < 25) && (j <= 80)) {
                    if (*(matrix + i * 80 + j) == 1) {
                        printw("*");
                    } else
                        printw(".");
                }
            }
        }
        printw("\n");
    }
    refresh();
}

int neighbours_checker(int *matrix, int row, int col) {
    // Принимает на вход указатель на массив и координаты проверяемой точки
    // На выходе 0, 1 или 2, где 0 - клетка мертвая , 1 - клетка
    // продолжает жить, 2 - в клетке зарождается жизнь
    int nhb_counter = 0;
    if (*(matrix + row * 80 + col) == 1) nhb_counter--;
    for (int rows = row - 1; rows < row + 2; rows++) {
        for (int cols = col - 1; cols < col + 2; cols++) {
            int true_row = (rows + 25) % 25;
            int true_col = (cols + 80) % 80;
            if (*(matrix + true_row * 80 + true_col) == 1) {
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

int proverka(int *matrix, int *matrix2) {
    // WIDTH = 25
    // LEN = 80
    int flag = 1;
    int count = 0;
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            if (*(matrix2 + i * 80 + j) == 1) count++;
            if (*(matrix + i * 80 + j) != *(matrix2 + i * 80 + j)) flag = 0;
        }
    }
    if (count == 0) flag = 1;
    return flag;
}

void privet(void) {
    printw(
        "---------------------------------------------------------------------"
        "-----------\n");
    printw("\n");
    printw("\n");
    printw("\n");
    printw("\t\tWelcome to the Game of life!\n");
    printw("\n");
    printw("\n");
    printw("\n");
    printw("\t\tpress + to speed up or - to slow down\n");
    printw("\n");
    printw("\n");
    printw("\n");
    printw("\t\tPress q to exit\n");
    printw("\n");
    printw("\n");
    printw("\n");
    printw(
        "---------------------------------------------------------------------"
        "-----------\n");

    printw("Enter delay:\n");
}

void POKAPOKA(int flag) {
    halfdelay(50);
    switch (flag) {
        case 1:
            printw("STATIC FIGURE OR EMPTY FIELD");
            break;
        case 2:
            printw("GAME OVER, GOOD BYE");
            break;
    }
    getch();
}
