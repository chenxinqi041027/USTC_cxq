# 作业9nd

## 选择题

- #### (3)：D

    - 最后一层有$1011-(2^{9}-1)=490$个叶节点，对应着$\frac{490}{2}=245$个父节点
    - 倒数第二层有$2^8-245=11$个叶节点
    - 总共有$490+11=501$个叶节点

- #### (4)：C

    - $\lceil\log_2(n+1)\rceil\sim n$

- #### (8)：B

    - $20\times4+10\times3+1\times2+10\times1=20+10+1+10+x-1$
    - $x=82$

- #### (10)：C

- #### (14)：C

## 应用题

- #### (1)：

    1. 先序序列与后序序列相同：
        - 空树、仅含一个节点的树
    2. 中序序列与后序序列相同：
        - 空树、所有节点无右子节点的树
    3. 先序序列与中序序列相同：
        - 空树、所有节点无左子节点的树
    4. 中序序列与层次遍历序列相同：
        - 空树、所有节点无左子节点的树

- #### (2)：设一棵二叉树的先序序列为`A B D F C E G H`，中序序列为`B F D A G E H C`

    1. ![image-20221027223442448](C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221027223442448.png)
    2. ![img](file:///C:\Users\23764\Documents\Tencent Files\2376419868\Image\C2C\5AE6CF0A2F1C84146618074FDEEC68F7.png)
    2. ![image-20221031140348644](C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221031140348644.png)

