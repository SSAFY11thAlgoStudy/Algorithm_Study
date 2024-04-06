#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<algorithm>
#include<deque>
using namespace std;
struct Pos
{
	int y;
	int x;
};
deque<Pos>pv;

int n;
int m;
int MAP[4][4];
int visited[4][4];
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
int endY = -1;
int endX = -1;
int ansCnt;

void input() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> MAP[i][j];
			// ��ֹ��̸� �̸� �湮 ó���ع�����
			if (MAP[i][j] == 1) {
				visited[i][j] = 1;
			}
		}
	}

	for (int i = 0; i < m; i++)
	{
		int y, x = 0;
		cin >> y >> x;
		pv.push_back({ y - 1,x - 1 });
	}
	// ������ ����
	endY = pv[m - 1].y;
	endX = pv[m - 1].x;
}

void func(int y, int x) {

	// ��������
	// ��ť�� ����� 0�̴� => �������� �� �鸰���� �̸�
	// �������϶� �����Ѵ�

	if (pv.size() == 0 && y == endY && x == endX) {
		ansCnt++;
		return;
	}

	int nowy = y;
	int nowx = x;
	for (int d = 0; d < 4; d++)
	{
		int ny = nowy + dy[d];
		int nx = nowx + dx[d];

		if (ny >= n || nx >= n || ny < 0 || nx < 0) continue;
		if (MAP[ny][nx] == 1) continue;
		if (visited[ny][nx] == 1) continue;
		int pvY = pv[0].y;
		int pvX = pv[0].x;

		// �ش� ĭ�� ������ �´� �������� ���
		// ������� ������ �����ϸ� ���� ��� ����
		if (ny == pv[0].y && nx == pv[0].x) {
			pv.pop_front();
		}
		// �湮 üũ
		visited[ny][nx] = 1;
		func(ny, nx);
		// �湮 üũ ����
		visited[ny][nx] = 0;

		// ���� ���ݴ� �������ΰ�� �ٽ� �߰�
		if (ny == pvY && nx == pvX) {
			pv.push_front({ ny,nx });
		}
	}
}

int main() {

	input();
	// ��������� ��� ������.
	// ����� y, x ���� ����
	int sy = pv[0].y;
	int sx = pv[0].x;
	// ����� �湮üũ
	visited[sy][sx] = 1;
	// ����� �� ����
	pv.pop_front();
	func(sy, sx);

	// ��� ������ �� ���
	cout << ansCnt;
	return 0;
}