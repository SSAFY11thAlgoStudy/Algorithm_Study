#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int N, M;
vector<int> v[32002];
bool vis[32002];
queue<int> q;

void dfs(int num) {
	if (vis[num] == true) return;

	for (int i = 0; i < v[num].size(); i++) {
		dfs(v[num][i]);
	}

	cout << num << " ";
	vis[num] = true;
}

int main() {

	cin >> N >> M;

	//벡터에 저장
	for (int i = 0; i < M; i++) {
		int t1, t2;
		cin >> t1 >> t2;
		v[t2].push_back(t1);
	}

	//처음부터 끝까지 탐색
	for (int i = 1; i <= N; i++) {
		//만약 그 수보다 앞에 오는 수가 없다면 바로 출력
		if (v[i].size() == 0) {
			cout << i << " ";
			vis[i] = true;
		}
		else {
			//아니면 큐에 저장
			q.push(i);
		}
	}

	while (!q.empty()) {
		int num = q.front();
		q.pop();
		dfs(num);
	}

	return 0;
}