#include<stdio.h>
int main(){
	/*int n;//ÐÐÊý 
	scanf("%d",&n);
	int a[2][n-1],b[n-1],c[n-1],j,k;
	//b xÖá
	//c yÖá 
	for(int i=0;i<n;i++){
		scanf("%d %d %d %d",&a[1][i],&a[2][i],&j,&k);
		b[i]=j+a[1][i];
		c[i]=k+a[2][i]; 
	}
	int h,l,m=0;
	scanf("%d %d",&h,&l);
	for(int i=0;i<n;i++){
		if(h<=b[i]&&h>=a[1][i]&&l<=c[i]&&l>=a[2][i]) m++;
	}
	if(m==0) printf("-1");
	else printf("%d",m); 
*/
	int a=1,b=2,c=3,d=4;
	printf("%d",(a<b?a:c)<d?c:d);
}
