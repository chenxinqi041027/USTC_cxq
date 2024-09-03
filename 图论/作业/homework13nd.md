# homework13nd

## 九

- ### 1

    - > 假设$f$是网络$N=(D,s,t,c)$上的流函数，证明：$\displaystyle\sum_{e\in\alpha(t)}f(e)-\sum_{e\in\beta(t)}f(e)=\sum_{e\in\beta(s)}f(e)-\sum_{e\in\alpha(s)}f(e)$

    - $$
        \begin{align}
        0&=\sum_{v\in V(D)}\left(\sum_{e\in\alpha(v)}f(e)-\sum_{e\in\beta(v)}f(e)\right)\\&=\sum_{v\in\{s,t\}}\left(\sum_{e\in\alpha(v)}f(e)-\sum_{e\in\beta(v)}f(e)\right)\\
        \sum_{e\in\alpha(t)}f(e)-\sum_{e\in\beta(t)}f(e)&=\sum_{e\in\beta(s)}f(e)-\sum_{e\in\alpha(s)}f(e)
        \end{align}
        $$

- ### 2（2）

    - > 假设$f$是网络$N=(D,s,t,c)$上的流函数，$X\subset V(D)$
        >
        > 举例说明：存在网络流$f$，使得$\displaystyle\sum_{v\in X}\sum_{e\in\beta(v)}f(e)\neq f^+(X)$，$\displaystyle\sum_{v\in X}\sum_{e\in\alpha(v)}f(e)\neq f^-(X)$

    - ```mermaid
        flowchart LR
        	s((s))
        	v1((v1))
        	v2((v2))
        	t((t))
        	s--1-->v1
            subgraph X
            v1--1--->v2
            end
            v2--1--->t
        ```
        
    - 上图中$\displaystyle\sum_{v\in X}\sum_{e\in\beta(v)}f(e)=2\neq f^+(X)=1$，$\displaystyle\sum_{v\in X}\sum_{e\in\alpha(v)}f(e)=2\neq f^-(X)=1$

- ### 4

    - > 求下图中网络的最大流
        >
        > <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221124164156925.png" alt="image-20221124164156925" style="zoom:50%;" />

    - <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221124170443087.png" alt="image-20221124170443087" style="zoom:30%;" />

    - 寻找可增广轨道$P_1(s,t)=sv_1v_3v_4t$，$l(P_1)=3$

    - <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221124170551593.png" alt="image-20221124170551593" style="zoom:30%;" />

    - 寻找可增广轨道$P_2(s,t)=sv_3v_4t$，$l(P_2)=3$

    - <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221124170716858.png" alt="image-20221124170716858" style="zoom:30%;" />

    - 得到最大流$f$，$\operatorname{Val}(f)=l(P_1)+l(P_2)=6$

- ### 5

    - > 证明：若网络中每条边的容量均为整数，则最大流的流量也一定是整数

    - 最小截$C_{min}(S,\bar{S})=\operatorname{Val}(f^*)$，而由于$\displaystyle C_{min}(S,\bar{S})=\sum_{e\in(S,\bar{S})}c(e)$为整数，故最大流量也为整数

