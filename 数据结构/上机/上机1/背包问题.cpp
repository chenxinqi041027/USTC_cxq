#include <stdio.h>

#define MAXSIZE 100

int result[MAXSIZE]; //存放结果的数组
int count=0; // 记录找到的解的数量

void OutputResult(int *a,int index,FILE* fpWrite){//输出结果
    for (int i=0;i<index;i++) {
            if (result[i]) {//选取该元素
                fprintf(fpWrite,"%d ",a[i]);
            }
        }
        fprintf(fpWrite,"\n");
}

// 回溯函数
void Backtracking(int T,int n,int* a,int index,int sum,FILE* fpWrite) {
    if(sum==T){ // 找到一个解
        OutputResult(a,index,fpWrite);
        count++;
        return;
    }

    if (index >= n||sum>T) {//处理完所有物品或者和大于T，直接结束
        return;
    }
    //选取当前物品
    result[index] = 1;
    Backtracking(T, n, a, index + 1, sum + a[index],fpWrite);

    //不选取当前物品
    result[index] = 0;
    Backtracking(T, n, a, index + 1, sum,fpWrite);
}

// 解决背包问题
void SolveKnapsack(int T,int n,int* a,FILE* fpWrite) {
    Backtracking(T,n,a,0,0,fpWrite);
    fprintf(fpWrite,"The number of solutions: %d\n", count);
}

int main(int argc,char *argv[]) {
    int T,n;
    //输入
    FILE* fpRead=NULL;
    fpRead=fopen(argv[1],"r");
    if(fpRead==NULL) return 0;
    fscanf(fpRead,"%d %d",&T,&n);
    if(n>MAXSIZE){
        printf("ERROR");
        return 0;
    }
    int a[MAXSIZE];
    for(int i=0;i<n;i++){
        fscanf(fpRead,"%d",&a[i]);
    }
    //输出
    FILE* fpWrite=NULL;
    fpWrite=fopen(argv[2],"w");
    //fprintf(fpWrite,"%d",a);
    
    SolveKnapsack(T, n, a,fpWrite);
    fclose(fpRead);
    fclose(fpWrite);
    return 0;
}