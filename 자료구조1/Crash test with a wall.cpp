#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Marble {
    int x, y, dir;
    bool active;
};

// 방향 매핑: U(0), D(1), R(2), L(3)
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, 1, -1};
int opp[] = {1, 0, 3, 2}; // 반대 방향 색인

int charToDir(char d) {
    if (d == 'U') return 0;
    if (d == 'D') return 1;
    if (d == 'R') return 2;
    return 3;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<Marble> marbles(m);
    for (int i = 0; i < m; i++) {
        int r, c;
        char d;
        cin >> r >> c >> d;
        marbles[i] = {r, c, charToDir(d), true};
    }

    // N이 50일 때 2*N 시간 정도면 모든 충돌 상황이 종료됩니다.
    // 넉넉하게 200초를 설정합니다.
    for (int t = 0; t < 2 * n; t++) {
        int grid_count[55][55] = {0};

        // 1. 구슬 이동
        for (int i = 0; i < m; i++) {
            if (!marbles[i].active) continue;

            int nx = marbles[i].x + dx[marbles[i].dir];
            int ny = marbles[i].y + dy[marbles[i].dir];

            // 벽에 부딪히는 경우: 이동하지 않고 방향만 바꿈
            if (nx < 1 || nx > n || ny < 1 || ny > n) {
                marbles[i].dir = opp[marbles[i].dir];
            } else {
                // 벽이 아니면 이동
                marbles[i].x = nx;
                marbles[i].y = ny;
            }
            grid_count[marbles[i].x][marbles[i].y]++;
        }

        // 2. 충돌 체크 및 제거
        for (int i = 0; i < m; i++) {
            if (marbles[i].active && grid_count[marbles[i].x][marbles[i].y] > 1) {
                // 해당 위치의 모든 구슬을 비활성화해야 하므로 다시 체크
                int tx = marbles[i].x;
                int ty = marbles[i].y;
                for (int j = 0; j < m; j++) {
                    if (marbles[j].active && marbles[j].x == tx && marbles[j].y == ty) {
                        marbles[j].active = false;
                    }
                }
            }
        }
    }

    int remaining = 0;
    for (int i = 0; i < m; i++) {
        if (marbles[i].active) remaining++;
    }
    cout << remaining << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t_cases;
    cin >> t_cases;
    while (t_cases--) {
        solve();
    }
    return 0;
}