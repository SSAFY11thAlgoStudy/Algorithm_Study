#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;

int N;
vector<long long>v;
int ans;
int SumNum;

bool tp(int st, int en, int tIdx) {

	while (st <= en) {

		// 타겟은 제외하고 생각한다
		if (st == tIdx || en == tIdx) {
			if (st == tIdx)st++;
			if (en == tIdx)en--;
		}

		// 시작점과 종료점은 겹치지 않으며
		// 시작 + 끝 합이 타겟이라면 true  
		if (st != en && v[st] + v[en] == SumNum) {
			return true;
		}

		// 합이 타겟보다 크다면 끝점 땡겨오기
		if (v[st] + v[en] > SumNum) {
			en = en - 1;
		}
		// 합이 타겟보다 작다면 시작점 밀기
		else {
			st = st + 1;
		}
	}
	return false;
}

int main() {

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		long long Num = 0;
		cin >> Num;
		v.push_back(Num);
	}
	// 숫자들 오름차순 정렬
	sort(v.begin(), v.end());

	for (int i = 0; i < N; i++)
	{
		// 숫자 하나를 정한다
		// 이 숫자가 두수의 합으로 이루어지는지 판단
		SumNum = v[i];
		// 투 포인터 
		if (tp(0, N - 1, i)) {
			ans++;
		}
	}
	cout << ans;

	return 0;
}