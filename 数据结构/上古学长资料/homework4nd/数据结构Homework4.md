# 数据结构Homework4

## 选择题

- #### (1)若让元素$1,2,3,4,5$依次进栈，则出栈次序不可能出现（  4,3,1,2,5  ）的情况。

    - A 5,4,3,2,1: Push Push Push Push Push Pop Pop Pop Pop Pop

    - B 2,1,5,4,3: Push Push Pop Pop Push Push Push Pop Pop Pop

    - C 4,3,1,2,5: 4首个出栈，则1,2,3必按倒序出栈

    - D 2,3,5,4,1: Push Push Pop Push Pop Push Push Pop Pop Pop

- #### (4)A

- #### (8)B

## 算法设计题

- #### 2.(2)

    - ```C++
        #include<bits/stdc++.h>
        using namespace std;
        bool Check(char* s){
        	int len=strlen(s);
        	char* stk=new char[len+1>>1];
        	int top=0;
        	for(int i=0;i<=(len-1>>1);i++)
        		stk[top++]=s[i];
        	for(int i=len>>1;i<len&&s[i]==stk[top-1];i++,top--);
        	free(stk);
        	return !top;
        }
        int main(){
        	char str[100];
        	cin>>str;
        	cout<<(Check(str)?"YES":"NO")<<endl;
        	return 0;
        }
        ```

