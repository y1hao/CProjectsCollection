#include <stdbool.h>
#include <stdlib.h>
#include "deck.h"

struct deck_card {
    int val;
    enum {
        HEART,
        DIAMOND,
        SPADE,
        CLUB
    } suit
};
static struct deck {
    deck_card stack;
    int ptr;
} deck[16];
void deck_init()
{
    if (*deck == NULL)
    {
        for (int i = 0; i < 16; ++i)
        {
            deck[i] = malloc(sizeof struct deck * 16);
            deck[i].ptr = 0;
            deck[i].stack = malloc(sizeof deck_card * 19);
        }
    }
    int 
}
void deck_move(int dest, int src, int num)
{

}
int deck_count_empty()
{

}
int deck_count_continuous(int stack)
{

}
bool deck_is_continuous(int stack, int num)
{

}
bool deck_is_movable(deck_card dest, deck_card src)
{

}
struct deck_card deck_peek(int stack, int num)
{

}
bool deck_is_winner()
{

}