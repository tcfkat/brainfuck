// Short implementation of programming language Brainfuck. tcfkat 20240320
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define TS 30000//Tape size
static uint8_t *t;//Tape
static int16_t tp;//Tape pointer
static char *in, *inp;//Input buffer
static void bs(char a,char b,uint8_t dir)//bracket search
{
uint8_t bc=0;
    while(1){
        if(*inp==a)bc++;
        if(*inp==b){bc--;if(!bc)return;}
        dir?inp++:inp--;
        if(inp<in||*inp==0||*inp=='\n'||*inp=='\r'){printf("No matching %c\n",b);free(t);free(in);exit(1);}
    }
}
int main(void)
{
    t=calloc(TS,1);
    inp=in=calloc(10002,1);
    if(!t||!in){printf("No mem\n");return 1;}
    scanf("%10000s",in);
    while(1){
        switch(*inp){
            case'>':if(++tp>=TS)tp=0;inp++;break;//Wrap around end of tape
            case'<':if(--tp<0)tp=TS-1;inp++;break;//Wrap around begin of tape
            case'+':++t[tp];inp++;break;
            case'-':--t[tp];inp++;break;
            case'.':putchar(t[tp]);inp++;break;
            case',':t[tp]=(uint8_t)*inp;inp++;break;
            case'[':if(t[tp]){inp++;}else{bs('[',']',1);inp++;};break;
            case']':bs(']','[',0);break;
            case 0:case'\n':case'\r':free(t);free(in);return 0;
            default:break;//Discard anything else
        }
    }
}
