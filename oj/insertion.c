#include <stdio.h>

#define MOD 998244353  

long long factorial(int n) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result = (result * i) % MOD;  
    }
    return result;
}

long long calculate_permutations(int n, int k) {
    int m = n - (k - 1);
    long long result = factorial(k);  
    result = (result * (m * n - m - n + 2)) % MOD;  
    return result;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    if(k>n){
        k=n;
    }
    long long permutations = calculate_permutations(n, k);
    printf("%lld\n", permutations);
    return 0;
}










