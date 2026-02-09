#include <iostream>
#include <vector>

using namespace std;

int n, m, k;
int grid[101][101];

// 1. 특정 열에 대해 폭발과 중력을 반복하는 함수
void ProcessColumn(int col) {
    while (true) {
        bool exploded = false;
        vector<bool> to_remove(n, false);

        // 연속된 구간 찾기
        for (int i = 0; i < n; i++) {
            if (grid[i][col] == 0) continue;
            int j = i;
            while (j < n && grid[j][col] == grid[i][col]) {
                j++;
            }

            if (j - i >= m) {
                for (int row = i; row < j; row++) to_remove[row] = true;
                exploded = true;
            }
            i = j - 1;
        }

        if (!exploded) break;

        // 중력 적용: 살아남은 폭탄을 아래로 밀기
        vector<int> temp;
        for (int i = n - 1; i >= 0; i--) {
            if (grid[i][col] != 0 && !to_remove[i]) {
                temp.push_back(grid[i][col]);
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            int idx = n - 1 - i;
            if (idx < (int)temp.size()) grid[i][col] = temp[idx];
            else grid[i][col] = 0;
        }
    }
}

// 2. 전체 격자의 모든 열에 대해 폭발 프로세스 실행
void ExplodeAllColumns() {
    for (int j = 0; j < n; j++) {
        ProcessColumn(j);
    }
}

// 3. 시계방향 90도 회전 및 중력 적용
void RotateAndGravity() {
    int next_grid[101][101] = {0};

    // 90도 회전 로직: (i, j) -> (j, n - 1 - i)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            next_grid[j][n - 1 - i] = grid[i][j];
        }
    }

    // 회전 후 중력 적용 (공중에 뜬 폭탄 아래로)
    for (int j = 0; j < n; j++) {
        vector<int> temp;
        for (int i = n - 1; i >= 0; i--) {
            if (next_grid[i][j] != 0) temp.push_back(next_grid[i][j]);
        }
        for (int i = n - 1; i >= 0; i--) {
            int idx = n - 1 - i;
            if (idx < (int)temp.size()) grid[i][j] = temp[idx];
            else grid[i][j] = 0;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> grid[i][j];
    }

    // K번의 주기 반복
    for (int i = 0; i < k; i++) {
        ExplodeAllColumns();
        RotateAndGravity();
    }
    
    // 마지막 회전 이후에도 터질 폭탄이 있다면 처리
    ExplodeAllColumns();

    // 남은 폭탄 개수 세기
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] != 0) count++;
        }
    }

    cout << count << endl;

    return 0;
}