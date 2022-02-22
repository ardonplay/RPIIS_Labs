#include <iostream>
#include <fstream>
#include <ctime>
#include "fenvick.h"

using namespace std;

int main(){
    string line;
    int counter = 0;

    srand(time(nullptr));

    ofstream test;
    ifstream file;
    fstream log;
    test.open("../test.in");
    for(long long int i = 0; i <= rand() % 10000; i++){
        test << rand() % 10000 << endl;
    }
    test.close();

    file.open("../test.in");

    while(!file.eof()){
        getline(file, line);
        counter++;
    }

    file.close();
    file.open("../test.in");

    counter--;

    Fenvick tree(counter);
    int* default_array = new int[counter];

    for (int i = 0; i < counter; i++) {    //injection in default array and Fenvick tree
        getline(file, line);
        int element = stoi(line);
        tree.increase(i, element);
        default_array[i] = element;
    }

    file.close();

    int first = rand() % counter, last = rand() % counter;
    while(true){
        if(first < last)
            break;
        first = rand() % counter;
        last = rand() % counter;
    }
    //обычный расчет
    clock_t start = clock();
    int default_sum = 0;
    for(int i = first; i <= last; i++){
        default_sum += default_array[i];
    }
    clock_t end = clock();

    double default_array_time = end - start;

    //расчет через фенвика
    start = clock();
    int fenvick_sum = tree.sum(first, last);
    end = clock();

    double fenvick_array_time = end - start;

        cout<<"first element: "<<first<<endl;
        cout<<"last element: "<<last<<endl;
        cout<<"Обычный расчет: "<<default_sum<<" Время расчета: "<<default_array_time<<endl;
        cout<<"Расчет через Фенвика: "<<fenvick_sum<<" Время расчета: "<<fenvick_array_time<<endl;

    return 0;
}