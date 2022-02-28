//
// Created by Vladimir Moshchuk on 20.02.22.
//

#ifndef LAB1_FENVICK_H
#define LAB1_FENVICK_H


class Fenvick
{
private:
    int number_of_array_elements;
    int  *array;
    int *bit;

public:
    explicit Fenvick(int number_of_array_elements);
    ~Fenvick();

    void increase(int i, int delta);
    int sum(int x);
    int sum(int l, int r);
};


#endif //LAB1_FENVICK_H