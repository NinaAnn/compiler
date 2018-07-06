//
//  syntaxique.c
//  project
//
//  Created by Nina Ann on 16/12/10.
//  Copyright © 2016年 Nina. All rights reserved.
//

#include "syntaxique.h"
#include "calculator.h"
#include "FileOpen.h"
#include "interpreteur.h"
void_to_void processeur[30];
Base LAC;

int ii=1;
int jj=0;
int VM[1000] = {0};
Pile * Type;
Pile * Data;
Pile * Retour;

char list_of_chain[1000] = {'\0'};
int chaine_position=0;

void push(int val, Pile **pile)
{
    Pile* tmp = malloc(sizeof(struct pile));
    tmp->valeur = val;
    tmp->next = NULL;
    if ((*pile) == NULL) {
        (*pile) = tmp;
    }
    else{
    tmp->next = (*pile);
        (*pile) = tmp;}
}

int pop(Pile **pile)
{
    int return_val = (*pile)->valeur;
    (*pile) = (*pile)->next;
    return return_val;
}


void Bdeclare(){
    LAC = (Base)malloc(sizeof(struct base));
    Type = (Pile *)malloc(sizeof(Pile));
    Data = (Pile *)malloc(sizeof(Pile));
    Data = NULL;
    Type = NULL;
    Retour = (Pile *)malloc(sizeof(Pile));
    Retour = NULL;

    char* plus = "+";
    char* minus = "-";
    char* fois = "*";
    char* duplicate = "dup";
    char* change = "swap";
    char* divi = "/";
    char* equal = "=";
    char* poi = ".";
    char* drop = "drop";
    char* lire = "lit";
    char *fini = "end";
    char* Count = "count";
    char* Print = "type";
    char* Ca = "calculate";
    char* Si = "if";
    char* Sinon = "else";
    char* rec = "recurse";
    char* ret = "cr";
    char* fun = "read";
    
    int input[]={};
    int output[] = {};
    int input1[] = {INT};
    int output1[] = {INT};
    int input11[] = {ANY};
    //int input22[] = {ANY,ANY};
    int output22[] = {ANY,ANY};
    int input2s[] = {ANY1,ANY2};
    int output2s[] = {ANY1,ANY2};
    int input2[] = {INT,INT};
    //int output2[] = {INT,INT};
    int inputC1[] = {CHAINE};
    int inputC2[] = {CHAINE, CHAINE};
    int outputC2[] = {CHAINE,CHAINE};
    int inputd1[] = {ANY3};
    
    int process = 0;
    int VM_position;
    VM_position = add_VM(process,&lit,0);
    declare_base(lire, 0, input, 0, output,VM_position);
    process ++;
    
    VM_position = add_VM(process,&end,0);
    declare_base(fini, 0, input, 0, output,VM_position);
    process ++;
    
    VM_position = add_VM(process,&Plus,0);
    declare_base(plus, 2, input2, 1, output1,VM_position);
    process ++;
    
    VM_position = add_VM(process,&multi,0);
    declare_base(fois, 2, input2, 1, output1,VM_position);
    process ++;
    
    
    VM_position = add_VM(process,&mois,0);
    declare_base(minus, 2, input2, 1, output1,VM_position);
    process ++;

    
    VM_position = add_VM(process,&Dup,0);
    declare_base(duplicate, 1, input11, 2, output22,VM_position);
    process ++;
    
    VM_position = add_VM(process,&swap,0);
    declare_base(change, 2, input2s, 2, output2s,VM_position);
    process ++;
    
    VM_position = add_VM(process,&Equal,0);
    declare_base(equal, 2, input2, 1, output1,VM_position);
    process ++;

    VM_position = add_VM(process,&divide,0);
    declare_base(divi, 2, input2, 1, output1,VM_position);
    process ++;

    VM_position = add_VM(process,&point,0);
    declare_base(poi, 1, input1, 0, output,VM_position);
    process ++;
    
    VM_position = add_VM(process,&Drop,0);
    declare_base(drop, 1, inputd1, 0, output,VM_position);
    process ++;
    
    VM_position = add_VM(process,&count,0);
    declare_base(Count, 1, inputC1, 2, outputC2,VM_position);
    process ++;

    VM_position = add_VM(process,&print,0);
    declare_base(Print, 2, inputC2, 0, output,VM_position);
    process ++;

    VM_position = add_VM(process,&calculat,0);
    declare_base(Ca, 1, inputC1, 1, output1,VM_position);
    process ++;
    
    VM_position = add_VM(process,&si,0);
    declare_base(Si, 1, input1, 0, output,VM_position);
    process ++;
    
    VM_position = add_VM(process,&sinon,0);
    declare_base(Sinon, 0, input, 0, output,VM_position);
    process ++;
    
    VM_position = add_VM(process,&recurse,0);
    declare_base(rec, 0, input, 0, output,VM_position);
    process ++;
    
    VM_position = add_VM(process,&retu,0);
    declare_base(ret, 0, input, 0, output,VM_position);
    process ++;
    
    VM_position = add_VM(process,&readfile,0);
    declare_base(fun, 1, inputC1, 0, output,VM_position);
    process ++;
    
    
}



 int add_VM(int process,void_to_void func,int t){
 processeur[process] = func;
 int VM_position = jj;
 VM[jj] = t;
 jj++;
 VM[jj]=process;
 jj++;
 return VM_position;
 }
 
 void add_LAC(int num){
 Base nouveau =(Base)malloc(sizeof(struct base));
 nouveau->number = num;
 nouveau->order = ii;
 nouveau->pre = LAC;
 nouveau->pre->next = nouveau;
 LAC = nouveau;
 ii++;
 }

 void declare_base(char nom[], int n_input, int input[], int n_output, int output [],int VM_position){
 //add to LAC
 int num = strlen(nom);
 int pos = ii;
 add_LAC(num);
int k;
 for (k=0; k<num; k++) {
 char a = nom[k];
 int aa = a;
 add_LAC(aa);
 }
 add_LAC(n_input);
 for (k=0; k<n_input; k++) {
 add_LAC(input[k]);
     
 }
 add_LAC(n_output);
 for (k=0; k<n_output; k++) {
 add_LAC(output[k]);
 }
 add_LAC(VM_position);
 add_LAC(pos);
 
 }

