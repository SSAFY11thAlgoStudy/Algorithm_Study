#include<iostream>

using namespace std;

int n;
int dp[31];
void fillValues() {
	dp[0] = 1;
	dp[2] = 3;
	for (int i = 4; i <= 30; i++) {
		if (i % 2 != 0)continue;
		for (int j = 2; j <= i; j += 2) {
			// n-2�� 2�� ���ϴ� ����� �� �켱 ����
			if (j == 2)dp[i] = dp[i - j] * dp[2];
			// ���� 4,6,8 ���� �����ϰ� ���� 2���� �߰�
			else dp[i] += dp[i - j] * 2;
		}
	}
}
int main() {
	cin >> n;
	fillValues();
	cout << dp[n];
	return 0;
}