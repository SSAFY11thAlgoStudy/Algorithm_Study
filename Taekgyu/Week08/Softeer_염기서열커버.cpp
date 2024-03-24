#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;

// ó���� �� ������ �������� �Է¼������ �ʿ��⼭���� ����
// ������ �ݷ� ���̽� ����
// ���� ��Ž���� ǰ
// �ٵ� �ð��ʰ���
// ����, ������ ���������
// ������ �Ʒ���, �Ʒ��� ����, �߰����� �����鼭, �߰����� ������ �ʿ��⼭���� ����
// �ٵ� �쿬ġ�ʰ� ���䳪��;;
vector<string>sv;
int N, M;
char MAP[15][20];
int visited[15];
string set;
int Min = 21e8;

void input() {

	cin >> N >> M;
	// �ʱ⿡ ���Ϳ� M���̸�ŭ�� ���ϵ� ī��� �ʱ�ȭ �Ѵ�
	for (int i = 0; i < M; i++)
	{
		set = set + ".";
	}
	sv.push_back(set);
	// �Է¹��� ���⼭�� MAP�� ����
	for (int i = 0; i < N; i++)
	{
		string str1;
		cin >> str1;
		for (int j = 0; j < M; j++)
		{
			MAP[i][j] = str1[j];
		}
	}
}


void makeSV(string str) {

	// ���� ���ڿ����� Ȯ���Ѵ�
	// ���� ���ڿ��߿� ���ĺ��� � �ִ��� �����Ѵ� An
	int An = 0;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] != '.') {
			An++;
		}
	}

	// ���� ������ ���Ͽ����� �ش� ������ ���� �ִٸ� ����
	// �ƴ϶�� ���Ӱ� ���Ϳ� �߰��Ѵ�.
	int flag = 0;
	for (int i = 0; i < sv.size(); i++)
	{
		// An������ ������Ű���� Ȯ��
		int AnCnt = 0;
		for (int j = 0; j < M; j++) {
			// ���ϰ��� �ϴ� ������ ���ϵ�ī���̰ų�
			// ������ ������ ���ٸ� AnCnt ����
			if (str[j] != '.') {
				if (sv[i][j] == '.' || sv[i][j] == str[j]) {
					AnCnt++;
				}
			}
		}
		// ������ �����Ѵٸ�
		if (An == AnCnt) {
			flag = 1;
			//���� sv��Ʈ������ str���� ���ĺ��� ��ģ������ �����Ѵ�.
			for (int k = 0; k < M; k++)
			{
				if (sv[i][k] == '.' && str[k] != '.') {
					sv[i][k] = str[k];
				}
			}
			break;
		}
	}
	// ������ �ִ� ��Ʈ���� ���� ���� ���
	// ���Ϳ� ��Ʈ���� ���Ӱ� �߰��Ѵ�
	if (flag == 0) {
		sv.push_back(str);
	}
}

int main() {
	//freopen("sample_input.txt", "r", stdin);
	input();

	for (int i = 0; i < N; i++)
	{
		// ������ �Ʒ��� �ʿ��⼭���� ������
		if (i == 0) {
			for (int j = 0; j < N; j++)
			{
				string str = "";
				for (int k = 0; k < M; k++)
				{
					str += MAP[j][k];
				}
				// MAP�� ���ٸ��� ������ ����� makeSV �Լ��� ����.
				makeSV(str);
			}
			// �� ����� ���� ������ �ּ� ����� �����Ѵ�.
			int a = sv.size();
			Min = min(Min, a);
			sv.clear();
		}
		// �Ʒ��� ���� �ʿ��⼭���� ������
		else if (i == N - 1) {
			for (int j = N - 1; j >= 0; j--)
			{
				string str = "";
				for (int k = 0; k < M; k++)
				{
					str += MAP[j][k];
				}
				makeSV(str);
			}
			int a = sv.size();
			Min = min(Min, a);
			sv.clear();
		}
		// �߰����� �ʿ��⼭���� ������
		else {
			for (int j = i; j < N; j++)
			{
				string str = "";
				for (int k = 0; k < M; k++)
				{
					str += MAP[j][k];
				}
				makeSV(str);
			}
			for (int j = i - 1; j >= 0; j--)
			{
				string str = "";
				for (int k = 0; k < M; k++)
				{
					str += MAP[j][k];
				}
				makeSV(str);
			}
			int a = sv.size();
			Min = min(Min, a);
			sv.clear();


			for (int j = i - 1; j >= 0; j--)
			{
				string str = "";
				for (int k = 0; k < M; k++)
				{
					str += MAP[j][k];
				}
				makeSV(str);
			}
			for (int j = i; j < N; j++)
			{
				string str = "";
				for (int k = 0; k < M; k++)
				{
					str += MAP[j][k];
				}
				makeSV(str);
			}
			a = sv.size();
			Min = min(Min, a);
			sv.clear();


			for (int j = 0; j <= i; j++)
			{
				string str = "";
				for (int k = 0; k < M; k++)
				{
					str += MAP[j][k];
				}
				makeSV(str);
			}
			for (int j = N - 1; j > i; j--)
			{
				string str = "";
				for (int k = 0; k < M; k++)
				{
					str += MAP[j][k];
				}
				makeSV(str);
			}
			a = sv.size();
			Min = min(Min, a);
			sv.clear();
		}
	}
	cout << Min;
	return 0;
}