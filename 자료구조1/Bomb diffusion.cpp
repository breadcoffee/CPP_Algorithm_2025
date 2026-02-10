#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int n, m, r, c;
int grid[105][105];

// 상하좌우 방향 벡터
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

bool InRange(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> r >> c;

    // 0초: 초기 폭탄 설치
    grid[r][c] = 1;

    // 1초부터 m초까지 시뮬레이션
    for (int t = 1; t <= m; t++) {
        // 이번 초에 폭발을 일으킬 기존 폭탄들의 위치를 미리 저장
        vector<pair<int, int>> current_bombs;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (grid[i][j] == 1) {
                    current_bombs.push_back({i, j});
                }
            }
        }

        // 폭발 거리 결정: 2^(t-1)
        int dist = pow(2, t - 1);

        // 모든 기존 폭탄이 동시에 폭발
        for (auto& pos : current_bombs) {
            int cur_r = pos.first;
            int cur_c = pos.second;

            for (int d = 0; d < 4; d++) {
                int nr = cur_r + dr[d] * dist;
                int nc = cur_c + dc[d] * dist;

                // 격자 범위 안이고 아직 폭탄이 없는 경우만 설치
                if (InRange(nr, nc) && grid[nr][nc] == 0) {
                    grid[nr][nc] = 1;
                }
            }
        }
    }

    // 최종 폭탄 개수 계산
    int bomb_count = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (grid[i][j] == 1) bomb_count++;
        }
    }

    cout << bomb_count << endl;

    return 0;
}