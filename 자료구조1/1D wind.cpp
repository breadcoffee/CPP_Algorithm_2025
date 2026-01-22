/*
0이상 9이하의 숫자로만 이루어진 N*M 행렬 모양의 건물에 총 Q번의 바람이 붑니다.
바람은 특정 행의 모든 원소들을 왼쪽 혹은 오른쪽으로 전부 한 칸씩 밀어 shift 하는 효과를 가져옵니다.
이 바람에 영향을 받아 특정 행의 숫자들이 한 칸씩 밀리게 되면, 위 아래로도 영향을 미치기 시작합니다. 
밀리기 시작한 행을 기준으로 위 아래 방향으로 순차적으로 전파가 되며 도중에 전파 방향이 바뀌는 경우는 없습니다.

전파가 이어질 조건은 현재 행과 나아가려는 행을 비교했을 때, 단 하나라도 같은 열에 같은 숫자가 적혀있는 경우라면 전파를 이어나갑니다. 
같은 숫자가 하나도 존재하지 않거나 끝에 다다랐다면 전파를 종료합니다. 전파가 진행되는 경우 나아가려는 행의 숫자들을 한 칸씩 밀게되며, 
현재 행이 밀렸던 방향과 반대 방향으로 작용합니다.

예를 들어 위의 예에서 우측 방향으로 바람이 불어와 3번째 행이 오른쪽으로 한 칸 밀린 이후에는 2행, 4행 방향으로 전파를 시도합니다. 
2번째 행과 4번째 행 모두 3번째 행과 같은 열에서 일치하는 숫자가 하나 이상 존재하므로 전파를 진행합니다. 
이때, 3행은 우측 방향으로 밀렸던 행이므로 2행, 4행은 전파의 영향을 받아 전부 반대 방향인 좌측 방향으로 한 칸씩 밀리게 됩니다.
전파는 계속 진행됩니다. 2행과 4행은 진행했던 방향으로 그다음 전파를 시도합니다.

한 바람이 분 이후 모든 전파가 완료 되었을 때 그 다음 바람이 불어 온다고 할 때, 총 Q개의 바람을 거친 이후 건물의 상태를 출력하는 프로그램을 작성해보세요

입력 형식
첫째 줄에는 행렬의 크기를 나타내는 N과 M 그리고 총 바람이 불어온 횟수를 의미하는 Q가 공백을 사이에 두고 주어집니다.

두 번째 줄 부터 N개의 줄에 걸쳐 한 줄에 M개 씩 건물의 상태를 나타내는 0이상 9이하의 숫자가 공백을 사이에 두고 주어집니다.

그 다음 줄 부터는 Q개의 줄에 걸쳐 불어오는 바람에 대한 정보 (r, d)가 공백을 사이에 두고 주어집니다. r은 바람에 영향을 받는 행 번호를 의미하며 d는 바람이 불어오는 방향을 의미합니다. d는 ‘L' 또는 ‘R’의 값을 가지며, ‘L’은 바람이 왼쪽에서 불어온다는 것을 'R’은 바람이 오른쪽에서 불어온다는 것을 의미합니다. (1 ≤ r ≤ N)

1 ≤ N ≤ 100

1 ≤ M ≤ 100

0 ≤ Q ≤ 100

출력 형식
Q개의 바람을 거친 이후 건물의 상태를 N개의 줄에 걸쳐 출력합니다. 각 줄마다 각각의 행에 해당하는 M개의 값을 공백을 사이에 두고 출력합니다.

입출력 예제
예제1
입력:

6 5 1
1 5 6 7 3
5 3 2 5 4
6 4 5 2 5
2 6 1 0 5
5 1 2 1 6
4 2 5 2 8
3 L
출력:

1 5 6 7 3
3 2 5 4 5
5 6 4 5 2
6 1 0 5 2
6 5 1 2 1
2 5 2 8 4
예제2
입력:

3 3 2
1 2 3
3 2 1
3 3 3
3 L
1 L
출력:

2 3 1
1 3 2
3 3 3
*/

