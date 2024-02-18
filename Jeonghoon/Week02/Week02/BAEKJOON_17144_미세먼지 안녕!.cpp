#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;

int R, C, T;
int map[51][51];
//분열에 사용할 방향배열
int dy[4] = { 0, -1, 0, 1 };
int dx[4] = { 1, 0, -1, 0 };
//분열한 상태의 맵 상태 저장
int visited[51][51];
//청정기 위치(y좌표) 저장
int y[2];
int ans;

void input() {
	cin >> R >> C >> T;
	int num = 0;

	// 입력배열 받기
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
		}

		//입력 배열중에 청정기 위치 찾기
		if (map[i][0] == -1) {
			y[num] = i;
			num++;
		}
	}
}

void solve1() {
	// 분열 과정
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			// 분열 가능한 상태일 때
			if (map[i][j] > 0) {
				// 분열된 갯수 저장
				int cnt = 0;

				for (int k = 0; k < 4; k++) {
					int ny = i + dy[k];
					int nx = j + dx[k];

					// 벽이거나 공기청정기가 있으면 분열X
					if (nx < 0 || nx >= C || ny < 0 || ny >= R || map[ny][nx] == -1) {
						continue;
					}

					//이전에 저장된 값에다가 이번에 분리된 값을 더함
					visited[ny][nx] += (map[i][j] / 5);
					cnt++;
				}
				//지금까지 저장된 값 + 맵에 인풋으로 있는 값 - 분열되서 나간 값
				visited[i][j] += map[i][j] - (map[i][j] / 5) * cnt;
			}
		}
	}

	//임시로 저장해둔 값들을 map으로 옮기고 초기화
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			map[i][j] = visited[i][j];
			visited[i][j] = 0;
		}
	}
}

void solve2(int y) {

	// 위 - 반시계
  //위
	for (int i = y - 1; i >= 1; i--) {
		map[i][0] = map[i - 1][0];
	}
	//오른쪽
	for (int i = 0; i < C - 1; i++) {
		map[0][i] = map[0][i + 1];
	}
	// 아래
	for (int i = 0; i < y; i++) {
		map[i][C - 1] = map[i + 1][C - 1];
	}
	// 왼쪽
	for (int i = C - 1; i >= 2; i--) {
		map[y][i] = map[y][i - 1];
	}

	// 정화한 자리는 0
	map[y][1] = 0;
	//청정기 자리 다시 -1로 만들기
	map[y][0] = -1;
}

void solve3(int y) {
	// 아래 - 시계
  // 아래쪽
	for (int i = y + 1; i < R - 1; i++) {
		map[i][0] = map[i + 1][0];
	}
	// 오른쪽
	for (int i = 0; i < C - 1; i++) {
		map[R - 1][i] = map[R - 1][i + 1];
	}
	// 위로
	for (int i = R - 1; i > y; i--) {
		map[i][C - 1] = map[i - 1][C - 1];
	}
	// 왼쪽
	for (int i = C - 1; i >= 2; i--) {
		map[y][i] = map[y][i - 1];
	}

	// 정화한 자리는 0
	map[y][1] = 0;
	//청정기 자리 다시 1로 만들기
	map[y][0] = -1;
}

void sum() {
	// 전체 탐색해서 남은 미세먼지 합하기
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			ans += map[i][j];
		}
	}
}

int main() {
	freopen("sample.txt", "r", stdin);

	input();

	// 초기 시간 1초
	int tim = 1;

	// 입력받은 T초까지 반복
	while (tim <= T) {
		solve1();
		solve2(y[0]);
		solve3(y[1]);
		tim++;
	}

	sum();

	// 청정기의 값(-1)이 2번 들어갔으므로 +2
	cout << ans + 2;

	return 0;
}