void judge_input(Base* temp,int debut,int fin){
    int k;
    int nom[20];
    int number = (*temp)->number ;
    //printf("%d",number);
    for (k=0; k<(*temp)->number; k++) {
        nom[k] = (*temp)->number;
        (*temp) = (*temp)->next;
    }
    
    int any=2;
    int any1=3;
    int any2=4;
    //(*temp)= (*temp)->next;
    int num = (*temp)->number;
    for (k=0; k<num; k++) {
        (*temp) = (*temp)->next;
        if (Type == NULL) {
            int k3;
            printf("Wrong: insufficient input of ");
            for (k3=0;k3<number;k3++){printf("%c",nom[k3]); }
            printf(" (%d,%d) !",debut,fin);
            exit(0);
        }
            int type1 = pop(&Type);
        if (type1 == (*temp)->number ) {
        }
        else if ((*temp)->number == 2){
            any = type1;
        }
        else if ((*temp)->number == 3){
            any1 = type1;
        }
        else if ((*temp)->number == 4){
            any2 = type1;
        }
        else if ((*temp)->number == 5){
            
        }
        else
        {
            int k3;
            printf("Wrong input type of ");
            for (k3=0;k3<number;k3++){printf("%c",nom[k3]); }
            printf(" (%d,%d)! ",debut,fin);
            exit(0);
        }
    }
    
        (*temp) = (*temp)->next;
        num = (*temp)->number;
        for (k=0; k<num; k++) {
            (*temp) = (*temp)->next;
            if ((*temp)->number == 2) {
                push(any, &Type);
            }
            else if ((*temp)->number == 3){
            push(any1, &Type);
            }
            else if ((*temp)->number == 4){
                push(any2, &Type);
            }
            else {
                push((*temp)->number, &Type);
            }
        }
    
    
    
}



