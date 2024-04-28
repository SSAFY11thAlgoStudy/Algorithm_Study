#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int T, N, M;
int a1[1001];
int a2[1001];

vector<int> v1;
vector<int> v2;
long long result;

void input() {
	cin >> T;

	cin >> N;
	for (int i = 0; i < N; i++){
		cin >> a1[i];
	}

	cin >> M;
	for (int i = 0; i < M; i++){
		cin >> a2[i];
	}

	for (int i = 0; i < N; i++){
		int temp = a1[i];
		v1.push_back(temp);
		for (int j = i+1; j < N; j++){
			temp += a1[j];
			v1.push_back(temp);
		}
	}

	for (int i = 0; i < M; i++) {
		int temp = a2[i];
		v2.push_back(temp);
		for (int j = i + 1; j < M; j++) {
			temp += a2[j];
			v2.push_back(temp);
		}
	}
	sort(v2.begin(), v2.end());
}

void solve() {
	for (int i = 0; i < v1.size(); i++){
		int tar = T - v1[i];

		int lo = lower_bound(v2.begin(), v2.end(), tar) - v2.begin();
		int hi = upper_bound(v2.begin(), v2.end(), tar) - v2.begin();
		result += (hi - lo);
	}
}

int main() {

	freopen("sample.txt", "r", stdin);
	input();
	solve();
	
	cout << result;
	return 0;
}