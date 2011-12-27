//
//  strcls.cpp
//  last
//
//  Created by Kandsoft on 21.12.11.

#include <iostream>
#include "strcls.h"
using namespace std;


/********************** 
  реализация класса
***********************/

// пустой конструктор
Strings::Strings(){
    rep = new Srep(0,"");
}

Strings::Strings(const char* s){
    rep = new Srep(strlen(s),s);
}

// копирование
Strings::Strings(const Strings& a){
    a.rep->n++;
    rep = a.rep; // разделяемое представление
}
   
Strings::~Strings(){
    if( --rep->n == 0 ) delete rep;
}


// перегрузка операторов =

Strings& Strings::operator=(const char* s){
    if (rep->n == 1)
        rep->assign(strlen(s), s);
    else {
        rep->n--;
        rep = new Srep(strlen(s),s);
    }
    
    return *this;
}

Strings& Strings::operator=(const Strings& x){
    x.rep->n++;     
    if( --rep->n == 0) delete rep;
    rep = x.rep;
    return *this;
}

ostream& operator<< (ostream& strm, Strings& str){
    return strm << str.rep->s << "\0\n";
}









