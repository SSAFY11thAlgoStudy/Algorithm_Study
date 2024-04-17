#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

using namespace std;

int N;
//전체 숫자 저장하는 배열
long long num[2001];
int cnt;

void input() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> num[i];
	}
	//오름차순으로 정렬
	sort(num, num + N);
}

void solve() {
	//인덱스 0번부터 타겟 숫자로 설정, 만들 수 있는지 확인
	for (int i = 0; i < N; i++) {
		//0번부터 사용해서 
		for (int j = 0; j < N; j++) {
			//같은 수를 사용하면 안되므로 continue
			if (i == j) continue;
			// 종료조건을 위한 flag
			int flag = 0;
			// 타겟 숫자에서 2개의 수 중 하나를 뺌
			// 타겟 수 = A + B => 타겟 수 - A = B 이므로
			long long temp = num[i] - num[j];

			// 이분탐색으로 B 찾기
			int sp = 0;
			int ep = N;

			while (sp < ep) {
				int mid = (sp + ep) / 2;

				//temp - num[mid] > 0 이면 num[mid]가 커져야 하므로
				if (temp - num[mid] > 0) {
					sp = mid + 1;
				}
				//temp - num[mid] > 0 이면 num[mid]가 작아져야 하므로
				else if (temp - num[mid] < 0) {
					ep = mid;
				}
				//temp - num[mid] = 0 일 때,
				else {
					//A와 같거나 B와 같으면 안되므로 mid를 바꿔서 다시 진행
					if (j == mid || i == mid) {
						sp = mid + 1;
					}
					//예외에 안걸리는 경우 flag 바꾸고 cnt++
					else {
						cnt++;
						flag = 1;
						break;
					}
				}
			}

			if (flag == 1) {
				break;
			}
		}
	}
}

int main() {

	//freopen("sample.txt", "r", stdin);

	input();
	if (N > 2) {
		solve();
	}
	cout << cnt;

	return 0;
}