#ifndef SORT_H
#define SORT_H

#include "structures.h"

int findFood(int id)
{
    for(int i = 0; i < menuCount; i++)
        if(menu[i].foodID == id)
            return i;

    return -1;
}

void sortByRating()
{
    for(int i = 0; i < menuCount - 1; i++)
    {
        for(int j = 0; j < menuCount - i - 1; j++)
        {
            if(menu[j].rating < menu[j + 1].rating)
            {
                MenuItem temp = menu[j];
                menu[j] = menu[j + 1];
                menu[j + 1] = temp;
            }
        }
    }
}

void sortByPrice()
{
    for(int i = 0; i < menuCount - 1; i++)
    {
        for(int j = 0; j < menuCount - i - 1; j++)
        {
            if(menu[j].price > menu[j + 1].price)
            {
                MenuItem temp = menu[j];
                menu[j] = menu[j + 1];
                menu[j + 1] = temp;
            }
        }
    }
}

#endif