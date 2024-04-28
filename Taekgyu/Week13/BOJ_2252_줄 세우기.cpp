#define _CRT_SECURE_NO_WARNINGS
#include<queue>
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

int N;
int M;
// ���� ����Ʈ ���� ����
vector<int>v[32001];
// �� �տ� ��� �ֳ�~~~~~
int DAT[32001];

int main() {

	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int fr, en = 0;
		cin >> fr >> en;
		v[fr].push_back(en);
		// en���� fr�� �տ� �����ϱ�
		// en��° DAT�� +1�� �߰��Ѵ�
		// ����� ���� ������� �����Ѵ�
		DAT[en]++;
	}

	queue<int>q;

	// �տ� �ִ� ��ҵ��� �̸� ť�� �־������
	for (int i = 1; i <= N; i++)
	{
		// ���� �켱���� ���� �л����� �̸� ť�� �־������
		// ���� ��µ� �� �ְ�
		if (DAT[i] == 0) {
			q.push(i);
		}
	}

	while (!q.empty()) {
		int now = q.front();
		q.pop();
		// q�� ����� ���� �տ� �ƹ��͵� ���� ť�� ��ҵ��� ����ȴ�
		cout << now << " ";
		// ���� ��Һ��� �ڿ� �ִ� ��Ұ� �ִٸ�
		for (int i = 0; i < v[now].size(); i++)
		{
			// �� �ڿ� �ִ� ����� ������ -1 �ٿ��ش�
			DAT[v[now][i]]--;
			// �� ��Ұ� ������ �������� 0�� �Ǹ� q�� �־� ����Ѵ�
			if (DAT[v[now][i]] == 0) {
				q.push(v[now][i]);
			}
		}
	}
	return 0;
}