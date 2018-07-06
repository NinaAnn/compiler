//
//  main.c
//  project
//
//  Created by Nina Ann on 16/12/5.
//  Copyright © 2016年 Nina. All rights reserved.
//




#include "syntaxique.h"
//#include "syntaxique.c"
//#include "interpreteur.c"

int main(int argc, const char * argv[]) {
    // insert code here...
    Bdeclare();
    
    char expression[100];
    printf("insert the expression:\n");
    
    scanf("%99[^\n]",expression);
     
    //interpreter(expression);
    executeur(expression);

    return 0;
}
