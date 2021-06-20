#include <stdbool.h>
#include <conio.h>
#include <Windows.h>
#include "deck.h"
#include "view.h"

enum status {
    INIT,
    SELECT,
    MOVE,
    QUIT,
    WIN
};

void game_init(enum status *status, int *src, int *count, int *dest)
{
    deck_init();
    *status = SELECT;
    *src = -1;
    *dest = -1;
    *count = 0;
    show_info();
    for (int i = 0; i < 16; ++i)
        show_stack(i, *src, *count);
}
void game_select(enum status *status, int *src, int *count, int *dest)
{
    while (true)
    {
        int c = _getch();
        if (c == 'q')
        {
            *status = QUIT;
            return;
        }
        if (c == 'n')
        {
            *status = INIT;
            return;
        }
        int stack = key_to_int(c);
        if (stack < 4)
            continue;
        if (stack == *src)
        {
            if (*count < deck_count_continuous(*src))
                ++*count;
            else 
                *count = 0;
            show_stack(stack, *src, *count);
            return;
        }
        else
        {
            *dest = stack;
            *status = MOVE;
            return;
        }
    }
}
void game_move(enum status *status, int *src, int *count, int *dest)
{
    *status = SELECT;
    if (!deck_is_movable())
        return;
    deck_move(*dest, *src, *count);
    show_stack(*dest, -1, 0);
    show_stack(*src, -1, 0);
    if (deck_is_winner())
        *status = WIN;
}
void game_win()
{
    show_win();
    int c = _getch();
    if (c == 'q')
        *status = QUIT;
    else if (c == 'n')
        *status = INIT;
    return;
}
void game_end()
{
    deck_finish();
}
int main()
{
    enum status status = INIT;
    int src, count, dest;
    while (status != QUIT)
    {
        switch (status)
        {
            case INIT:
                game_init(&status, &src, &count, &dest);
                break;
            case SELECT:
                game_select(&status, &stack, &count, &dest);
                break;
            case MOVE:
                game_move(&status, &stack, &count, &dest);
                break;
            case WIN:
                game_win();
        }  
    }
    game_end();
    system("cls");
    printf(
        "\n"
        "\n"
        "\tThank you for playing!\n"
        "\tAuthor: Yihao Wang, 22/12/2019\n"
    );
}