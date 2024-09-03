#include<stdio.h>
int main(){
    int a;
    FILE* fpRead;
    fpRead=fopen("input_3.txt","r");
    if(fpRead==NULL) return 0;
    fscanf(fpRead,"%d",&a);
    FILE* fpWrite;
    fpWrite=fopen("output_3.txt","w");
    fprintf(fpWrite,"%d",a);
    fclose(fpRead);
    fclose(fpWrite);
    return 0;
}