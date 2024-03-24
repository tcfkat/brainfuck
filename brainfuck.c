// Short implementation of programming language Brainfuck. tcfkat 20240324
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define TS 30000//Tape size
#define IS 10000//Input size
static uint8_t *t;//Tape
static int16_t tp;//Tape pointer
static char *i,*ip;//Input buffer and pointer
static void bs(char a,char b,uint8_t dir)//bracket search
{
uint8_t bc=0;//bracket counter
    while(1){
        if(*ip==a)bc++;
        if(*ip==b){bc--;if(!bc)return;}
        dir?ip++:ip--;
        if(ip<i||*ip==0){printf("No matching %c\n",b);free(t);free(i);exit(1);}
    }
}
int main(void)
{
    t=calloc(TS,1);
    ip=i=calloc(IS,1);
    if(!t||!i){if(t)free(t);if(i)free(i);printf("No mem\n");return 1;}
    fgets(i,IS-2,stdin);//Minor bug: \n terminates input, no multi-line input
    while(1){
        switch(*ip){
            case'>':if(++tp>=TS)tp=0;ip++;break;//Wrap around end of tape
            case'<':if(--tp<0)tp=TS-1;ip++;break;//Wrap around begin of tape
            case'+':++t[tp];ip++;break;
            case'-':--t[tp];ip++;break;
            case'.':putchar(t[tp]);ip++;break;
            case',':t[tp]=(uint8_t)*ip;ip++;break;
            case'[':if(!t[tp])bs('[',']',1);ip++;break;
            case']':bs(']','[',0);break;
            case 0:free(t);free(i);return 0;
            default:ip++;break;//Discard anything else
        }
    }
}