#include <iostream>

#define MAX_N 100
#define MAX_M 100
#define SHIFT_RIGHT 0
#define SHIFT_LEFT 1

using namespace std;

// 전역 변수 선언:
int n, m, q;

int a[MAX_N + 1][MAX_M + 1];

// row 줄의 원소들을 dir 방향에 따라 한 칸 밀어줍니다.
// dir이 0인 경우 오른쪽으로
// dir이 1인 경우 왼쪽으로 밀어야 합니다.
void Shift(int row, int dir) {
    // 오른쪽으로 밀어야 하는 경우
    if(dir == SHIFT_RIGHT) {
        int temp = a[row][m];
        for(int col = m; col >= 2; col--)
            a[row][col] = a[row][col - 1];
        a[row][1] = temp;
    }
    // 왼쪽으로 밀어야 하는 경우
    else {
        int temp = a[row][1];
        for(int col = 1; col <= m - 1; col++)
            a[row][col] = a[row][col + 1];
        a[row][m] = temp;
    }
}

// row1, row2 행에 대해 같은 열에 같은 숫자를 갖는 경우가
// 있는지를 찾아줍니다.
bool HasSameNumber(int row1, int row2) {
    for(int col = 1; col <= m; col++)
        if(a[row1][col] == a[row2][col])
            return true;
    
    return false;
}

// 주어진 방향으로부터 반대 방향의 값을 반환합니다.
bool Flip(int dir) {
    return (dir == SHIFT_LEFT) ? SHIFT_RIGHT : SHIFT_LEFT;
}

// 조건에 맞춰 움직여봅니다.
// dir이 SHIFT_RIGHT 인 경우 오른쪽으로
// dir이 SHIFT_LEFT 인 경우 왼쪽으로 밀어야 합니다.
void Simulate(int start_row, int start_dir) {
    // Step1
    // 바람이 처음으로 불어 온 행의 숫자들을 해당 방향으로 밀어줍니다.
    Shift(start_row, start_dir);

    // 그 이후부터는 반전된 방향에 영향을 받으므로, 방향을 미리 반전 시켜줍니다.
    start_dir = Flip(start_dir);

    // Step2
    // 위 방향으로 전파를 계속 시도해봅니다.
    for(int row = start_row, dir = start_dir; row >= 2; row--) {
        // 인접한 행끼리 같은 숫자를 가지고 있다면
        // 위의 행을 한 칸 shift하고
        // 방향을 반대로 바꿔 계속 전파를 진행합니다.
        if(HasSameNumber(row, row - 1)) {
            Shift(row - 1, dir);
            dir = Flip(dir);
        }
        // 같은 숫자가 없다면 전파를 멈춥니다.
        else
            break;
    }

    // Step3
    // 아래 방향으로 전파를 계속 시도해봅니다.
    for(int row = start_row, dir = start_dir; row <= n - 1; row++) {
        // 인접한 행끼리 같은 숫자를 가지고 있다면
        // 아래 행을 한 칸 shift하고
        // 방향을 반대로 바꿔 계속 전파를 진행합니다.
        if(HasSameNumber(row, row + 1)) {
            Shift(row + 1, dir);
            dir = Flip(dir);
        }
        // 같은 숫자가 없다면 전파를 멈춥니다.
        else
            break;
    }
}

int main() {
    // 입력:
    cin >> n >> m >> q;
    
    for(int row = 1; row <= n; row++)
        for(int col = 1; col <= m; col++)
            cin >> a[row][col];
    
    while(q--) {
        int r; char d;
        cin >> r >> d;

        // 조건에 맞춰 움직여봅니다.
        Simulate(r, d == 'L' ? SHIFT_RIGHT : SHIFT_LEFT);
    }

    // 출력:
    for(int row = 1; row <= n; row++) {
        for(int col = 1; col <= m; col++)
            cout << a[row][col] << " ";
        cout << endl;
    }
    return 0;
}