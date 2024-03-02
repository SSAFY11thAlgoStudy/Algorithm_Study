#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace std;

int T;
// +, -, *, /
int cal[4] = { 0, };
int N;
int Num[12];
int Max = 0;
int Min = 21e8;
int DAT[11];

vector<int>v;

void init() {
	memset(DAT, 0, sizeof(DAT));
	memset(Num, 0, sizeof(Num));
	Max = -21e8;
	Min = 21e8;
}

void dfs(int now) {
	if (now == N - 1) {

		int sum = Num[0];

		for (int i = 0; i < N - 1; i++)
		{
			if (DAT[i] == 0) {
				sum += Num[i + 1];
			}
			else if (DAT[i] == 1) {
				sum -= Num[i + 1];
			}
			else if (DAT[i] == 2) {
				sum *= Num[i + 1];
			}
			else {
				sum = sum / Num[i + 1];
			}
		}
		v.push_back(sum);
		Max = max(Max, sum);
		Min = min(Min, sum);
		return;
	}

	// 사칙연산 고고
	for (int i = 0; i < 4; i++)
	{
		if (cal[i] == 0)continue;

		DAT[now] = i;
		cal[i]--;
		dfs(now + 1);
		DAT[now] = 0;
		cal[i]++;

	}
}

int main() {

	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		init();
		cin >> N;
		for (int i = 0; i < 4; i++)
		{
			cin >> cal[i];
		}
		for (int i = 0; i < N; i++)
		{
			cin >> Num[i];
		}
		dfs(0);

		int ans = Max - Min;
		cout << "#" << tc << " " << ans << endl;
	}

	return 0;
}