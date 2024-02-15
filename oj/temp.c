#include <stdio.h>
#include <string.h>

#define N 1000004

int f[N];
int pre[N];
int ans[N];
int n, sum = 0, cnt = 0;
int p[N];
int q[N];
int dlen = 0;

void reset()
{
    memset(f, 0, sizeof(f));
    memset(p, 0, sizeof(p));
    memset(q, 0, sizeof(q));
    dlen = 0;
    cnt = 0;
    for (int i = 0; i <= 100000; i++)
        pre[i] = i;
}

int find(int x)
{
    if (pre[x] == x)
        return x;
    pre[x] = find(pre[x]);
    return pre[x];
}

void merge(int x, int y)
{
    int fx = find(x), fy = find(y);
    if (fx != fy)
        pre[fx] = fy;
    return;
}

int judge()
{
    for (int i = 0; i < dlen; i++)
    {
        if (find(p[i]) == find(q[i]))
            return 1;
    }
    return 0;
}

int main()
{
    scanf("%d", &n);
    reset();

    for (int i = 0; i < n; i++)
    {
        int x, y, e;
        scanf("%d %d %d", &x, &y, &e);
        cnt++;
        if (e)
        {
            merge(x, y);
            if (judge())
            {
                ans[sum++] = cnt;
                reset();
            }
        }
        else
        {
            int fx = find(x), fy = find(y);
            if (fx == fy)
            {
                ans[sum++] = cnt;
                reset();
            }
            else
            {
                p[dlen] = x;
                q[dlen] = y;
                dlen++;
            }
        }
    }

    printf("%d\n", sum);
    for (int i = 0; i < sum; i++)
    {
        printf("%d\n", ans[i]);
    }

    return 0;
}
