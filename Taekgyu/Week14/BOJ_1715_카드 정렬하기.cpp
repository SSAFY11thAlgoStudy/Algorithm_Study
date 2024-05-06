#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
// ���� ī�� ������ ������ ũ�Ⱑ �־�����
// �ּ��� ����� �񱳰� �ʿ����� ���϶�
struct Num
{
	int num;
	bool operator<(Num right) const {
		if (num > right.num)return true;
		if (num < right.num)return false;
		return false;
	}
};
priority_queue<Num>q;

int main() {

	int N;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int Num = 0;
		cin >> Num;
		q.push({ Num });
	}
	int Sum = 0;
	int Cnt = 0;
	long long Ans = 0;
	while (!q.empty()) {
		// pq�� Ȱ���Ͽ� ���� ���� ���� ������ ������ ��ġ
		Num front = q.top();
		q.pop();
		Sum += front.num;
		Cnt++;
		// ī�幭���� �ΰ� �̾����� ���´�
		// �� ������ ���� ���� �ٽ� pq�� �ִ´�
		if (Cnt % 2 == 0) {
			q.push({ Sum });
			// ī�� ���� ���� �� ���ؼ� ���� ����
			Ans += Sum;
			Sum = 0;
			// ���������� ī�� ������ �ϳ��� �Ǿ�����
			// pop�� ���� while�� ����
			if (q.size() == 1) {
				q.pop();
			}
		}
	}
	cout << Ans;

	return 0;
}