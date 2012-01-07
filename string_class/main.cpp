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
    Strings a, b,c ;
    a = "  assdlKFDSfjdsdl ";
    
    b = "HELLO";
    c = "lk";
    
//    int position = a.pos("lkf", 0, a.len());
//    a.del(b);
//    a.del(2, 3);
//    a.delall(b);
//    a.ins(b, 5);
//    a.replace(c, b);
//    a.replaceAll(c, b);
//    a.trim();
    a.lower();
    
    Strings z;
    z += b;

    cout << a;
    
    return 0;
}
