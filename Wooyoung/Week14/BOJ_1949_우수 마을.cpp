#include<iostream>
#include<vector>
using namespace std;

int n;
int population[10001];

vector<int>trees[10001];
bool visited[10001];
// 1번을 루트로, 각 마을에 대해 초기값 설정 (아래 2가지)
	// 리프 노드까지 모두 값 설정 후 자신의 부모 노드를 채워가며 1번 노드까지 탐색
// 현재 마을이 우수 마을인 경우
// 현재 마을이 우수 마을이 아닌 경우
int cur_best[10001];
int cur_normal[10001];
void func(int par) {
	visited[par] = true;
	cur_best[par] = population[par];
	for (int i = 0; i < trees[par].size(); i++) {
		int child = trees[par][i];
		if (visited[child])continue;
		func(child);
		cur_best[par] += cur_normal[child];
		cur_normal[par] += max(cur_best[child], cur_normal[child]);
	}
}


int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> population[i];
	}
	for (int i = 0; i < n - 1; i++) {
		int s, e;
		cin >> s >> e;
		trees[s].push_back(e);
		trees[e].push_back(s);
	}
	func(1);
	cout << max(cur_best[1], cur_normal[1]);
	return 0;
}