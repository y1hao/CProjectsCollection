#include <conio.h>
#include <Windows.h>
#include "deck.h"
#include "view.h"

enum status {
    INIT,
    SELECT,
    MOVE,
    QUIT
};
void game_init(enum status *status, int *stack, int *count)
{
    *status = SELECT;
    *stack = 0;
    *count = 0;
}
void game_select(enum status *status, int *stack, int *count)
{
    while (true)
    {
        int c = _getch();
        switch (c)
        {
            case 
        }
    }
}
void game_move(enum status *status, int *stack, int *count)
{

}
int main()
{
    enum status status = INIT;
    int stack, count;
    while (status != QUIT)
    {
        switch (status)
        {
            case INIT:
                game_init(&status, &stack, &count);
                break;
            case SELECT:
                game_select(&status, &stack, &count);
                break;
            case MOVE:
                game_move(&status, &stack, &count);
                break;
            default:
                break;
        }  
    }
    system("cls");
    printf(
        "\n"
        "\n"
        "\tThank you for playing!\n"
        "\tAuthor: Yihao Wang, 20/12/2019\n"
    );
}