int find_cfa(char * nom, Base *temp){
    int cfa = -1;
    int tag = 0;
    int k;
    do{
        
        tag = 0;
        int position = (*temp)->number;
        int curr_pos = (*temp)->order;
        cfa = (*temp)->pre->number;
        for (k=0; k<(curr_pos-position); k++) {
            (*temp) = (*temp)->pre;
        }
        Base judge = (Base)malloc(sizeof(struct base));
        judge = *temp;
        for (k=0; k<(*temp)->number; k++) {
            judge = judge->next;
            int nomb = nom[k];
            if (judge->number != nomb) {
                tag = 1;
                break;
            }
        }
        if(nom[k]!='\0') tag = 1;
        if (tag == 1) {
            (*temp) = (*temp)->pre;
        }
        
    }while (tag == 1 && (*temp)->order!= 0);
    if (tag == 1) {
        return -1;
    }
    return cfa;
}


void read_function(int cfa){
    cfa = cfa+1;
    
    push(cfa, &Retour);
    int cur=0;
    
    while (Retour!=NULL) {
        cur = pop(&Retour);
        push(cur+1, &Retour);
        //Retour.push(cur+1);
        processeur[VM[cur]]();
    }
    
    
}

int read_chaine(char* Chaine, char* chaine_list,int position,int debut,int end){
    int p=0;
    int ini = position;
    chaine_list[ini] = '0';
    ++position;
    for (p=0; p<(end-debut+1); p++) {
        chaine_list[position++] = Chaine[p];
    }
    char pi = p;
    chaine_list[ini] = pi;
    return position;
}

void readcfa(int cfa){
    //printf("%d",VM[cfa]);
    
    if (VM[cfa] == 0) {
        processeur[VM[cfa+1]]();
    }
    else if (VM[cfa] == 1){
        //printf("YES");
        read_function(cfa);
    }
}

void Read(char expression[],content_t t,int debut,int fin){
    char * exprr = expression;
    expression[fin-debut+1] = '\0';
    //printf("%s",expression);
    if (t == CHAIN) {
        push(CHAINE, &Type);
        push(chaine_position, &Data);
        chaine_position = read_chaine(exprr, list_of_chain, chaine_position,debut,fin);
    }
    else {
        int isint=1;
        //int number=0;
        int k;
        for (k=0; k<(fin-debut+1); k++) {
            if(expression[k] == '\0'){
            break;
	    }
            int ab = expression[k]- '0';
            if (ab>=0 && ab<=9) {
            }
            else
            {
                isint =0;
                break;
            }
        }
        
        
        if (isint) {
            push(atoi(expression), &Data);
            push(INT, &Type);
        }
        else
        {
            /*
            if (strcmp(exprr, "dup")== 0) {
                type = 1;
            }
            else if (strcmp(exprr, "swap") == 0){
                type = 2;
            }*/
            Base temp = (Base)malloc(sizeof(struct base));
            temp = LAC;
            int cfa = find_cfa(expression,&temp);
            if (cfa == -1) {
                int longeur = fin - debut +1;
                expression[longeur] = '\0';
                printf("Invalide (unknown) input of %s (%d,%d)",expression,debut,fin);
                exit(0);
            }
            judge_input(&temp,debut,fin);
            readcfa(cfa);
            //add_output(&temp);
            //printf("%d",cfa);
            
        }
    }
}
/*
void Read_fun(char expression[],int debut,int fin){
    Base temp = (Base)malloc(sizeof(struct base));
    temp = LAC;
    int cfa = find_cfa(expression, &temp);
    //judge_input(&temp, debut, fin, 0);
    readcfa(cfa);
}
*/
void generateIO(Base *temp,int* n_input, int input[],int* n_output, int output[],int* in,int *out){
    //char name[20];
    //int len = (*temp)->number;
    int k;
    for (k=0; k<(*temp)->number; k++) {
        //name[k]= (*temp)->number;
        (*temp) = (*temp)->next;
    }
    int num = (*temp)->number;
    int any=2;
    //int anyp = 0;
    int any1=3;
    int any2=4;
        for (k=0; k<num; k++) {
        (*temp) = (*temp)->next;
            
        if ((*out)!=0) {
            //int outt = output[*out-1];
            if (output[*out-1]==(*temp)->number) {
                output[*out-1] =-1;
                (*out)--;
                (*n_output)--;
            }
            else if (output[*out-1] == 2){
                for (k=0; k<*out; k++) {
                    if (output[k] == 2) {
                        output[k] = (*temp)->number;
                    }
                }
                for (k=0; k<*in; k++) {
                    if (input[k] == 2) {
                        input[k] = (*temp)->number;
                    }}
                (*out)--;
                (*n_output)--;
            }
            else if (output[*out-1] == 3){
                for (k=0; k<*out; k++) {
                    if (output[k] == 3) {
                        output[k] = (*temp)->number;
                    }
                }
                for (k=0; k<*in; k++) {
                    if (input[k] == 3) {
                        input[k] = (*temp)->number;
                    }}
                (*out)--;
                (*n_output)--;
            }
            else if (output[*out-1] == 4){
                for (k=0; k<*out; k++) {
                    if (output[k] == 4) {
                        output[k] = (*temp)->number;
                    }
                }
                for (k=0; k<*in; k++) {
                    if (input[k] == 4) {
                        input[k] = (*temp)->number;
                    }}
                (*out)--;
                (*n_output)--;
            }
            else if ((*temp)->number == 2){
                any = output[*out-1];
                output[*out-1] =-1;
                (*out)--;
                (*n_output)--;
            }
            else if ((*temp)->number == 3){
                any1 = output[*out-1];
                output[*out-1] =-1;
                (*out)--;
                (*n_output)--;
            }
            else if ((*temp)->number == 4){
                any2 = output[*out-1];
                output[*out-1] =-1;
                (*out)--;
                (*n_output)--;
            }
            else if ((*temp)->number == 5){
                output[*out-1] =-1;
                (*out)--;
                (*n_output)--;
            }
            else{
                
                printf("Wrong input type!");
                exit(0);
            }
        }
        else if ((*out) == 0){
        input[*in]=(*temp)->number;
            (*in)++;
            (*n_input)++;
        }
    }
    (*temp)=(*temp)->next;
    int onum = (*temp)->number;
    for (k=0; k<onum; k++) {
        (*temp) = (*temp)->next;
        if ((*temp)->number == 2) {
            output[*out] = any;
        }
        else if ((*temp)->number == 3){
            output[*out] = any1;
        }
        else if ((*temp)->number == 4){
            output[*out] = any2;
        }
        else{
            output[*out]=(*temp)->number;
        }
        
        (*out)++;
        (*n_output)++;
    }
    
}



