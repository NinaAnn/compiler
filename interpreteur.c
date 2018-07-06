//
//  interpreteur.c
//  project
//
//  Created by Nina Ann on 16/12/7.
//  Copyright © 2016年 Nina. All rights reserved.
//

#include "interpreteur.h"


void interpreter(char* expr,contents **INTER)
{
    //contents* INTER = (contents*)malloc(sizeof(struct content));
    regmatch_t pmatch[1];
    const size_t nmatch = 1;
    regex_t reg;
    const char * pattern0 = " \" [^\"]*[(][^\"]*[)][^\"]* \"";
    const char * pattern3 = " [(] .*[\n\r].*[)]|^[(] .*[\n\r]*.*[)]| [(] .*[)]";
    const char * pattern2 = " \" [^\"]+\"|^\" [^\"]+\"";
    const char * pattern1 = " [^ ]+ | [^ ]+$|^[^ ]+ ";
    const char * pattern4 = "^[\\] .*$| [\\] .*$";
/*
    const char * pattern2 = " \" [^\"]+\"|^\" [^\"]+\"";
    const char * pattern1 = " [^ ]+ | [^ ]+$|^[^ ]+ ";
 */
    int status;
    int size = strlen(expr);
    int *mark = (int*)malloc(size *sizeof(int));
    char * temp = expr;
    int k0;
    for(k0=0;k0<size;k0++){
        mark[k0]=0;
    }
    int i=0;
    int move =0;
    if(!regcomp(&reg, pattern0, REG_EXTENDED|REG_NEWLINE)){
        do{
            int tag=0;
            status = regexec(&reg, expr, nmatch, pmatch, 0);
            if(status) break;
            char tmp[100]={'\0'};
            int k=0;
            int debut = pmatch[0].rm_so;
            int fin = pmatch[0].rm_eo;
            fin -- ;
            while (expr[debut] == ' '||expr[debut] == '\"') {
                debut ++;
            }
            while (expr[fin] == ' '||expr[fin] == '\"') {
                fin --;
            }
            for(i=pmatch[0].rm_so; i<pmatch[0].rm_eo;i++){
                if(mark[i+move]==1){
                    tag=1;break;}
                else mark[i+move]=1;
            }
            
            if(tag == 0){
                for(i=debut; i<=fin;i++){
                    //putchar(expr[i]);
                    tmp[k++]=expr[i];
                }
                //printf("(%d,%d)\n",debut+move,fin+move);
                add(tmp, debut+move, fin+move, CHAIN,INTER);
                for (i=0; i<100; i++) {
                    tmp[i]='\0';
                }}
            expr += pmatch[0].rm_eo;
            move+= pmatch[0].rm_eo;
        }while(status == 0);
    }
    regfree(&reg);
    expr = temp;
    
    move =0;
    
    if(!regcomp(&reg, pattern4, REG_EXTENDED|REG_NEWLINE)){
        do{
            status = regexec(&reg, expr, nmatch, pmatch, 0);
            if(status) break;
            //int k=0;
            int debut = pmatch[0].rm_so;
            int fin = pmatch[0].rm_eo;
                for(i=debut; i<fin;i++){
                    mark[i+move]=1;
                    //putchar(expr[i]);
                }
                printf("\n");
            expr += pmatch[0].rm_eo;
            move += pmatch[0].rm_eo;
        }while(status == 0);
        
    
    regfree(&reg);
    
    expr = temp;
    
    move =0;}
    
    if(!regcomp(&reg, pattern3, REG_EXTENDED|REG_NEWLINE)){
        do{
            status = regexec(&reg, expr, nmatch, pmatch, 0);
            if(status) break;
            //int k=0;
            int debut = pmatch[0].rm_so;
            int fin = pmatch[0].rm_eo;
            for(i=debut; i<fin;i++){
                mark[i+move]=1;
                //putchar(expr[i]);
            }
            //printf("\n");
            expr += pmatch[0].rm_eo;
            move += pmatch[0].rm_eo;
        }while(status == 0);
        
    }
    regfree(&reg);

    
    expr = temp;
    
    move =0;
    if(!regcomp(&reg, pattern2, REG_EXTENDED|REG_NEWLINE)){
        do{
            int tag=0;
            status = regexec(&reg, expr, nmatch, pmatch, 0);
            if(status) break;
            char tmp[100]={'\0'};
            int k=0;
            int debut = pmatch[0].rm_so;
            int fin = pmatch[0].rm_eo;
            fin -- ;
            while (expr[debut] == ' '||expr[debut] == '\"') {
                debut ++;
            }
            while (expr[fin] == ' '||expr[fin] == '\"') {
                fin --;
            }
            for(i=pmatch[0].rm_so; i<pmatch[0].rm_eo;i++){
                if(mark[i+move]==1){
                    tag=1;break;}
                else mark[i+move]=1;
            }
            
            if(tag == 0){
                for(i=debut; i<=fin;i++){
                    //putchar(expr[i]);
                    tmp[k++]=expr[i];
                }
                //printf("(%d,%d)\n",debut+move,fin+move);
                add(tmp, debut+move, fin+move, CHAIN,INTER);
                for (i=0; i<100; i++) {
                    tmp[i]='\0';
                }}
            expr += pmatch[0].rm_eo;
            move+= pmatch[0].rm_eo;
        }while(status == 0);
    
    regfree(&reg);

    
    move = 0;
    expr = temp;}
    if(!regcomp(&reg, pattern1, REG_EXTENDED|REG_NEWLINE)){
        int debut;
        int fin;
        do{
            int tag=0;
            status = regexec(&reg, expr, nmatch, pmatch, 0);
            if(status) break;
            debut = pmatch[0].rm_so;
            fin = pmatch[0].rm_eo;
            char tmp[100]={'\0'};
            fin-- ;
            int k=0;
	    
            while(expr[debut] == ' ') {
                debut++;
            }
            while(expr[fin] == ' ') {
                fin --;
            }
            //printf("%d",fin);
            for(i=debut; i<=fin;i++){
                if(mark[i+move]!=1){
                        //putchar(expr[i]);
                        tmp[k++]=expr[i];
                        tag = 1;}
                    else {
                        if (i == debut) {
                            debut++;
                        }
                        else if(i == fin)
                            fin--;
                    }
            }
            //printf("%d",fin);
            /*if(tag == 0){
             for(int i=pmatch[0].rm_so; i<pmatch[0].rm_eo-1;i++){
             if (tmp[i]!=' ') {
             putchar(tmp[i]);
             }
             mark[i+move]=1;
             }
             printf("\n");}*/
            if (tag == 1) {
                add(tmp, debut + move, fin+move, IDENT,INTER);
                //printf("(%d,%d)\n",debut+move,fin+move);
                for (i=0; i<100; i++) {
                    tmp[i]='\0';
                }
            }
            expr += pmatch[0].rm_eo-1;
            move+= pmatch[0].rm_eo-1;
        }while(status == 0);

        regfree(&reg);}

    else{
        printf("Mauvais expression rationnelle");
    }
    
    return ;
}

