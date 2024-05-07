#include<iostream>
#include<queue>
#include<vector>
using namespace std;

priority_queue<int, vector<int>, greater<>>pq;

int N, result = 0;
void input() {
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int num;
		cin >> num;
		pq.push(num);
	}
}

void solve() {
	int sum = pq.top();
	pq.pop();
	sum += pq.top();
	pq.pop();
	pq.push(sum);
	result += sum;
}

int main() {
	input();

	while (pq.size() != 1) {
		solve();
	}
	cout << result;

	return 0;
}