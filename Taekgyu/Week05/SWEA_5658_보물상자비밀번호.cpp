#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>

using namespace std;

int T;
int N;
int K;
string str;
vector<string> v;// �ߺ� �Ű���� ��´�. ������ �Ұ�
vector<string> parsedVect; // �ߺ� ����

bool compare(string a, string b) {

	return a > b;//��������
}

void init() {
	v.clear();
	parsedVect.clear();
}

void input() {
	cin >> N >> K;
	cin >> str;
}

int solve() {
	// numLength ��ŭ ���� ó���� �Ȱ���
	// �� �����ʿ䰡 ����
	int numLength = N / 4;
	string temp = "";
	for (int i = 0; i < numLength; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			v.push_back(str.substr(j * numLength, numLength));
		}
		temp = str.substr(1, str.size() - 1) + str[0];
		str = temp;
	}

	sort(v.begin(), v.end(), compare);
	// sort(arr, arr + N, compare);
	for (int i = 0; i < v.size(); i++)
	{
		if (i == 0 || v[i] != v[i - 1]) {
			parsedVect.push_back(v[i]);
		}
	}

	return stoi(parsedVect[K - 1], nullptr, 16);
}

int main() {

	//freopen("sample_input.txt", "r", stdin);
	cin >> T;
	int ans = 0;
	for (int tc = 1; tc <= T; tc++)
	{
		init();
		input();
		ans = solve();
		cout << "#" << tc << " " << ans << endl;
	}

	return 0;
}