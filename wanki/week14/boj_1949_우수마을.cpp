// 백준 1949번 : 우수 마을
#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> v[10001];
int population[10001];
int dp[10001][2]; //0인 경우 우수 마을X
//1인 경우 우수 마을
bool visited[10001];


void input() {
    cin >> N;
    //입력에 node가 0이 없어서 1부터 시작함
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
    dp[node][0] = 0; // 해당 노드가 우수 마을이 아닐 경우
    dp[node][1] = population[node]; // 해당 노드가 우수 마을일 경우

    for (int town : v[node]) {
        if (visited[town])continue; //방문했으면 continue
        dfs(town);
        //인접마을에 우수마을인경우와 아닌경우중 인구수가 많은 것은 저장
        dp[node][0] += max(dp[town][0], dp[town][1]);
        //본인이 우수마을인 경우 옆에는 우수마을이 있으면 안됨
        dp[node][1] += dp[town][0];
    }
}

int main() {
    input();
    dfs(1);
    cout << max(dp[1][0], dp[1][1]);
    return 0;
}