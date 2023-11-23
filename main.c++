#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Piece {
    int width, height, price;
};

int maximizeValue(int X, int Y, vector<Piece>& pieces) {
    int n = pieces.size();
    vector<vector<int>> dp(X + 1, vector<int>(Y + 1, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= X; ++j) {
            for (int k = 0; k <= Y; ++k) {
                // Tenta incluir a peça atual o máximo de vezes possível
                for (int count = 0; count * pieces[i].width <= j && count * pieces[i].height <= k; ++count) {
                    dp[j][k] = max(dp[j][k], dp[j - count * pieces[i].width][k - count * pieces[i].height] + count * pieces[i].price);
                }
            }
        }
    }

    return dp[X][Y];
}

int main() {
    int X, Y;
    cin >> X >> Y;

    int n;
    cin >> n;

    vector<Piece> pieces(n);
    for (int i = 0; i < n; ++i) {
        cin >> pieces[i].width >> pieces[i].height >> pieces[i].price;
    }

    int result = maximizeValue(X, Y, pieces);

    cout << result << endl;

    return 0;
}