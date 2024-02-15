import heapq

def find(x):
    if parent[x] != x:
        parent[x] = find(parent[x])
    return parent[x]

def union(x, y):
    parent[find(x)] = find(y)

L = int(input())
parent = list(range(L+1))
rank = [0] * (L+1)
res = []
cnt = 0

for _ in range(L):
    i, j, e = map(int, input().split())
    if e == 1:
        union(i, j)
    else:
        if find(i) == find(j):
            cnt += 1
            res.append(cnt)
            cnt = 0
        else:
            cnt += 1
res.append(cnt)

print(len(res))
for r in res:
    print(r)
