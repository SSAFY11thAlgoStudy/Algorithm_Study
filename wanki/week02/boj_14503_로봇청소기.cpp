#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>

using namespace std;

struct pos {
	int y;
	int x;
	int d;//����
};
pos robot;
int dy[] = { -1,0,1,0 }, dx[] = { 0,1,0,-1 }; //�ϵ�����
int N, M, cnt;//cnt���
int map[50][50];//(0,0)����, (N-1,M-1)����. �� ������ �Ѿ�׿��ִ�.
/*
1. ���� ĭ�� ���� û�ҵ��� ���� ���, ���� ĭ�� û���Ѵ�.
2. ���� ĭ�� �ֺ� 4ĭ �� û�ҵ��� ���� �� ĭ�� ���� ���,
	a.�ٶ󺸴� ������ ������ ä�� �� ĭ ������ �� �ִٸ� �� ĭ �����ϰ� 1������ ���ư���.
	b. �ٶ󺸴� ������ ���� ĭ�� ���̶� ������ �� ���ٸ� �۵��� �����.
3. ���� ĭ�� �ֺ�4ĭ �� û�ҵ��� ���� �� ĭ�� �ִ� ���
	a. �ݽð� �������� 90�� ȸ���Ѵ�.
	b. �ٶ󺸴� ������ �������� ���� ĭ�� û�ҵ��� ���� �� ĭ�� ��� �� ĭ �����Ѵ�.
	c. 1������ ���ư���.
*/

void func() {
	while (1) {
		int flag = 0;
		//1. ���� ĭ�� ���� û�ҵ��� ���� ���, ���� ĭ�� û���Ѵ�.
		if (map[robot.y][robot.x] == 0) {
			map[robot.y][robot.x] = 2;
			cnt++;
		}

		//�ֺ� Ž��
		for (int i = 0; i < 4; i++)
		{
			int ny = robot.y + dy[i];
			int nx = robot.x + dx[i];

			if (map[ny][nx] == 0) flag = 1;
		}

		//2. ���� ĭ�� �ֺ� 4ĭ �� û�ҵ��� ���� �� ĭ�� ���� ���
		if (flag == 0) {
			//a.�ٶ󺸴� ������ ������ ä�� �� ĭ ������ �� �ִٸ� �� ĭ �����ϰ� 1������ ���ư���.
			int ny = robot.y + dy[(robot.d + 2) % 4];
			int nx = robot.x + dx[(robot.d + 2) % 4];

			//b. �ٶ󺸴� ������ ���� ĭ�� ���̶� ������ �� ���ٸ� �۵��� �����.
			if (map[ny][nx] == 1) {
				return;
			}

			robot.y = ny;
			robot.x = nx;
		}
		//3. ���� ĭ�� �ֺ�4ĭ �� û�ҵ��� ���� �� ĭ�� �ִ� ���
		else {
			while (1) {
				//a. �ݽð� �������� 90�� ȸ���Ѵ�.
				robot.d = (robot.d + 3) % 4;
				//	b. �ٶ󺸴� ������ �������� ���� ĭ�� û�ҵ��� ���� �� ĭ�� ��� �� ĭ �����Ѵ�.
				int ny = robot.y + dy[robot.d];
				int nx = robot.x + dx[robot.d];
				if (map[ny][nx] == 0) {
					robot.y = ny;
					robot.x = nx;
					//c. 1������ ���ư���.
					break;
				}
			}
		}
	}
}

void input() {
	cin >> N >> M;

	cin >> robot.y >> robot.x >> robot.d;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];
		}
	}
}

int main() {
	//�Է�
	input();

	func();

	//���
	cout << cnt;
	return 0;
}