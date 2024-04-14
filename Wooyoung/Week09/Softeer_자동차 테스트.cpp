#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_map>
using namespace std;

int n, q;
vector<int>fuels;
unordered_map<int, int>ans;
int main() {
	cin >> n >> q;
	for (int i = 0; i < n; i++) {
		int fuel;
		cin >> fuel;
		fuels.push_back(fuel);
	}
	sort(fuels.begin(), fuels.end());

	for (int i = 0; i < n; i++) {
		int s = i;
		int b = n - (1 + i);
		ans[fuels[i]] = s * b;
	}
	for (int i = 0; i < q; i++) {
		int mi;
		cin >> mi;
		if (ans.count(mi) == 0) {
			cout << 0 << "\n";
		}
		else {
			cout << ans[mi] << "\n";
		}
	}
	return 0;
}