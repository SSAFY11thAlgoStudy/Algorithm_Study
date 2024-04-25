#include<iostream>

using namespace std;

int N;
int block[31];
//(block[N - 2] * 3) + (block[N - 2] * 2) + (block[N - 4] * 2)... + 2
int main() {
	cin >> N;

	block[0] = 1;
	block[1] = 0;
	block[2] = 3;

	for (int n = 3; n <= N; n++)
	{
		//홀수 크기의 틀은 완전히 채울수 없음
		if (n % 2 == 1) {
			block[n] = 0;
			continue;
		}
		else {
			for (int i = 2; i <= n; i += 2)
			{
				//n은 자신보다 작은 n-2의 크기를 가진 모형에서
				//n-2의 횟수와 2번의 경우를 곱한 경우의 수를 가진다.
				if (i == 2) {
					block[n] = block[n - 2] * block[2];
				}
				//자신안에 존재할수 있는 가지수 X 2의 경우를 가진다.
				else {
					block[n] += block[n - i] * 2;
				}
			}
		}
	}

	cout << block[N];//N의 고유 모양값 2
}