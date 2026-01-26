#include <iostream>

#define MAX_N 200

using namespace std;

// 전역 변수 선언:
int n, t;

int u[MAX_N + 1]; // 첫번째 줄
int d[MAX_N + 1]; // 두번째 줄
int r[MAX_N + 1]; // 두번째 줄

int main() {
    cin >> n >> t;

    for(int i = 0; i < n; i++)
        cin >> u[i];
    for(int i = 0; i < n; i++)
        cin >> d[i];
    for(int i = 0; i < n; i++)
        cin >> r[i];

    while(t--){
        int temp = u[n-1]; // 첫번째 줄 가장 오른쪽 하나 미리 보관
        
        for(int i = n - 1; i >= 1; i--)
            u[i] = u[i - 1];
        u[0] = r[n - 1];

        int temp2 = d[n-1]; // 두번째 줄 까장 오른쪽 하나 보관
        for(int i = n - 1; i >= 1; i--)
            d[i] = d[i - 1];
        d[0] = temp;

        for(int i = n - 1; i >= 1; i--)
            r[i] = r[i - 1];
        r[0] = temp2;
    }

    // 출력:
    for(int i = 0; i < n; i++)
		cout << u[i] << " ";
	cout << endl;
    
	for(int i = 0; i < n; i++)
		cout << d[i] << " ";
    cout << endl;
        
    for(int i = 0; i < n; i++)
		cout << r[i] << " ";

    return 0;
}
