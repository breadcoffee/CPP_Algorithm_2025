#include <iostream>
#include <vector>

using namespace std;

vector<int> RemoveRange(vector<int> v, int s, int e) {
    vector<int> temp;
    for(int i = 0; i < (int)v.size(); i++) {
        // 인덱스는 0부터 시작하므로 s-1, e-1 범위 체크
        if(i < s - 1 || i > e - 1) {
            temp.push_back(v[i]);
        }
    }
    return temp;
}

int main() {
    int n;
    cin >> n;
    vector<int> blocks(n);
    for(int i = 0; i < n; i++) cin >> blocks[i];

    int s1, e1, s2, e2;
    cin >> s1 >> e1;
    blocks = RemoveRange(blocks, s1, e1);

    cin >> s2 >> e2;
    blocks = RemoveRange(blocks, s2, e2);

    cout << blocks.size() << "\n";
    for(int b : blocks) cout << b << "\n";

    return 0;
}