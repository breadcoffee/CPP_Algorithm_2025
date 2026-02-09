#include <iostream>
#include <vector>

using namespace std;

int n, m, k;
int grid[105][105];

// 특정 행(row)의 k열부터 k+m-1열까지 블럭이 있는지 확인하는 함수
bool HasObstacle(int row, int col_s, int col_e) {
    // 격자 범위를 벗어나면 장애물이 있는 것으로 간주(바닥 체크)
    if (row >= n) return true;
    
    for (int j = col_s; j <= col_e; j++) {
        if (grid[row][j] == 1) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // 1. 입력 받기
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    // 0-based index 변환
    int col_start = k - 1;
    int col_end = k + m - 2;

    // 2. 블럭이 멈출 행 찾기
    int target_row = 0;
    
    // 첫 번째 행은 항상 0이므로 i=1부터 아래로 내려가며 체크
    for (int i = 1; i < n; i++) {
        // i번째 행에 장애물이 있다면 i-1번째 행에 안착해야 함
        if (HasObstacle(i, col_start, col_end)) {
            target_row = i - 1;
            break;
        }
        // 마지막 바닥까지 도달한 경우
        if (i == n - 1) {
            target_row = n - 1;
        }
    }

    // 3. 찾은 위치에 블럭 표시
    for (int j = col_start; j <= col_end; j++) {
        grid[target_row][j] = 1;
    }

    // 4. 결과 출력
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}