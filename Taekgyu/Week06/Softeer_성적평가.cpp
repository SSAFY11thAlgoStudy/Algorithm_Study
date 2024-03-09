#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

// ����ü ���� 
// ���� �л���ȣ ���� ������ ����
struct sd
{
	int score;
	int idx;
	int top;
};

// ������ �����ϱ� ���� ���� ��������
bool compare(sd left, sd right) {
	if (left.score > right.score)return true;
	if (left.score < right.score)return false;
	return false;
}

// ����� ���� �л���ȣ ��������
bool com(sd left, sd right) {
	if (left.idx < right.idx)return true;
	if (left.idx > right.idx)return false;
	return false;
}

// 0,1,2�� �ε��� = ��ȸ ��� ����
// 3�� �ε��� = �� ���� �ջ� ����
vector<sd>sv[4];

int N;

void input() {
	cin >> N;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int score = 0;
			cin >> score;
			sv[i].push_back({ score,j,0 });
		}
	}

	// �հ踦 ������ �ε��� �ʱ�ȭ
	for (int i = 0; i < N; i++)
	{
		sv[3].push_back({ 0,i,0 });
	}

	// 3�� ��ȸ ������ ���� ����
	for (int j = 0; j < N; j++)
	{
		sv[3][j].score = sv[0][j].score + sv[1][j].score + sv[2][j].score;
	}
}

void func() {

	// ������ ū ������� ����
	for (int i = 0; i < 4; i++)
	{
		sort(sv[i].begin(), sv[i].end(), compare);
	}
	// ������ ū ������� ������ �ű��
	for (int i = 0; i < 4; i++)
	{
		int k = 1;
		int cnt = 0;
		for (int j = 1; j < N; j++)
		{
			if (sv[i][j - 1].score == sv[i][j].score) {
				sv[i][j - 1].top = k;
				sv[i][j].top = k;
				cnt++;
			}
			else {
				if (sv[i][j - 1].top == 0) {
					sv[i][j - 1].top = k;
				}
				k += cnt + 1;
				cnt = 0;
				sv[i][j].top = k;
			}
		}
	}

	// ��¿� �°� �л� ������� �ٽ� ����
	for (int i = 0; i < 4; i++)
	{
		sort(sv[i].begin(), sv[i].end(), com);
	}
}

int main() {

	input();
	func();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << sv[i][j].top << " ";
		}cout << endl;
	}

	return 0;
}