void declare_if(contents**INTER, int* n_input, int input[],int* n_output, int output[],int* in,int *out, int pos){
    Base temp = (Base)malloc(sizeof(struct base));
    temp =LAC;
    int cfa = find_cfa("if", &temp);
    generateIO(&temp,n_input,input,n_output,output,in,out);
    VM[jj++] = VM[++cfa];
    int el = jj;
    int elp = jj;
    VM[jj++] = 0;
    (*INTER) = (*INTER)->next;
    
    int isif = 1;
    int k;
    int n_inputi =(* n_input);
    int n_inputo = (* n_input);
    int inputi[10];
    int outputi[10];
    int inputo[10];
    int outputo[10];
    for (k=0; k<10; k++) {
        inputi[k]= input[k];
        inputo[k] = input[k];
        outputi[k] = output[k];
        outputo[k] = output[k];
    }
    int n_outputi = (* n_output);
    int n_outputo = (* n_output);
    
    int curIi;
    int curOi;
    int curIo;
    int curOo;
    curIi = curIo = *in;
    curOi = curOo = *out;


    
    while ((*INTER)->expression[0]!='t'||(*INTER)->expression[1]!='h'||(*INTER)->expression[2]!='e'||(*INTER)->expression[3]!='n'){
        
        if ((*INTER)->type==CHAIN) {
            VM[jj++] = 0; //processeur de la fonction lit;
            VM[jj++] = chaine_position;
            chaine_position = read_chaine((*INTER)->expression, list_of_chain, chaine_position, (*INTER)->debut, (*INTER)->fin);

        }
        else if ((*INTER)->expression[0]=='i'&&(*INTER)->expression[1]=='f'){
            declare_if(INTER,n_input,input,n_output,output,in,out,pos);
        }
        else if ((*INTER)->expression[0]=='e'&&(*INTER)->expression[1]=='l'&&(*INTER)->expression[2]=='s'&&(*INTER)->expression[3]=='e'){
            isif = 0;
            temp =LAC;
            cfa = find_cfa("else", &temp);
            VM[jj++] = VM[++cfa];
            elp = jj;
            VM[el] = elp;
            VM[jj++] = 0;
        }
        
        else{
            int isint=0;
            isint = judgeint((*INTER)->expression,(*INTER)->debut,(*INTER)->fin);
            if (isint == 0) {
                int number = atoi((*INTER)->expression);
                VM[jj++] = 0; //processeur de la fonction lit;
                VM[jj++] = number;
                if (isif == 1) {
                    outputi[curOi++]=0;
                    n_outputi ++;
                }
                else{
                    outputo[curOo++]=0;
                    n_outputo ++;
                }
                //output[curO++]=0;
                //n_output ++;
                
            }
            else{
                Base temp = (Base)malloc(sizeof(struct base));
                temp =LAC;
                
                int longeur = (*INTER)->fin - (*INTER)->debut + 1;
                (*INTER)->expression[longeur] = '\0';
                int cfa = find_cfa((*INTER)->expression, &temp);
                if (cfa == -1) {
                    int longeur = (*INTER)->fin - (*INTER)->debut +1;
                    (*INTER)->expression[longeur] = '\0';
                    printf("Invalide(unknown) input of %s (%d,%d)",(*INTER)->expression,(*INTER)->debut,(*INTER)->fin);
                    exit(0);
                }
                else{
                    if (VM[cfa] == 0) {
                        int add = VM[++cfa];
                        VM[jj++] = add;
                        if ((*INTER)->expression[0]=='r'&&(*INTER)->expression[1]=='e'&&(*INTER)->expression[2]=='c'&&(*INTER)->expression[3]=='u'&&(*INTER)->expression[4]=='r'&&(*INTER)->expression[5]=='s'&&(*INTER)->expression[6]=='e'){
                            VM[jj++] = pos+1;
                            if (isif == 1) {
                                if (inputi[n_inputi-1]!=outputi[n_outputi-1]) {
                                    printf("conflict input and output for recurse!\n");
                                    exit(0);
                                }
                            }
                            else{
                                if (inputo[n_inputo-1]!=outputo[n_outputo-1]) {
                                    printf("conflict input and output for recurse!\n");
                                    exit(0);
                                }
                            }
                            
                        }
                    }
                    else if (VM[cfa] == 1){
                        cfa++;
                        Base tmp = (Base)malloc(sizeof(struct base));
                        tmp =LAC;
                        int read = find_cfa("recurse", &tmp);
                        VM[jj++] = VM[++read];
                        VM[jj++] = cfa;
                    }
                    if (isif == 1) {
                        generateIO(&temp,&n_inputi,inputi,&n_outputi,outputi,&curIi,&curOi);
                    }
                    else{
                        generateIO(&temp,&n_inputo,inputo,&n_outputo,outputo,&curIo,&curOo);

                    }
                            }
            }
        }
        (*INTER) = (*INTER)->next;
    }

    VM[elp]=jj-1;
    int ifelse = 0;
    if (n_inputi != n_inputo || n_outputi != n_outputo) {
        ifelse = 1;
    }
    if (ifelse == 0) {
        for (k=0; k<n_inputi; k++) {
            if (inputi[k]!=inputo[k]) {
                ifelse = 1;
                break;
            }
        }
    }
    
    if (ifelse == 0) {
        for (k=0; k<n_outputi; k++) {
            if (outputi[k]!=outputo[k]) {
                ifelse = 1;
                break;
            }
        }
    }
    
    
    if (isif == 1||ifelse == 0) {
        (* n_input) = n_inputi;
        (* n_output) = n_outputi;
        for (k=0; k<10; k++) {
            input[k]= inputi[k];
            output[k] = outputi[k];
        }
        *in=curIi;
        *out = curOi;
    }
    else{
        printf("if and else has different input or output!");
        exit(0);
    }
}

