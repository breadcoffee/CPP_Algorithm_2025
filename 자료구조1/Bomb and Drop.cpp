#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int grid[201][201];
int temp[201][201]; // 중력 적용 시 값을 임시로 저장할 배열

// 격자 범위 내에 있는지 확인하는 함수
bool InRange(int r, int c) {
    return r >= 1 && r <= n && c >= 1 && c <= n;
}

void Bomb(int r, int c) {
    int dist = grid[r][c];
    
    // 상하좌우 방향 벡터
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // 폭탄 중심을 포함하여 십자 모양을 0으로 만듦
    // 거리(len)는 0부터 dist-1까지
    for (int i = 0; i < 4; i++) {
        for (int len = 0; len < dist; len++) {
            int nr = r + dr[i] * len;
            int nc = c + dc[i] * len;
            if (InRange(nr, nc)) {
                grid[nr][nc] = 0;
            }
        }
    }
}

void ApplyGravity() {
    // 모든 열에 대해 중력을 적용
    for (int j = 1; j <= n; j++) {
        int next_row = n; // 아래쪽부터 채우기 위한 변수
        
        // 해당 열의 아래(n)부터 위(1)까지 0이 아닌 값만 찾음
        for (int i = n; i >= 1; i--) {
            if (grid[i][j] != 0) {
                temp[next_row--][j] = grid[i][j];
            }
        }
        
        // 나머지 위쪽 칸은 0으로 채움
        while (next_row >= 1) {
            temp[next_row--][j] = 0;
        }
    }

    // temp 배열의 결과를 다시 grid로 복사
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            grid[i][j] = temp[i][j];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // 1. 입력 받기
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> grid[i][j];
        }
    }

    int r, c;
    cin >> r >> c;

    // 2. 폭탄 터뜨리기
    Bomb(r, c);

    // 3. 중력 적용하기
    ApplyGravity();

    // 4. 출력하기
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}

/*
입출력 예제
예제1
입력:

4
1 2 4 3
3 2 2 3
3 1 6 2
4 5 4 4
2 3
출력:

1 0 0 0
3 2 0 3
3 1 0 2
4 5 4 4
예제2
입력:

4
1 2 4 3
3 2 2 3
3 1 6 2
4 5 4 4
2 3
출력:

1 0 0 0
3 2 0 3
3 1 0 2
4 5 4 4
*/