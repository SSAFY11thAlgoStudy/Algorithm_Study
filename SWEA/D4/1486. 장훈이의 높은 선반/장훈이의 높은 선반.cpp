#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int t,n,b;
int arr[21];
int res;

void init() {
	memset(arr, 0, sizeof(arr));
	res = 1e9;
}

void input() {
	cin >> n >> b;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
}

void dfs(int x, int s) {
	if (s >= b) {
		res = min(res, s - b);
		return;
	}
	for (int i = x; i < n; i++) {
		s += arr[i];
		dfs(i + 1, s);
		s -= arr[i];
	}
}

int main() {
	cin >> t;
	for (int tc = 0; tc < t; tc++) {
		init();
		input();
		dfs(0, 0);
		cout << "#" << tc + 1 << " " << res << "\n";
	}

}