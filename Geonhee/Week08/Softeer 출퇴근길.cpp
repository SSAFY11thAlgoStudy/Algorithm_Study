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

//��ٱ�
void go(int x) {
    //�湮������ return
    if (visited1[x]) return;
    //�湮�������� �湮üũ
    visited1[x] = true;
    //���� ���
    for (auto i : a[x]) {
        go(i);
    }
}
//��ٱ�
void leave(int x) {
    if (visited2[x]) return;
    visited2[x] = true;
    for (auto i : a[x]) {
        leave(i);
    }
}
//��ٱ� �ݴ��
void reverse_go(int x) {
    if (visited3[x]) return;
    visited3[x] = true;
    for (auto i : b[x]) {
        reverse_go(i);
    }

}
//��ٱ� �ݴ��
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
    //ȸ�� �ѹ��� �����ϹǷ� true
    visited1[t] = true;
    //�� �ѹ��� �����ϹǷ� true
    visited2[s] = true;
    //���!
    go(s);
    //���!
    leave(t);
    //��ٱ� �ݴ�� Ȯ��
    reverse_go(s);
    //��ٱ� �ݴ�� Ȯ��
    reverse_leave(t);
    int res = 0;
    for (int i = 1; i <= n; i++) {
        //������� �� �� ����
        if (i == s || i == t) continue;
        //4���� �� ��ġ�� ��� �湮 �̹Ƿ� res++
        if (visited1[i] && visited2[i] && visited3[i] && visited4[i]) res++;
    }
    cout << res;
    return 0;
}