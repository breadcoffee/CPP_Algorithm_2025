/*
n×n크기의 이차원 영역에 파묻힌 금을 손해를 보지 않는 선에서 최대한 많이 채굴하려고 합니다. 
채굴은 반드시 [그림 1, 2]과 같은 마름모 모양으로 단 한 번 할 수 있으며, 
마름모 모양을 지키는 한 [그림 3]와 같이 이차원 영역을 벗어난 채굴도 가능하지만 이차원 영역 밖에 금은 존재하지 않습니다.

여기서 마름모 모양이란 특정 중심점을 기준으로 K번 이내로 상하좌우의 인접한 곳으로 이동하는 걸 반복했을 때 
갈 수 있는 모든 영역이 색칠되어 있는 모양을 의미합니다. [그림 1]은 K가 1일때의 마름모 모양이고, 
[그림 2]는 K가 2일때 마름모 모양입니다. K가 0인 경우는 지점 한 곳에서만 채굴하는 것을 의미하며 이 역시 올바른 마름모 모양이라 할 수 있습니다. 
올바르지 않은 마름모 모양을 이용해서는 채굴이 불가능합니다.

이 때 채굴에 드는 비용은 마름모 안의 격자 갯수만큼 들어가며, 이는 K∗K+(K+1)∗(K+1)로 계산될 수 있습니다. 
금 한 개의 가격이 m일 때, 손해를 보지 않으면서 채굴할 수 있는 가장 많은 금의 개수를 출력하는 코드를 작성해보세요. 
단 한 개의 격자 안에는 최대 한 개의 금만 존재합니다

출력 형식
손해를 보지 않으면서 채굴할 수 있는 가장 많은 금의 개수를 출력해줍니다.

입출력 예제
예제1
입력:

5 5
0 0 0 0 0
0 1 0 0 0
0 0 1 0 1
0 0 0 0 0
0 0 0 1 0
출력:

3
*/

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