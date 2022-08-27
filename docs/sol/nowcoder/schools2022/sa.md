### J:[Jellyfish and its dream](https://ac.nowcoder.com/acm/contest/38727/J)


#### z3475

##### 标签

环

##### 题意

给定长度为$n$,0下标开始的数列$\{a_i\},a_i\in[0,2]$，每次可以选择$i$满足$(a_i+1) \mod 3=a_{i+1 \mod 3}$使$a_i\leftarrow (a_i+1) \mod 3$。求能否使$\{a_i\}$变成全部元素相同的数列。

##### 思路

将数列延伸一倍拆环建立$\{b_i\}$，发现其一段区间$[l,r]$能变成相同的数$c$时$b_r=c$。如果使$l$最小，$> r$的所有元素都不会影响$l$的值。所以可以定义$s[i]$为以$i$为$r$的最小$l$。初始化所有$s[i]=i$，当且仅当$j<i,b[j]=b[i]\land (b[j]+1)\mod 3 = b[i],s[i]=s[j]$，又因为区间连续，所以不断将$j=s[i]-1$即可。

时间复杂度$O(n)$，~~自证不难~~。

##### 代码

??? note "参考代码"
    ```cpp
    --8<-- "docs/sol/code/nowcoder/schools2022_sa_J.cpp"
    ```

### K:[Killer Sajin's Matrix](https://ac.nowcoder.com/acm/contest/38727/K)


##### 标签


##### 题意


##### 思路


##### 代码
