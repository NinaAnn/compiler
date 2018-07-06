//
//  FileOpen.h
//  project
//
//  Created by Nina Ann on 16/12/5.
//  Copyright © 2016年 Nina. All rights reserved.
//

#ifndef FileOpen_h
#define FileOpen_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

typedef enum content_t{
    CHAIN,
    IDENT
}content_t;

typedef struct content contents;
struct content{
    int debut;
    int fin;
    char expression[100];
    content_t type;
    contents *next;
};

void openfile(char* );
void add_content(char* ,int , int ,int ,contents** );

#endif /* FileOpen_h */
