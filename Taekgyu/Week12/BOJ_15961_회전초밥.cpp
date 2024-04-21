#define _CRT_SECURE_NO_WARNINGS
#include<algorithm>
#include<vector>
#include<cstring>
#include<iostream>
using namespace std;
vector<int>sv;

int N;
int d;
int k;
int c;
int eat[3001];
int Max;

// 일단 회전초밥 테이블에서 
// k개를 뽑는다
// 여기서 중복이 있으면 중복제거

// 처음에 벨트에 쿠폰 초밥이 없었다면
// 무조건 +1

// k개 먹은것중에 쿠폰이 있다면 그대로
// k개 먹은것중에 쿠폰이 없다면 +1

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> d >> k >> c;
	for (int i = 0; i < N; i++)
	{
		int kind = 0;
		cin >> kind;
		sv.push_back(kind);
	}

	// 0인덱스에서 시작하는 처음 케이스
	// DAT에 추가한다
	int idx = 0;
	int count = k;
	bool eatCoupon = false;
	// 중복 개수
	int uptwo = 0;
	for (int i = 0; i < k; i++)
	{
		eat[sv[i]]++;
	}

	for (int i = 0; i < 3001; i++)
	{
		if (eat[i] >= 2) {
			uptwo += eat[i] - 1;
		}
	}
	if (eat[c] >= 1) {
		eatCoupon = true;
		Max = count - uptwo;
	}
	else {
		Max = count - uptwo + 1;
	}

	// 처음 케이스에서 
	// 앞의 요소를 제거하고
	// 뒤의 요소를 추가하는 방식으로 N번 탐색
	for (int i = 0; i < N; i++)
	{
		int idx = i + k;
		if (idx >= N) {
			idx = idx - N;
		}
		count = k;
		// 앞에 있는 초밥 DAT빼기
		// 뒤에 있는 초밥 DAT추가하기

		// 그리고 중복체크한다
		// DAT판단해서 2이상인것이 있으면 k-개수 진행 ㄱㄱ
		eat[sv[i]]--;
		// 1개를 초과하는 경우 그만큼이 uptwo이다
		if (eat[sv[i]] != 0)uptwo--;
		eat[sv[idx]]++;
		if (eat[sv[idx]] != 1)uptwo++;

		// 중복체크 = 초밥의 종류의 개수
		count -= uptwo;
		// 이벤트초밥을 먹은상태라면~
		if (eat[c] >= 1) {
			Max = max(Max, count);
		}
		else {
			Max = max(Max, count + 1);
		}
	}
	cout << Max;

	return 0;
}