//
//  calculator.c
//  project
//
//  Created by Nina Ann on 16/12/6.
//  Copyright © 2016年 Nina. All rights reserved.
//

#include "calculator.h"

llexeme result;
int cur = 0;
int j = 0;
calculatrice * cal;


int calculator(char *expr){
    // insert code here...
    result.tab[0].valeur[0] = '0';
    cal = (calculatrice*) malloc(sizeof(calculatrice));
    cal->value = -1;
    /*char s[100];
    printf("insert the expression:\n");
    char* expr;
    expr = gets(s);*/
    result.N = 0;
    int length = strlen(expr);
    add_number(expr, 0);
    int jud;
    for (cur = 0; cur<length; cur++) {
        jud = judge(cur,expr);
        if (jud == 0) {
            printf("The calculating expression is invalid!");
            return 0;
        }
        else if (jud == 1) {
            if(cur == length-1){
                j++;
                int start = cur-j+1;
                add_number(expr,start);
                j=0;
            }
            else{
                j++;}
        }
        else{
            if (j!=0) {
                int start = cur-j;
                add_number(expr,start);
                j=0;
            }
            switch (jud) {
                case 2:
                    add_type(expr, OP_l);
                    break;
                case 3:
                    add_type(expr, OP_h);
                    break;
                case 4:
                    add_type(expr, Par_ou);
                    break;
                case 5:
                    add_type(expr, Par_fe);
                    break;
            }
        }
    }
    /*for (int ini=0; ini<result.N; ini++) {
        printf("%s\n",result.tab[ini].valeur);
    }*/
    
    arbre bitree = malloc(sizeof(struct noeud));
    int islegle;
    islegle = somme(1, result.N-1,&bitree);
    if (!islegle) {
        printf("Your expressions of calculations are illegle!");
    }
    else{
        //int res = calcul(&bitree);
        //printf("%d",res);
    }
    //printf("%d\n",cal->value);
    
    return cal->value;
}

int judge(int cur,char* expr){
    char element;
    element = expr[cur];
    switch (element) {
        case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
            return 1;
            break;
        case '+':case '-':
            return 2;
            break;
        case 'x':case '/':
            return 3;
            break;
        case '(':
            return 4;
            break;
        case ')':
            return 5;
            break;
        default:
            return 0;
            break;
    }
    
}

void add_number(char* expr,int start){
    lexeme lu;
    lu.type = NOMBRE;
    strncpy(lu.valeur, expr+start, j);
    lu.valeur[j]='\0';
    result.tab[result.N]= lu;
    result.N++;
    int k;
    for (k=0; k<20; k++) {
        lu.valeur[k]='\0';
    };
};

void add_type(char* expr,int type){
    lexeme lu;
    lu.type = type;
    strncpy(lu.valeur, expr+cur, 1);
    lu.valeur[1]='\0';
    result.tab[result.N] = lu;
    result.N++;
    int k1;
    for (k1=0; k1<20; k1++) {
        lu.valeur[k1]='\0';
    };
};


int naturel(int N){
    int isnatu;
    isnatu = (result.tab[N].type == NOMBRE)&&(result.tab[N].valeur[0]!='0'||(result.tab[N].valeur[0]=='0'&&result.tab[N].valeur[1]=='\0'));
    return (isnatu);
}

int facteur(int begin, int end, arbre *temp){
    arbre s = malloc(sizeof(struct noeud));
    int isfacteur = (naturel(begin)&&(begin==end))||(result.tab[begin].type==Par_ou && result.tab[end].type==Par_fe && somme(begin+1,end-1,&s));
    if (isfacteur==1 && begin==end) {
        arbre t = NULL;
        s = addtree(begin, &t, &t);
    }
    if (isfacteur) {
        *temp = s;
    }
    return(isfacteur);
}

int term(int begin, int end,arbre *temp){
    int isfactor;
    int i=end-1;
    int tab=0;
    arbre t = malloc(sizeof(struct noeud));
    isfactor=facteur(begin,end,&t);
    while ((isfactor==0) && (i>begin)) {
        isfactor = facteur(i+1,end,&t->rightch) && term(begin,i-1,&t->leftch) && result.tab[i].type == OP_h;
        i--;
        tab=1;
    }
    
    if (tab == 1 && isfactor == 1) {
        t = addtree(i+1, &t->leftch, &t->rightch);
    }
    if (isfactor == 1) {
        *temp = t;
    }
    return isfactor;
}

int somme(int begin, int end,arbre *temp){
    int isterm;
    int i=end-1;
    int tab=0;
    arbre s = malloc(sizeof(struct noeud));
    isterm = term(begin,end,&s);
    if (isterm == 0) {
        isterm = result.tab[begin].type == OP_l && term(begin+1, end,&s->rightch);
        if (isterm == 1) {
            arbre t =NULL;
            s = addtree(begin, &t, &s->rightch);
        }
    }
    
    while ((isterm == 0)&& (i>begin)) {
        isterm = (term(i+1,end,&s->rightch) && somme(begin, i-1,&s->leftch) && result.tab[i].type==OP_l);
        i--;
        tab = 1;
    }
    if (tab == 1 && isterm == 1) {
        s = addtree(i+1, &s->leftch, &s->rightch);
    }
    if (isterm == 1) {
        *temp = s;
    }
    return isterm;
}



arbre addtree(int num,arbre *fg,arbre *fd){
    arbre new = malloc(sizeof(struct noeud));
    new->value = num;
    new->leftch = *fg;
    new->rightch = *fd;
    return new;
}

int calcul(arbre * bitree)
{
    if ((*bitree) == NULL) {
        return 0;
    }
    arbre newl = malloc(sizeof(struct noeud));
    arbre newr = malloc(sizeof(struct noeud));
    newl = (*bitree)->leftch;
    newr = (*bitree)->rightch;
    if (newl == NULL && newr != NULL) {
        arbre new = malloc(sizeof(struct noeud));
        new->value = 0;
        newl = new;
    }
    calcul(&newl);
    calcul(&newr);
    int order = (*bitree)->value;
    if (result.tab[order].type == NOMBRE) {
        calculatrice* temp = (calculatrice*) malloc(sizeof(calculatrice));
        temp->value = atoi(result.tab[order].valeur);
        temp->next = cal;
        cal = temp;
    }
    else{
        char value = result.tab[order].valeur[0];
        int right = cal->value;
        cal = cal->next;
        int left = cal->value;
        cal = cal->next;
        if (value == '+') {
            int re = left + right;
            calculatrice* temp = (calculatrice*) malloc(sizeof(calculatrice));
            temp->value = re;
            temp->next = cal;
            cal = temp;
        }
       else if (value == '-') {
            int re = left - right;
            calculatrice* temp = (calculatrice*) malloc(sizeof(calculatrice));
            temp->value = re;
            temp->next = cal;
            cal = temp;
        }
       else if (value == 'x') {
            int re = left*right;
            calculatrice* temp = (calculatrice*) malloc(sizeof(calculatrice));
            temp->value = re;
            temp->next = cal;
            cal = temp;
        }
        if (value == '/') {
            if (right == 0) {
                printf("the denominator in calculation is 0！");
                exit(0);
            }
            int re = left / right;
            calculatrice* temp = (calculatrice*) malloc(sizeof(calculatrice));
            temp->value = re;
            temp->next = cal;
            cal = temp;
        }
    }
    return 0;
    
}
