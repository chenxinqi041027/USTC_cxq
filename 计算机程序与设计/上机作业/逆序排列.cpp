#include<stdio.h>
int main(){
	int m=5,n=6,i,j,k=1,l;
	double seq1[m],seq2[n],seq3[n+m];
	for(i=1;i<=m;i++,k++)
	{ 
		scanf("%lf",&seq1[i]);  
		seq3[k] = seq1[i];
	} 
	for(j=1;j<=n;j++,k++)
	{
		scanf("%lf",&seq2[j]);
		seq3[k]=seq2[j];
	}
	printf("seq1=[%.1lf",seq1[1]);
	for(i=2;i<=m;i++) printf(", %.1lf",seq1[i]);
	printf("]\n");
	printf("seq2=[%.1lf",seq2[1]);
	for(j=2;j<=n;j++) printf(", %.1lf",seq2[j]);
	printf("]\n");
	for(l=1;l<=n+m;l++)
	{
	for(k=1;k<n+m;k++)
	{if(seq3[k]>seq3[k+1])
			{
				int temp=seq3[k+1];
				seq3[k+1]=seq3[k];
				seq3[k]=temp;}
			}
			//printf("\n");
		}
		printf("seq3=[%.1lf",seq3[1]);
	for(k=2;k<=n+m;k++)
	{
		printf(", %.1lf",seq3[k]);
	}
	printf("]\n");
	return 0;
}
//		for(int s = 1; s <= m + n; ++s) printf("%.1lf    ", seq3[s]);
//		for(int s = 1; s <= m + n; ++s) printf("%.1lf    ", seq3[s]);
//	for(i = 1; i <= m + n; i++) printf("%.1lf  ", seq3[i]);
	//	for(int s = 1; s <= m + n; ++s) printf("%.1lf    ", seq3[s]);
// 2 4 3 1 5 
// 1  4  3  2 5
// 1  3 2 4 5
//	int min=seq3[l];
	/*	for(k=l+1;k<n+m;k++)
		{
			if(seq3[k]<min)
			{
				int temp=min;
				min=seq3[k];
				seq3[k]=temp;
			}*/
			
		//	printf("%.1lf  ",min);
