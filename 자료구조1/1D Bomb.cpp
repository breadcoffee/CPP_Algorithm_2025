#include <iostream>

using namespace std;

int n, m;
int bombs[101]; // 폭탄 숫자를 저장하는 배열
int current_n;  // 현재 남은 폭탄의 개수

// M개 이상 연속된 폭탄을 찾아 터뜨리는 함수
bool Explode() {
    bool to_remove[101] = {false}; // 터뜨릴 위치 표시
    bool exploded = false;

    // 1. 연속된 구간 탐색
    for (int i = 0; i < current_n; i++) {
        int j = i;
        // 현재 위치(i)부터 같은 숫자가 어디까지 연속되는지 확인
        while (j < current_n && bombs[j] == bombs[i]) {
            j++;
        }

        int count = j - i;
        // 연속된 개수가 M개 이상이면 삭제 표시
        if (count >= m) {
            for (int k = i; k < j; k++) {
                to_remove[k] = true;
            }
            exploded = true;
        }
        
        // i를 연속 구간의 끝으로 이동 (for문의 i++와 합쳐져 다음 숫자로 넘어감)
        i = j - 1;
    }

    // 2. 중력 작용 (살아남은 폭탄만 임시 배열로 이동)
    int temp[101];
    int temp_count = 0;
    for (int i = 0; i < current_n; i++) {
        if (!to_remove[i]) {
            temp[temp_count++] = bombs[i];
        }
    }

    // 3. 임시 배열의 내용을 다시 원래 배열로 복사 및 개수 갱신
    current_n = temp_count;
    for (int i = 0; i < current_n; i++) {
        bombs[i] = temp[i];
    }

    return exploded;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // 입력 받기
    cin >> n >> m;
    current_n = n;
    for (int i = 0; i < n; i++) {
        cin >> bombs[i];
    }

    // M=1이면 모든 폭탄이 한 번에 터지므로 즉시 종료
    if (m == 1) {
        cout << 0 << endl;
        return 0;
    }

    // 더 이상 터질 폭탄이 없을 때까지 반복
    while (true) {
        if (!Explode()) break;
    }

    // 결과 출력
    cout << current_n << "\n";
    for (int i = 0; i < current_n; i++) {
        cout << bombs[i] << "\n";
    }

    return 0;
}