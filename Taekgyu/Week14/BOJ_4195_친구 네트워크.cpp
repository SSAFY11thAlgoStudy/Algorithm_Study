#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<unordered_map>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;

int T;
int F;
// 몇명의 사람이 친구가 되었는지 친구수 저장 
unordered_map<string, int>nm;
// UnionFind Arr 역할
unordered_map<string, string>um;

void init() {
	um.clear();
	nm.clear();
}

string find(string tar) {
	if (tar == um[tar])return tar;
	string ret = find(um[tar]);
	um[tar] = ret;
	return ret;
}

void setUnion(string str1, string str2) {
	string t1 = find(str1);
	string t2 = find(str2);
	if (t1 == t2)return;

	// t2는 t1의 친구가 되었다
	um[t2] = t1;
	// 친구가 되었다면 친구수 더해서 저장
	nm[t1] += nm[t2];

}

void input() {
	cin >> F;
	for (int i = 0; i < F; i++)
	{
		string str1, str2 = " ";
		cin >> str1 >> str2;
		// 새롭게 나온친구라면 Arr에 추가
		// find하기 전 그 친구는 혼자 이므로 1로 저장
		if (um.count(str1) == 0) {
			um[str1] = str1;
			nm[str1] = 1;
		}
		if (um.count(str2) == 0) {
			um[str2] = str2;
			nm[str2] = 1;
		}

		setUnion(str1, str2);
		// endl 사용하면 시간초과
		// '\n'이 훨씬 빠르다
		cout << nm[find(str1)] << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		init();
		input();
	}

	return 0;
}