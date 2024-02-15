#include <stdio.h>
#define MAX_SIZE 1000000

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void push(Stack* stack, int value) {
    stack->data[stack->top++] = value;
}

int pop(Stack* stack) {
    return stack->data[--stack->top];
}

int main() {
    int n;
    scanf("%d", &n);
    int A[n];
    int B[n];
    Stack stack;
    stack.top = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < n; i++) {
        while (stack.top > 0 && A[stack.data[stack.top - 1]] < A[i]) {
            int index = pop(&stack);
            B[index] = i + 1;
        }
        push(&stack, i);
    }
    while (stack.top > 0) {
        int index = pop(&stack);
        B[index] = 0;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", B[i]);
    }
    
    return 0;
}
