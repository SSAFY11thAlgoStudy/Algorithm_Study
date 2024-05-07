#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
// 숫자 카드 묶음의 각각의 크기가 주어진다
// 최소한 몇번의 비교가 필요한지 구하라
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
		// pq를 활용하여 가장 작은 수의 묶음이 앞으로 위치
		Num front = q.top();
		q.pop();
		Sum += front.num;
		Cnt++;
		// 카드묶음을 두개 뽑았을때 섞는다
		// 두 묶음을 더한 값을 다시 pq에 넣는다
		if (Cnt % 2 == 0) {
			q.push({ Sum });
			// 카드 묶음 섞은 값 더해서 정답 갱신
			Ans += Sum;
			Sum = 0;
			// 마지막으로 카드 묶음이 하나가 되었을때
			// pop을 통해 while문 종료
			if (q.size() == 1) {
				q.pop();
			}
		}
	}
	cout << Ans;

	return 0;
}