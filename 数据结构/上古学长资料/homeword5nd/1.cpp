#include<cstdio>
const int maxn=1e6+5;
int n,A[maxn],pos[maxn];
int stk[maxn],top;
bool instk[maxn];
void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&A[i]);
        pos[A[i]]=i;
        instk[i]=0;
    }
    top=0;
    int x;
    int cur=0;
    for(int i=0;i<n;i++){
        scanf("%d",&x);
        while(cur<=pos[x]){
            stk[++top]=A[cur];
            instk[A[cur]]=top;
            cur++;
        }
        if(stk[top]!=x)return puts("NO"),void();
        top--;
        instk[x]=0;
    }puts("YES");
}
int main(){
    solve();
    return 0;
}