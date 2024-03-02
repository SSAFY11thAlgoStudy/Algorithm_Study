#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

int N;
int op[4];
int num[13];
int mmax, mmin;

void init() {
	mmax = -21e8;
	mmin = 21e8;
}

void input() {
	cin >> N;

	for (int i = 0; i < 4; i++) {
		cin >> op[i];
	}

	for (int i = 0; i < N; i++) {
		cin >> num[i];
	}
}

int cal(int ind_c, int sum, int ind_n) {

	if (ind_c == 0) {
		sum += num[ind_n];
	}
	else if (ind_c == 1) {
		sum -= num[ind_n];
	}
	else if (ind_c == 2) {
		sum *= num[ind_n];
	}
	else {
		sum /= num[ind_n];
	}

	return sum;
}

void solve(int level, int sum) {
	if (level == N - 1) {
		if (sum > mmax) {
			mmax = sum;
		}

		if (sum < mmin) {
			mmin = sum;
		}
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (op[i] == 0) continue;

		int res = cal(i, sum, level + 1);

		op[i]--;
		solve(level + 1, res);
		op[i]++;
	}
}

int main() {

	//freopen("sample.txt", "r", stdin);

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		init();
		input();
		int sum = num[0];
		solve(0, sum);
		cout << "#" << tc << " " << mmax - mmin << "\n";
	}

	return 0;
}