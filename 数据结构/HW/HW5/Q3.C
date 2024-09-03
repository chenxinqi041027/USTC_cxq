#include<stdio.h>
#define max_size 100

int judge(int arr[][max_size],int m,int n){
    int base[max_size]={0};
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(base[arr[i][j]]) return 0;
            base[arr[i][j]]=1;//对已经出现的数字在数组中相应的位置做标记
        }
    }
    return 1;
}

int main(){
    int m,n;
    int a[max_size][max_size];
    printf("input1:");//输入行数列数
    scanf("%d %d",&m,&n);
    printf("input2:");//输入数据
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&a[i][j]);
        }
    }
    if(judge(a,m,n)) printf("yes");
    else printf("no");
    return 0;
}