#include <iostream>
#include <vector>

using namespace std;

int n;
int grid[105][105];

// 우선순위: 상(0), 하(1), 좌(2), 우(3)
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool InRange(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c;
    cin >> n >> r >> c;

    // 1-based index를 0-based로 변환
    int curr_x = r - 1;
    int curr_y = c - 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    // 시작 위치 숫자 출력
    cout << grid[curr_x][curr_y] << " ";

    while (true) {
        bool moved = false;

        // 우선순위에 따라 상하좌우 순서대로 확인
        for (int i = 0; i < 4; i++) {
            int nx = curr_x + dx[i];
            int ny = curr_y + dy[i];

            // 범위 안이고, 현재 위치보다 더 큰 숫자가 있다면
            if (InRange(nx, ny) && grid[nx][ny] > grid[curr_x][curr_y]) {
                curr_x = nx;
                curr_y = ny;
                cout << grid[curr_x][curr_y] << " ";
                moved = true;
                
                // 이동했으므로 즉시 방향 탐색 중단 (우선순위 보장)
                break;
            }
        }

        // 4방향 모두 갈 곳이 없으면 종료
        if (!moved) break;
    }

    return 0;
}