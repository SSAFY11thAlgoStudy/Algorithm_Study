#include<iostream>
#include<unordered_map>
using namespace std;

int dA[1001];
int dB[1001];
int t, n, m;
long long int ans;
unordered_map<int, long long int>cntA;
unordered_map<int, long long int>cntB;
// dA, dB에 구간 합 저장
// cntA, cntB에 부배열 합의 개수 저장
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
	// 두 종류의 합이 t인 경우 판단
	// cnt의 최대 크기 대략 50만 -> 2번 돌리면 시간초과 
	// 한 번의 반복문으로 찾아야함!
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