#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <vector>
#include<algorithm>

using namespace std;

int N;

int pop[10001];

//üũ�� �������� Ȯ��
bool vis[10001];
vector<int> v[10001];

//0 : �Ϲݸ��� �� �� ����Ʈ���� �α���
//1 : ������� �� �� ����Ʈ���� �α���
int dp[10001][2];

void input() {

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> pop[i];
    }

    for (int i = 1; i < N; i++) {
        int t1, t2;
        cin >> t1 >> t2;
        //������ ���� ����Ǿ��ֱ⿡ �������� �� �־� ��
        v[t1].push_back(t2);
        v[t2].push_back(t1);
    }
}

void dfs(int now) {
    //�湮������ true
    vis[now] = true;

    //�Ϲ� �����̸� 0
    dp[now][0] = 0;
    //��� �����̸� �α��� ���� �ֱ�
    dp[now][1] = pop[now];

    for (int i = 0; i < v[now].size(); i++) {
        int next = v[now][i];
        if (vis[next]) continue;
        dfs(next);

        dp[now][0] += max(dp[next][0], dp[next][1]);
        dp[now][1] += dp[next][0];
    }
}

int main() {

    freopen("sample.txt", "r", stdin);

    input();
    //1�� �������� Ȯ���ؼ� ��������
    dfs(1);
    cout << max(dp[1][0], dp[1][1]);
    return 0;
}