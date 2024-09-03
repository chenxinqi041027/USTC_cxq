#include<stdio.h>
#include<stdlib.h>
void merge(float *list,int m,int n)
{
	int i;
    float a[m],b[n],c[m+n];
    for(i=0;i<m;i++)
    a[i]=*(list+i);
    for(i=0;i<n;i++)
    b[i]=*(list+m+i);
    int j=0,k=0;
	for(i=0;j<m&&k<n;i++)
	{
		
	   if (a[j]<=b[k]) 
	   {
	 	  c[i]=a[j];
			j++;
	    }
	    else
	    {
	 	   c[i]=b[k];
	 	   k++;
	 	} 
    }
    if(j<m){
    	for(i=j+k;i<m+n;i++,j++){
    		c[i]=a[j];
		}
	}
	else{
		for(i=j+k;i<m+n;i++,k++){
    		c[i]=b[k];
		}
	}
	for(i=0;i<m+n;i++){
		*(list+i)=c[i];
	}
	return;
	
}
void merge_sort_recursive(float*list,int start,int end)
{
	float t;	
	if(end==start+2)
	{
		if(list[start]>list[start+1])
		{
			t=list[start];
			list[start]=list[start+1];
			list[start+1]=t;
		}
		return;
	}
    else if(end==start+1) return;
	else
	{
		merge_sort_recursive(list,start,(start+end+1)/2);
		merge_sort_recursive(list,(start+end+1)/2,end);
		merge(list+start,(start+end+1)/2-start,end-(start+end+1)/2);
	}
}
void merge_sort(float *list,int len)
{
	int sub_len=2;
	int i,k,t;
    while(sub_len<len)
    {
    	i=0;k=0;
    	t=len-len%sub_len;
		while(i<t)
		{
		   merge(list+i,sub_len/2,sub_len/2);	
		   i+=sub_len;
		   k++;
		}
		if(t<len)
		merge(list+t-sub_len,sub_len,len%sub_len);
		if(k>0)
		sub_len*=2;	
		else
		sub_len=len;	
	}	
}
int main()
{
	float list[]={4,0,7,2,5,2,4,3,1,3,5,1,4,1,3,2,6,2,3,7,7,5,3,2,9,6,5,2,3,0};
	int len =30,i;
	float *sort_recursive=(float *)malloc(len*sizeof(float)),*sort_iterative=(float *)malloc(len*sizeof(float));
	for(i=0;i<len;i++)
	{
		sort_recursive[i]=list[i];
		sort_iterative[i]=list[i];
	}
	merge_sort_recursive(sort_recursive,0,len);
	printf("sort_recursive = [");
	for(i=0;i<len-1;i++)
	    printf("%.01f, ",sort_recursive[i]);
	printf("%.01f]\n",sort_recursive[len-1]);
	merge_sort(sort_iterative,len);
	printf("sort_iterative =[");
	for(i=0;i<len-1;i++)
	    printf("%.01f, ",sort_iterative[i]);
	printf("%.01f]\n",sort_iterative[len-1]);	
	
	free(sort_recursive);
	sort_recursive=NULL;
	free(sort_iterative);
	sort_iterative=NULL;
	return 0;
}
