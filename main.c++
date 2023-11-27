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

    int width = pieces[remainingItems].width;
    int height = pieces[remainingItems].height;

    // se a peça tiver dimensões diferentes em todos os lados
    if ((width > remainingWidth || height > remainingHeight) &&
        (width > remainingHeight || height > remainingWidth)){
        result = maximizeValue(pieces, remainingWidth, remainingHeight, remainingItems-1, memo);
    }

    //corta a peça e tenta cortar novamente com a mesma peça
    else{
        int finalRemainingHeight = remainingHeight;
        int finalRemainingWidth = remainingWidth;

        if(remainingWidth == width && remainingWidth != height){
            finalRemainingHeight -= height;

        } else if(remainingHeight == height && remainingHeight != width){
            finalRemainingWidth -= width;

        } else if(remainingWidth == height){
            finalRemainingHeight -= width;

        } else if (remainingHeight == width){
            finalRemainingWidth -= height;
        }

        result = max(maximizeValue(pieces, remainingWidth, remainingHeight, remainingItems - 1, memo), 
            pieces[remainingItems].price + maximizeValue(pieces, finalRemainingWidth, finalRemainingHeight, remainingItems, memo));

    }

    printf("%d ", result);
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