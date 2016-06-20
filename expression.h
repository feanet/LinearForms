#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <vector>
#include <iostream>
using namespace std;

typedef enum { tO, tS, tH, tA } VType;

struct OVar { int i, j; static const VType v = tO; };
struct SVar { int i, j; static const VType v = tS; };
struct HVar { int i, j; static const VType v = tH; };
struct AVar { int i, j; static const VType v = tA; };



typedef struct {int i, j; double coeff; const VType type; } Var;

typedef enum { Less, Equal } Sense;



struct Expression
{
    Sense sense;
    double rhs;
    vector<Var> place;

    Expression() {}

    Expression(AVar&& a) {
        place.push_back( Var{ a.i, a.j, 1.0, tA });
        cout << "AVar up to Expression" << endl;
    }
    Expression(SVar&& a) {
        place.push_back( Var{ a.i, a.j, 1.0, tS });
        cout << "SVar up to Expression" << endl;
    }

    Expression(Var&& a) {
        place.push_back( a );
        cout << "SVar up to Expression" << endl;
    }

//    Expression& operator*(double d)
//    {
//        for (Var& v : place)
//            v.coeff *= d;

//        return *this;
//    }


    void operator+=(const Expression& e)
    {
        for (const Var& v : e.place)
            place.push_back(v);
    }
};


/////////////////////////////////////////////////////////////////////
/// Оператор умножения на константу
/// Функции отличаются только move-семантикой у второго метода
/////////////////////////////////////////////////////////////////////


template<class B>
Var operator*(double d, B&& b)
{
    cout << "Up to Var" << endl;
    return Var{b.i, b.j, d, B::v};
}


/////////////////////////////////////////////////////////////////////
/// Оператор plus
/// Функции отличаются только move-семантикой у второго метода
/////////////////////////////////////////////////////////////////////

template<class B>
Expression& operator+(Expression& e, B&& b)
{
    e.place.push_back( Var{b.i,b.j, 1.0, B::v} );
    cout << "expression& + B" << endl;
    return e;
}

Expression& operator+(Expression&& e, Var&& v)
{
    e.place.push_back(v);
    cout << "plus var" << endl;
    return e;
}

template<class B>
Expression& operator+(Expression&& e, B&& b)
{
    e.place.push_back( Var{ b.i, b.j, 1.0, B::v} );
    cout << "expression&& + B" << endl;
    return e;
}



/////////////////////////////////////////////////////////////////////
/// Оператор равно константе
/////////////////////////////////////////////////////////////////////
Expression& operator==(Expression& e, double b)
{
    e.rhs = b;
    e.sense = Equal;
    cout << "equals& + b" << endl;
    return e;
}

Expression& operator==(Expression&& e, double b)
{
    e.rhs = b;
    e.sense = Equal;
    cout << "equals&& + b" << endl;
    return e;
}



/////////////////////////////////////////////////////////////////////
/// Оператор меньше константы
/////////////////////////////////////////////////////////////////////

Expression& operator<=(Expression& e, double b)
{
    e.rhs = b;
    e.sense = Less;
    cout << "less& + b" << endl;
    return e;
}

Expression& operator<=(Expression&& e, double b)
{
    e.rhs = b;
    e.sense = Less;
    cout << "less&& + b" << endl;
    return e;
}




/////////////////////////////////////////////////////////////////////
/// Оператор равно
/////////////////////////////////////////////////////////////////////
Expression& operator==(Expression& e, Expression& b)
{
    for (auto& v : b.place)
    {
        v.coeff = -v.coeff;
        e.place.push_back(v);
    }
    e.sense = Equal;
    cout << "equals& expression" << endl;
    return e;
}

Expression& operator==(Expression& e, Expression&& b)
{
    for (Var& v : b.place)
    {
        v.coeff = -v.coeff;
        e.place.push_back(v);
    }
    e.sense = Equal;
    cout << "equals&& expression" << endl;
    return e;
}

Expression& operator==(Expression&& e, Expression&& b)
{
    for (Var& v : b.place)
    {
        v.coeff = -v.coeff;
        e.place.push_back(v);
    }
    e.sense = Equal;
    cout << "equals&&& expression" << endl;
    return e;
}



/////////////////////////////////////////////////////////////////////
/// Оператор равно
/////////////////////////////////////////////////////////////////////
Expression& operator<=(Expression& e, Expression& b)
{
    for (Var& v : b.place)
    {
        v.coeff = -v.coeff;
        e.place.push_back(v);
    }
    e.sense = Less;
    cout << "less& expression" << endl;
    return e;
}

Expression& operator<=(Expression& e, Expression&& b)
{
    for (Var& v : b.place)
    {
        v.coeff = -v.coeff;
        e.place.push_back(v);
    }
    e.sense = Less;
    cout << "less&& expression" << endl;
    return e;
}

Expression& operator<=(Expression&& e, Expression&& b)
{
    for (Var& v : b.place)
    {
        v.coeff = -v.coeff;
        e.place.push_back(v);
    }
    e.sense = Less;
    cout << "less&&& expression" << endl;
    return e;
}




/////////////////////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////////////////////



//template<class A, class B>
//Expression operator+(A&& a, B&& b)
//{
//    Expression e;
//    e.place.push_back( Var{1.0,a.i,a.j, A::v });
//    e.place.push_back( Var{1.0,b.i,b.j, B::v });

//    cout << "New expression" << endl;
//    return e;
//}





#endif // EXPRESSION_H
