#include <conio.h>
#include <Windows.h>
#include "deck.h"
#include "view.h"

enum status {
    INIT,
    SELECT,
    MOVE,
    QUIT
} status = INIT;

int main()
{
    int c;
    while (status != QUIT)
    {
        switch (status)
        {
            case INIT:
                break;
            case SELECT:
                break;
            case MOVE:
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