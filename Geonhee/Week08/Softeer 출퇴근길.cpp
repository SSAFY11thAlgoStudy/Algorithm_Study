#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, m, s, t;
vector<int> a[100001];
vector<int> b[100001];
bool visited1[100001];
bool visited2[100001];
bool visited3[100001];
bool visited4[100001];

//출근길
void go(int x) {
    //방문했으면 return
    if (visited1[x]) return;
    //방문안했으면 방문체크
    visited1[x] = true;
    //다음 길로
    for (auto i : a[x]) {
        go(i);
    }
}
//퇴근길
void leave(int x) {
    if (visited2[x]) return;
    visited2[x] = true;
    for (auto i : a[x]) {
        leave(i);
    }
}
//출근길 반대로
void reverse_go(int x) {
    if (visited3[x]) return;
    visited3[x] = true;
    for (auto i : b[x]) {
        reverse_go(i);
    }

}
//퇴근길 반대로
void reverse_leave(int x) {
    if (visited4[x]) return;
    visited4[x] = true;
    for (auto i : b[x]) {
        reverse_leave(i);
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        b[v].push_back(u);
    }
    cin >> s >> t;
    //회사 한번만 가야하므로 true
    visited1[t] = true;
    //집 한번만 가야하므로 true
    visited2[s] = true;
    //출근!
    go(s);
    //퇴근!
    leave(t);
    //출근길 반대로 확인
    reverse_go(s);
    //퇴근길 반대로 확인
    reverse_leave(t);
    int res = 0;
    for (int i = 1; i <= n; i++) {
        //출발점과 끝 점 빼고
        if (i == s || i == t) continue;
        //4개가 다 겹치면 모두 방문 이므로 res++
        if (visited1[i] && visited2[i] && visited3[i] && visited4[i]) res++;
    }
    cout << res;
    return 0;
}