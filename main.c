#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.c"
#define SIZE 50

typedef struct{
    char formula[SIZE];//产生式
}grammerElement;

grammerElement gramOldset[SIZE];//原始文法产生式集

/*char formula[SIZE][SIZE]={"E TR","R +TR","R $","T FY",
                          "Y *FY","Y $","F (E)","F i"};//产生式集，$代表空字符，空格为箭头*/
char formula[SIZE][SIZE];

//char terSymbol[SIZE]={'i','+','*','(',')','\0'};//终结符号

char terSymbol[SIZE];

//char non_ter[SIZE]={'E','R','T','Y','F','\0'};//非终结符

char non_ter[SIZE];

char allSymbol[SIZE];//所有符号

char firstSET[SIZE][SIZE];//First集

char followSET[SIZE][SIZE];//各产生式的Follow集

char forFirst[SIZE][SIZE];//每条产生式可推出的终结符集

int M[SIZE][SIZE];//分析表

void Init1(){
/*    int i,j;
    for(i=0;i<SIZE;i++)
      for(j=0;j<SIZE;j++)
        M[i][j]=-1;
    M[0][0]=0;
    M[0][3]=0;
    M[1][1]=1;
    M[1][4]=2;
    M[1][5]=2;
    M[2][0]=3;
    M[2][3]=3;
    M[3][1]=5;
    M[3][2]=4;
    M[3][4]=5;
    M[3][5]=5;
    M[4][0]=7;
    M[4][3]=6;
   */ }

void MainControl(char *str){
    char x,_str[SIZE];
    int i,j,n=0,flag,a,b,p;
    SqStack S;
    InitStack(&S);
    for(i=0,j=0;terSymbol[i]!='\0';i++){
      if(terSymbol[i]!='$')
        _str[j++]=terSymbol[i];
         }
    _str[j++]='#';
    _str[j]='\0';
    Push(&S,'#');
    Push(&S,non_ter[0]);//#和开始符进栈
    ShowStack(S);
    for(p=n;str[p]!='\0';p++)  printf("%c",str[p]);
    printf("\n");
    while(1){
      //ShowStack(S);
      flag=0;
      i=0;
      Pop(&S,&x);
      //printf("pop %c\n",x);
      ShowStack(S);
      for(p=n;str[p]!='\0';p++)  printf("%c",str[p]);
      printf("\n");
      while(_str[i]!='\0'){
        if(x!='#')
        if(x==_str[i]){
          flag=1;
          break;
        }
        i++;
    }
    if(1==flag){
        if(x==str[n]){
          n++;
          continue;
        }else{
          printf("error 1\n");
          DestroyStack(&S);
          exit(0);
          }
    }else if(x=='#'){
      if(x==str[n]){
          printf("It's a words! \n");
          DestroyStack(&S);
          break;
          }else{
          printf("error 2\n");
          DestroyStack(&S);
          exit(0);
          }
    }else{
      a=0;
      b=0;
      while(non_ter[a]!='\0'){
          if(x==non_ter[a]){
            //printf("a is %d\n",a);
            break;}
          a++;
        }
      while(_str[b]!='\0'){
          if(str[n]==_str[b]){
            //printf("b is %d\n",b);
            break;}
          b++;
      }
      if(M[a][b]==-1){
        printf("error 3\n");
        printf("a=%d,b=%d\n",a,b);
        DestroyStack(&S);
        exit(0);
        }else{
           i=M[a][b];
           j=3;
           //printf("i=%d\n",i);
           while(formula[i][j]!='\0')
             j++;
           for(j--;!(formula[i][j]=='>'&&formula[i][j-1]=='-');j--){
             if(formula[i][j]=='$')
               break;
              // printf("2\n");
             Push(&S,formula[i][j]);
             ShowStack(S);
             for(p=n;str[p]!='\0';p++)  printf("%c",str[p]);
             printf("\n");
             //printf("push %c\n",formula[i][j]);
           }
          }
     }
    }
  }

