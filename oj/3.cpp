#include <bits/stdc++.h>
using namespace std;

const int N=1e6+4;  // 定义常量 N 的值为 1000004
bool f[N];          // 布尔数组，用于跟踪访问过的节点
int pre[N], ans[N], n, sum=0, cnt=0, p[N], q[N], dlen=0;

// 重置各种数组和计数器的函数
void reset()
{
    memset(f, false, sizeof(f));   // 将 f 数组初始化为 false
    memset(p, 0, sizeof(p));       // 将 p 数组初始化为零
    memset(q, 0, sizeof(q));       // 将 q 数组初始化为零
    dlen = 0;                       // 将 dlen 重置为零
    cnt = 0;                        // 将 cnt 重置为零
    for(int i = 0; i <= 1e5; i++)   // 遍历 pre 数组，并将每个元素初始化为其索引
        pre[i] = i;
}

// 使用路径压缩查找集合的根的函数
int find(int x)
{
    if(pre[x] == x) return x;       // 如果 x 是根，返回 x
    pre[x] = find(pre[x]);          // 进行路径压缩
    return pre[x];
}

// 合并两个集合的函数
void merge(int x, int y)
{
    int fx = find(x), fy = find(y); // 找到包含 x 和 y 的集合的根
    if(fx != fy) pre[fx] = fy;       // 如果根不同，合并集合
    return;
}

// 检查当前边集中是否存在环的函数
bool judge()
{
    for(int i = 0; i < dlen; i++)
    {
        if(find(p[i]) == find(q[i])) return true;  // 如果任何边的端点在同一个集合中，存在环
    }
    return false;  // 没有找到环
}

int main()
{
    cin >> n;      // 输入边的数量
    reset();       // 重置数组和计数器
    
    for(int i = 0; i < n; i++)
    {
        int x, y, e;
        cin >> x >> y >> e;   // 输入当前边的端点和类型
        cnt++;
        if(e)
        {
            merge(x, y);        // 如果边的类型为 true，则合并包含 x 和 y 的集合
            if(judge())         // 检查合并后是否存在环
            {
                ans[sum++] = cnt;  // 如果存在环，记录当前边的编号并重置
                reset();
            }
        }
        else
        {
            int fx = find(x), fy = find(y);
            if(fx == fy)
            {
                ans[sum++] = cnt;  // 如果 x 和 y 已经在同一个集合中，记录当前边的编号并重置
                reset();
            }
            else
            {
                p[dlen] = x;       // 记录当前边的端点
                q[dlen] = y;
                dlen++;
            }
        }
    }
    
    cout << sum << endl;      // 输出检测到环的边的数量
    for(int i = 0; i < sum; i++)
    {
        cout << ans[i] << endl;  // 输出检测到环的边的编号
    }
    
    return 0;
}


//999983

/*
13
2 2 1
2 2 1
1 1 1
3 1 1
1 3 1
1 3 0
1 1 0
1 2 0
2 1 1
2 1 1
1 2 0
1 1 0
10 10 0
*/

/*
4
1 2 0
2 3 1
3 1 1
1 1 0
*/