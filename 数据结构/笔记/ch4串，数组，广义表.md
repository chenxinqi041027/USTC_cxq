# ch4 串，数组，广义表

## 串

> 串是特殊线性表，结点是单个字符

1. 静态存储分配的顺序串

```cpp
Typedef char SeqString[MaxStrSize];
SeqString S;
```

> 串终止符："\0"

2. 动态存储分配的字符串的两种方式

```cpp
typedef char *string;
typedef struct{
	char *ch;
	int length;
}Hstring;
```

### 串的链式存储

```cpp
#define CHUNKSIZE 80       //可由用户定义的块大小
typedef struct Chunk{
   char  ch[CHUNKSIZE];
   struct Chunk *next;
}Chunk;

typedef struct{
   Chunk *head,*tail;      //串的头指针和尾指针
   int curlen;             //串的当前长度
}LString;
```

> 操作方便但是存储密度低
>
> ==$$存储密度 =  \frac{串值所占的存储位}{实际分配的存储位}$$==

### 串的模式匹配算法

+ BF算法

  + 逐个比较字符，若相等则继续比较，若不相等则从第一个字符开始重新比较

    ```cpp
    int  Index(Sstring S,Sstring T,int pos){
        i=pos;   j=1;
       while (i<=S[ 0 ] && j <=T[ 0 ]){
           if ( S[ i ]=T[ j ]) {++i;  ++j; }
          else{ i=i-j+2;    j=1; }
       if ( j>T[ 0 ])   return   i－T[0];
       else return 0;
    }
    ```

  + 最坏的情况，比较了$(n-m+1)*m$次算法复杂度$O(n*m)$



+ **KMP算法**

  + 定义next[j]函数，表明当模式中第j个字符与主串中相应的字符“失配”，在模式中需重新和主串中该字符进行比较的字符的位置。

  + ```cpp
    int Index_KMP (SString S,SString T, int pos) 
    {      
           i= pos,j =1;
           while (i<S[0] && j<T[0]) {     
                 if (j==0 || S[i]==T[j]) {   i++;j++;  }
                 else 
                     j=next[j];         /*i不变,j后退*/
           }
           if (j>T[0])  return i-T[0];  /*匹配成功*/
           else   return 0; 	         /*返回不匹配标志*/
    } 
    ```

  

  + 求next[j]:

    + next[1] = 0;表明主串从下一字符si+1起和模式串重新开始匹配。i = i+1; j = 1;

    + **设next[j] = k，则next[j+1] = ?**

      **①****若pk=pj，则有“p1…pk-1pk”=“pj-k+1…pj-1****p****j****”** **，如果在** **j+1****发生不匹配，则有****next[j+1] = k+1 = next[j]+1****。**

      **②若****p****k****≠p****j****，可把求****next****值问题看成是一个模式匹配问****题，整个模式串既是主串，又是子串。**

```cpp
void get_next(SString T, int &next[])
{
     j= 1; next[1] = 0; k = 0;   
     while( j<T[0]){
          if(k==0 || T[j] == T[k]){
                ++j; ++k; 
                next[j] = k;
          }
          else
                k = next[k];
     }
}            
```



+ KMP算法时间复杂度：

求next数组的时间复杂度为O(m),比较次数为n,时间复杂度为O(n+m)

+ KMP算法中优化的nextval数组

```cpp
void get_nextval(SString T, int &nextval[])
{
     j= 1; nextval[1] = 0; k = 0;   
     while( j<T[0]){
          if(k==0 || T[j] == T[k]){
                ++j; ++k; 
                if(T[j] != T[k]) nextval[j] = k;
                else  nextval[j] = nextval[k];
          }
          else  k = nextval[k];
     }
}       
```



## 数组

> 本章中数组是顺序的也可以是链式的

+ 存储方式
  + 行优先：列下标变换快
  + 列优先：行下标变换快
  + 地址计算：基地址：a11的地址，维数，每维的上下界，每个元素占用的单元数（元素大小）

> 行序列$A_{m*n}(m行n列)$ 
>
> $Loc(a_{ij}) = Loc(a_{11})+[(i-1)*n + (j-1)]*L$

>  随机存取

### 矩阵压缩存储

> **存于sa[0……n(n+1)/2-1]中**

1. 对称阵：只存上三角或者下三角，元素个数$n(n+1)/2$

​	对于aij

+ 下三角中j>=i
+ 上三角中i<j

​	sa[k]中的$k=i(i+1)/2+j$

​	令$I=max(i,j),J=min(i,j),k=I(I+1)/2+J$

2. 三角矩阵，在sa中多增加一个单元sa[0……n(n+1)/2]，将C存于最后一个分量中
3. 对角矩阵
4. 稀疏矩阵：零元素非常多

> 只存储非零元，须存储辅助信息，才能确定其位置，三元组（行号，列好，非零元的值）
>
> 两种方式：顺序和链式





## 广义表

> n(n>0)个表元素组成的有限序列
>
> LS= (a0,a1,a2,……,an-1)
>
> LS是表名，ai是表元素，可以是表，可以是数据元素s
>
> n为表的长度,n=0的广义表为空表

**广义表和线性表的区别**

+ 线性表的成分都是结构上不可分的单元素；广义表的成分可以是单元素，也可以是有结构的表
+ 线性表是一种特殊的广义表，广义表不一定是线性表，也不一定是线性结构

**广义表的基本运算**

+ 表头：非空广义表的第一个元素可以是氮元素也可以是一个子表
+ 表尾：非空广义表除去表头元素以外其他元素构成的表，**表尾一定是一个表**

**广义表特性**

+ 有次序行：一个直接前驱，一个直接后继
+ 有长度：表中元素个数
+ 有深度：表中括号的重数
+ 可递归：自己可以做自己的子表
+ 可共享：可为其他广义表共享

























