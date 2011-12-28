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

/*
    перегрузки операторов ввода/вывода
 */

ostream& operator<< (ostream& out, const Strings& str){
    return out << str.rep->s << "\0\n";
}

istream& operator>> (istream& in, Strings& str){
    char *temp = new char[256];
    in.get(temp,255,'\n');

    str.rep->assign(strlen(temp), temp);
    delete [] temp;
        
    return in;
}

//////////////
// функции
//////////////

// проверка
void Strings::check (int i) const { 
    if (i < 0 || rep->sz <= i) 
        throw Range(); 
}

// запись символа
void Strings::write(int i, char c) { 
    if (i>=0 && i< rep->sz) { 
        rep = rep->get_own_copy(); 
        rep->s[i] = c; 
    }
}

// вывод символа
char Strings::read(int i) const { 
    return rep->s[i]; 
}

// длина строки
size_t Strings::len() const{
    return rep->sz;
}

// Поиск вхождения подстроки what, начиная с символа с номером start и заканчивая на символе end:
// int pos(T what, int start  = 0, int end = this->len)

int Strings::pos(Strings what, int start, int end){
    if (end > this->len() || start < 0 || end < 1 || start >= this->len() || end-start + 1 < what.len()){
        return -1; // в случае ошибки
    } else {
        // индикатор соответствия
        bool flag;
        
        for (int i = start; i < end - what.len(); i++){
            flag = true;
            for (int j = 0; j < what.len() && flag; j++){
                if (rep->s[i+j] != what[j])
                    flag = false;
            }
            if (flag) return i;
        }
        //если ничего не найдено - отправляем -1, знак, что ничего не найдено
        return -1;
            
    }
}

// Удаление подстроки. Две реализации. Первая удаляет первое вхождение
// указанной подстроки:
// void del(T& what)

void Strings::del(Strings& what){
    if (what.len() < this->len()){
        
    }
}










