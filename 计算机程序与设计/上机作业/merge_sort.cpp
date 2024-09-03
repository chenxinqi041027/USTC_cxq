#include<stdio.h>
#include<math.h>
#include<stdlib.h>
void merge(float *list, int m, int n )
{
    float *merge_sort =(float *)malloc((m+n) *sizeof(float));
    int i=0, j=0;
    for(int k=0;k<(m+n);k++)
    {
        if(i==m)
        {
            merge_sort[k]=*(list+m+j);
            j++;
            continue;
        }
        if(j==n)
        {
            merge_sort[k]=*(list+i);
            i++;
            continue;
        }
        if(*(list+i)<=*(list+j+m))
        {
            merge_sort[k]=*(list+i);
            i++;
            continue;
        }
        else
        {
            merge_sort[k]=*(list+j+m);
            j++;
            continue;
        }
    }
    for(int p=0;p<(m+n);p++) list[+p] = merge_sort[p];
    free(merge_sort);
    return;
}

void merge_sort_recursive(float *list,int start, int end)
{
    int s=(start+end)/2;
    if(start<end){
    merge_sort_recursive(list,start,s);
    merge_sort_recursive(list,s+1,end);
    }
    merge(list+start,s-start+1,end-s);
    return;
}

void merge_sort_iterative(float *list,int len)
{
    int sub_len=1;
    int num,rest=0,last_rest=0;
    while (sub_len<len)
    {
        sub_len*=2;
        num=len/sub_len;
        last_rest=rest;
        rest=len%sub_len;
        for(int i=1;i<=num;i++) merge(list+sub_len*(i-1),sub_len/2,sub_len/2);
        merge(list+num*sub_len,rest-last_rest,last_rest);
    }
    return;
}

int main()
{
    float list[200];
    int len , i;
    scanf("%d",&len);
    float* sort_recursive = (float *)malloc(len * sizeof(float)) , *sort_iterative = (float *)malloc(len * sizeof(float));
    for(int i=0;i<len;i++)
    {
        scanf("%f",&list[i]);
        sort_recursive[i]=list[i];
        sort_iterative[i]=list[i];
    }
    
    merge_sort_recursive(sort_recursive,0,len-1);
    printf("sort_recursive = [");
    for(int i=0;i<len-1;i++) printf("%.01f ",sort_recursive[i]);
    printf("%.01f]\n",sort_recursive[len-1]);
    
    merge_sort_iterative(sort_iterative,len);
    printf("sort_iterative = [");
    for(int i=0;i<len-1;i++) printf("%.01f ",sort_iterative[i]);
    printf("%.01f]\n",sort_iterative[len-1]);
    
    free(sort_iterative);
    free(sort_recursive);
    
    return 0;
}