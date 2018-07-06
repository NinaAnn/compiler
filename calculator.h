//
//  calculator.h
//  project
//
//  Created by Nina Ann on 16/12/6.
//  Copyright © 2016年 Nina. All rights reserved.
//

#ifndef calculator_h
#define calculator_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

typedef enum lexeme_t{
    NOMBRE,
    Par_ou,
    Par_fe,
    OP_l,
    OP_h
}lexeme_t;

typedef struct lexeme{
    lexeme_t type;
    char valeur[20];
}lexeme;

typedef struct llexeme{
    lexeme tab[100];
    int N;
}llexeme;

typedef struct noeud * arbre;
struct noeud{
    int value;
    arbre leftch;
    arbre rightch;
};
typedef struct stack calculatrice;
struct stack{
    int value;
    calculatrice *next;
};

void add_number(char* ,int );
void add_type(char* ,int );
int judge(int ,char* );
int naturel(int );
int facteur(int , int ,arbre* );
int term(int , int ,arbre* );
int somme(int , int ,arbre* );
arbre addtree(int ,arbre* ,arbre* );
void printtree(arbre *);
int calcul(arbre *);
int calculator(char *);


#endif /* calculator_h */
