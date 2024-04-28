#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

// 점화식 찾는게 이 문제의 전부...
// 일단 N이 홀수면 타일로 딱 맞게 채울수가 없다 => 경우의 수가 없다 => 0출력
// N이 2일때 3가지인것 확인
// 길이가 짝수여야 타일로 채울수 있다

// f(2) = 3 * f(0)
// f(4) = 3 * f(2) + 2 * f(0)
// f(6) = 3 * f(4) + 2 * f(2) + 2 * f(0)
// f(N) = 3 * f(N-2) + 2 * f(N-4) + ... + 2 * f(0)  

int N;

int func(int Num) {

	int Cnt = 0;
	int totalAns = 0;

	if (Num == 0) {
		return 1;
	}
	for (int i = Num - 2; i >= 0; i -= 2)
	{
		if (i == Num - 2) {
			Cnt = 3 * func(i);
		}
		else {
			Cnt = 2 * func(i);
		}
		totalAns += Cnt;
	}
	return totalAns;
}

int main() {

	cin >> N;
	if (N % 2 == 1) {
		cout << 0;
	}
	else {
		int Ans = func(N);
		cout << Ans;
	}
	return 0;
}