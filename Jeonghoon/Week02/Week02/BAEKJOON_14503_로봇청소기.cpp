#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;

int N, M;
int sp_x, sp_y;
int map[51][51];
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
int dirc;
int cnt;


void input() {

	//�� ũ��
	cin >> N >> M;

	//���� ��ġ, ����
	cin >> sp_y >> sp_x >> dirc;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
}

void solve(int y, int x) {

	while (1) {
		//1. ó�� ���� ���� û�Ұ� �ȵǾ��� ��
		//���ο� �ڸ��� ���� �� û���ؾ� �� ��
		if (map[y][x] == 0) {
			map[y][x] = 2;
			cnt++;
		}

		//2. 4������ 0�� ��
		if (map[y + 1][x] != 0 && map[y - 1][x] != 0 && map[y][x + 1] != 0 && map[y][x - 1] != 0) {

			//2-1 �ڷ� ����
			x = x - dx[dirc];
			y = y - dy[dirc];

			//2-2 ���� ���̶�� �۵� ����
			if (map[y][x] == 1) {
				break;
			}
		}
		else {
			//4���� �� 1���̶� û�� �ȵǾ��� ��
			dirc = (dirc + 3) % 4;

			//�������� ������ ����
			int nx = x + dx[dirc];
			int ny = y + dy[dirc];

			//�� ������ û�Ҹ� �ؾ��Ѵٸ� x,y�� ����
			if (map[ny][nx] == 0) {
				x = nx;
				y = ny;
			}
		}
	}
}

int main() {

	freopen("sample.txt", "r", stdin);

	input();
	solve(sp_y, sp_x);

	cout << cnt;

	return 0;
}