// ���� 1949�� : ��� ����
#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> v[10001];
int population[10001];
int dp[10001][2]; //0�� ��� ��� ����X
//1�� ��� ��� ����
bool visited[10001];


void input() {
    cin >> N;
    //�Է¿� node�� 0�� ��� 1���� ������
    for (int i = 1; i <= N; i++) {
        cin >> population[i];
    }
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
}

void dfs(int node) {
    visited[node] = true;
    dp[node][0] = 0; // �ش� ��尡 ��� ������ �ƴ� ���
    dp[node][1] = population[node]; // �ش� ��尡 ��� ������ ���

    for (int town : v[node]) {
        if (visited[town])continue; //�湮������ continue
        dfs(town);
        //���������� ��������ΰ��� �ƴѰ���� �α����� ���� ���� ����
        dp[node][0] += max(dp[town][0], dp[town][1]);
        //������ ��������� ��� ������ ��������� ������ �ȵ�
        dp[node][1] += dp[town][0];
    }
}

int main() {
    input();
    dfs(1);
    cout << max(dp[1][0], dp[1][1]);
    return 0;
}