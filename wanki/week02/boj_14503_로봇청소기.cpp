#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>

using namespace std;

struct pos {
	int y;
	int x;
	int d;//방향
};
pos robot;
int dy[] = { -1,0,1,0 }, dx[] = { 0,1,0,-1 }; //북동남서
int N, M, cnt;//cnt결과
int map[50][50];//(0,0)부터, (N-1,M-1)까지. 단 벽으로 둘어쌓여있다.
/*
1. 현재 칸이 아직 청소되지 않은 경우, 현재 칸을 청소한다.
2. 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 없는 경우,
	a.바라보는 방향을 유지한 채로 한 칸 후진할 수 있다면 한 칸 후진하고 1번으로 돌아간다.
	b. 바라보는 방향의 뒤쪽 칸이 벽이라 후진할 수 없다면 작동을 멈춘다.
3. 현재 칸의 주변4칸 중 청소되지 않은 빈 칸이 있는 경우
	a. 반시계 방향으로 90도 회전한다.
	b. 바라보는 방향을 기준으로 앞쪽 칸이 청소되지 않은 빈 칸인 경우 한 칸 전진한다.
	c. 1번으로 돌아간다.
*/

void func() {
	while (1) {
		int flag = 0;
		//1. 현재 칸이 아직 청소되지 않은 경우, 현재 칸을 청소한다.
		if (map[robot.y][robot.x] == 0) {
			map[robot.y][robot.x] = 2;
			cnt++;
		}

		//주변 탐색
		for (int i = 0; i < 4; i++)
		{
			int ny = robot.y + dy[i];
			int nx = robot.x + dx[i];

			if (map[ny][nx] == 0) flag = 1;
		}

		//2. 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 없는 경우
		if (flag == 0) {
			//a.바라보는 방향을 유지한 채로 한 칸 후진할 수 있다면 한 칸 후진하고 1번으로 돌아간다.
			int ny = robot.y + dy[(robot.d + 2) % 4];
			int nx = robot.x + dx[(robot.d + 2) % 4];

			//b. 바라보는 방향의 뒤쪽 칸이 벽이라 후진할 수 없다면 작동을 멈춘다.
			if (map[ny][nx] == 1) {
				return;
			}

			robot.y = ny;
			robot.x = nx;
		}
		//3. 현재 칸의 주변4칸 중 청소되지 않은 빈 칸이 있는 경우
		else {
			while (1) {
				//a. 반시계 방향으로 90도 회전한다.
				robot.d = (robot.d + 3) % 4;
				//	b. 바라보는 방향을 기준으로 앞쪽 칸이 청소되지 않은 빈 칸인 경우 한 칸 전진한다.
				int ny = robot.y + dy[robot.d];
				int nx = robot.x + dx[robot.d];
				if (map[ny][nx] == 0) {
					robot.y = ny;
					robot.x = nx;
					//c. 1번으로 돌아간다.
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
	//입력
	input();

	func();

	//출력
	cout << cnt;
	return 0;
}