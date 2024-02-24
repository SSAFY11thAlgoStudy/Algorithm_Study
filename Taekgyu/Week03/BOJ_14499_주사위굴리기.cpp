#define _NO_CRT_NO_SECURE
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

int N, M, X, Y, K;
int MAP[21][21];
// ���� ���� �°� ����迭 ����
// ������ �� : �� ���������� x�� y�� ���� �ݴ�� �����Ѵ�.
int dy[4] = { 1,-1,0,0 };
int dx[4] = { 0,0,-1,1 };
int dir;
// �ֻ��� �迭 0���� �ʱ�ȭ
int dice[4][4] = { 0, };

void init() {
	memset(MAP, 0, sizeof(MAP));
	memset(dice, 0, sizeof(dice));
}

int func(int x, int y, int dir) {

	// ���⿡ ���� �� ���� �ֻ����� ��ġ
	int ny = y + dy[dir - 1];
	int nx = x + dx[dir - 1];
	// �� �ٱ����� �̵��Ϸ��� �ϴ� ���
	if (nx >= N || ny >= M || nx < 0 || ny < 0) {
		return -1;
	}

	// �� �ٱ��� �ƴϸ� �ֻ����� ������~~
	else {
		// �ֻ��� �迭 �����
		// �� �� �ֻ��� ������

		// ���� : dice�迭�� 4*4�� ������ ��
		// �� �ٴڿ� �ش��ϴ� �ε��� dice(1,3), dice(3,1)

		// �������� ���� �� 
		if (dir == 1) {
			int temp = dice[1][3];
			for (int i = 2; i >= 0; i--)
			{
				dice[1][i + 1] = dice[1][i];
			}
			dice[1][0] = temp;
			dice[3][1] = dice[1][3];
		}
		// �������� ���� ��
		else if (dir == 2) {
			int temp = dice[1][0];
			for (int i = 0; i < 3; i++)
			{
				dice[1][i] = dice[1][i + 1];
			}
			dice[1][3] = temp;
			dice[3][1] = dice[1][3];
		}
		// �������� ���� ��
		else if (dir == 3) {
			int temp = dice[0][1];
			for (int i = 0; i < 3; i++)
			{
				dice[i][1] = dice[i + 1][1];
			}
			dice[3][1] = temp;
			dice[1][3] = dice[3][1];
		}
		// �������� ���� ��
		else {
			int temp = dice[3][1];
			for (int i = 2; i >= 0; i--)
			{
				dice[i + 1][1] = dice[i][1];
			}
			dice[0][1] = temp;
			dice[1][3] = dice[3][1];
		}

		// ���� �ֻ��� ��ġ ����
		X = nx;
		Y = ny;

		// ���� ��ġ�� MAP���� 0�� �� 
		if (MAP[nx][ny] == 0) {
			// �ֻ������� ĭ���� ����
			MAP[nx][ny] = dice[3][1];
			// �ֻ��� ���� ����~
			return dice[1][1];
		}

		// ���� ��ġ�� MAP���� 0�� �ƴ� �� 
		else {
			// ĭ���� �ֻ����� ����
			// �ֻ��� �� �ٴڿ� �ش��ϴ� �� ����
			dice[3][1] = MAP[nx][ny];
			dice[1][3] = MAP[nx][ny];

			// ĭ�� 0���� �ٲ�
			MAP[nx][ny] = 0;
			// �ֻ��� ���� ����~
			return dice[1][1];
		}
	}
}

int main() {

	cin >> N >> M >> X >> Y >> K;
	// �ʱ�ȭ
	init();

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> MAP[i][j];
		}
	}
	for (int i = 0; i < K; i++)
	{
		cin >> dir;
		int ans = func(X, Y, dir);
		// �� �ȿ� �������� ���
		if (ans != -1) {
			cout << ans << endl;
		}
	}
	return 0;
}