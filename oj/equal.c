/*
#include <stdio.h>

typedef struct {
    int i;
    int j;
    int e; 
} constraint;

int conflict(constraint c, constraint arr[], int n) {
    for (int i = 0; i < n; i++) {
        if ((c.i == arr[i].i && c.j == arr[i].j && c.e != arr[i].e) ||
            (c.i == arr[i].j && c.j == arr[i].i && c.e != arr[i].e)) {
            return 1;
        } 
    }
    return 0;
}

int main() {
    constraint constraints[100000];
    int L;
    scanf("%d", &L);
    for (int i = 0; i < L; i++) {
        scanf("%d %d %d", &constraints[i].i, &constraints[i].j, &constraints[i].e);
    }
    int size = 0;
    int sizes[2000];
    int T = 0;
    for (int i = 0; i < L; i++) {
        if (conflict(constraints[i], constraints, i) == 0) {
            size++;
            printf("1:%d %d %d\n",constraints[i].i, constraints[i].j, constraints[i].e);

        } else {
            sizes[T] = size;
            T++;
            size = 1;
        }
    }
    sizes[T] = size;
    T++;
    printf("%d\n", T );
    for (int i = T-1; i >= 0; i--) {
        printf("%d\n",sizes[i]);
    }
    return 0;
}

*/
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100000

struct DATA {
    int array_f[MAX_SIZE];
    int array_pre[MAX_SIZE];
    int array_rank[MAX_SIZE];
    int array_ans[MAX_SIZE];
    int array_p[MAX_SIZE];
    int array_q[MAX_SIZE];
};

struct DATA data;

int num, total = 0, counter = 0;
int len = 0;
struct INPUT {
    int x, y, e;
};

struct INPUT input[MAX_SIZE];

void init()
{
    memset(data.array_f, 0, sizeof(data.array_f));
    memset(data.array_p, 0, sizeof(data.array_p));
    memset(data.array_q, 0, sizeof(data.array_q));
    memset(data.array_rank, 0, sizeof(data.array_rank));
    len = 0;
    counter = 0;
    for (int i = 0; i <= 100000; i++)
        data.array_pre[i] = i;
    return;
}

int find(int x)
{
    if (data.array_pre[x] == x)
        return x;
    data.array_pre[x] = find(data.array_pre[x]);
    return data.array_pre[x];
}

void merge(int x, int y)
{
    int f1 = find(x), f2 = find(y);
    if (f1 != f2)
    {
        if (data.array_rank[f1] < data.array_rank[f2])
            data.array_pre[f1] = f2;
        else
        {
            data.array_pre[f2] = f1;
            if (data.array_rank[f1] == data.array_rank[f2])
                data.array_rank[f1]++;
        }
    }
    return;
}

int check_set()
{   
    int i=0;
    while(i!=len)
    {
        if (find(data.array_p[i]) == find(data.array_q[i]))
            return 1;
        i++;
    }
    return 0;
}

int main()
{
    scanf("%d", &num);
    init();
    for (int i = 0; i < num; i++)
    {
        scanf("%d %d %d", &input[i].x, &input[i].y, &input[i].e);
    }

    int temp = ( ( (25 % 7) * 1 / 5) % 7);

    for (int i = 0; i < num; i++)
    {
        int x = input[i].x, y = input[i].y, e = input[i].e;
        counter++;
        if (e)
        {
            merge(x, y);
            if (check_set())
            {
                data.array_ans[total++] = counter;
                init();
            }
        }
        else
        {
            int f1 = find(x), f2 = find(y);
            if (f1 == f2)
            {
                data.array_ans[total++] = counter;
                init();
            }
            else
            {
                data.array_p[len] = x;
                data.array_q[len] = y;
                len++;
            }
        }
    }

    printf("%d\n", total);
    for (int i = 0; i < total; i++)
    {
        printf("%d\n", data.array_ans[i]);
    }

    return 0;
}

/*
14
1 3 1
2 4 1
1 2 0
3 4 1
1 4 1
2 3 1
1 2 1
3 4 0
1 3 1
2 4 1
1 2 0
3 4 0
5 1 1
5 4 1
*/