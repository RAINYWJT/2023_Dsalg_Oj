#include <stdio.h>
#include <string.h>

#define MAX 500  // 定义最大长度为500

int dp[MAX][MAX];  // dp数组用于存储动态规划的结果
char s[MAX];  // 字符数组s用于存储输入的字符串

// max函数用于返回两个数中的最大值
int max(int a, int b) {
    return a > b ? a : b;
}

// solve函数用于求解从l到r的最大匹配长度
int solve(int l, int r) {
    if (l > r) return 0;  // 如果l大于r，返回0
    if (dp[l][r] != -1) return dp[l][r];  // 如果dp[l][r]已经计算过，直接返回结果
    int ans = 0;
    for (int i = l + 1; i <= r; i++) {
        // 如果s[l]和s[i]是匹配的括号
        if ((s[l] == '(' && s[i] == ')') || (s[l] == '[' && s[i] == ']')) {
            // 更新ans为当前的ans和solve(l + 1, i - 1) + 2 + solve(i + 1, r)中的最大值
            ans = max(ans, solve(l + 1, i - 1) + 2 + solve(i + 1, r));
        }
    }
    // 更新ans为当前的ans和solve(l + 1, r)中的最大值
    ans = max(ans, solve(l + 1, r));
    dp[l][r] = ans;  // 将结果存入dp数组
    return ans;  // 返回结果
}

int main() {
    scanf("%s", s);  // 读入字符串
    memset(dp, -1, sizeof(dp));  // 初始化dp数组为-1
    printf("%d\n", solve(0, strlen(s) - 1));  // 输出从0到字符串长度-1的最大匹配长度
    return 0;
}