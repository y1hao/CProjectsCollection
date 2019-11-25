#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
enum status
{
    NEW,
    MOVE,
    WIN,
    END,
    EXIT
} status = NEW;
int map[4][4];
int score;
int empty = 16;
enum dir
{
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
int main()
{
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
            case WIN:
                win();
                break;
            case END:
                end();
                break;
            default:
                break;
        }
    }
}
void new()
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            map[i][j] = 0;
    score = 0;
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
            case 'w': case 'k': case 38:
                dir = UP;
                break;
            case 'a': case 'h': case 37:
                dir = LEFT;
                break;
            case 's': case 'j': case 40:
                dir = DOWN;
                break;
            case 'd': case 'l': case 39:
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
                        ++map[cur++][c];
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
                        ++map[cur--][c];
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
                        ++map[r][cur++];
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
                        ++map[r][cur--];
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
    srand((unsigned)time(NULL));
    int new_block = 1;
    if (rand() % 10 == 0)
        new_block = 2;
    int n = rand() % empty + 1, i = 0;
    for (; i < 16; ++i)
        if (map[i / 4][i % 4] == 0)
        {
            if (--n == 0)
                break;
        }
    map[i / 4][i % 4] = new_block;
    --empty;
    return true;
}
void show()
{
    int cur;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
            if ((cur = (int)pow(2, map[i][j])) != 1)
                printf("%6d\t", (int)pow(2, map[i][j]));
            else
                printf("%6d\t", 0);
        printf("%c", '\n');
    }
    printf("\n");
    printf("empty:\t%d\n", empty);
}
void win()
{

}
void end()
{

}