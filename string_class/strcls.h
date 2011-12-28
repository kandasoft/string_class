//
//  strcls.h
//  last
//
//  Created by Kandasoft on 21.12.11.
//


#ifndef last_strcls_h
#define last_strcls_h
#include <iostream>
using namespace std;

class Strings {
    
    /*
         Структура, в которой храним саму строку и данные о ней, так же количество обращений для оптимального использования. 
         По сути, этот член класса является каркасом всего класса, так как главные функции — хранения, удалени, разыменовывания — выполняет он. 
     */
    struct Srep;
    struct Strings::Srep{
        
        public:
       
        char* s;    // указатель на строку
        size_t sz;  // размер строки
        int n;      // количество обращений
        
        // конструктор (на ввод приходит размер и сама строка)
        Srep (size_t nsz, const char* p){
            
            n = 1;
            sz = nsz;
            s = new char[sz + 1]; // выделяем память + под символ \0
            strcpy(s,p);
        }
        
        // деструктор — освобождает память, выделенную под строку
        ~Srep () { delete [] s; }
        
        // копирование.
        Srep* get_own_copy() { 
            if (n == 1) return this;
            n--;
            return new Srep(sz,s);
        }
        
        // когда нужно присвоить другую строку. т.е. Strings a = "sadfd"; a = "fdas";
        void assign(size_t nsz, const char* p){
            // если размеры не равны — нужно выделять память заново
            if (sz != nsz) {
                delete [] s;
                sz = nsz;
                s = new char(sz + 1);
            }
            strcpy(s,p);
        }
        
        private:  // предохраняет от копирования

        Srep(const Srep&); 
        Srep& operator= (const Srep&);
    };
    
    Srep *rep;
    
public:
    
    /*
     Реализация оператора индексирования, который различает операции чтения и записи
     */
    class Cref;     
    class Strings::Cref {
        friend class Strings;
        Strings& s;
        int i;
        Cref(Strings& ss, int ii):s(ss),i(ii){}
        
        public:
        operator char() const { return s.read(i); }     // выдаем значение
        void operator = (char c) { s.write(i,c); }      // записываем значение
    };
    
    /*
     Класс обработки исключений
     */
    class Range{};     
    
    // конструкторы
    Strings();                          // a = ""
    Strings(const char*);               // a = "asd"
    Strings(const Strings&);            // a = b 

    
    // диструктор
    ~Strings();
    
    // методы и дополнительные перегрузки
    
    void check (int) const;
    char read(int) const;
    void write(int, char);
    
    size_t len() const;
    int pos(Strings, int, int);         // индексация. Первое вхождение
    void del(Strings&);                 // удаление подстроки
    
    Cref operator[] (int i) { check(i); return Cref(*this,i); }
    char operator[] (int i) const { check(i); return rep->s[i]; };
    
    // перегрузка операторов
    
    Strings& operator=(const char*);
    Strings& operator=(const Strings&);
    
    // дополнительно
    
    Strings& operator+ (const Strings&);
    
    Strings& operator+= (const Strings&);
    Strings& operator+= (const char*);
    
    // дружественные функции, вывод
    
    friend ostream& operator<<(ostream&, const Strings&);
    friend istream& operator>>(istream&, Strings&);
};

#endif
