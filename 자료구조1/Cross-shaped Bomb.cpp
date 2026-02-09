#include <iostream>
#include <vector>

using namespace std;

int n, m;
int grid[201][201];

// 격자 범위 내에 있는지 확인
bool InRange(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < n;
}

// 2차원 격자에 중력 적용
void ApplyGravity() {
    int temp[201][201] = {0};
    
    for (int j = 0; j < n; j++) {
        int next_row = n - 1;
        for (int i = n - 1; i >= 0; i--) {
            if (grid[i][j] != 0) {
                temp[next_row--][j] = grid[i][j];
            }
        }
    }
    
    // 결과를 다시 grid로 복사
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = temp[i][j];
        }
    }
}

// 특정 열 c에서 폭탄 터뜨리기
void Explode(int c) {
    int target_r = -1;
    
    // 1. 해당 열에서 가장 위에 있는 폭탄 찾기
    for (int i = 0; i < n; i++) {
        if (grid[i][c] != 0) {
            target_r = i;
            break;
        }
    }
    
    // 만약 해당 열에 폭탄이 없으면 종료
    if (target_r == -1) return;
    
    int dist = grid[target_r][c];
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    // 2. 십자 모양으로 폭발 (0으로 변경)
    // 중심점 포함을 위해 len=0부터 시작
    for (int d = 0; d < 4; d++) {
        for (int len = 0; len < dist; len++) {
            int nr = target_r + dr[d] * len;
            int nc = c + dc[d] * len;
            if (InRange(nr, nc)) {
                grid[nr][nc] = 0;
            }
        }
    }
    
    // 3. 중력 적용
    ApplyGravity();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    while (m--) {
        int target_col;
        cin >> target_col;
        // 1-based index를 0-based로 보정
        Explode(target_col - 1);
    }

    // 최종 결과 출력
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}