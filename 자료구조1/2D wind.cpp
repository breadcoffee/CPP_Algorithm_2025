/*
0이상 9이하의 숫자로만 이루어진 N*M 행렬 모양의 건물에 총 Q번의 바람이 붑니다.

이 바람은 굉장히 특이해서 특정 직사각형 영역의 경계에 있는 숫자들을 시계 방향으로 한 칸씩 shift 하고 
해당 직사각형 내 영역에 있는 값들을 각각 자신의 위치를 기준으로 자신과 인접한 원소들과의 평균 값으로 바꿉니다. 
(평균 계산시에는 항상 버림하여 정수값이 나오도록 합니다.)

먼저 직사각형의 경계에 있는 숫자들이 시계 방향으로 한 칸씩 회전을 하게 됩니다.
그 다음 직사각형 영역 내에 있는 각각의 숫자들의 값이 현재 칸에 적혀있는 숫자 + 인접한 곳에 적혀있는 숫자들의 평균 값으로 바뀌게 됩니다. 
이 과정은 순차적으로 일어나는 것이 아니라 동시에 일어납니다.

예를 들어 (2, 2) 위치에 있던 원소는 인접한 4개의 값들과의 평균값을 버림한 값인 3으로 바뀌어야 합니다.
(1+5+2+2+6)/5 = 3

한 바람이 분 이후 모든 값 변경이 완료된 이후에 그 다음 바람이 불어 온다고 할 때, 총 Q개의 바람을 거친 이후 건물의 상태를 출력하는 프로그램을 작성해보세요

입력 형식
첫째 줄에는 행렬의 크기를 나타내는 N과 M 그리고 총 바람이 불어온 횟수를 의미하는 Q가 공백을 사이에 두고 주어집니다.

두 번째 줄 부터 N개의 줄에 걸쳐 한 줄에 M개 씩 건물의 상태를 나타내는 0이상 9이하의 숫자가 공백을 사이에 두고 주어집니다.

그 다음 줄 부터는 Q개의 줄에 걸쳐 불어오는 바람에 대한 정보 (r1, c1, r2, c2)가 공백을 사이에 두고 주어집니다. (r1, c1)은 바람에 영향을 받는 직사각형의 좌측 상단의 위치이며 (r2, c2)는 바람에 영향을 받는 직사각형의 우측 하단의 위치입니다. 즉, 해당 바람에 의해 r1행 c1열부터 r2행 c2열까지의 직사각형이 영향을 받게 됨을 의미합니다. (1 ≤ r1 < r2 ≤ N, 1 ≤ c1 < c2 ≤ M)

2 ≤ N ≤ 100

2 ≤ M ≤ 100

0 ≤ Q ≤ 100

출력 형식
Q개의 바람을 거친 이후 건물의 상태를 N개의 줄에 걸쳐 출력합니다. 각 줄마다 각각의 행에 해당하는 M개의 값을 공백을 사이에 두고 출력합니다.

입출력 예제
예제1
입력:

4 6 1
4 5 2 5 6 6
2 1 6 1 0 5
5 2 2 1 6 5
4 5 2 8 8 6
2 2 4 6
출력:

4 5 2 5 6 6 
2 3 2 2 3 3 
5 3 3 4 3 4 
4 4 5 5 6 5
예제2
입력:

3 3 2
1 2 3
3 2 1
3 3 3
1 1 2 2
2 2 3 3
출력:

2 2 3 
2 2 2 
3 2 1
*/

#include <iostream>

#define DIR_NUM 5
#define MAX_N 100
#define MAX_M 100

using namespace std;

// 전역 변수 선언:
int n, m, q;

int a[MAX_N + 1][MAX_M + 1];
int temp_arr[MAX_N + 1][MAX_M + 1];


