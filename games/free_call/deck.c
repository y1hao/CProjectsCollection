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
static struct deck_card *deck[16];
void deck_init()
{
    for (int i = 0; i < )
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
bool deck_is_movable(struct deck_card dest, struct deck_card src)
{

}
struct deck_card deck_peek(int stack, int num)
{

}
bool deck_is_winner()
{

}