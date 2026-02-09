#include <iostream>
#include <vector>

using namespace std;

int grid[4][4];
int next_grid[4][4];

// 특정 방향으로 밀기 전, 1차원 배열(한 줄)을 처리하는 핵심 로직
void ProcessLine(vector<int>& line) {
    vector<int> temp;
    // 1. 0이 아닌 숫자만 앞으로 모으기
    for (int num : line) {
        if (num != 0) temp.push_back(num);
    }

    vector<int> merged;
    // 2. 인접한 같은 숫자 합치기
    for (int i = 0; i < (int)temp.size(); i++) {
        if (i + 1 < (int)temp.size() && temp[i] == temp[i + 1]) {
            merged.push_back(temp[i] * 2);
            i++; // 합쳐졌으므로 다음 숫자는 건너뜀
        } else {
            merged.push_back(temp[i]);
        }
    }

    // 3. 결과를 다시 line에 담고 나머지는 0으로 채움
    line.assign(4, 0);
    for (int i = 0; i < (int)merged.size(); i++) {
        line[i] = merged[i];
    }
}

void Move(char dir) {
    // 결과를 저장할 next_grid 초기화
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            next_grid[i][j] = 0;

    if (dir == 'U' || dir == 'D') {
        for (int j = 0; j < 4; j++) {
            vector<int> line;
            if (dir == 'U') {
                for (int i = 0; i < 4; i++) line.push_back(grid[i][j]);
            } else {
                for (int i = 3; i >= 0; i--) line.push_back(grid[i][j]);
            }
            
            ProcessLine(line);
            
            if (dir == 'U') {
                for (int i = 0; i < 4; i++) next_grid[i][j] = line[i];
            } else {
                for (int i = 3; i >= 0; i--) next_grid[i][j] = line[3 - i];
            }
        }
    } else { // 'L' or 'R'
        for (int i = 0; i < 4; i++) {
            vector<int> line;
            if (dir == 'L') {
                for (int j = 0; j < 4; j++) line.push_back(grid[i][j]);
            } else {
                for (int j = 3; j >= 0; j--) line.push_back(grid[i][j]);
            }

            ProcessLine(line);

            if (dir == 'L') {
                for (int j = 0; j < 4; j++) next_grid[i][j] = line[j];
            } else {
                for (int j = 3; j >= 0; j--) next_grid[i][j] = line[3 - j];
            }
        }
    }
}

int main() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cin >> grid[i][j];

    char dir;
    cin >> dir;

    Move(dir);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << next_grid[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}