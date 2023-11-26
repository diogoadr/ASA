#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Piece {
    int width, height, price;
};

int maximizeValue(const vector<Piece>& pieces, int remainingWidth, int remainingHeight, int remainingItems ,vector<vector<vector<int>>>& memo) {

    if (memo[remainingItems][remainingWidth][remainingHeight] != -1) {
        return memo[remainingItems][remainingWidth][remainingHeight];
    }

    int result = 0;
    
    if (remainingItems == 0 || remainingWidth == 0 || remainingHeight == 0) {
        result = 0;
    }

    // se a peça tiver dimensões maiores que a peça restante
    //lógica: a peça não pode caber nem na horizontal, nem na vertical
    else if ((pieces[remainingItems].width > remainingWidth && pieces[remainingItems].height > remainingHeight) ||
        (pieces[remainingItems].width > remainingHeight || pieces[remainingItems].height > remainingWidth)){
        result = maximizeValue(pieces, remainingWidth, remainingHeight, remainingItems-1, memo);
    }

    // caso não seja preciso rodar a peça
    else if (pieces[remainingItems].width <= remainingWidth || pieces[remainingItems].height <= remainingHeight) {
            result = max(maximizeValue(pieces, remainingWidth, remainingHeight, remainingItems-1, memo), 
                pieces[remainingItems].price + maximizeValue(pieces, remainingWidth - pieces[remainingItems].width, remainingHeight, remainingItems, memo));
        }

    // caso seja preciso rodar a peça
    else{
        result = max(maximizeValue(pieces, remainingWidth, remainingHeight, remainingItems, memo), 
            pieces[remainingItems].price + maximizeValue(pieces, remainingWidth, remainingHeight - pieces[remainingItems].width, remainingItems, memo));

    }

    memo[remainingItems][remainingWidth][remainingHeight] = result;
    return result;
}

int main() {
    int width, height;
    cin >> width >> height;

    int items;
    cin >> items;

    vector<Piece> pieces(items + 1);
    for (int i = 1; i <= items; ++i) {
        cin >> pieces[i].width >> pieces[i].height >> pieces[i].price;
    }

    vector<vector<vector<int>>> memo(items + 1, vector<vector<int>>(width + 1, vector<int>(height + 1, -1)));

    cout << maximizeValue(pieces, width, height, items, memo) << endl;

    return 0;
}