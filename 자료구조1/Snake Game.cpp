#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int n, m, k;
int grid[105][105]; // 0: 빈칸, 1: 뱀의 몸통, 2: 사과
deque<pair<int, int>> snake;

// 방향 벡터 매핑
int dx[128], dy[128];

bool InRange(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // 방향 초기화
    dx['U'] = -1; dy['U'] = 0;
    dx['D'] = 1;  dy['D'] = 0;
    dx['R'] = 0;  dy['R'] = 1;
    dx['L'] = 0;  dy['L'] = -1;

    if(!(cin >> n >> m >> k)) return 0;

    for (int i = 0; i < m; i++) {
        int r, c;
        cin >> r >> c;
        grid[r][c] = 2; // 사과
    }

    // 초기 상태: (1, 1)에서 시작
    int cur_x = 1, cur_y = 1;
    snake.push_front({cur_x, cur_y});
    grid[cur_x][cur_y] = 1;

    int total_time = 0;

    for (int i = 0; i < k; i++) {
        char d;
        int p;
        cin >> d >> p;

        for (int step = 0; step < p; step++) {
            total_time++;
            
// 이동할 위치 저장
            int nx = cur_x + dx[d];
            int ny = cur_y + dy[d];

            if (!InRange(nx, ny)) { cout << total_time << endl; return 0; }

            bool apple = (grid[nx][ny] == 2);
            if (!apple) {
                // 사과가 없으면 꼬리를 먼저 치우고
                pair<int, int> tail = snake.back();
                grid[tail.first][tail.second] = 0;
                snake.pop_back();
            }

            // 그 다음에 머리가 들어갈 자리에 몸이 있는지 확인
            if (grid[nx][ny] == 1) {
                cout << total_time << endl;
                return 0;
            }

            // 머리 배치
            grid[nx][ny] = 1;
            snake.push_front({nx, ny});
            cur_x = nx; cur_y = ny;
        }
    }

    cout << total_time << endl;
    return 0;
}