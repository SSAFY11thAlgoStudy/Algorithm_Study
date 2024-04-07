#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;

struct threeOil
{
	long long f1;
	long long f2;
	long long Sum;
};

int N;
vector<long long>v;
vector<threeOil> li[10000];
vector<long long>ansv;

int i = 0;
long long mid = 0;
long long mid_extra = 0;
long long Max = 3000000001;
long long ansS;
long long ansE;

void input() {

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		long long Num = 0;
		cin >> Num;
		v.push_back(Num);
	}
	sort(v.begin(), v.end());

}

void bs(int st, int en) {

	long long Sum = v[st] + v[en];
	li[i].push_back({ v[st], v[en], Sum });

	if (en - st == 2) {
		mid = v[st + 1];

		if (mid == mid_extra) {
			for (int k = 0; k <= i; k++)
			{
				li[k][0].Sum += mid;
				if (Max >= abs(0 - li[k][0].Sum)) {
					Max = abs(0 - li[k][0].Sum);
					ansS = li[k][0].f1;
					ansE = li[k][0].f2;
				}
			}
		}
		else {
			for (int k = 0; k <= i; k++)
			{
				li[k][0].Sum += mid;
				if (mid != li[k][0].f1 && mid != li[k][0].f2 && Max >= abs(0 - li[k][0].Sum)) {
					Max = abs(0 - li[k][0].Sum);
					ansS = li[k][0].f1;
					ansE = li[k][0].f2;
				}
				li[k][0].Sum -= mid;
			}
			for (int k = 0; k <= i; k++)
			{
				li[k][0].Sum += mid_extra;
				if (mid_extra != li[k][0].f1 && mid_extra != li[k][0].f2 && Max >= abs(0 - li[k][0].Sum)) {
					Max = abs(0 - li[k][0].Sum);
					ansS = li[k][0].f1;
					ansE = li[k][0].f2;
					mid = mid_extra;
				}
			}
		}
		return;
	}
	if (Sum >= 0) {
		en = en - 1;
		long long reverSum = v[st + 1] + v[en + 1];
		i++;
		li[i].push_back({ v[st + 1], v[en + 1], reverSum });
		if ((en + 1) - (st + 1) == 2) {
			mid_extra = v[st + 2];
		}
	}
	else {
		st = st + 1;
		long long reverSum = v[st - 1] + v[en - 1];
		i++;
		li[i].push_back({ v[st - 1], v[en - 1], reverSum });
		if ((en - 1) - (st - 1) == 2) {
			mid_extra = v[st];
		}
	}
	i++;
	bs(st, en);

}

int main() {

	input();
	if (N == 3) {
		cout << v[0] << " " << v[1] << " " << v[2];
	}
	else {
		bs(0, N - 1);
		ansv.push_back(ansS);
		ansv.push_back(ansE);
		ansv.push_back(mid);
		sort(ansv.begin(), ansv.end());

		cout << ansv[0] << " " << ansv[1] << " " << ansv[2];
	}

	return 0;
}