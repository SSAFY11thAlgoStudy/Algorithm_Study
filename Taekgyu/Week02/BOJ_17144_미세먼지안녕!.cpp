#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>

using namespace std;

int R, C, T;
int MAP[60][60];
int CusMAP[60][60];
int sum;
int dy[4] = { 0,0,-1,1 };
int dx[4] = { -1,1,0,0 };
int AirClean;//����û���� ��ġ

void dust() {
	// 1�ʵ��� �̼����� Ȯ�� ��� ���� �Լ�
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (MAP[i][j] > 0) {
				int spreadDust = MAP[i][j] / 5;
				int cnt = 0;
				for (int d = 0; d < 4; d++)
				{
					int ny = i + dy[d];
					int nx = j + dx[d];
					if (ny >= R || nx >= C || ny < 0 || nx < 0 || MAP[ny][nx] == -1) {
						continue;
					}
					CusMAP[ny][nx] += spreadDust;
					cnt++;
				}
				CusMAP[i][j] += MAP[i][j] - (spreadDust * cnt);
			}
		}
	}
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			MAP[i][j] = CusMAP[i][j];
			CusMAP[i][j] = 0;
		}
	}

}

void Airfresh() {

	// ����ȯ ����
	//int temp = MAP[AirClean][1];

	queue<int>Uq;
	Uq.push(MAP[AirClean][1]);
	MAP[AirClean][1] = 0;
	// �� ��ȯ �Ʒ�
	for (int i = 1; i < C - 1; i++)
	{
		Uq.push(MAP[AirClean][i + 1]);
		MAP[AirClean][i + 1] = Uq.front();
		Uq.pop();
	}
	//�� ��ȯ ������
	for (int i = AirClean; i > 0; i--)
	{
		Uq.push(MAP[i - 1][C - 1]);
		MAP[i - 1][C - 1] = Uq.front();
		Uq.pop();
		//MAP[i - 1][C-1] = MAP[i][C-1];
	}
	// �� ��ȯ ����
	for (int i = C - 1; i > 0; i--)
	{
		Uq.push(MAP[0][i - 1]);
		MAP[0][i - 1] = Uq.front();
		Uq.pop();
	}
	// �� ��ȯ ����
	for (int i = 0; i < AirClean; i++)
	{
		Uq.push(MAP[i + 1][0]);
		MAP[i + 1][0] = Uq.front();
		Uq.pop();
	}
	MAP[AirClean][0] = 0;


	// �Ʒ���ȯ����

	queue<int>Dq;
	int DownAirclean = AirClean + 1;
	Dq.push(MAP[DownAirclean][1]);
	MAP[DownAirclean][1] = 0;
	// �Ʒ� ��ȯ ��
	for (int i = 1; i < C - 1; i++)
	{
		Dq.push(MAP[DownAirclean][i + 1]);
		MAP[DownAirclean][i + 1] = Dq.front();
		Dq.pop();
	}
	//�Ʒ� ��ȯ ������
	for (int i = DownAirclean; i < R - 1; i++)
	{
		Dq.push(MAP[i + 1][C - 1]);
		MAP[i + 1][C - 1] = Dq.front();
		Dq.pop();
		//MAP[i - 1][C-1] = MAP[i][C-1];
	}
	// �Ʒ� ��ȯ �Ʒ�
	for (int i = C - 1; i > 0; i--)
	{
		Dq.push(MAP[R - 1][i - 1]);
		MAP[R - 1][i - 1] = Dq.front();
		Dq.pop();
	}
	// �Ʒ� ��ȯ ����
	for (int i = R - 1; i > DownAirclean; i--)
	{
		Dq.push(MAP[i - 1][0]);
		MAP[i - 1][0] = Dq.front();
		Dq.pop();
	}
	MAP[DownAirclean][0] = 0;

}


int main() {

	cin >> R >> C >> T;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cin >> MAP[i][j];
		}
	}
	// ����û���� ��ġ ã��
	for (int i = 0; i < R; i++)
	{
		if (MAP[i][0] == -1) {
			AirClean = i;
			break;
		}
	}
	// t�ʵ��� ����
	for (int i = 0; i < T; i++)
	{
		dust();
		Airfresh();
	}
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			sum += MAP[i][j];
		}
	}
	cout << sum;
}