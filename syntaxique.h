//
//  syntaxique.h
//  project
//
//  Created by Nina Ann on 16/12/10.
//  Copyright © 2016年 Nina. All rights reserved.
//

#ifndef syntaxique_h
#define syntaxique_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include "interpreteur.h"

typedef struct base* Base;
struct base{
    int number;
    int order;
    Base pre;
    Base next;
};

typedef enum type{
    INT,
    CHAINE,
    ANY,
    ANY1,
    ANY2,
    ANY3
}type;

typedef struct pile{
    int valeur;
    struct pile * next;
}Pile;

typedef void (*void_to_void)(void);

void push(int , Pile **);
int pop(Pile **);

int judgeint(char*,int,int);

void Bdeclare();
int add_VM(int ,void_to_void ,int );
void add_LAC(int num);
void declare_base(char[], int , int[], int , int[],int );

void executeur(char*);
void Read(char[],content_t,int,int);
void judge_input(Base* ,int,int);
int find_cfa(char * , Base *);

void lit(void);
void end(void);
void Plus(void);
void multi(void);
void mois(void);
void Dup(void);
void swap(void);
void divide(void);
void Equal(void);
void point(void);
void Drop(void);
void count(void);
void print(void);
void calculat(void);
void si(void);
void sinon(void);
void recurse(void);
void retu(void);
void readfile(void);
#endif /* syntaxique_h */
