# ch 2
## 笔记
## 习题
1. 给定n位，能表示少个二进制数？
$$2^n$$个
2. 英语字母表里，有26个字母，用多少位可以表示26个字母？用多少位可以表示大小写的26位字母？
只表示26个字母：
$$\left\lceil\log2 26\right\rceil=5$$
表示大小写：
$$\left\lceil\log2 52\right\rceil=6$$
3. a. 9
   b.112
4. 2^n 0~2^n-1
5. 
|number|1's complement|signed magnitude|2's complement|
|---|---|---|---|
|7|00111|00111|00111|
|6|00110|00110|00110|
|0|00000|00000|00000|
|-1|11110|10001|11111|

6. 32的原码10000
   -32的补码110000

8. a. 2^7-1,01111111,b. -2^7,10000000,c. 2^n-1-1,d. -2^n-1
9. log 2 6.02*10^23 向上取整
10. -6,90,……
11. ……
12. 正数，则为偶数，负数则为11+1=10，也为偶数
13. 符号位拓展1111_1010
14. ……
15. 除2，向下取整
16. ……
17. ……
18. ……
19. ……
20. ……
21. 得出的符号位与现今的符号位不用同
22. ……
23. 得出的结果太大
24. ……
25. 因为最大最小的运算不会超过范围
26. 7，63，127
27. 溢出，负数
28. 都为1
29. 
|X|Y|result|
|---|---|---|
|0|0|0|
|0|1|0|
|1|0|0|
|1|1|1|

30. 01010111
    11010111
    01010111
31. 有一个是1
32.  ……
33.  ……
34.  ……
35.  用于计算或者存储值
36.  按位与0000_0010，判断结果是否为0
    按位与0010_0010，判断结果是否为0
    按位与1111_1111,判断结果是否为1
    按位与1111_1111,判断结果是否为1
    按位与1111_1100,之后按位与0000_0100，判断2是否有效
37. 二进制补码表示范围-8~7；与，或，非，或，异或第一步：通过AND将n和m的左侧第一位bit提取出来，在通过XOR比较两者是否相同，如果不相同则表示正数和负数相加，此时肯定不会溢出。
如果 (n AND 1000) XOR (m AND 1000) = 1000则返回0000表示不会溢出，否则继续判断
第二步：左侧第一位bit相同，如果两数相加没有溢出，则s的左侧第一位bit应该和n、m相同，如果相同则表示没有溢出，如果不同，则表示溢出。
如果(n AND 1000) XOR (s AND 1000) = 1000则返回0000表示没有溢出
如果(n AND 1000) XOR (s AND 1000) = 0000则返回1000表示溢出
38. **第一步 (n OR m) AND 1000，如果为0000则代表肯定没有溢出直接返回，第二步 ((n OR m) AND 1000) XOR (s AND 1000)将结果直接返回**
39. 010000000111……，11000010110111010111……
40.  2，-17……
41.  011111110111111111111111111111,11111110111111……
42.  ASCII码
43.  ……
44.  ……
45.  D1AF
46. ^
47. ^
48. ^
49. ^
50. ^
51. ^
52. ^
53. ^
54. ^
55. 4^3-1,4^n-1,……4^m-1
56. ！！！**重点**
    11100101
    1符号位，1100阶码，101尾数
    -2^(12-7)*1.101=-110100=-52

    