void Init(int n){
    int i=0,j=0,a=0,b=0,flag=0,o=0;
    char str[SIZE];
    printf("Input syntax:\n");
    for(;i<n;i++){
        scanf("%s",str);
        strcpy(formula[i],str);
        for(j=0;str[j]!='\0';j++){
           // printf("  str[%d]=%c\n",j,str[j]);
          if(str[j]>=65&&str[j]<=90){
              for(o=0;o<=a;o++){
                if(str[j]==non_ter[o]){
                  flag=1;
                  break;
                  }
                }//判断非终结符是否重复
                if(flag==0){
                  non_ter[a++]=str[j];//非终结符存入内存
                  //printf("          non=%c\n",non_ter[a-1]);
                  }else flag=0;
            }else if(str[j]=='-'&&str[j+1]=='>'){
                j=j+1;//跳过箭头
            }else{
              for(o=0;o<b;o++){
                if(str[j]==terSymbol[o]){
                  flag=1;
                  break;
                  }
              }//判断终结符是否重复
              if(flag==0){
                terSymbol[b++]=str[j];//终结符存入内存
                //printf("         ter=%c\n",terSymbol[b-1]);
                }else flag=0;
        }
        }
    }
    non_ter[a]='\0';
    terSymbol[b]='\0';
    printf("all syntax is:\n");
    for(i=0;i<n;i++){
        printf("%s\n",formula[i]);
        }
    printf("all non_ter is:%s\n",non_ter);
    printf("all terSymbol is:%s\n",terSymbol);
    }

int addFirst(int n,char ch){
	int i=0;
	if(!strchr(firstSET[n],ch)){
		while(firstSET[n][i]!='\0')
		  i++;
		firstSET[n][i++]=ch;
		firstSET[n][i]='\0';
		return 1;
	}
	return 0;
}

int addFollow(int n,char ch){
	int i=0;
	if(!strchr(followSET[n],ch)){
		while(followSET[n][i]!='\0')
		  i++;
		followSET[n][i++]=ch;
		followSET[n][i]='\0';
		return 1;
	}
	return 0;
}

int inNon(char ch){
	int i=0;
	while(non_ter[i]!='\0'){
		if(ch==non_ter[i])  return i;
		else  i++;
	}
	return -1;
}//判断一个字符是否在非终结符集 ,如果在则返回其位置

int inTer(char ch){
	int i=0;
	while(terSymbol[i]!='\0'){
		if(ch==terSymbol[i])  return 1;
		else  i++;
	}
	return 0;
}//判断是否属于终结符集

void getFirst(int n){
	int i=0,j,change=0,flag=0,o=0,k,x;
	for(;i<SIZE;i++)
		firstSET[i][0]='\0';
	do{
		change=0;
		i=0;
	while(non_ter[i]!='\0'){
		j=0;
		for(;j<n;j++){
			flag=1;//flag标志是否查找该产生式下一位
			o=3;
			while(flag==1&&formula[j][o]!='\0'){
			if(formula[j][0]!=non_ter[i])  break;
			else{
				if(inTer(formula[j][3])){
					if(addFirst(i,formula[j][3]))
					  change=1;//产生式首位是终结符加入first集
					  break;
				}else if(formula[j][3]==non_ter[i]){
					continue;//首位是相同非终结符，跳过
				}else{
						x=inNon(formula[j][o]);//得到该非终结符在非终结符集中的位置
						if(!strchr(firstSET[x],'$'))
						  flag=0;//非终结符不含空，则标记不再寻找该条产生式
						else if(formula[j][o+1]=='\0'){
							if(addFirst(i,'$'))
							  change=1;//如果当前非终结符为最后一位非终结符且包含空，则把空加入first集中
						}
						for(k=0;firstSET[x][k]!='\0';k++){
							if(firstSET[x][k]!='$'&&addFirst(i,firstSET[x][k]))
							  change=1;//把当前非终结符first集加入
						}
						o++;
				}
			}
		}
		}
		i++;
	}
  }while(change==1);
}

