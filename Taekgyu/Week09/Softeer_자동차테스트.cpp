#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;

int n;
int q;
int target;
vector<int>cv;
vector<int>tv;


void input() {
	cin >> n >> q;
	for (int i = 0; i < n; i++)
	{
		int Num = 0;
		cin >> Num;
		cv.push_back(Num);
	}
	for (int i = 0; i < q; i++)
	{
		int Num = 0;
		cin >> Num;
		tv.push_back(Num);
	}
	sort(cv.begin(), cv.end());
}

int bs(int st, int en) {
	int mid = 0;

	while (st <= en) {
		mid = (st + en) / 2;

		if (cv[mid] == target) {
			return mid;
		}

		if (cv[mid] > target) {
			en = mid - 1;
		}
		else {
			st = mid + 1;
		}
	}
	return -1;
}

int main() {

	input();
	for (int i = 0; i < q; i++)
	{
		target = tv[i];

		int ret = bs(0, n - 1);

		if (ret == -1) {
			cout << 0 << endl;
		}
		else {
			int lowCnt = ret;
			int highCnt = n - 1 - ret;
			cout << lowCnt * highCnt << endl;
		}
	}
	return 0;
}