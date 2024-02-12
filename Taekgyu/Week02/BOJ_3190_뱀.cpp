#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>

using namespace std;

queue<pair<int, int>>q;


int N, K;//������ ũ��, ����� ����
int MAP[120][120];// MAP����
int y, x;//��� ��ǥ
int L;// ���⺯ȯ Ƚ��
int dirY;
int dirX = 1; //ó���� ���������� ����
int DAT[99999]; //cnt�� �־����ϱ� ũ�� �����
char dirDAT[99999];
int ny, nx; //���� ��ǥ
int cnt; //�ð�

void init() {
	// �������� �ʱ�ȭ
	memset(MAP, 0, sizeof(MAP));
	memset(DAT, 0, sizeof(DAT));
	memset(dirDAT, 0, sizeof(dirDAT));
	cnt = 0;
}

int func(int nowY, int nowX) {

	// ���� ����
	if (DAT[cnt] != 0) {
		// ���� ���������� ������ ��
		if (dirY == 0 && dirX == 1 && dirDAT[cnt] == 'D') {
			dirY = 1;
			dirX = 0;
		}
		else if (dirY == 0 && dirX == 1 && dirDAT[cnt] == 'L') {
			dirY = -1;
			dirX = 0;
		}
		// ���� �Ʒ��� ������ ��
		else if (dirY == 1 && dirX == 0 && dirDAT[cnt] == 'D') {
			dirY = 0;
			dirX = -1;
		}
		else if (dirY == 1 && dirX == 0 && dirDAT[cnt] == 'L') {
			dirY = 0;
			dirX = 1;
		}
		// ���� ���� ������ ��
		else if (dirY == -1 && dirX == 0 && dirDAT[cnt] == 'D') {
			dirY = 0;
			dirX = 1;
		}
		else if (dirY == -1 && dirX == 0 && dirDAT[cnt] == 'L') {
			dirY = 0;
			dirX = -1;
		}
		// ���� �������� ������ ��
		else if (dirY == 0 && dirX == -1 && dirDAT[cnt] == 'D') {
			dirY = -1;
			dirX = 0;
		}
		else if (dirY == 0 && dirX == -1 && dirDAT[cnt] == 'L') {
			dirY = 1;
			dirX = 0;
		}
	}
	cnt++;
	ny = nowY + dirY;
	nx = nowX + dirX;

	//�� ������ ������ ����
	if (ny >= N || nx >= N || ny < 0 || nx < 0) {
		return cnt;
	}
	else {
		//����� �Ծ��� ���
		if (MAP[ny][nx] == 2) {
			// ť�� �Ӹ� ��ġ ����
			q.push({ ny,nx });
			// �� ���� �����
			MAP[ny][nx] = 1;
		}
		//���� �ʾ��� ���
		else {
			// ť�� �Ӹ� ��ġ ����
			q.push({ ny,nx });
			// �ڽ��� ���� ����� ���
			if (MAP[ny][nx] == 1) {
				return cnt;
			}
			// �� ���� �����
			MAP[ny][nx] = 1;
			// ���� �ڸ���
			MAP[q.front().first][q.front().second] = 0;
			q.pop();
		}
		func(ny, nx);
		return cnt;
	}
}

int main()
{
	init();
	cin >> N >> K;
	for (int i = 0; i < K; i++)
	{
		cin >> y >> x;
		MAP[y - 1][x - 1] = 2;//��� ��ġ 2�� ǥ��
	}
	cin >> L;
	for (int i = 0; i < L; i++)
	{
		int Num = 0;
		char C = 0;
		cin >> Num >> C;
		DAT[Num] = 1;
		dirDAT[Num] = C;
	}
	q.push({ 0,0 });//������ push
	func(0, 0);
	cout << cnt;
	return 0;
}