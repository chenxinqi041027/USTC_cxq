#include<cstdio>
using namespace std;
const int N=9;
int oper[N+5];
void dfs(int cur,int sum){
    if(cur>N){
        if(sum==110){
            for(int i=1;i<=N;i++){
                if(oper[i]&&i>1)putchar(~oper[i]?'+':'-');
                printf("%d",i);
            }puts("=110");
        }return;
    }
    int res=0;
    int ccur=cur;
    while(cur<=N){
        res=res*10+cur;
        oper[ccur]=1;dfs(cur+1,sum+res);
        if(ccur>1)oper[ccur]=-1;dfs(cur+1,sum-res);
        oper[cur]=0;
        cur++;
    }oper[ccur]=0;
}
int main(){
    dfs(1,0);
    return 0;
}