#include <iostream>
#include <string>
#include <queue>

using namespace std;

int n, m;
int r, c, d;

// map의 값이 0이면 청소되지 않은 빈 칸
// map의 값이 1이면 벽이 있는 칸
int map[51][51];

// d = 0 -> 북쪽 (-1,0)
// d = 1 -> 동쪽 (0,1)
// d = 2 -> 남쪽 (1,0)
// d = 3 -> 서쪽 (0,-1)


// 북 동 남 서 순서로 저장 (d 값을 인덱스로)
// 그렇다면 북쪽을 바라보는 경우 후진은 ?
// d = 0 이면 dy, dx의 인덱스가 2 으로 후진
// d = 1 이면 dy, dx의 인덱스가 3 으로 후진
// d = 2 이면 dy, dx의 인덱스가 0 으로 후진
// d = 3 이면 dy, dx의 인덱스가 1 으로 후진

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

int ans;

struct Info {
	int y, x, dir;
};

bool isValid(int y, int x) {
	return x >= 0 && y >= 0 && y <= n - 1 && x <= m - 1 && (map[y][x] != 1);
}

bool isCleaned(int y, int x) {
	return (map[y][x] == 0);
}

void bfs(int start_y, int start_x, int start_dir) {

	// 시작 칸이 청소되지 않은 빈 방인 경우
	// 값을 2로 수정
	// -> 0인 경우만 방문하지 않은 빈 방으로 판단 가능
	// 방문 체크를 visited 배열 사용 x
	if (map[start_y][start_x] == 0) {
		map[start_y][start_x] = 2;
		ans++;
	}

	queue<Info>q;
	q.push({ start_y,start_x,start_dir });
	while (!q.empty()) {
		int cur_y = q.front().y;
		int cur_x = q.front().x;
		int cur_dir = q.front().dir;
		//cout << cur_y << " " << cur_x << " "<< cur_dir<<"\n";
		q.pop();

		if (map[cur_y][cur_x] == 0) {
			map[cur_y][cur_x] = 2;
			ans++;
		}


		// 현재 칸의 주변 4칸에서 청소할 수 있는 빈 칸이 없는 경우 확인
		bool check_clean = false;

		for (int i = 0; i < 4; i++) {
			int next_y = cur_y + dy[i];
			int next_x = cur_x + dx[i];
			if (!isValid(next_y, next_x) || !isCleaned(next_y, next_x))continue;

			check_clean = true;

		}
		// 현재 주변 4칸 모두 청소 불가인 경우 후진
		if (!check_clean) {

			// 후진이 가능한 구간인가?
			// dy[cur_dir], dx[cur_dir]가 현재 바라보는 방향에 대해 한 칸 후진

			// cur_dir가 0, 1 이면 + 2
			// cur_dir가 2, 3 이면 - 2

			int next_dir = 0;

			if (cur_dir < 2) {
				next_dir = cur_dir + 2;
			}
			else {
				next_dir = cur_dir - 2;
			}

			int next_y = cur_y + dy[next_dir];
			int next_x = cur_x + dx[next_dir];

			// 후진 불가능 ? -> (이게 종료 조건인 줄 알았으나 그게 아님)
			// 후진이 가능 한 경우에는 (벽이 아니고 그냥 이미 청소한 구간이면 그 장소로 다시 이동)
			if (isValid(next_y, next_x)) {
				q.push({ next_y, next_x, cur_dir });
			}

		}

		// 현재 주변 4칸 중 청소 가능
		else {
			// 바라보는 방향을 반시계로 90도 회전
			// 0->3->2->1->0..
			// 360도 회전을 하며 도중에 가능하면 그곳으로 이동

			int next_dir = cur_dir;
			for (int i = 0; i < 4; i++) {

				// 동, 남, 서 (1, 2, 3)는 인덱스 -1하면 가능
				if (next_dir > 0) {
					next_dir -= 1;
				}

				// 북(0) 은 최대인 3으로 이동
				else {
					next_dir = 3;
				}

				// 바라보는 방향 회전 후 앞쪽 칸의 좌표
				int next_y = cur_y + dy[next_dir];
				int next_x = cur_x + dx[next_dir];

				// 만약 이 좌표가 유효하고  빈 칸이라면 전진 
				if (isValid(next_y, next_x) && isCleaned(next_y, next_x)) {
					q.push({ next_y, next_x, next_dir });
					break;
				}
			}

		}

	}
}

int main() {

	cin >> n >> m;
	cin >> r >> c >> d;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	bfs(r, c, d);
	cout << ans;

	return 0;
}