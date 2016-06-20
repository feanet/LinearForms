#include <iostream>
#include "expression.h"
using namespace std;

// с коэффициентами пока косячки

int main()
{
    vector<int> idx {1};


    for (int i : idx) for (int j : idx)
        2*SVar{j,i} + 3*AVar{i,j} == 3.0;


    for (int i : idx) for (int j : idx)
        AVar{i,j} <= 5.0;


    Expression obj;
    for (int i : idx) for (int j : idx)
        obj += AVar{i,j} + SVar{i,j};



    cout << "Exp size " << obj.place.size() << endl;
    for (Var& v : obj.place)
        cout << v.type << " " << v.i << " " << v.j << endl;

}

