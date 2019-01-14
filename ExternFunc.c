#include "stdio.h"
#include "string.h"
#include "ExternFunc.h"
#include "stm32f4xx_hal.h"

#define MATCH_CASE_ENABLE     0             //函数调用名称大小写是否敏感 1表示敏感 0 表示不敏感
//typedef struct
//{
//    const char * FuncName;
//    void *( (*func)(void* args,...));
//    const char * fmt;
//    const char * Introduction;
//} CALLFUNCTIONTABLE;
//
//#define EXPOTRFUNC(NAME,FUNC,FTM,INTRO) {#NAME,(void *(*)(void* args,...))FUNC,#FTM,#INTRO}
void show(int i);
void showcircle(char ch,int r);
void simplefunction(char* str,unsigned int sum,float dee,char ch);


static int ExternFunc_Find(char* funcname);
static void ExternFunc_list(void);
static void ExternFunc_SocReset(void);
static unsigned char matchString(const char* str1,const char* str2);

const CALLFUNCTIONTABLE functable[] =
{
    EXPOTRFUNC(LIST,ExternFunc_list, ,函数列表),
    EXPOTRFUNC(RST,ExternFunc_SocReset,,芯片软件复位),
    EXPOTRFUNC(circle,showcircle,%c %d,串口显示一个圆),
    EXPOTRFUNC(九九乘法表,show,%d,%d乘法表),
    EXPOTRFUNC(simp,simplefunction,%s %X %f %c,格式测试函数)
};
//EXPOTRFUNC( 函数别名命令行调用的名字 |真正的函数名 | 函数传参的格式字符串 |这个函数的简介)
void simplefunction(char* str,unsigned int sum,float dee,char ch)
{
    
//    fl.flo = dee;
    printf("接收到的字符串是:%s,\n\
接收到的字符是: %c \n\
接受到的数字是 %d\n\
接收到的小数是 %f __ \n ",str,ch,sum,dee);
}

void showcircle(char ch,int r)
{
    for(int i = 1; i<=(2*r); i++)
    {
        for(int j = 1; j<(2*r); j++)
        {
            if(((i-r)*(i-r)+(j-r)*(j-r))<=(r*r))
                printf("%c ",ch);
            else
                printf("%c ",' ');
        }
        printf("\n");
    }
}

void show(int i)
{
    for(int qq = 1;qq<= i;qq++)
    {
        for(int j = 1;j<=qq;j++)
        {
            printf("%dx%d=%2d  ",j,qq,j*qq);
        }
        printf("\n");
    }
}



























static int ExternFunc_Find(char* funcname)
{
    int size = sizeof(functable)/sizeof(functable[0]);
    for(int i = 0; i<size; i++)
    {
        if(matchString(funcname,functable[i].FuncName) == 0)
            return i;
    }
    return -1;
}


static void* args[7][100] = {0};
void ExternFunc_excute(char* str)
{
    char* ptemp;
    char ch;
    ptemp = strstr(str," ");
    if(ptemp == NULL)
    {
        ptemp = str+strlen(str);
        ch = *ptemp;
    }
    else
    {
        ch = '\0';
        *ptemp = '\0';
        ptemp++;
    }



    
    int loc = ExternFunc_Find(str); //寻找函数
    if(loc == -1)
    {
        printf("%s are not find\n the function list :\n",str);
        ExternFunc_list();
        return ;
    }

    if(ch != '\0')
        *ptemp = ch;
    int success = sscanf(ptemp,functable[loc].fmt,&args[0][1],&args[1][1],&args[2][1],&args[3][1],&args[4][1],&args[5][1]);
    
    //为兼容 可以输入字符串而做出的妥协
    int i = 0;
    ptemp = (char*)functable[loc].fmt;
    for(i = 0;i<7;i++)
    {
        if((ptemp=strstr(ptemp,"%")) !=NULL)
        {
            
            if(*(++ptemp) == 's')
                args[i][0] = &args[i][1];
            else if(*ptemp == 'f')
            {
                args[i][0] = args[i][1];
            }else               
                args[i][0] = args[i][1];
        }else break;
    }
    if(i!= success)
    {    
        printf("Err: 函数%s 参数应该为%d个,但只有%d\n",functable[loc].FuncName,i,success);
        return ;
    }
    //调用真正的函数    
    functable[loc].func(args[0][0],args[1][0],args[2][0],args[3][0],args[4][0],args[5][0],args[6][0]);
}


void ExternFunc_list(void)
{
    static char isfirstPrint = 0;
    
    int size = sizeof(functable)/sizeof(functable[0]);
        printf("QuickComplet:");
        for(int i = 0;i<size;i++)
        {
            printf("\"%s\"",functable[i].FuncName);
            if(i != (size-1))
                printf(",");
        }
    printf("\n\n*---------------------------------------------------------\n");
    for(int i = 0; i<size; i++)
    {
        printf(" |    %s(%s);%30s\n",functable[i].FuncName,functable[i].fmt,functable[i].Introduction);
        if(i != size-1)
            printf(" |--------------------------------------------------------\n");
    }
    printf("*---------------------------------------------------------\n");
}




static void ExternFunc_SocReset(void)
{
    
    __set_FAULTMASK(1);//关闭所有中断
    NVIC_SystemReset();//复位
}


static unsigned char matchString(const char* str1,const char* str2)
{
    char* ptemp1 = (char*) str1;
    char* ptemp2 = (char*) str2;
    while(*ptemp1 != '\0' || *ptemp2 != '\0')
    {
#if MATCH_CASE_ENABLE==0        
        if(((*ptemp1-*ptemp2) == ('A'-'a') || (*ptemp1-*ptemp2) == ('a'-'A'))&& 
            (*ptemp1>= 'A' && *ptemp1<= 'z' && *ptemp2>= 'A' && *ptemp2<= 'z'))
        {
            ptemp1++;
            ptemp2++;  
        }else if(*ptemp1 != *ptemp2) return 1;
#else
        if(*ptemp1 != *ptemp2) return 1;
#endif
            
        else 
        {
            ptemp1++;
            ptemp2++;            
        }
    }
    if(*ptemp1 == '\0'&& *ptemp2 == '\0')
        return 0;
    else
        return 0xFF;
}

