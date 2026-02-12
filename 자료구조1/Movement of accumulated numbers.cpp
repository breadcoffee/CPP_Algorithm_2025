#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<int> board[21][21]; // 각 격자의 숫자 스택
pair<int, int> num_pos[401]; // 각 숫자의 현재 (r, c) 위치

// 8방향 벡터 (상, 하, 좌, 우, 대각선 4방향)
int dr[] = {-1, 1, 0, 0, -1, -1, 1, 1};
int dc[] = {0, 0, -1, 1, -1, 1, -1, 1};

bool InRange(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < n;
}

void Move(int target_num) {
    int r = num_pos[target_num].first;
    int c = num_pos[target_num].second;

    int max_val = -1;
    int next_r = -1, next_c = -1;

    // 1. 주변 8방향 중 가장 큰 숫자가 있는 칸 찾기
    for (int i = 0; i < 8; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if (InRange(nr, nc) && !board[nr][nc].empty()) {
            // 해당 칸에서 가장 큰 값 찾기
            int current_max = -1;
            for (int val : board[nr][nc]) {
                current_max = max(current_max, val);
            }
            
            if (current_max > max_val) {
                max_val = current_max;
                next_r = nr;
                next_c = nc;
            }
        }
    }

    // 2. 이동할 곳이 없으면 종료
    if (next_r == -1) return;

    // 3. target_num과 그 위의 숫자들을 함께 이동
    vector<int>& curr_stack = board[r][c];
    auto it = find(curr_stack.begin(), curr_stack.end(), target_num);
    
    vector<int> to_move;
    // target_num부터 끝까지 복사
    to_move.assign(it, curr_stack.end());
    // 원래 칸에서 삭제
    curr_stack.erase(it, curr_stack.end());

    // 4. 새로운 칸으로 이동 및 위치 업데이트
    for (int moving_num : to_move) {
        board[next_r][next_c].push_back(moving_num);
        num_pos[moving_num] = {next_r, next_c};
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int num;
            cin >> num;
            board[i][j].push_back(num);
            num_pos[num] = {i, j};
        }
    }

    while (m--) {
        int target;
        cin >> target;
        Move(target);
    }

    // 결과 출력
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j].empty()) {
                cout << "None\n";
            } else {
                // 가장 위에 있는 숫자부터 출력 (스택의 뒤에서부터)
                for (int k = board[i][j].size() - 1; k >= 0; k--) {
                    cout << board[i][j][k] << (k == 0 ? "" : " ");
                }
                cout << "\n";
            }
        }
    }

    return 0;
}