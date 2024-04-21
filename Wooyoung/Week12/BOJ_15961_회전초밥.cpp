#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

int n, d, k, c;
int ans;
int kinds_cnt[3001];
vector<int>kinds;

void func() {
	queue<int>q;
	int cur_cnt = 0;
	for (int i = 0; i < n + k - 1; i++) {
		int temp_i = i;
		if (i >= n) {
			temp_i = i - n;
		}
		q.push(kinds[temp_i]);
		kinds_cnt[kinds[temp_i]]++;
		if (kinds_cnt[kinds[temp_i]] == 1)cur_cnt++;
		if (i >= k - 1) {
			if (kinds_cnt[c] == 0) {
				ans = max(ans, cur_cnt + 1);
			}
			else {
				ans = max(ans, cur_cnt);
			}
			kinds_cnt[q.front()]--;
			if (kinds_cnt[q.front()] == 0) {
				cur_cnt--;
			}
			q.pop();
		}
	}

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> d >> k >> c;
	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		kinds.push_back(num);
	}
	func();
	cout << ans;
	return 0;
}