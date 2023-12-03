#include <iostream>
#include <vector>
#include <algorithm>

int maxSum(int x, int y, std::vector<std::vector<int>> &dp){

    //value change
    if(x == 1 && y == 1 || dp[x][y] != 0){
        return dp[x][y];
    }
    //recursive part
    int i = 1;

    for (int divisions = x/2; divisions > 0; divisions--){
        dp[x][y] = std::max(dp[x][y], maxSum(x - i,  y, dp) + maxSum(i, y, dp)); 
        i++;
    }
    i = 1;

    for (int divisions = y/2; divisions > 0; divisions--){
        dp[x][y] = std::max(dp[x][y], maxSum(x, y - i, dp) + maxSum(x, i, dp)); 
        i++;
    }

}

int maximizeValue(int X, int Y, std::vector<std::vector<int>>& pieces, std::vector<std::vector<int>> & dp) {
    int size = pieces.size();

    for (int x = 1; x <= X; x++) {
        for (int y = 1; y <= Y; y++) {

            maxSum(x, y, dp);

            printf("(%d, %d): %d ",x, y, dp[x][y]);

        }
        printf("\n");
    }

    return dp[X][Y];
}

int main() {
    int X, Y, n, x, y, price;
    scanf("%d %d %d", &X, &Y, &n);

    std::vector<std::vector<int>> pieces(n, std::vector<int>(3));
    std::vector<std::vector<int>> dp(X + 1, std::vector<int>(Y + 1, 0));
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &x, &y, &price);
        dp[x][y] = price;
    }

    //forces X to be always larger
    if(X < Y){
        int a = Y;
        Y = X;
        X = a;
    }

    std::cout << maximizeValue(X, Y, pieces, dp) << std::endl;

    return 0;
}