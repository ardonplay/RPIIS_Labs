//
// Created by Vladimir Moshchuk on 20.02.22.
//

#include "fenvick.h"
#include <iostream>

Fenvick::Fenvick(int  number_of_array_elements)
{
    this-> number_of_array_elements =  number_of_array_elements;
    array = new int[ number_of_array_elements];
    bit = new int[ number_of_array_elements];
}

Fenvick::~Fenvick()
{
    delete [] array;
    delete [] bit;
}

void Fenvick::increase(int index, int delta)
{
    array[index] += delta;

    for (; index <  number_of_array_elements; index |= index + 1) {
        bit[index] += delta;
    }
}

int Fenvick::sum(int x)
{
    int result = 0;
    for (; x >= 0; x = (x & (x + 1)) - 1) {
        result += bit[x];
    }

    return result;
}

int Fenvick::sum(int l, int r)
{
    if(l)
    {
        return sum(r) - sum(l - 1);
    }
    else
    {
        return sum(r);
    }
}