int declare_function(contents**INTER){
    
    int VM_pos = jj;
    int position = ii;
    VM[jj++] = 1;
    //printf("%d",jj-1);
    (*INTER) = (*INTER)->next;
    char* funcnom = (*INTER)->expression;
    int funclength = (*INTER)->fin - (*INTER)->debut +1;
    
    int n_input = 0;
    int input[10];
    int n_output = 0;
    int output[10];
    int curI=0;
    int curO=0;
    (*INTER) = (*INTER)->next;
    
    while ((*INTER)->expression[0]!=';') {
     //printf(" %s ",(*INTER)->expression);
        if ((*INTER)->type==CHAIN) {
            VM[jj++] = 0; //processeur de la fonction lit;
            VM[jj++] = chaine_position;
            chaine_position = read_chaine((*INTER)->expression, list_of_chain, chaine_position,(*INTER)->debut, (*INTER)->fin);
            output[curO++]=1;
            n_output ++;
        }
        else if ((*INTER)->expression[0]=='i'&&(*INTER)->expression[1]=='f'){
            declare_if(INTER,&n_input,input,&n_output,output,&curI,&curO,VM_pos);
        }
        else{
            int isint=0;
            isint = judgeint((*INTER)->expression,(*INTER)->debut,(*INTER)->fin);
            //printf("%d%d%d ",isint,(*INTER)->debut, (*INTER)->fin);
            if (isint == 0) {
                int number = atoi((*INTER)->expression);
                VM[jj++] = 0; //processeur de la fonction lit;
                VM[jj++] = number;
                output[curO++]=0;
                n_output ++;
                
            }
            else{
                Base temp = (Base)malloc(sizeof(struct base));
                temp =LAC;
                int longeur = (*INTER)->fin - (*INTER)->debut + 1;
                (*INTER)->expression[longeur] = '\0';
                int cfa = find_cfa((*INTER)->expression, &temp);
                if (cfa == -1) {
                    int longeur = (*INTER)->fin - (*INTER)->debut +1;
                    (*INTER)->expression[longeur] = '\0';
                    printf("Invalide (unknown) input of %s (%d,%d)",(*INTER)->expression,(*INTER)->debut,(*INTER)->fin);
                    exit(0);
                }
                else{
                    if (VM[cfa] == 0) {
                        int add = VM[++cfa];
                        VM[jj++] = add;
                        if ((*INTER)->expression[0]=='r'&&(*INTER)->expression[1]=='e'&&(*INTER)->expression[2]=='c'&&(*INTER)->expression[3]=='u'&&(*INTER)->expression[4]=='r'&&(*INTER)->expression[5]=='s'&&(*INTER)->expression[6]=='e'){
                                printf("can't use recurse outside if!\n");
                                exit(0);
                        }
                    }
                    else if (VM[cfa] == 1){
                        cfa++;
                        Base tmp = (Base)malloc(sizeof(struct base));
                        tmp =LAC;
                        int read = find_cfa("recurse", &tmp);
                        VM[jj++] = VM[++read];
                        VM[jj++] = cfa;
                        /*while (VM[cfa]!=1) {
                            VM[jj++] = VM[cfa++];
                        }*/
                    }
                    
                    
                    generateIO(&temp,&n_input,input,&n_output,output,&curI,&curO);
                }
            }
    }
    (*INTER) = (*INTER)->next;
    }
    int k;
    VM[jj++] = 1; //end of function
    add_LAC(funclength);
    //printf("\n");
    for (k=0; k<funclength; k++) {
        int n = funcnom[k];
        add_LAC(n);
        printf("%c",funcnom[k]);
    }
    printf("{");
    add_LAC(n_input);
    if (n_input == 0) {
        printf("void");
    }
    
    for (k=0; k<n_input; k++) {
        add_LAC(input[k]);
        char * T;
        if (input[k] == 0) {
            T = "INT";
        }
        else if (input[k] == 1)
        {
            T = "CHAINE";
        }
        else if (input[k] == 2)
        {
            T = "ANY";
        }
        else if (input[k] == 3)
        {
            T = "ANY1";
        }
        else if (input[k] == 4)
        {
            T = "ANY2";
        }
        printf("%s",T);
    }
    printf(" ->");
    add_LAC(n_output);
    if (n_output == 0) {
        printf("void");
    }
    for (k=0; k<n_output; k++) {
        add_LAC(output[k]);
        char * T;
        if (output[k] == 0) {
            T = "INT";
        }
        else if (output[k] == 1)
        {
            T = "CHAINE";
        }
        else if (output[k] == 2)
        {
            T = "ANY";
        }
        else if (output[k] == 3)
        {
            T = "ANY1";
        }
        else if (output[k] == 4)
        {
            T = "ANY2";
        }
        printf("%s",T);
    }
    printf("}");
    printf("\n");
    add_LAC(VM_pos);
    add_LAC(position);
    return (*INTER)->fin;
    }

