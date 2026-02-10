#include <iostream>
#include <string>
#include <vector>

using namespace std;

int n;
int curr_x, curr_y, curr_dir;
char grid[105][105];

// 방향: 우(0), 하(1), 좌(2), 상(3) -> 시계 방향 순서
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

bool InRange(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

// 현재 위치와 방향에서 오른쪽에 벽이 있는지 확인하는 함수
bool HasRightWall(int x, int y, int dir) {
    int r_dir = (dir + 1) % 4; // 현재 방향의 시계 방향 90도(오른쪽)
    int rx = x + dx[r_dir];
    int ry = y + dy[r_dir];
    
    // 격자 밖은 벽이 없는 것으로 간주하거나 문제 조건에 맞게 처리
    if (!InRange(rx, ry)) return false;
    return grid[rx][ry] == '#';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    cin >> curr_x >> curr_y;
    curr_x--; curr_y--; // 0-based 변환
    
    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < n; j++) {
            grid[i][j] = row[j];
        }
    }

    curr_dir = 0; // 시작 방향: 우측
    long long time = 0;
    int limit = n * n * 4; // 무한 루프 체크를 위한 임계값

    while (time <= limit) {
        int nx = curr_x + dx[curr_dir];
        int ny = curr_y + dy[curr_dir];

        // 1. 바라보는 방향이 벽인 경우
        if (InRange(nx, ny) && grid[nx][ny] == '#') {
            curr_dir = (curr_dir + 3) % 4; // 반시계 90도 회전
        }
        // 2. 앞이 격자 밖인 경우 (탈출 성공)
        else if (!InRange(nx, ny)) {
            time++;
            cout << time << endl;
            return 0;
        }
        // 3. 앞으로 전진 가능한 경우
        else {
            // 이동 후 그 위치에서 오른쪽에 벽이 있는지 확인
            if (HasRightWall(nx, ny, curr_dir)) {
                curr_x = nx;
                curr_y = ny;
                time++;
            }
            // 오른쪽에 벽이 없다면 (코너를 도는 경우)
            else {
                curr_x = nx;
                curr_y = ny;
                time++;
                
                // 방향을 시계 방향으로 틀어 한 칸 더 전진
                curr_dir = (curr_dir + 1) % 4;
                curr_x += dx[curr_dir];
                curr_y += dy[curr_dir];
                time++;
                
                // 두 번째 이동에서 격자 밖으로 나가는 경우 탈출 처리
                if (!InRange(curr_x, curr_y)) {
                    cout << time << endl;
                    return 0;
                }
            }
        }
    }

    // 탈출 불가능
    cout << -1 << endl;
    return 0;
}