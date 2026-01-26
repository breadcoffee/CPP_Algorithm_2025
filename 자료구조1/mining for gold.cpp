#include <iostream>
#include <algorithm>
#include <cstdlib>

#define MAX_NUM 20

using namespace std;

int n, m;
int grid[MAX_NUM][MAX_NUM];

// 주어진 k에 대하여 마름모의 넓이를 반환합니다.
int GetArea(int k) {
    return k * k + (k+1) * (k+1); 
}

// 주어진 k에 대하여 채굴 가능한 금의 개수를 반환합니다.
int GetNumOfGold(int row, int col, int k) {
    int num_of_gold = 0;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(abs(row - i) + abs(col - j) <= k)
                num_of_gold += grid[i][j];

    return num_of_gold;
}

int main() {
    int max_gold = 0;

    // 입력:
    cin >> n >> m;
    for(int row = 0; row < n; row++)
        for(int col = 0; col < n; col++)
            cin >> grid[row][col];

    // 격자의 각 위치가 마름모의 중앙일 때 채굴 가능한 금의 개수를 구합니다.
    for(int row = 0; row < n; row++) {
        for(int col = 0; col < n; col++) {
            for(int k = 0; k <= 2 * (n-1); k++) {
                int num_of_gold = GetNumOfGold(row, col, k);

                // 손해를 보지 않으면서 채굴할 수 있는 최대 금의 개수를 저장합니다.
                if(num_of_gold * m >= GetArea(k))
                    max_gold = max(max_gold, num_of_gold);
            }
        }
    }

    cout << max_gold;
}