/*
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Marble {
    int id, x, y, w, dir;
    bool active;
};

// 방향: U(0), D(1), R(2), L(3)
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int getDir(char d) {
    if (d == 'U') return 0;
    if (d == 'D') return 1;
    if (d == 'R') return 2;
    return 3;
}

// 좌표 순 정렬 (충돌 판정용)
bool posComp(const Marble& a, const Marble& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

// 영향력 순 정렬 (무게 큰 순 -> 번호 큰 순)
bool weightComp(const Marble& a, const Marble& b) {
    if (a.w != b.w) return a.w > b.w;
    return a.id > b.id;
}

void solve() {
    int n;
    if (!(cin >> n)) return;
    
    vector<Marble> marbles(n);
    for (int i = 0; i < n; i++) {
        int x, y, w;
        char d;
        cin >> x >> y >> w >> d;
        // 2초에 한 칸 이동 -> 좌표 2배 확장 (정수 좌표 충돌을 위해)
        marbles[i] = {i + 1, x * 2, y * 2, w, getDir(d), true};
    }

    int last_collision_time = -1;

    // 최대 4000초 시뮬레이션 (범위 -2000 ~ 2000 고려)
    for (int t = 1; t <= 4000; t++) {
        // 1. 모든 활성 구슬 이동
        for (int i = 0; i < n; i++) {
            if (marbles[i].active) {
                marbles[i].x += dx[marbles[i].dir];
                marbles[i].y += dy[marbles[i].dir];
            }
        }

        // 2. 충돌 판정 (정렬을 이용해 같은 좌표 구슬 찾기)
        // 현재 살아있는 구슬들만 임시 벡터에 모음
        vector<Marble> temp;
        for (int i = 0; i < n; i++) {
            if (marbles[i].active) temp.push_back(marbles[i]);
        }
        
        if (temp.empty()) break;

        sort(temp.begin(), temp.end(), posComp);

        bool collision_occurred = false;
        vector<int> to_remove_ids;

        for (int i = 0; i < (int)temp.size(); ) {
            int j = i + 1;
            // 같은 좌표에 있는 구슬 그룹 찾기
            while (j < (int)temp.size() && temp[i].x == temp[j].x && temp[i].y == temp[j].y) {
                j++;
            }

            // 구슬이 2개 이상 겹쳤다면
            if (j - i > 1) {
                collision_occurred = true;
                // 해당 그룹 내에서 가장 영향력 있는 구슬 찾기
                int best_idx = i;
                for (int k = i + 1; k < j; k++) {
                    if (weightComp(temp[k], temp[best_idx])) {
                        best_idx = k;
                    }
                }

                // 가장 강한 구슬 제외하고 모두 삭제 리스트에 추가
                for (int k = i; k < j; k++) {
                    if (k != best_idx) {
                        to_remove_ids.push_back(temp[k].id);
                    }
                }
            }
            i = j; // 다음 그룹으로 이동
        }

        // 실제 구슬 배열에서 비활성화 처리
        if (collision_occurred) {
            last_collision_time = t;
            for (int id : to_remove_ids) {
                for (int i = 0; i < n; i++) {
                    if (marbles[i].id == id) {
                        marbles[i].active = false;
                        break;
                    }
                }
            }
        }
    }

    cout << last_collision_time << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t_cases;
    cin >> t_cases;
    while (t_cases--) {
        solve();
    }
    return 0;
}
*/ // 조건에 맞춰서 코딩했을때

// 밑에는 이벤트를 미리 시간별로 예측해서 계산했을때 제미나이가 짬
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Marble {
    int id, x, y, w, dir;
};

struct Event {
    int time, x, y, m1, m2;
    bool operator<(const Event& other) const {
        if (time != other.time) return time < other.time;
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

int dx[] = {0, 0, 1, -1}; // U, D, R, L
int dy[] = {1, -1, 0, 0};

void solve() {
    int n; cin >> n;
    vector<Marble> ms(n);
    for (int i = 0; i < n; i++) {
        char d; int x, y;
        cin >> x >> y >> ms[i].w >> d;
        ms[i].x = x * 2; ms[i].y = y * 2; ms[i].id = i;
        if (d == 'U') ms[i].dir = 0;
        else if (d == 'D') ms[i].dir = 1;
        else if (d == 'R') ms[i].dir = 2;
        else ms[i].dir = 3;
    }

    vector<Event> events;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // 두 구슬 i, j가 만날 수 있는 조건 계산
            // 상대 속도와 상대 거리를 이용해 충돌 시간 t 도출
            int dx_rel = ms[i].x - ms[j].x;
            int dy_rel = ms[i].y - ms[j].y;
            int dvx_rel = dx[ms[j].dir] - dx[ms[i].dir];
            int dvy_rel = dy[ms[j].dir] - dy[ms[i].dir];

            int tx = -1, ty = -1;
            if (dvx_rel == 0) { if (dx_rel == 0) tx = 0; }
            else if (dx_rel % dvx_rel == 0 && dx_rel / dvx_rel > 0) tx = dx_rel / dvx_rel;

            if (dvy_rel == 0) { if (dy_rel == 0) ty = 0; }
            else if (dy_rel % dvy_rel == 0 && dy_rel / dvy_rel > 0) ty = dy_rel / dvy_rel;

            if (tx != -1 && ty != -1 && (tx == ty || tx == 0 || ty == 0)) {
                int t = max(tx, ty);
                events.push_back({t, ms[i].x + dx[ms[i].dir] * t, ms[i].y + dy[ms[i].dir] * t, i, j});
            }
        }
    }

    sort(events.begin(), events.end());

    vector<int> dead_time(n, 1e9);
    int last_t = -1;

    for (int i = 0; i < (int)events.size(); ) {
        int j = i;
        vector<int> candidates;
        // 같은 시간, 같은 좌표에서 일어나는 모든 충돌을 한꺼번에 처리
        while (j < (int)events.size() && events[i].time == events[j].time && 
               events[i].x == events[j].x && events[i].y == events[j].y) {
            if (dead_time[events[j].m1] >= events[j].time && dead_time[events[j].m2] >= events[j].time) {
                candidates.push_back(events[j].m1);
                candidates.push_back(events[j].m2);
            }
            j++;
        }

        if (!candidates.empty()) {
            sort(candidates.begin(), candidates.end());
            candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());
            
            // 영향력 가장 큰 구슬 찾기
            int winner = candidates[0];
            for (int idx : candidates) {
                if (ms[idx].w > ms[winner].w) winner = idx;
                else if (ms[idx].w == ms[winner].w && ms[idx].id > ms[winner].id) winner = idx;
            }

            // 승자 제외하고 모두 제거 시점 기록
            bool real_collision = false;
            for (int idx : candidates) {
                if (idx != winner) {
                    dead_time[idx] = events[i].time;
                    real_collision = true;
                }
            }
            if (real_collision) last_t = events[i].time;
        }
        i = j;
    }
    cout << last_t << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}