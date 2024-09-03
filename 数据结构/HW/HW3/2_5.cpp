#include<stdio.h>
#include<string.h>
bool Judge(char s[]){
    int i=0,j=0,k=0;//i表示第i个字符，j表示入栈个数，k表示出栈个数
    while(s[i]!='\0'){
        switch(s[i]){
            case 'I':j++;
                    break;
            case 'O':k++;
                    break;
            default:return false;
        }
        if(j<k) return false;
        i++;
    }
    if(j!=k) return false;
    return true;
}

int main(){
    char s[10]={'I','O','O','I','O','I','I','O'};
    if(Judge(s)) printf("1");
    else printf("0");
    return 0;
}