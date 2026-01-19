/*
n * m크기의 이차원 영역의 각 위치에 정수 값이 하나씩 적혀있습니다. 
이 영역 안에서 서로 겹치지 않는 두 직사각형을 적절하게 잡아, 
두 직사각형 안에 적힌 숫자들의 총 합을 최대로 하는 프로그램을 작성해보세요. 
이때, 각 직사각형의 변들은 격자 판에 평행해야 하고 꼭 2개의 직사각형을 골라야만 하며, 두 직사각형의 경계는 서로 닿아도 됩니다.

입력 형식
첫 번째 줄에는 n과 m이 공백을 사이에 두고 주어지고, 두 번째 줄부터 (n+1)번째 줄까지는 각 행의 숫자가 공백을 사이에 두고 주어집니다.

2 ≤ n, m ≤ 5

-1,000 ≤ 정수 값 ≤ 1,000

출력 형식
겹치지 않게 두 직사각형을 잡았을 때, 얻을 수 있는 최대 합을 출력해주세요.

입출력 예제
예제1
입력:

2 2
-1 -2
-3 -4
출력:

-3

예제4
입력:

4 5
6 5 4 -3 1
3 -4 -4 14 1
6 1 -3 15 -5
3 -5 1 16 3
출력:

63
*/
#include <iostream>
#include <algorithm>
#include <climits>

#define MAX_NUM 5

using namespace std;

int n, m;
int grid[MAX_NUM][MAX_NUM];
int board[MAX_NUM][MAX_NUM];

void ClearBoard() {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            board[i][j] = 0;
}

void Draw(int x1, int y1, int x2, int y2) {
    for(int i = x1; i <= x2; i++)
        for(int j = y1; j <= y2; j++)
            board[i][j]++;
}

bool CheckBoard() {
    // 동일한 칸을 2개의 직사각형이 모두 포함한다면
    // 겹치게 됩니다.
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(board[i][j] >= 2)
                return true;
    return false;
}

// (x1, y1), (x2, y2) 그리고
// (x3, y3), (x4, y4) 로 이루어져있는
// 두 직사각형이 겹치는지 확인하는 함수
bool Overlapped(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    ClearBoard();
    Draw(x1, y1, x2, y2);
    Draw(x3, y3, x4, y4);
    return CheckBoard();
}

int RectSum(int x1, int y1, int x2, int y2) {
    int sum_of_nums = 0;
    for(int i = x1; i <= x2; i++)
        for(int j = y1; j <= y2; j++)
            sum_of_nums += grid[i][j];
    
    return sum_of_nums;
}

// 첫 번째 직사각형이 (x1, y1), (x2, y2)를 양쪽 꼭지점으로 할 때
// 두 번째 직사각형을 겹치지 않게 잘 잡아
// 최대 합을 반환하는 함수
int FindMaxSum(int x1, int y1, int x2, int y2) {
    int max_sum = INT_MIN;
    
    // (i, j), (k, l)을 양쪽 꼭지점으로 하는
    // 두 번째 직사각형을 정하여
    // 겹치지 않았을 때 중
    // 최댓값을 찾아 반환합니다.
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            for(int k = i; k < n; k++)
                for(int l = j; l < m; l++) {
                    if(!Overlapped(x1, y1, x2, y2, i, j, k, l))
                        max_sum = max(max_sum, 
                                      RectSum(x1, y1, x2, y2) +
                                      RectSum(i, j, k, l));
                }
    
    return max_sum;
}

// 두 직사각형을 잘 잡았을 때의 최대 합을 반환하는 함수
int FindMaxSum() {
    int max_sum = INT_MIN;
    
	// (i, j), (k, l)을 양쪽 꼭지점으로 하는
    // 첫 번째 직사각형을 정하여
    // 그 중 최댓값을 찾아 반환합니다.
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            for(int k = i; k < n; k++)
                for(int l = j; l < m; l++)
                    max_sum = max(max_sum,
                                  FindMaxSum(i, j, k, l));
    return max_sum;
}

int main() {
	cin >> n >> m;
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			cin >> grid[i][j];
	
	int ans = FindMaxSum();
	cout << ans;
	
	return 0;
}