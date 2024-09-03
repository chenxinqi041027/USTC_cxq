## 一(4)：

  - 将群体中所有人抽象为图的顶点，构成$V(G)$
  - 定义$E(G):\{uv|u,v\in V(G)且u和v是朋友\}$，则朋友数即为各点度数
  - 若所有人的朋友数均不相同，即$deg(u),u=1,2,\cdots,n$互不相同
  - 由$deg(u)\leq n-1$知$\{deg(u)|u=1,\cdots,n\}=\{d|d=0,1,\cdots,n-1\}$
  - 不妨设$deg(u_1)=n-1,deg(u_2)=0$，$u_1\neq u_2$
  - 则$u_2$不与任何人为朋友，而$u_1$与所有人都为朋友，矛盾
  - 故必有两人朋友数一样多

## 一(5)：

  - 将$2n$个人抽象为图的顶点，构成$V(G)$
  - 定义$E(G):\{uv|u,v\in V(G)且u和v认识\}$，则有$deg(u)\geq n,u=1,2,\cdots n$
  - 必存在$u_1,u_2\in V(G)$使得$deg(u_1)+deg(u_2)\geq 2n$
  - 则在除$u_1$和$u_2$的$n-2$个顶点中，必存在至少两个顶点$v_1,v_2$分别同时与$u_1$和$u_2$相邻
  - 将四人按$u_1,v_1,u_2,v_2$排成一圈，可使每个人旁边都是他认识的人

## 一（8）：

  - 定义函数$s(n)=\begin{cases}1&,n为奇数\\0&,n为偶数\end{cases}$
  - 设$m=\left\lvert\{u|u\in V'且s(deg(u))=1\}\right\rvert$，即度数为奇数的点数
  - 则$s\left(\sum_{u\in V'}deg(u)\right)=s(m)$
  - 不妨设$E':\{uv|u,v\in V'且uv\in E(G)\}$，$E'':\{uv|u\in V(G)-V'且v\in V';v\in V(G)-V'且u\in V'\}$
  - 则$|E''|=k$
  - 而$|E''|+2|E'|=\sum_{u\in V'}deg(u)$
  - 故$s(k)=s(|E''|)=s\left(|E''|+2|E'|\right)=s\left(\sum_{u\in V'}deg(u)\right)=s(m)$
  - 原题得证

## 一（15）：

- 先将图$G$任意拆成两个子图$X:=(V(X),E(X))$和$Y:=(V(Y),E(Y))$，满足$V(G)=V(X)+V(Y)$且$V(X)\cap V(Y)=\emptyset$
- 其中$E(X)=\{uv|u,v\in V(X)且uv\in E(G)\}$，$E(Y)=\{uv|u,v\in V(Y)且uv\in E(G)\}$
- 定义生成子图$H:=(V(G),E(H))$，其中$E(H)=\{uv|u\in V(X),v\in V(Y)且uv\in E(G)\}$
- 则$H$显然为二分图
- 随后按如下规则进行操作：
    1. 若存在某点$u\in V(X)$满足$|\{uv|uv\in E(X)\}|>|\{uv|uv\in E(H)\}|$，即$d_H(u)<\frac{1}{2}d_G(u)$。则将点$u$移到$Y$中，即令$V(X)=V(X)-u$，$V(Y)=V(Y)+u$。
    2. 若存在某点$u\in V(Y)$满足$d_H(u)<\frac{1}{2}d_G(u)$，同理，将点$u$移到$X$中。
    3. 若不存在点满足上述条件，即$\forall u\in V(G)=V(H)$，都有$d_H(u)\geq d_G(u)/2$，结束操作，此时的图$H$即为题所求。
    4. 否则重复上述操作。
- 现证明上述操作的有穷性：
    - 不妨某次操作是将点$u$从$X$中移动到$Y$中
    - 则操作过后$E’(H)=E(H)-\{uv|uv\in E(H)\}+\{uv|uv\in E(X)\}$，有$|E'(X)|>|E(X)|$
    - 即每次操作都会使$|E(H)|$增加，而有限制$|E(H)|\leq |E(G)|$，故操作一定次数后一定会停止，并得到最终符合要求的图$H$

## 一（16）：

  - 对于$G$任意一条长度为$l$（$0\leq l<k$）的轨道$u_0e_1u_1\cdots e_lu_l$
  - 由于$deg(u_l)\geq\delta(G)\geq k>l-1$，故存在点$u_{l+1}\in V(G)$，其不在该轨道上且与$u_l$相邻，不妨记$e_{l+1}:{u_lu_{l+1}}$
  - 则存在长度为$l+1$的轨道$u_0e_1u_1\cdots e_lu_le_{l+1}u_{l+1}$
  - 由归纳法可得$G$内一定存在长度为$k$的轨道