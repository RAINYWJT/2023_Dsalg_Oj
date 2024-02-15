#include <stdio.h>
#include <stdlib.h>

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int check(int* S, int n, int k, int mid) {
    int cnt = 0, prev = S[0];
    for (int i = 1; i < n; i++) {
        while (i < n && S[i] - prev < mid) {
            cnt++;
            i++;
        }
        if (i < n) {
            prev = S[i];
        }
    }
    return cnt <= k;
}

int binary_search(int* S, int n, int k) {
    int left = 0, right = S[n-1] - S[0] + 1;
    while (right - left > 1) {
        int mid = left + (right - left) / 2;
        if (check(S, n, k, mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return left;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int S[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &S[i]);
    }
    qsort(S, n, sizeof(int), cmpfunc);
    int max_min_diff = binary_search(S, n, k);
    printf("%d\n", max_min_diff);
    
    return 0;
}
