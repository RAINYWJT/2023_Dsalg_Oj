#include <stdio.h>
#include <stdlib.h>

#define N 100000 // 定义一个常量 N，表示最大的方块数量
#define INF 2147483647 // 定义一个常量 INF，表示一个很大的整数

// 定义一个结构体类型 Block，表示一个方块的属性
typedef struct {
    int weight; // 方块的重量
    int stability; // 方块的稳定性，即方块能承受的最大重量
    int riskvalue; // 方块的风险值，即方块的重量和稳定性之差
} Block;

// 定义一个比较函数，用于对 Block 类型的数据进行排序
// 比较的依据是风险值，风险值小的排在前面
int compare(const void *a, const void *b) {
    Block *blockA = (Block *)a;
    Block *blockB = (Block *)b;
    return (blockA->riskvalue - blockB->riskvalue);
}

// 主函数
int main() {
    int n; // 输入的方块数量
    scanf("%d", &n); // 从标准输入读取方块数量
    Block blocks[N]; // 定义一个 Block 类型的数组，用于存储方块的信息
    int sum_weight = 0; // 定义一个变量，用于记录所有方块的重量之和
    for (int i = 0; i < n; i++) { // 遍历每个方块
        scanf("%d %d", &blocks[i].weight, &blocks[i].stability); // 从标准输入读取方块的重量和稳定性
        sum_weight += blocks[i].weight; // 累加方块的重量
    }
    int maxb = -INF; // 定义一个变量，用于记录最大的风险值
    for (int i = 0; i < n; i++) { // 遍历每个方块
        blocks[i].riskvalue = sum_weight - blocks[i].weight - blocks[i].stability; // 计算方块的风险值
    }

    qsort(blocks, n, sizeof(Block), compare); // 调用标准库函数 qsort 对方块数组进行排序
    
    for (int i = 0; i < n; i++) { // 遍历每个方块
        sum_weight -= blocks[i].weight; // 减去当前方块的重量
        maxb = (maxb > blocks[i].riskvalue) ? maxb : blocks[i].riskvalue; // 更新最大的风险值
        blocks[i].weight = INF; // 将当前方块的重量设为一个很大的数，表示已经移除
        blocks[i].stability = INF; // 将当前方块的稳定性设为一个很大的数，表示已经移除
        if (i+1 < n) { // 如果还有下一个方块
            blocks[i+1].riskvalue = sum_weight - blocks[i+1].weight - blocks[i+1].stability; // 重新计算下一个方块的风险值
        }
    }
    
    printf("%d\n", maxb); // 输出最大的风险值到标准输出
    return 0; // 返回 0，表示程序正常结束
}