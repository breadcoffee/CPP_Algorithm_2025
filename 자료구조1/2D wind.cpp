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