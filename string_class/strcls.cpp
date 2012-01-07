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
   
// деструктор
Strings::~Strings(){
    if( --rep->n == 0 ) delete rep;
}


////////////////////////////
//
//   перегрузка операторов
//
////////////////////////////

Strings& Strings::operator=(const char* s){
    if (rep->n == 1)
        rep->assign(strlen(s), s);
    else {
        rep->n--;
        rep = new Srep(strlen(s),s);
    }
    
    return *this;
}

// перегрузка = с подсчетом ссылок
Strings& Strings::operator=(const Strings& x){
    x.rep->n++;     
    if( --rep->n == 0) delete rep;
    rep = x.rep;
    return *this;
}

// перегрузка + (ака конкатенация в нашем случае) 
Strings& Strings::operator+(const Strings& x){
    
    char* temp = new char[this->len() + x.len() + 1];
    
    for(int i = 0; i < this->len(); i++)
        temp[i] = this->read(i);
    
    for(int i = 0; i < x.len(); i++)
        temp[i+this->len()] = x[i];

    return *new Strings(temp);
}


// перегрузка знака +=
Strings& Strings::operator+=(const Strings& x){
    
    char* temp = new char[this->len() + x.len() + 1];
    
    for(int i = 0; i < this->len(); i++)
        temp[i] = this->read(i);
    
    for(int i = 0; i < x.len(); i++)
        temp[i+this->len()] = x[i];
    
    this->rep->assign(strlen(temp), temp);
    delete [] temp;
    
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

////////////////////
//
//    функции
//
////////////////////


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


/*
 Поиск вхождения подстроки what, начиная с символа с номером start и заканчивая на символе end:
 int pos(T what, int start  = 0, int end = this->len)
*/

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

/*
    Удаление подстроки. Две реализации. Первая удаляет первое вхождение
    указанной подстроки:
    void del(T& what)
*/

void Strings::del(Strings& what){
    if (what.len() < this->len()){
        bool flag; // флаг о том, что вхождение найдено
        for (int i = 0; i < this->len() - what.len() && !flag; i++){
            flag = true;
            
            // проверяем полное ли вхождение
            for(int j = 0; j < what.len() && flag; j++){
                if (this->read(i+j) != what[j])
                    flag = false;
            }
            
            // если полное
            if (flag) {
                char* a = new char[i+1];
                strncpy(a, this->rep->s, i);
                
                char* b = new char[this->len() - i - what.len() + 1];
                int size = (this->len() - (i + what.len()));
                
                for (int g = 0; g < size; g++){
                    b[g] = this->read(g+i+what.len());
                }
                
                // освобождаем себя от дальнейшего извращенства
                Strings aTemp = a, 
                        bTemp = b;
                
                *this = *new Strings(aTemp+bTemp);
                
                //чистимся
                delete [] a;
                delete [] b;
            }
        }
    }
}


/*
    Удаление подстроки. 
    Вторая удаляет подстроку указанной длины по указанной позиции:
    void del(int begin, int length)
 */

void Strings::del(int begin,int length){
    
    // проверяем на ограничения
    if (this->len() > begin || this->len() < begin+length){
        
        begin--; //декриментим, так как символы будем считать как надо 1,2,3… а не 0,1…
        // создаем временную переменную
        char* temp = new char[this->len() - (begin + length)];
        int j = 0; //для корректной нумерации переменной temp
        
        for (int i = 0; i < this->len(); i++){
            if (i > begin && i <= begin+length)
                continue;
            
            temp[j] = this->read(i);
            j++;
        }
        
        this->rep->assign(strlen(temp), temp);
        delete [] temp; // очищаем временную переменную
    }
}


/* 
    Удаление всех входжений подстроки:
    void delall(T& what)
 
    TODO: проверить, что за упоротая магия парила мозги в течении часа с левым символом во втором вхождении
 */

void Strings::delall(Strings& what){
    if (this->len() >= what.len()){
        bool flag;
        
        for (int i = 0; i < this->len() - what.len(); i++){
            flag = true;
            
            // проверяем полное ли вхождение
            for(int j = 0; j < what.len(); j++){
                if (this->read(i+j) != what[j])
                    flag = false;
            }
            
            // если полное
            if (flag) {
                char* a = new char[i+1];
                strncpy(a, this->rep->s, i);
                
                char* b = new char[this->len() - i - what.len() + 1];
                int size = (this->len() - (i + what.len()));
                
                for (int g = 0; g < size; g++){
                    b[g] = this->read(g+i+what.len());
                }
            
                // освобождаем себя от дальнейшего извращенства
                Strings aTemp = a, 
                bTemp = b;
                
                *this = *new Strings(aTemp+bTemp);
                
                //чистимся
                delete [] a;
                delete [] b;
                
                //инкриментим, чтобы не крутить в холостую
                i += what.len();
            }
        }
        
    }
}

/*
    Вставка подстроки на указанную позицию:
    void ins(T& what, int where)
 */

void Strings::ins(Strings& what, int where){
    if (where < this->len() && where >= 0){
        
        //первая часть слова
        char* a = new char[where+1];
        strncpy(a, this->rep->s, where);
        
        //вторая часть
        char* b = new char[this->len() - where + 1];
        for (int i = 0; i < this->len(); i++){
            b[i] = this->read(i + where);
        }
        
        Strings aT = a,
                bT = b;
        
        *this = *new Strings(aT+what+bT);
        
        delete [] a;
        delete [] b;
    }
}

/*
    Замена первого вхождения подстроки what на replace_with.
    void replace(T& what, T& replace_with)
 */

void Strings::replace(Strings& what, Strings& replace_with){
    
    if (what.len() < this->len()){
        bool flag; // флаг о том, что вхождение найдено
        for (int i = 0; i < this->len() - what.len() && !flag; i++){
            flag = true;
            
            // проверяем полное ли вхождение
            for(int j = 0; j < what.len() && flag; j++){
                if (this->read(i+j) != what[j])
                    flag = false;
            }
            
            // если полное
            if (flag) {
                char* a = new char[i+1];
                strncpy(a, this->rep->s, i);
                
                char* b = new char[this->len() - i - what.len() + 1];
                int size = (this->len() - (i + what.len()));
                
                for (int g = 0; g < size; g++){
                    b[g] = this->read(g+i+what.len());
                }
                
                // освобождаем себя от дальнейшего извращенства
                Strings aTemp = a, 
                        bTemp = b;
                
                *this = *new Strings(aTemp + replace_with + bTemp);
                
                //чистимся
                delete [] a;
                delete [] b;
            }
        }
    }
}


/* 
    Замена всех вхождений подстроки what на replace_with.
    void replaceall(T& what, T& replace_with)
 */

void Strings::replaceAll(Strings& what, Strings& replace_with){
    
    if (this->len() >= what.len()){
        bool flag;
        
        for (int i = 0; i < this->len() - what.len(); i++){
            flag = true;
            
            // проверяем полное ли вхождение
            for(int j = 0; j < what.len(); j++){
                if (this->read(i+j) != what[j])
                    flag = false;
            }
            
            // если полное
            if (flag) {
                char* a = new char[i+1];
                strncpy(a, this->rep->s, i);
                
                char* b = new char[this->len() - i - what.len() + 1];
                int size = (this->len() - (i + what.len()));
                
                for (int g = 0; g < size; g++){
                    b[g] = this->read(g+i+what.len());
                }
                
                // освобождаем себя от дальнейшего извращенства
                Strings aTemp = a, 
                bTemp = b;
                
                *this = *new Strings(aTemp + replace_with + bTemp);
                
                //чистимся
                delete [] a;
                delete [] b;
                
                //инкриментим, чтобы не крутить в холостую
                i += replace_with.len();
            }
        }
    }
}

/*
    Отсечение пробельных символов (перенос строки, пробел, табуляция) с обеих
    сторон.
 */
void Strings::trim(){
    
    char* temp = new char[this->len()+1];
    
    //считаем сколько пробельных и другого мусора в начале
    int i = 0;
    while (this->read(i) == ' ' || this->read(i) == '\n')
        i++;
    
    //до какого символа в конце
    int z = this->len()-1;
    while (this->read(z) == ' ' || this->read(z) == '\n')
        z--;
    
    for (int j = i; j <= z; j++){
        temp[j-i] = this->read(j);
    }

    this->rep->assign(strlen(temp), temp);
    delete [] temp;
}

/* 
    Приведение всех буквенных символов (и латинских и кириллицы) к нижнему
    регистру:
    void lower();
 */

void Strings::lower(){
    char* temp =  new char[this->len()+1];
    
    for (int i = 0; i < this->len(); i++){
        temp[i] = this->read(i);
        tolower(temp[i]);
    }
    strlen(temp);
    this->rep->assign(strlen(temp), temp);
    delete [] temp;
    
}


