#include<iostream>
#include<vector>

using namespace std;

vector<int>v1[100001];
vector<int>v2[100001];
bool visited1[100001];
bool visited2[100001];
bool visited3[100001];
bool visited4[100001];

// 1. S->T ����� �湮 ���
// 2. T->S ����� �湮 ���
// 3. S���� ����Ͽ� S�� �ٽ� ���ƿ� �� �ִ� ���
// 4. T���� ����Ͽ� T�� �ٽ� ���ƿ� �� �ִ� ��� 
// 3,4 ��Ȳ���� ������ �׷����� �̿��Ͽ� �Ǻ� ���� 

void dfs(int cur, bool visited[], vector<int>v[]) {
    if (visited[cur])return;
    visited[cur] = true;
    for (auto next : v[cur]) {
        dfs(next, visited, v);
    }
}

int main(int argc, char** argv)
{
    int n, m, x, y, s, e, answer = 0;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        v1[x].push_back(y);
        v2[y].push_back(x);
    }
    cin >> s >> e;

    // ��ٱ濡�� e�� 1���� �湮, ��ٱ濡�� s�� �ѹ��� �湮
    visited1[e] = true;
    visited2[s] = true;
    dfs(s, visited1, v1);
    dfs(e, visited2, v1);
    dfs(s, visited3, v2);
    dfs(e, visited4, v2);
    for (int i = 1; i <= n; i++) {
        if (visited1[i] && visited2[i] && visited3[i] && visited4[i])answer++;
    }
    cout << answer - 2;
    return 0;
}