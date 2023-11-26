#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Piece {
    int width, height, price;
};

int maximizeValue(int items, int totalArea, vector<Piece>& pieces, vector<vector<int>>& memo) {
    if(memo[items][totalArea] != -1){
        return memo[items][totalArea];
    }

    //caso base -> não há mais items || já não existe mais área
    else if(items == 0 || totalArea == 0){
        return 0;
    }

    else if (pieces[])
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