void getFollow(int n){
	int i=0,change=1,j,x,y,p,o,flag;
	followSET[0][0]='#';
	followSET[0][1]='\0';//开始符放入#
	for(i=1;i<SIZE;i++)
	  followSET[i][0]='\0';
	do{
		change=0;
		for(i=0;i<n;i++){
			j=3;
			while(formula[i][j]!='\0'){
				if(inTer(formula[i][j])){
					j++;
					continue;
				}else{
					x=inNon(formula[i][j]);
					if(formula[i][j+1]!='\0'){
						if(inTer(formula[i][j+1])){
							if(addFollow(x,formula[i][j+1]))
							  change=1;
							j++;
							continue;//若有A->Ba形式，把a加入B的follow集
						}else{
							o=1;
							flag=1;
							while(flag==1&&formula[i][j+o]!='\0'){
						    	y=inNon(formula[i][j+o]);
							    for(p=0;firstSET[y][p]!='\0';p++){
								  if(firstSET[y][p]!='$')
								    if(addFollow(x,firstSET[y][p]))
								      change=1;
						    	}//若有A->BACD形式，把ACD的first集除去去空加入到B的follow集中
							    if(!strchr(firstSET[y],'$'))
							      flag=0;
							    o++;
							    if(inTer(formula[i][j+o])){
								  if(addFollow(x,formula[i][j+o]))
								    change=1;
								  flag=0;
									}
						}//A->BAC，若A含有空，把C的first集加入A中
						}
					}
					}
					j++;
				}//规则1，2
				j=3;
				while(formula[i][j++]!='\0');
				j=j-2;
				flag=1;
				x=inNon(formula[i][0]);
				while(!inTer(formula[i][j])&&flag==1){
					y=inNon(formula[i][j]);
					for(p=0;followSET[x][p]!='\0';p++)
					  if(addFollow(y,followSET[x][p]))
					    change=1;
					j--;
					if(!strchr(firstSET[y],'$'))
					  flag=0;
				}//规则3
			}
		}while(change==1);
	}

int addForFirst(int n,char ch){
    int i=0;
    if(!strchr(forFirst[n],ch)){
        while(forFirst[n][i]!='\0')
          i++;
        forFirst[n][i]=ch;
        forFirst[n][i+1]='\0';
        return 1;
      }else return 0;
}

void getForFirst(int n){
    int i,j,x,o,flag;
    for(i=0;i<n;i++){
        flag=1;
        j=0;
        if(inTer(formula[i][3])){
          forFirst[i][j]=formula[i][3];
          continue;
        }else{
            o=3;
            while(flag&&formula[i][o]!='\0'){
              x=inNon(formula[i][o]);
              if(!strchr(firstSET[x],'$'))
                flag=0;
              for(j=0;firstSET[x][j]!='\0';j++)
                addForFirst(i,firstSET[x][j]);
              o++;
              if(inTer(formula[i][o])){
                addForFirst(i,formula[i][o]);
                break;
              }
            }
    }
    }
}

void getForm(int n){
    int i,j,o,x,k;
    char str[SIZE],ch;
    for(i=0,j=0;terSymbol[i]!='\0';i++){
      if(terSymbol[i]!='$')
        str[j++]=terSymbol[i];
         }
    str[j++]='#';
    str[j]='\0';
    for(i=0;i<SIZE;i++)
      for(j=0;j<SIZE;j++)
        M[i][j]=-1;
    for(i=0;i<n;i++){
      o=inNon(formula[i][0]);
      for(j=0;forFirst[i][j]!='\0';j++){
          if(forFirst[i][j]=='$'){
            for(x=0;followSET[o][x]!='\0';x++){
              ch=followSET[o][x];
              for(k=0;str[k]!='\0';k++){
                if(str[k]==ch){
                  M[o][k]=i;
                  break;
                  }
            }
            }
          }else {
          for(x=0;str[x]!='\0';x++)
            if(str[x]==forFirst[i][j]){
              M[o][x]=i;
              break;
            }
          }
        }
        }
    printf("  ");
    for(i=0;str[i]!='\0';i++)  printf("     %c",str[i]);
    printf("\n");
    for(i=0;non_ter[i]!='\0';i++){
      printf("%c",non_ter[i]);
      for(j=0;str[j]!='\0';j++)
        if(M[i][j]!=-1)
          printf(" %s ",formula[M[i][j]]);
        else  printf(" error ");
        printf("\n");
      }
    }

int main()
{
    int i,n;
    printf("Input Num of syntax:\n");
    scanf("%d",&n);
    Init(n);
    getFirst(n);
    getFollow(n);
    for(i=0;non_ter[i]!='\0';i++)
      printf(" %c  First is %s\n",non_ter[i],firstSET[i]);
    for(i=0;non_ter[i]!='\0';i++)
      printf(" %c  Follow is %s\n",non_ter[i],followSET[i]);
    getForFirst(n);
    for(i=0;i<n;i++){
		printf("%d-----%s\n",i,forFirst[i]);
	}
	getForm(n);
	char* str="i*i+#";
    MainControl(str);
    return 0;
}