void executeur(char* expr)
{
    contents* INTER = (contents*)malloc(sizeof(struct content));
    INTER->expression[0] = '\0';
    interpreter(expr,&INTER);
    
    while (INTER->expression[0]!='\0') {
        if (INTER->expression[0] == ':') {
            //int debut = INTER->debut;
            //char* funnom = INTER->next->expression;
            declare_function(&INTER);
            //Read_fun(funnom,debut,fin);
        }
        else
       Read(INTER->expression,INTER->type,INTER->debut,INTER->fin);
        
        INTER = INTER->next;
    }
    
   if(Data != NULL){
   printf("Wrong execute because there is still data remaining!");
   }
}
//
void lit(void){
    int cur = pop(&Retour);
    push(cur+1, &Retour);
    push(VM[cur], &Data);
    //Type.push(INT);
}

void end(void){
    pop(&Retour);
}

//define a fonction named plus to test;
void Plus(void){
    //int a=1;
    int val1 = pop(&Data);
    int val2 = pop(&Data);
     int val = val1 + val2;
    push(val, &Data);
    
}

void mois(void){
    //int a=1;
    int val1 = pop(&Data);
    int val2 = pop(&Data);
    int val = val2 - val1;
    push(val, &Data);
    
}


void multi(void){
    int val1 = pop(&Data);
    int val2 = pop(&Data);
    int val = val1*val2;
    push(val, &Data);

}

