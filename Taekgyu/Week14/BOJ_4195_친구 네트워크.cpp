#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<unordered_map>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;

int T;
int F;
// ����� ����� ģ���� �Ǿ����� ģ���� ���� 
unordered_map<string, int>nm;
// UnionFind Arr ����
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

	// t2�� t1�� ģ���� �Ǿ���
	um[t2] = t1;
	// ģ���� �Ǿ��ٸ� ģ���� ���ؼ� ����
	nm[t1] += nm[t2];

}

void input() {
	cin >> F;
	for (int i = 0; i < F; i++)
	{
		string str1, str2 = " ";
		cin >> str1 >> str2;
		// ���Ӱ� ����ģ����� Arr�� �߰�
		// find�ϱ� �� �� ģ���� ȥ�� �̹Ƿ� 1�� ����
		if (um.count(str1) == 0) {
			um[str1] = str1;
			nm[str1] = 1;
		}
		if (um.count(str2) == 0) {
			um[str2] = str2;
			nm[str2] = 1;
		}

		setUnion(str1, str2);
		// endl ����ϸ� �ð��ʰ�
		// '\n'�� �ξ� ������
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