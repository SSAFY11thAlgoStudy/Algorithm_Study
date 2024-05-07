#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <vector>
#include<algorithm>

using namespace std;

int N;

int pop[10001];

//체크한 마을인지 확인
bool vis[10001];
vector<int> v[10001];

//0 : 일반마을 일 때 서브트리의 인구수
//1 : 우수마을 일 때 서브트리의 인구수
int dp[10001][2];

void input() {

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> pop[i];
    }

    for (int i = 1; i < N; i++) {
        int t1, t2;
        cin >> t1 >> t2;
        //방향이 없이 연결되어있기에 양쪽으로 다 넣어 줌
        v[t1].push_back(t2);
        v[t2].push_back(t1);
    }
}

void dfs(int now) {
    //방문했으니 true
    vis[now] = true;

    //일반 마을이면 0
    dp[now][0] = 0;
    //우수 마을이면 인구수 더해 넣기
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
    //1번 마을부터 확인해서 내려가기
    dfs(1);
    cout << max(dp[1][0], dp[1][1]);
    return 0;
}