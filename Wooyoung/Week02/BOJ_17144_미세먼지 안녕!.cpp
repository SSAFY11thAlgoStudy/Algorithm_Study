#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

int r, c, t;

int dy[4] = { 1,-1,0,0 };
int dx[4] = { 0,0,1,-1 };

int map[51][51];
int spread_cnt[51][51];

// 공기청정기 윗부분, 아랫부분 
int airc_up_y, airc_up_x;
int airc_down_y, airc_down_x;

// 윗부분, 아랫부분 이동 방향 배열
int dy_up[4] = { -1,0,1,0 };
int dx_up[4] = { 0,1,0,-1 };
int dy_down[4] = { 1,0,-1,0 };
int dx_down[4] = { 0,1,0,-1 };

bool visited[51][51];

bool isValid(int y, int x) {
	return y >= 0 && x >= 0 && y <= (r - 1) && x <= (c - 1);
}

bool isDust(int y, int x) {
	return map[y][x] >= 1;
}

bool isAirc(int y, int x) {
	return map[y][x] == -1;
}

// 1초마다 모든 먼지 칸에서 동시에 일어난다? 
// -> 임시 맵에 각 칸별로 확산된 먼지를 카운트하고
// 원본 맵에 결과를 추가한다.
// Why? 하나 확산 후 더해버리면 다른 모든 먼지에 영향이 미치기 때문!
void spread() {

	for (int cur_y = 0; cur_y < r; cur_y++) {
		for (int cur_x = 0; cur_x < c; cur_x++) {
			// 현재 칸에 먼지가 없거나, 공기청정기가 있으면 진행 x
			if (!isDust(cur_y, cur_x)) continue;
			// 먼지를 퍼뜨린 수 카운트 
			int temp_cnt = 0;
			for (int k = 0; k < 4; k++) {
				int next_y = cur_y + dy[k];
				int next_x = cur_x + dx[k];
				// 유효한 인덱스가 아니거나, 공기청정기가 있는 곳이라면 진행 x
				if (!isValid(next_y, next_x) || isAirc(next_y, next_x))continue;
				spread_cnt[next_y][next_x] += (map[cur_y][cur_x] / 5);
				temp_cnt++;
			}
			// (퍼뜨린 수 x 개당 퍼진 값)을 원래 먼지 확산 출발지에서 빼주기
			// spread_cnt에 -로 저장하여 그냥 더하면 나중에 알아서 빠짐!
			spread_cnt[cur_y][cur_x] += (-1) * (temp_cnt) * (map[cur_y][cur_x] / 5);
		}
	}

	// 확산 기록을 원본 맵에 추가하기 & spread_cnt 초기화
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			map[i][j] += spread_cnt[i][j];
			spread_cnt[i][j] = 0;
		}
	}

}

// 공기청정기 작동
// 공기청정기의 윗부분 -> 반시계, 아랫부분 -> 시계

void do_clean() {

	// 윗부분 먼저 처리
	// 현재 (y,x)가 공기청정기 윗부분이라면
	// 역방향으로 하나씩 땡겨온다. -> 공기청정기 흡입 하면 그 칸은 공란이기 때문에 사용할 수 있음

	// 바로 윗칸은 흡입에 의해 0으로 됨
	int up_cur_y = airc_up_y - 1;
	int up_cur_x = airc_up_x;
	int prev_up_cur_y;
	int prev_up_cur_x;
	//map[up_cur_y][up_cur_x] = 0;

	// 다시 돌아올 때 까지 반복

	for (int i = 0; i < 4; i++) {
		while (1) {
			prev_up_cur_y = up_cur_y;
			prev_up_cur_x = up_cur_x;

			// 현재 위치와 다음 위치를 설정하고 현재 위치에 다음 위치의 값을 저장한다.
			// 즉, 바람의 이동방향을 역으로 설정하여 밀어내는 방식이 아닌 당겨오는 방식을 사용
			// 현재 위치에서 이동방향으로 다음 위치를 설정했을 때 불가능하다면
			// 현재 위치에서 시계방향 90도로 회전 후 한칸 이동한 좌표를 다음 위치로 설정
			// 이후 현재 위치의 값을 다음 위치의 값으로 설정한 후 다시 진행


			if ((prev_up_cur_y == 0 && prev_up_cur_x == 0) ||
				(prev_up_cur_y == 0 && prev_up_cur_x == c - 1) ||
				(prev_up_cur_y == airc_up_y && prev_up_cur_x == c - 1)) {

				if (i < 3) {
					up_cur_y += dy_up[i + 1];
					up_cur_x += dx_up[i + 1];
					map[prev_up_cur_y][prev_up_cur_x] = map[up_cur_y][up_cur_x];
					break;

				}

			}
			up_cur_y += dy_up[i];
			up_cur_x += dx_up[i];

			map[prev_up_cur_y][prev_up_cur_x] = map[up_cur_y][up_cur_x];


			if (up_cur_y == airc_up_y && up_cur_x == airc_up_x + 1) {
				map[up_cur_y][up_cur_x] = 0;
				break;
			}
		}
	}

	// 아랫부분 처리
	// 현재 (y,x)가 공기청정기 아랫부분이라면
	// 역방향으로 하나씩 땡겨온다. -> 공기청정기 흡입 하면 그 칸은 공란이기 때문에 사용할 수 있음

	int down_cur_y = airc_down_y + 1;
	int down_cur_x = airc_down_x;
	int prev_down_cur_y;
	int prev_down_cur_x;

	// 다시 돌아올 때 까지 반복

	for (int i = 0; i < 4; i++) {
		while (1) {
			prev_down_cur_y = down_cur_y;
			prev_down_cur_x = down_cur_x;

			if ((prev_down_cur_y == r - 1 && prev_down_cur_x == 0) ||
				(prev_down_cur_y == r - 1 && prev_down_cur_x == c - 1) ||
				(prev_down_cur_y == airc_down_y && prev_down_cur_x == c - 1)) {

				if (i < 3) {

					down_cur_y += dy_down[i + 1];
					down_cur_x += dx_down[i + 1];
					map[prev_down_cur_y][prev_down_cur_x] = map[down_cur_y][down_cur_x];
				}

				break;

			}
			down_cur_y += dy_down[i];
			down_cur_x += dx_down[i];


			map[prev_down_cur_y][prev_down_cur_x] = map[down_cur_y][down_cur_x];

			if (down_cur_y == airc_down_y && down_cur_x == airc_down_x + 1) {
				map[down_cur_y][down_cur_x] = 0;
				break;
			}
		}
	}


}


int main() {

	cin >> r >> c >> t;
	bool find_airc = false;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> map[i][j];
			if (map[i][j] == -1 && !find_airc) {
				airc_up_y = i;
				airc_up_x = j;
				airc_down_y = i + 1;
				airc_down_x = j;
				find_airc = true;
			}
		}
	}

	for (int i = 0; i < t; i++) {
		spread();
		do_clean();
	}

	int ans = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (map[i][j] > 0) {

				ans += map[i][j];
			}
		}
	}
	cout << ans;
	return 0;
}