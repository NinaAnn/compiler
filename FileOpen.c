//
//  FileOpen.c
//  project
//
//  Created by Nina Ann on 16/12/5.
//  Copyright © 2016年 Nina. All rights reserved.
//

#include "FileOpen.h"
#include "syntaxique.h"

contents * CONTENTS;
contents *tail;

void openfile(char* address){
    //contents * head = (contents*)malloc(sizeof(struct content));
    tail = (contents*)malloc(sizeof(struct content));
    CONTENTS = (contents*)malloc(sizeof(struct content));
    //head = CONTENTS;
    tail = CONTENTS;
    FILE *file;
    file = fopen(address,"r+");
    fseek(file, 0, SEEK_END);
    long file_size;
    file_size = ftell( file );
    //printf("%ld", file_size);
    char *lac;
    fseek(file, 0, SEEK_SET);
    lac = (char*)malloc(file_size * sizeof(char));
    fread(lac, file_size, sizeof(char), file);
    //char *tmp = (char*)malloc(file_size * sizeof(char));
    //strcpy(tmp,lac);
    executeur(lac);
    
}
