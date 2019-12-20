#include "view.h"
#include "deck.h"
int key_to_int(char c)
{
    switch(c)
    {
        case 'a': return 8;
        case 's': return 9;
        case 'd': return 10;
        case 'f': return 11;
        case 'j': return 12;
        case 'k': return 13;
        case 'l': return 14;
        case ';': return 15;
        case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8':
            return c - '1';
        default: return -1;   
    }
}
int int_to_key(int n)
{
    static char keys[] = {'1', '2', '3', '4', '5', '6', '7', '8', 'a', 's', 'd', 'f', 'j', 'k', 'l', ';'};
    if (n >=0 && n < 16) 
        return keys[n];
    return -1;
}