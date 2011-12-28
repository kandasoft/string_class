//
//  main.cpp
//  string_class
//
//  Created by Kandsoft on 21.12.11.
//

#include <iostream>
#include <stdio.h>
#include "strcls.h"
using namespace std;


int main (int argc, const char * argv[])
{
    Strings a, b ;
    a = "assdlkfjdslkf";
    b = "dlk";
    int position = a.pos("lkf", 0, a.len());
    
    
    cout << position;
    
    return 0;// 
}
