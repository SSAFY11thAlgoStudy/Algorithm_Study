#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int n, m, st_point, end_point;
int visit_start_to_end[100001], visit_end_to_start[100001];
vector<int>path[100001];


void input() {
    int from, to;
    cin >> n >> m; // n개의 노드, M개의 노선
    for (int i = 0; i < m; i++) {
        cin >> from >> to;
        path[from].push_back(to);
    }
    cin >> st_point >> end_point;
}

int start_to_end(int st, int ed) {
    if (path[st].size() == 0 || st == ed) {
        return 1;
    }
    int flag = 1;
    for (int var : path[st]) {
        if (var == ed || visit_start_to_end[var]) {
            flag = 0;
            continue;
        }
        visit_start_to_end[var] = 1;
        if (start_to_end(var, ed)) {
            visit_start_to_end[var] = 0;
        }
        else flag = 0;
    }
    return flag;
}

int end_to_start(int st, int ed) {
    if (path[st].size() == 0 || st == ed) {
        return 1;
    }
    int flag = 1;
    for (int var : path[st]) {
        if (var == ed || visit_end_to_start[var]) {
            flag = 0;
            continue;
        }
        visit_end_to_start[var] = 1;
        if (end_to_start(var, ed)) {
            visit_end_to_start[var] = 0;
        }
        else flag = 0;
    }
    return flag;
}

int check() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (i == st_point || i == end_point) continue;
        if (visit_end_to_start[i] && visit_start_to_end[i]) cnt++;
    }
    return cnt;
}

int main() {
    input();
    start_to_end(st_point, end_point);

    end_to_start(end_point, st_point);
    cout << check();
    return 0;
}