void Dup(void){
    int doub = pop(&Data);
    push(doub, &Data);
    push(doub, &Data);
}


void swap(void){
    int value = pop(&Data);
    int value2 = pop(&Data);
    push(value, &Data);
    push(value2, &Data);

}

void Equal(void){
    int val1 = pop(&Data);
    int val2 = pop(&Data);
    if (val1 == val2) {
        push(1, &Data);
    }
    else{
        push(0, &Data);
            }
}
 
void point(void){
    int value = pop(&Data);
    printf("%d ",value);
}

void Drop(void){
    pop(&Data);
}

void count(void){
        int val = pop(&Data);
        int number = list_of_chain[val] - 0;
        push(number, &Data);
        //Type.push(CHAINE);
        push(val+1, &Data);
        //Type.push(CHAINE);

}

void print(void){
    int pos = pop(&Data);
    int count = pop(&Data);
    int k;
    for (k=0; k<=count; k++) {
        printf("%c",list_of_chain[k+pos]);
    }
    printf(" ");
    //printf("\n");
}

void calculat(void){
    int val = pop(&Data);
    int number = list_of_chain[val]-0;
    char exprC[100];
    int k;
    for (k=0; k<=number; k++) {
        exprC[k]=list_of_chain[val+1+k];
        }
    int resultat = calculator(exprC);
    push(resultat, &Data);
}


void si(void){
    int val = pop(&Data);
    int next = pop(&Retour);
    if (val == 0) {
	next = VM[next];
        push(next+1, &Retour);
    }
    else{
        //push(VM[next], &Retour);
        push(next+1, &Retour);
    }
}

void recurse(void){
    int next = pop(&Retour);
    push(next+1, &Retour);
    push(VM[next], &Retour);
    
}

void sinon(void){
    int next = pop(&Retour);
    //int val = Retour->valeur;
        push(VM[next]+1, &Retour);

}

void readfile(void){
    int val = pop(&Data);
    int number = list_of_chain[val] - 0;
    val++;
    char address[100];
    int k;
    for (k=0; k<=number; k++) {
        address[k] = list_of_chain[k+val];
    }
    openfile(address);
}

void divide(void){
    int val1 = pop(&Data);
    int val2 = pop(&Data);
    if(val1 == 0){
    printf("Wrong: the denominator is 0!\n"); exit(0);}
    push(val2/val1, &Data);
}

void retu(void){
    printf("\n");
}

int judgeint(char str[],int debut,int end){
    int isnumber=0;
    //int libre = strlen(str);
    int n;
    for (n=0; n<(end-debut+1); n++) {
        if (!(0<=(str[n]-'0')&&(str[n]-'0')<=9)){
            isnumber = 1;
        }
    }
    return isnumber;
    
}

