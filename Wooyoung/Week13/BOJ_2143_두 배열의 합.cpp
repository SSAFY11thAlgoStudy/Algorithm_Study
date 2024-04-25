#include<iostream>
#include<unordered_map>
using namespace std;

int dA[1001];
int dB[1001];
int t, n, m;
long long int ans;
unordered_map<int, long long int>cntA;
unordered_map<int, long long int>cntB;
// dA, dB�� ���� �� ����
// cntA, cntB�� �ι迭 ���� ���� ����
void func() {
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			cntA[dA[j] - dA[i - 1]] += 1;
		}
	}
	for (int i = 1; i <= m; i++) {
		for (int j = i; j <= m; j++) {
			cntB[dB[j] - dB[i - 1]] += 1;
		}
	}
	// �� ������ ���� t�� ��� �Ǵ�
	// cnt�� �ִ� ũ�� �뷫 50�� -> 2�� ������ �ð��ʰ� 
	// �� ���� �ݺ������� ã�ƾ���!
	for (auto p : cntA) {
		if (cntB.count(t - p.first) != 0) {
			ans += (cntB[t - p.first] * p.second);
		}
	}
}

int main() {
	cin >> t >> n;
	for (int i = 1; i <= n; i++) {
		int num;
		cin >> num;
		dA[i] = dA[i - 1] + num;
	}
	cin >> m;
	for (int i = 1; i <= m; i++) {
		int num;
		cin >> num;
		dB[i] = dB[i - 1] + num;
	}
	func();
	cout << ans;
	return 0;
}