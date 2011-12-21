//
//  strcls.cpp
//  last
//
//  Created by Kandsoft on 21.12.11.

#include <iostream>

class Strings {
private:
    char *str;
    int length;
    
public:
    
    //first constructor without param's
    Strings(){
        
        this->str = new char(1);
        this->str = "\0";
        this->length = 0;
    }
    
    // int to string constructor
    Strings( int param ){
        
        
    }
    
};