#include <iostream>
#include <vector>
#include <algorithm>

int maximizeValue(int X, int Y, std::vector<std::vector<int>>& pieces, std::vector<std::vector<int>>& dp) {

    for (int x = 1; x <= X; x++) {
        // only doing all of the matrix (y<=x), the rest is transposed because it's the same
        for (int y = 1; y <= Y && y <= x; y++) {

            int i = 1;
            int changeFlag;

            //all the possible combinations of cuts horizontally in (x, y): 
            for (int divisions = x/2; divisions > 0; divisions--){

                changeFlag = dp[x][y];
                dp[x][y] = std::max(dp[x][y], dp[x - i][y] + dp[i][y]);

                //transposing results (only changes if needed, time saving)
                if(X >= y && Y >= x && changeFlag != dp[x][y]){
                    dp[y][x] = dp[x][y];
                }
                i++;
            }

            i = 1;

            //all the possible combinations of cuts vertically in (x, y)
            for (int divisions = y/2; divisions > 0; divisions--){
                
                changeFlag = dp[x][y];
                dp[x][y] = std::max(dp[x][y], dp[x][y - i] + dp[x][i]);

                //transposing results (only changes if needed, time saving)
                if(X >= y && Y >= x && changeFlag != dp[x][y]){
                    dp[y][x] = dp[x][y];
                }


                i++;

            }

        }
    }

    if(dp[X][Y] == -1){
        return 0;
    }

    return dp[X][Y];
}

//swaps a and b
void swap(int &a, int &b){
    int c = a;
    a = b;
    b = c;
}

int main() {
    int X, Y, n, x, y, price;
    scanf("%d %d %d", &X, &Y, &n);

    //X needs to be always bigger than Y
    if(X < Y){
        swap(X, Y);
    }

    std::vector<std::vector<int>> dp(X + 1, std::vector<int>(Y + 1, 0));
    std::vector<std::vector<int>> pieces(n, std::vector<int>(3));
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &x, &y, &price);

        //X needs to be always bigger than Y
        if(x < y){
            swap(x, y);
        }

        if(price > 0 && X >= x && Y >= y){
            if(dp[x][y] < price){
                dp[x][y] = price;

                if(X >= y && Y >= x){
                    dp[y][x] = price;
                }
            }
        }
        
    }

    std::cout << maximizeValue(X, Y, pieces, dp) << std::endl;

    return 0;

}