// 직사각형의 경계에 있는 숫자들을 시계 방향으로 한 칸씩 회전해줍니다.
void Rotate(int start_row, int start_col, int end_row, int end_col) {
    // Step1-1. 직사각형 가장 왼쪽 위 모서리 값을 temp에 저장합니다.
    int temp = a[start_row][start_col];

    // Step1-2. 직사각형 가장 왼쪽 열을 위로 한 칸씩 shift 합니다.
    for(int row = start_row; row < end_row; row++)
        a[row][start_col] = a[row + 1][start_col];
    
    // Step1-3. 직사각형 가장 아래 행을 왼쪽으로 한 칸씩 shift 합니다.
    for(int col = start_col; col < end_col; col++)
        a[end_row][col] = a[end_row][col + 1];

    // Step1-4. 직사각형 가장 오른쪽 열을 아래로 한 칸씩 shift 합니다.
    for(int row = end_row; row > start_row; row--)
        a[row][end_col] = a[row - 1][end_col];
    
    // Step1-5. 직사각형 가장 위 행을 오른쪽으로 한 칸씩 shift 합니다.
    for(int col = end_col; col > start_col; col--)
        a[start_row][col] = a[start_row][col - 1];

    // Step1-6. temp를 가장 왼쪽 위 모서리를 기준으로 바로 오른쪽 칸에 넣습니다. 
    a[start_row][start_col + 1] = temp;
}

// 격자를 벗어나는지 판단합니다.
bool InRange(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= m;
}

// x행 y열 (x, y)과 인접한 숫자들과의 평균 값을 계산해줍니다.
// 격자를 벗어나지 않는 숫자들만을 고려해줍니다.
int Average(int x, int y) {
    // 자기 자신의 위치를 포함하여 평균을 내야 하므로 
    // DIR_NUM을 5로 설정하면 한번에 처리가 가능합니다.
    int dx[DIR_NUM] = {0, 1, -1, 0, 0};
    int dy[DIR_NUM] = {0, 0, 0, 1, -1};
    
    int sum = 0, cnt = 0;

    for(int dir = 0; dir < DIR_NUM; dir++) {
        int nx = x + dx[dir], ny = y + dy[dir];
        if(InRange(nx, ny)) {
            sum += a[nx][ny]; cnt++;
        }
    }

    return sum / cnt;
}

// 직사각형 내 숫자들을 인접한 숫자들과의 평균값으로 바꿔줍니다.
// 동시에 일어나야 하는 작업이므로 이미 바뀐 숫자에 주위 숫자들이 영향을 받으면 안되기 때문에 
// temp_arr 배열에 평균 값들을 먼저 전부 적어 준 다음, 그 값을 다시 복사해옵니다.
void SetAverage(int start_row, int start_col, int end_row, int end_col) {
    // Step2-1. temp_arr에 평균 값을 적습니다.
    for(int row = start_row; row <= end_row; row++)
        for(int col = start_col; col <= end_col; col++)
            temp_arr[row][col] = Average(row, col);
    
    // Step2-2. temp_arr 값을 다시 가져옵니다.
    for(int row = start_row; row <= end_row; row++)
        for(int col = start_col; col <= end_col; col++)
            a[row][col] = temp_arr[row][col];
}

// 조건에 맞춰 값을 바꿔봅니다.
void Simulate(int start_row, int start_col, int end_row, int end_col) {
    // Step1
    // 직사각형의 경계에 있는 숫자들을 시계 방향으로 한 칸씩 회전해줍니다.
    Rotate(start_row, start_col, end_row, end_col);

    // Step2
    // 직사각형 내 각각의 숫자들을 인접한 숫자들과의 평균값으로 바꿔줍니다.
    SetAverage(start_row, start_col, end_row, end_col);
}

int main() {
    // 입력:
    cin >> n >> m >> q;
    
    for(int row = 1; row <= n; row++)
        for(int col = 1; col <= m; col++)
            cin >> a[row][col];
    
    while(q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        // 조건에 맞춰 값을 바꿔봅니다.
        Simulate(r1, c1, r2, c2);
    }

    // 출력:
    for(int row = 1; row <= n; row++) {
        for(int col = 1; col <= m; col++)
            cout << a[row][col] << " ";
        cout << endl;
    }
    return 0;
}