void add(char* expr,int debut, int fin,int type,contents** head){
    contents* temp = (contents*) malloc(sizeof(struct content));
    contents* point =(contents*) malloc(sizeof(struct content));
    //contents* temp2 =(contents*) malloc(sizeof(struct content));
    point = *head;
    //temp2 = *head;
    temp->debut = debut;
    temp->fin = fin;
    //int tag=0;
    int i;
    for (i=0; i<strlen(expr); i++) {
        temp->expression[i]=expr[i];
    }
    temp->type = type;
    if (point->expression[0] == '\0'){
        temp->next = (*head);
        (*head) = temp;
    }
    else if(point->debut >= fin)
    {
        
        temp->next = (*head);
        (*head) = temp;
    }
    else if ((point->fin)<=debut && point->next->expression[0] == '\0')
    {
        temp->next = point->next;
        point->next = temp;
    }
    else if ((point->next->debut)>=fin && (point->fin)<=debut)
    {
        temp->next = point->next;
        point->next = temp;
    }

    else{
        do{
            point = point->next;
            if ((point->fin)<=debut) {
                if (point->next == NULL) {
                    break;
                }
                //else if (point->next->expression[0] == '\0'){break;}
                else if((point->next->debut)>=fin){break;}
            }
        }while (point->next != NULL&&point->next->expression[0] != '\0');
        
            temp->next = point->next;
            point->next = temp;
        
    }
    //*head = point;
}



