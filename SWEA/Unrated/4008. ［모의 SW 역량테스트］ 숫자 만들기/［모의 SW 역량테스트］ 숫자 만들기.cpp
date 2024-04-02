#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int t,n;
int op[4];
int num[13];
int maxres;
int minres;

void init() {
	memset(op, 0, sizeof(op));
	memset(num, 0, sizeof(num));
	maxres = -21e8;
	minres = 21e8;
}

void input() {
	cin >> n;
	for (int i = 0; i < 4; i++) cin >> op[i];
	for (int i = 0; i < n; i++) cin >> num[i];
}

void dfs(int x, int plus, int sub, int mul, int div,int cnt) {
	if (cnt == n) {
		maxres = max(maxres, x);
		minres = min(minres, x);
		return;
	}
	if (plus) dfs(x + num[cnt], plus - 1, sub, mul, div, cnt + 1);
	if (sub) dfs(x - num[cnt], plus, sub - 1, mul, div, cnt + 1);
	if (mul) dfs(x * num[cnt], plus, sub, mul - 1, div, cnt + 1);
	if (num[cnt] > 0 && div) dfs(x / num[cnt], plus, sub, mul, div - 1, cnt + 1);
}

int main() {
	cin >> t;
	for (int tc = 0; tc < t; tc++) {
		init();
		input();
		dfs(num[0], op[0], op[1], op[2], op[3],1);
		cout << "#" << tc + 1 << " " << maxres - minres << "\n";
	}

}