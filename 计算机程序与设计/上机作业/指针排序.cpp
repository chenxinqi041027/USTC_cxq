#include<stdio.h>
#include<stdlib.h>
struct S
{
    float value;
    char name[1000];
};
void sort(struct S **p_list,int n)
{
    struct S *p;
    for(int i=0;i<n;i++)
    {
        p=p_list[i];
        for(int j=i;j<n;j++)
        {
            if((*p_list[j]).value<(*p_list[i]).value)
            {
                p=p_list[j];
                p_list[j]=p_list[i];
                p_list[i]=p;
            }
        }
    }
    return;
}

int main()
{
    int n=30,i;
    struct S *list=(struct S *)malloc(n * sizeof(struct S));
    struct S **p_list=(struct S **)malloc(n *sizeof(struct S *));
	for(i=0;i<n;i++){
		list[i].value=30-i;
		p_list[i]=list+i;
		}
		sort(p_list,n);
		for(i=0;i<n;i++)
		printf("%2.01f,",(*(p_list[i])).value);
		return 0; 
} 
