// 1 3 7 10
// 2 4 8 9
// -> 1 2 3 4 7 8 9 10

// 10장, 20장, 40장 -> 10장 + 20장 -> 30장 + 40장
// -> 30 + 30 + 40 = 100

// 합치는 순서에 따라 값이 달라짐
// 따라서, 작은것들 먼저 합쳐야함

// N이 100000일 때, 모두 1000인 경우
// 1000 + 1000
// 1, 2, 3 -> (1+2) + (1+2+3)
// 1000, 1000, ... -> (1000+1000) + (1000+1000+1000+...) +(1000x9999) -> 999억?

#include<iostream>
#include<queue>
using namespace std;

int n;
long long int ans;
priority_queue<long long int, vector<long long int>, greater<long long int>>pq;
void func() {
	long long int sum = 0;
	int cnt = 0;
	while (!pq.empty()) {
		//ans += pq.top();
		sum += pq.top();
		cnt++;
		if (cnt == 2) {
			pq.push(sum);
			ans += sum;
			cnt = 0;
			sum = 0;
		}
		pq.pop();
	}
	cout << ans;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		pq.push(num);
	}
	func();
	return 0;
}