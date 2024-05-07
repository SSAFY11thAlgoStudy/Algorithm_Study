// 1 3 7 10
// 2 4 8 9
// -> 1 2 3 4 7 8 9 10

// 10��, 20��, 40�� -> 10�� + 20�� -> 30�� + 40��
// -> 30 + 30 + 40 = 100

// ��ġ�� ������ ���� ���� �޶���
// ����, �����͵� ���� ���ľ���

// N�� 100000�� ��, ��� 1000�� ���
// 1000 + 1000
// 1, 2, 3 -> (1+2) + (1+2+3)
// 1000, 1000, ... -> (1000+1000) + (1000+1000+1000+...) +(1000x9999) -> 999��?

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