#include <iostream>
#include <vector>

using namespace std;

int n, m, curr_r, curr_c;
int grid[101][101];

// 주사위 면 정보 (초기 상태)
int u = 1, d = 6, f = 2, b = 5, l = 4, r = 3;

bool InRange(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

void Roll(char dir) {
    int next_r = curr_r, next_c = curr_c;
    
    if (dir == 'L') next_c--;
    else if (dir == 'R') next_c++;
    else if (dir == 'U') next_r--;
    else if (dir == 'D') next_r++;

    // 격자 밖으로 벗어나면 무시
    if (!InRange(next_r, next_c)) return;

    // 현재 위치 이동
    curr_r = next_r;
    curr_c = next_c;

    // 주사위 회전 로직
    int temp_u = u;
    if (dir == 'L') {
        u = r; r = d; d = l; l = temp_u;
    } else if (dir == 'R') {
        u = l; l = d; d = r; r = temp_u;
    } else if (dir == 'U') {
        u = f; f = d; d = b; b = temp_u;
    } else if (dir == 'D') {
        u = b; b = d; d = f; f = temp_u;
    }

    // 바닥면에 적힌 숫자를 격자판에 기록
    grid[curr_r][curr_c] = d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> curr_r >> curr_c;

    // 초기 위치에 바닥면 숫자 기록
    grid[curr_r][curr_c] = d;

    for (int i = 0; i < m; i++) {
        char move_dir;
        cin >> move_dir;
        Roll(move_dir);
    }

    // 격자판의 모든 숫자 합산
    long long total_sum = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            total_sum += grid[i][j];
        }
    }

    cout << total_sum << endl;

    return 0;
}