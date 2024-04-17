#include<iostream>
#include <algorithm>
using namespace std;

long long n;
long long num[2001];
long long cnt;

bool bs(long long tar, int idx) {
	long long st = 0;
	long long en = n - 1;
	long long mid = 0;

	while (st < en) {
		mid = num[st] + num[en];
		//두 수의 합과 어떤 수가 같은데
		if (mid == tar) {
			//idx가 모두 달라야 true를 return
			// ex) 0,0,0,3이면 안됨 
			if (st != idx && en != idx) return true;
			//st와 같다면 st값 1키우기
			else if (st == idx) st += 1;
			//ed과 같다면 en값 1줄이기
			else en -= 1;
		}
		//어떤 수보다 크면 더 작은 값에서 탐색하기 위해 en값 -1
		else if (mid > tar) en -= 1;
		//어떤 수 보다 작으면 더 큰 값에서 탐색하기 위해 st값 +1
		else st += 1;
	}
	//찾지 못하고 끝났다면 false return
	return false;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> num[i];
	}
	//이분탐색을 위해 정렬
	sort(num, num + n);
	//num[i]부터 확인 인덱스가 겹치면 안되므로 i도 같이
	for (int i = 0; i < n; i++) {
		bool check = bs(num[i], i);
		//합이 구해지면 최종 갯수에 더해주기
		if (check)cnt++;

	}
	cout << cnt;
	return 0;
}