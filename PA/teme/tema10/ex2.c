#include <stdio.h>

#define MAX_CAPACITY 15
#define ITEMS_NUMBER 5

// Function to return the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve the 0/1 Knapsack problem
int knapsack(int weights[], int values[]) {
    int dp[ITEMS_NUMBER + 1][MAX_CAPACITY + 1];

    for (int i = 0; i <= ITEMS_NUMBER; i++) {
        for (int w = 0; w <= MAX_CAPACITY; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (weights[i - 1] <= w) {
                dp[i][w] = max(
                    values[i - 1] + dp[i - 1][w - weights[i - 1]],
                    dp[i - 1][w]
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[ITEMS_NUMBER][MAX_CAPACITY];
}

int main() {
    // Example values and weights for 5 items
    int values[ITEMS_NUMBER]  = {1, 2, 2, 4, 10};
    int weights[ITEMS_NUMBER] = {1,  1,  2,  12,  4};

    int maxValue = knapsack(weights, values);
    printf("Maximum value that can be carried: %d\n", maxValue);

    return 0;
}
