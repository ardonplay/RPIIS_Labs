#include <iostream>
#include "fenvick.h"

using namespace std;

int main() {
    int n = 0;
    int k = 0, l = 0, m = 0;
    cout<<"Введите сколько элементов в массиве: ";
    cin >> n;
    Fenvick tree(n);
    for (int i = 0; i < n; i++) {    //ввод массива и заполнение дерева Фенвика
        int t;
        cin >> t;
        tree.increase(i, t);
    }
    cout<<"Введите до какого числа вы хотите рассчитать сумму: "<<endl;
    cout<<">>";
    cin>>k;
    cout<<"Сумма эдементов от 0 до "<<k<<": "<<tree.sum(k-1)<<endl;
    cout<<"Введите диапазон с которой вы хотите посчитать сумму: "<<endl;
    cout<<">>";
    cin>>l>>m;
    cout<<"Сумма элементов от "<<l<<" до "<<m<<":"<<tree.sum(l, m)<<endl;
    tree.increase(3, 60);
    cout<<"Введите до какого числа вы хотите рассчитать сумму: "<<endl;
    cout<<">>";
    cin>>k;
    cout<<"Сумма эдементов от 0 до "<<k<<": "<<tree.sum(k-1)<<endl;

}