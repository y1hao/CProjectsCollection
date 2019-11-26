#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define SET_TO_DEFAULT SetConsoleTextAttribute(handle, default_background | default_color)
#define SET_COLOR(i) SetConsoleTextAttribute(handle, background[(i)] | color[(i)])
enum status {
    NEW,
    MOVE,
    END,
    EXIT
} status = NEW;
int map[4][4];
unsigned long score;
int empty = 16;
int default_background;
int default_color;
HANDLE handle;
int background[] = {
//     0     2     4     8    16    32    64   128   256   512  1024  2048  4096  8192 16384 32768 65536
    0x70, 0x70, 0xf0, 0x60, 0xe0, 0x20, 0xa0, 0x30, 0xb0, 0x10, 0x90, 0x40, 0xc0, 0x50, 0xd0, 0x80, 0x00
};
int color[] = {
    0x08, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07
};
enum dir {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};
void new();
void move();
bool compute(enum dir);
void show();
void win();
void end();
bool test_cols();
bool test_rows();
int main()
{
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);
    default_background = info.wAttributes & 0xf0;
    default_color = info.wAttributes & 0xf;
    CONSOLE_CURSOR_INFO show_cursor;
    GetConsoleCursorInfo(handle, &show_cursor);
    CONSOLE_CURSOR_INFO hide_cursor = {.bVisible = false, .dwSize = 1};
    SetConsoleCursorInfo(handle, &hide_cursor);
    while (status != EXIT)
    {
        switch (status)
        {
            case NEW:
                new();
                break;
            case MOVE:
                move();
                break;
            case END:
                end();
                break;
            default:
                break;
        }
    }
    system("cls");
    printf("\n\n\tThank you for playing!");
    printf("\n\n\tAuthor: Yihao Wang, 26/11/2019\n");
    Sleep(2000);
    system("cls");
    SetConsoleCursorInfo(handle, &show_cursor);
}
void new()
{
    static char header[] = 
        "\n\n"
        "\t\tGame 2048\n\n\n"
        "\tMerge the squares to reach 2048\n\t (or as high as you can reach)\n"
        "\tUse arrow keys, or 'awsd',\n\t or vim-style 'jhkl' to control\n\n"
        "\tPress 'q' to exit \n\tPress 'n' to start a new game\n\n"
        "\t";
    system("cls");
    printf("%s", header);
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 4; ++c)
            map[r][c] = 0;
    score = 0;
    empty = 16;
    compute(UP);
    show();
    status = MOVE;
}
void move()
{
    enum dir dir;
    bool key_got = false;
    
    while (!key_got)
    {
        key_got = true;
        switch(_getch())
        {
            case 'w': case 'k': case 72:
                dir = UP;
                break;
            case 'a': case 'h': case 75:
                dir = LEFT;
                break;
            case 's': case 'j': case 80:
                dir = DOWN;
                break;
            case 'd': case 'l': case 77:
                dir = RIGHT;
                break;
            case 'q':
                status = EXIT;
                return;
            case 'n':
                status = NEW;
                return;
            default:
                key_got = false;
                break;
        }
    }
    if (compute(dir))
        show();
    else
        status = END;
}
bool compute(enum dir dir)
{
    switch (dir)
    {
        case UP:
            for (int c = 0; c < 4; ++c)
            {
                int cur = 0;
                for (int r = 1; r < 4; ++r)
                {
                    if (map[cur][c] == 0)
                    {
                        map[cur][c] = map[r][c];
                        map[r][c] = 0;
                    }
                    else if (map[r][c] == map[cur][c])
                    {
                        ++map[cur][c];
                        score += 1UL << map[cur][c];
                        ++cur;
                        map[r][c] = 0;
                        ++empty;
                    }
                    else if (map[r][c] != 0 && r - cur > 1)
                    {
                        map[++cur][c] = map[r][c];
                        map[r][c] = 0;
                    }
                    else if (map[r][c] != 0 && r - cur <= 1)
                    {
                        ++cur;
                    }
                }
            }
            break;
        case DOWN:
            for (int c = 0; c < 4; ++c)
            {
                int cur = 3;
                for (int r = 2; r >= 0 ; --r)
                {
                    if (map[cur][c] == 0)
                    {
                        map[cur][c] = map[r][c];
                        map[r][c] = 0;
                    }
                    else if (map[r][c] == map[cur][c])
                    {
                        ++map[cur][c];
                        score += 1UL << map[cur][c];
                        --cur;
                        map[r][c] = 0;
                        ++empty;
                    }
                    else if (map[r][c] != 0 && cur - r > 1)
                    {
                        map[--cur][c] = map[r][c];
                        map[r][c] = 0;
                    }
                    else if (map[r][c] != 0 && cur - r <= 1)
                    {
                        --cur;
                    }
                }
            }
            break;
        case LEFT:
            for (int r = 0; r < 4; ++r)
            {
                int cur = 0;
                for (int c = 1; c < 4; ++c)
                {
                    if (map[r][cur] == 0)
                    {
                        map[r][cur] = map[r][c];
                        map[r][c] = 0;
                    }
                    else if (map[r][c] == map[r][cur])
                    {
                        ++map[r][cur];
                        score += 1UL << map[r][cur];
                        ++cur;
                        map[r][c] = 0;
                        ++empty;
                    }
                    else if (map[r][c] != 0 && c - cur > 1)
                    {
                        map[r][++cur] = map[r][c];
                        map[r][c] = 0;
                    }
                    else if (map[r][c] != 0 && c - cur <= 1)
                    {
                        ++cur;
                    }
                }
            }
            break;
        case RIGHT:
            for (int r = 0; r < 4; ++r)
            {
                int cur = 3;
                for (int c = 2; c >= 0; --c)
                {
                    if (map[r][cur] == 0)
                    {
                        map[r][cur] = map[r][c];
                        map[r][c] = 0;
                    }
                    else if (map[r][c] == map[r][cur])
                    {
                        ++map[r][cur];
                        score += 1UL << map[r][cur];
                        --cur;
                        map[r][c] = 0;
                        ++empty;
                    }
                    else if (map[r][c] != 0 && cur - c > 1)
                    {
                        map[r][--cur] = map[r][c];
                        map[r][c] = 0;
                    }
                    else if (map[r][c] != 0 && cur - c <= 1)
                    {
                        --cur;
                    }
                }
            }
            break;
        default:
            break;
    }
    if (empty > 0)
    {
        srand((unsigned)time(NULL));
        int new_block = 1;
        if (rand() % 10 == 0)
            new_block = 2;
        int n = rand() % empty + 1, i = 0;
        for (; i < 16; ++i)
            if (map[i / 4][i % 4] == 0 && --n == 0)
                break;
        map[i / 4][i % 4] = new_block;
        --empty; 
    }
    if (!test_cols() && !test_rows())
        return false;
    return true;
}
bool test_rows()
{
    int c = 0, r = 0;
    for (; r < 4; ++r)
    {
        for (; c < 3; ++c)
            if (map[r][c] == map[r][c + 1] || map[r][c] == 0)
                return true;
        if (map[r][c] == 0)
            return true;
    }
    return false;
}
bool test_cols()
{
    int c = 0, r = 0;
    for (; c < 4; ++c)
    {
        for (; r < 3; ++r)
            if (map[r][c] == map[r + 1][c] || map[r][c] == 0)
                return true;
        if (map[r][c] == 0)
            return true;
    }
    return false;
}
void show()
{
    int cur;
    COORD coord = {8, 13};
    SetConsoleCursorPosition(handle, coord);
    for (int r = 0; r < 4; ++r)
    {
        for (int c = 0; c < 4; ++c)
        {
            SET_COLOR(map[r][c]);
            printf("     ");
        }
        SET_TO_DEFAULT;
        printf("\n\t");
        for (int c = 0; c < 4; ++c)
        {
            SET_COLOR(map[r][c]);
            if ((cur = 1 << map[r][c]) == 1)
                printf("     ");
            else if (cur < 10)
                printf("%3d  ", cur);
            else if (cur < 1000)
                printf("%4d ", cur);
            else
                printf("%5d", cur);
        }
        SET_TO_DEFAULT;
        printf("\n\t");
        for (int c = 0; c < 4; ++c)
        {
            SET_COLOR(map[r][c]);
            printf("     ");
        }
        SET_TO_DEFAULT;
        printf("\n\t");
    }
    SET_TO_DEFAULT;
    printf("\n\tScore:\t%lu\n", score);
}
void end()
{
    show();
    printf("\n\n\tGame ends, your final score is:\n\n\t");
    printf("%lu\n\n\t", score);
    printf("Press 'q' to quit, press 'n' to start a new game\n\n");
    while (true)
    {
        switch (_getch())
        {
            case 'q':
                status = EXIT;
                return;
            case 'n':
                status = NEW;
                return;
            default:
                break;
        }
    }
}