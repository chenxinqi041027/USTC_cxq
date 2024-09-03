# homework11nd

## 应用题

- #### (5)：

    1. 最早$43$分钟结束

    2. |      | $ve$ | $vl$ |
        | ---- | ---- | ---- |
        | 1    | 0    | 0    |
        | 2    | 19   | 19   |
        | 3    | 15   | 15   |
        | 4    | 29   | 37   |
        | 5    | 38   | 38   |
        | 6    | 43   | 43   |

    3. 关键活动有$1,2,3,5,6$

## 选择题

- #### (5)：C

## 应用题

- > #### (1)：假定对于有序表：`(3,4,5,7,24,30,42,54,63,72,87,95)`进行折半查找，试回答下列问题

    1. ##### 画出描述折半查找过程的判定树：

        - <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221130163135857.png" alt="image-20221130163135857" style="zoom:50%;" />

    2. ##### 若查找元素$54$，需依次与哪些元素比较？

        - `30,63,42,54`

    3. ##### 若查找元素$90$，需依次与哪些元素比较？

        - `30,63,87,95`

    4. ##### 假定每个元素的查找概率相等，求查找成功时的平均查找长度。

        - $\frac{4\times5+3\times4+2\times2+1\times1}{12}=\frac{37}{12}$

- > #### (2)：在一棵空的二叉排序树中依次插入关键字序列为`12,7,17,11,16,2,13,9,21,4`，画出所得到的二叉排序树

    - <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221130163629294.png" alt="image-20221130163629294" style="zoom: 67%;" />

## 算法设计题

- ### (3)：

    - ```C++
        #include<bits/stdc++.h>
        using namespace std;
        template<class T>class Tree{
        public:
        	T data;
        	Tree *lchild,*rchild;
        	Tree():lchild(NULL),rchild(NULL){}
        	Tree(const T& data):data(data),lchild(NULL),rchild(NULL){}
        };
        template<class T>void AddData(Tree<T>*& Root,T data){
        	if(!Root)Root=new Tree<T>(data);
        	else{
        		Tree<T>* cur=Root;
        		while(1){
        			if(data<cur->data){
        				if(cur->lchild)cur=cur->lchild;
        				else{
        					cur->lchild=new Tree<T>(data);
        					break;
        				}
        			}else{
        				if(cur->rchild)cur=cur->rchild;
        				else{
        					cur->rchild=new Tree<T>(data);
        					break;
        				}
        			}
        		}
        	}
        }
        template<class T>void dfs(const Tree<T>* cur,bool& flag,const T& x){
        	if(!cur)return;
        	if(!(cur->data<x))dfs(cur->lchild,flag,x);
        	if(flag)cout<<',';
        	if(flag|=!(cur->data<x))cout<<cur->data;
        	dfs(cur->rchild,flag,x);
        }
        int main(){
        	Tree<int>* T=NULL;
        	int n,x;
        	cin>>n;
        	while(cin>>x,n--)AddData(T,x);
        	bool flag=0;
        	dfs(T,flag,x);
        	return 0;
        }
        /*
        12
        3 4 5 7 24 30 42 54 63 72 87 95
        24
        */
        ```