- ### 7

    - > 在图示的网络中，除了边有容量外，源$s$与汇$t$没有容量，而其余的顶点都有容量。求此网络的最大流
        >
        > <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221130210728099.png" alt="image-20221130210728099" style="zoom:50%;" />

    - 记点容量$g(v)$，$v\in V(D)-\{s,t\}$，构造网络$N'=(D',s,t,c')$

    - 其中$V(D')=\{s,t\}\cup\{v^+|v\in V(D)\}\cup\{v^-|v\in V(D)\}$

    - $\begin{align}E(D')=&\{(u^+,u^-)|u\in V(D)\}\\\cup&\{(u^-,v^+)|u,v\in V(D)且(u,v)\in E(D)\}\\\cup&\{(s,u^+)|u\in V(D)且(s,u)\in E(D)\}\\\cup&\{(v^-,t)|v\in V(D)且(v,t)\in E(D)\end{align}$

    - $\displaystyle c'(e)=\begin{cases}g(u),&e=(u^+,u^-)\\c(u,v),&e=(u^-,v^+)\\c((s,u)),&e=(s,u^+)\\c((v,t)),&e=(v^-,t)\end{cases}$

    - 得到网络$N'$如下：

    - <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221130213323418.png" alt="image-20221130213323418" style="zoom:30%;" />

    - 先删去边$(d^-,t)$，求得最大流$\operatorname{Val}(f')=6$

    - <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221130214716406.png" alt="image-20221130214716406" style="zoom:33%;" />

    - 不妨记$C=c'((d^-,t))$

    - 若$C\geq4$，则有最大流$\operatorname{Val}(f')=10$

    - <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221130215515395.png" alt="image-20221130215515395" style="zoom:33%;" />

    - 若$3\leq C<4$，则有最大流$\operatorname{Val}(f')=6+C$

    - <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221130220253458.png" alt="image-20221130220253458" style="zoom:33%;" />

    - 若$0\leq C<3$，则有最大流$\operatorname{Val}(f')=6+C$

    - <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221130220531755.png" alt="image-20221130220531755" style="zoom:33%;" />

- ### 8

    - > (1)：写一个如同$2F$算法的标志过程，但标记是由汇$t$开始的，到达$s$时即可得一可增载轨道

    - (1)：令$T=\{t\}$，令$\operatorname{prev}(s)=∗$。

    - (2)：若$s\in T$，则已经找到可增载轨道, 通过$\operatorname{prev}(s)$回溯输出可增载轨道，算
        法停止；否则，转第(3)步。

    - (3)：若存在$u\in\overline{T}$，$v\in T$，使得$(u,v)\in E(D)$且边$(u,v)$未满载，即$f((u,v))<c((u,v))$（$(u,v)$是正向边），则令$T\leftarrow T\cup\{T\}$，$\operatorname{prev}(u)=v$，转第(2)步；否则，转第(4)步。

    - (4)：若存在$u\in\overline{T}$，$v\in T$，使得$(v,u)\in E(D)$且边$(v,u)$正载，即$f((u,v))>0$（$(v,u)$是反向边），则令$T\leftarrow T\cup\{u\}$，$\operatorname{prev}(u)=v$，转第(2)步；否则，输出无可增载轨道，算法停止。

    - > (2)：写一个定位算法，该算法能够确定某条边，当该边容量增大时，最大流量也随之增加

    - 枚举每条边，并给该边容量增加$1$，执行可增载轨道算法寻找可增载轨道

    - 若存在可增载轨道，则最大流量将会增加，该边满足条件。

    - > (3)：(2)中所述的边是否一定存在？

    - 不一定，例如

    - ```mermaid
        graph LR
        s((s))
        v((v))
        t((t))
        s--1---v
        v--1---t
        ```

- ### 10

    - > 证明：在有正下界$b(e)$但无上界$c(e)(=+\infty)$的网络中，存在可行流的充要条件是对每一条边$e$，要么$e$在一个有向回路上，要么$e$在由$s$到$t$或由$t$到$s$的有向轨道上
        >
        > 注：当$e$在$t$到$s$的有向轨道上时，流量有可能为负值

    - 若存在可行流，添加一条边$(t,s)$，其流量$f((t,s))=Val(f)$。由于该流量方案可由若干个内部各边流量相同的回路叠加得到，故每条边都必须位于某个有向回路中。删去边$(t,s)$相当于每条边都在某个有向回路上或在$P(s,t)$或$P(t,s)$上

    - 若每条边都在某个有向回路或在$P(s,t)$或$P(t,s)$上，添加一条边$(t,s)$，则此时所有边都在某个有向回路上。为每个有向回路都赋予一个极大的流量并叠加后，显然可以做到每条边流量均超过$b(e)$。此时删去边$(t,s)$，即为可行流

- ### 13(1)

    - > 在图中，若存在可行流，请求出最大流与最小流；若不存在可行流，找出一个不含源与汇的顶点子集$V'$，需$V'$“冒出”流或者需$V'$“漏掉”流
        >
        > <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221130220843784.png" alt="image-20221130220843784" style="zoom:50%;" />

    - 构造伴随网络$N'$

    - <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221130222709130.png" alt="image-20221130222709130" style="zoom:25%;" />

    - 求最大流

    - <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221130222231177.png" alt="image-20221130222231177" style="zoom:25%;" />

    - 由于边$(s',c)$未满载，故令$c$漏掉$2$

    - 由于边$(b,t')$、$(d,t')$未满载，故令$b$冒出$3$、$d$冒出$4$

    - 得到原网络对应的可行流：

    - <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221130225417451.png" alt="image-20221130225417451" style="zoom:33%;" />
