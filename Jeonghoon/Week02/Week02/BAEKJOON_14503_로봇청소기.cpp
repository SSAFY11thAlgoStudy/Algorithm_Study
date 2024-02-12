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

	//맵 크기
	cin >> N >> M;

	//시작 위치, 방향
	cin >> sp_y >> sp_x >> dirc;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
}

void solve(int y, int x) {

	while (1) {
		//1. 처음 시작 점이 청소가 안되었을 때
		//새로운 자리로 갔을 때 청소해야 할 때
		if (map[y][x] == 0) {
			map[y][x] = 2;
			cnt++;
		}

		//2. 4방향이 0일 때
		if (map[y + 1][x] != 0 && map[y - 1][x] != 0 && map[y][x + 1] != 0 && map[y][x - 1] != 0) {

			//2-1 뒤로 후진
			x = x - dx[dirc];
			y = y - dy[dirc];

			//2-2 만약 벽이라면 작동 멈춤
			if (map[y][x] == 1) {
				break;
			}
		}
		else {
			//4방향 중 1곳이라도 청소 안되었을 때
			dirc = (dirc + 3) % 4;

			//다음번에 움직일 방향
			int nx = x + dx[dirc];
			int ny = y + dy[dirc];

			//그 방향이 청소를 해야한다면 x,y값 갱신
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