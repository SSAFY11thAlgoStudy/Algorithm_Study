#include<iostream>
#include<vector>
#include<queue>
using namespace std;

vector<int>v[32001];
int cnt[32001];
int n, m;
queue<int>ans;

void func() {

	queue<int>q;
	for (int i = 1; i <= n; i++) {
		if (cnt[i] == 0) {
			q.push(i);
			ans.push(i);
		}
	}
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		for (auto p : v[now]) {
			cnt[p]--;
			if (cnt[p] == 0) {
				q.push(p);
				ans.push(p);
			}
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		v[a].push_back(b);
		cnt[b]++;
	}
	func();
	while (!ans.empty()) {
		cout << ans.front() << " ";
		ans.pop();
	}

	return 0;
}