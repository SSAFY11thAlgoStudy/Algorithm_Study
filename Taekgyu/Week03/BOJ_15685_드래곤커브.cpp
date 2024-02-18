#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<algorithm>
#include<deque>
#include<queue>

using namespace std;

int N;
int x, y, d, g;
int MAP[110][110];
int cnt;
int ansCnt;

// ���� �ε����� �°� ���� �迭 ����
int dy[4] = { 0,-1,0,1 };
int dx[4] = { 1,0,-1,0 };

// ��ť�� Ȱ���Ͽ� ���⺯�� ����
deque<int>Aq;

// �ʱ�ȭ �ڵ�
void init() {
	memset(MAP, 0, sizeof(MAP));
	ansCnt = 0;
	cnt = 0;
	Aq.clear();
}

// �巡�� Ŀ�긦 �׸���!
void DragonCurve() {
	// ó�� ������ ���
	MAP[y][x] = 1;

	// Aq��� ��ť�� ���⺯�� ����
	Aq.push_back(d);

	// �巡�� Ŀ�� ��Ģ�� Ȱ���Ͽ� ���븸ŭ ��ť ����
	// ���⺯�� 0���� ����
	// 0���� 0
	// 1���� 0 -> 1
	// 2���� 0 1 -> 2 1
	// 3���� 0 1 2 1 -> 2 3 2 1
	// �� �� �ִ� ��Ģ : �� ������ ��ť���� ������ ���� ���� �� +1�� �ؼ� �߰��ض�~~~

	for (int i = 0; i < g; i++)
	{
		deque<int>copyQ(Aq);
		// �� ������ ���⺯���� ����
		int qsize = copyQ.size();
		for (int j = 0; j < qsize; j++)
		{
			int qBack = copyQ.back();
			copyQ.pop_back();
			// �ڿ������� �ϳ��� ���� +1 �� �߰�
			Aq.push_back((qBack + 1) % 4);
		}
	}

	// ����� ���� ��ť�� �°� �ʿ� �׸���~
	int qsize = Aq.size();
	for (int i = 0; i < qsize; i++)
	{
		int dir = Aq.front();
		Aq.pop_front();
		int ny = y + dy[dir];
		int nx = x + dx[dir];

		MAP[ny][nx] = 1;
		y = ny;
		x = nx;
	}
}

// �巡�� Ŀ�� �� �׸��� ���簢�� ���� �Ǵ�
int squareCheck() {

	// ��ǥ�� �°� �׷ȱ� ������
	// 2*2 ũ���� ���簢�� ���� ���
	// �� : (0,0)�� �迭���� 1�̸� (0,0)���������� �巡�� Ŀ�갡 ��������.
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			cnt = MAP[i][j] + MAP[i + 1][j] + MAP[i][j + 1] + MAP[i + 1][j + 1];
			if (cnt == 4) {
				ansCnt++;
				cnt = 0;
			}
		}
		cnt = 0;
	}
	return ansCnt;
}

int main()
{
	init();
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> x >> y >> d >> g;
		DragonCurve();
	}
	int Ans = squareCheck();
	cout << Ans;
	return 0;
}