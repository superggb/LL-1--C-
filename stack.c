#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT   10
typedef char SElemType;
typedef struct{
SElemType *base;
SElemType *top;
SElemType stacksize;
}SqStack;

void InitStack(SqStack *S)//形参为指针则函数内部也应用->而不是.来引用结构体
{
    S->base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S->base)
    exit(0);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    //printf("InitStack success\n");
}

int GetTop(SqStack S,SElemType *e)
{
    if(S.top==S.base)
    return 0;
    *e=*(S.top-1);
    return 1;
}

void Push(SqStack *S,SElemType e)
{
    if(S->top-S->base>=S->stacksize)
    {
        S->base=(SElemType*)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SElemType));
      if(!S->base)
       exit(0);
      S->top=S->base+S->stacksize;
      S->stacksize+=STACKINCREMENT;
    }
    *S->top++=e;
    //printf("Push success\n");
}

void DestroyStack(SqStack *S)
{
    free(S->base);
    S->base=NULL;
    //printf("Destroy success\n");
}

void ClearStack(SqStack *S)
{
    S->top=S->base;
    printf("Clear success\n");
}

int StackEmpty(SqStack S)
{
    if(S.top==S.base)
     return 1;
    else
     return 0;
}

int StackLength(SqStack S)
{
    int n;
    n=S.top-S.base;
    return n;
}

int Pop(SqStack *S,SElemType *e)
{
    if(S->top==S->base)
     return 0;
    *e=*--S->top;
    return 1;
}

 int StackTraverse(SqStack S,int(*visit)(int))
 {
     SElemType *q;
     q=S.base;
     while(q!=S.top)
     {
         if(visit(*q)==1)
          q++;
         else
          return 0;
     }
     return 1;
 }

 int ShowStack(SqStack S){
     if(S.top==S.base)
       return 0;
     SElemType *show;
     show=S.base;
     while(show!=S.top){
       printf("%c",*show++);
     }
     printf("        ");
      return 1;
     }

 int show(int n)
 {
   printf("%d\n",n);
   return 1;
 }

//int main()
//{
//    SqStack S;
//    int n,e;
//    printf("1.InitStack          2.GetTop\n");
//    printf("3.Push               4.Pop\n");
//    printf("5.StackTraverse      6.StackLength\n");
//    printf("7.StackEmpty         8.ClearStack\n");
//    printf("9.DestroyStack       0.exit\n");
//    scanf("%d",&n);
//    while(n)
//    {
//       switch(n)
//       {
//           case 1:
//             InitStack(&S);
//             break;
//           case 2:
//             if(GetTop(S,&e)==1)
//              printf("e=%d\n",e);
//             else
//              printf("Empty\n");
//             break;
//           case 3:
//             printf("Input the e:\n");
//             scanf("%d",&e);
//             Push(&S,e);
//             break;
//           case 4:
//             if(Pop(&S,&e)==1)
//               printf("e=%d\n",e);
//             else
//               printf("Empty\n");
//             break;
//           case 5:
//             if(StackTraverse(S,show)==0)
//              printf("Traverse success\n");
//             else
//              printf("Traverse failed\n");
//             break;
//           case 6:
//             printf("Length is %d\n",StackLength(S));
//             break;
//           case 7:
//             if(StackEmpty(S)==1)
//              printf("Empty\n");
//             else
//              printf("Not Empty\n");
//             break;
//           case 8:
//             ClearStack(&S);
//             break;
//           case 9:
//             DestroyStack(&S);
//             break;
//       }
//       scanf("%d",&n);
//    }
//    return 0;
//}
