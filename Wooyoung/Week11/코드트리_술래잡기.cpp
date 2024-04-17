#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

int n, m, h, k;

// 도망자의 방향배열
int dy[2] = { 1,-1 };
int dx[2] = { 1,-1 };

// 술래의 방향배열
// 상우하좌
int dy1[4] = { -1,0,1,-1 };
int dx1[4] = { 0,1,0,-1 };

// 하우상좌
int dy2[4] = { 1,0,-1,0 };
int dx2[4] = { 0,1,0,-1 };

struct Info {
	int y, x, id, d;
	bool isDead;
};

struct Info2 {
	int y, x, d, move_cnt;
};

// 벡터에서 꺼내어 등록된 참가자들만 이동
// 이동 기록은 맵에 저장

vector<Info>runners;
vector<Info>runnersMap[100][100];
int trees[100][100];
// sd가 0 -> 중심에서 (1,1)로, sd가 1 -> (1,1)에서 중심으로
Info2 Hero;
vector<pair<int, int>>HeroPos;
int sy, cy, sx, cx;
int turn;
int ans;
int dead_runners;
void input() {
	cin >> n >> m >> h >> k;
	int y, x, d;
	for (int i = 0; i < m; i++) {
		cin >> y >> x >> d;
		Info now = { y,x,d,0,false };
		runners.push_back(now);
	}
	for (int i = 0; i < h; i++) {
		cin >> y >> x;
		trees[y][x] = 1;
	}
	sy = (n / 2) + 1;
	sx = sy;
	cy = sy;
	cx = sy;
	Hero = { sy,sx,0,0 };
}

void makeHeroPos() {

	// (1,1)부터 역순으로 저장
	// 첫번째 열은 그냥 저장
	for (int i = 1; i <= n; i++) {
		HeroPos.push_back({ i,1 });
	}

	int y = n, x = 1, cnt = 0, cnt1 = 0;
	int dy = 0, dx = 1;
	int temp_n = n - 1;
	while (1) {
		y += dy;
		x += dx;
		cnt++;
		HeroPos.push_back({ y,x });
		if (sy == y && sx == x)break;
		if (cnt == temp_n) {
			if (dy == 0 && dx == 1) {
				dy = -1;
				dx = 0;
			}
			else if (dy == -1 && dx == 0) {
				dy = 0;
				dx = -1;
			}
			else if (dy == 0 && dx == -1) {
				dy = 1;
				dx = 0;
			}
			else if (dy == 1 && dx == 0) {
				dy = 0;
				dx = 1;
			}
			cnt1++;
			if (cnt1 == 2) {
				temp_n--;
				cnt1 = 0;
			}
			cnt = 0;
		}
	}
}

void moveRunner() {
	for (int i = 0; i < runners.size(); i++) {
		Info now = runners[i];

		// 잡힌 도망자는 진행 x
		if (now.isDead)continue;

		// 술래와의 거리가 3 초과인 경우 진행 x
		int dis = abs(now.y - Hero.y) + abs(now.x - Hero.x);
		if (dis > 3)continue;

		// 다음 칸 
		int ny = now.y;
		int nx = now.x;

		// id가 1인 경우 좌우, 2인 경우 상하
		if (now.id == 1) {
			nx += dx[now.d];
			// nx가 격자 초과할 때 (0 또는 n+1일 때)
			if (nx == 0 || nx == n + 1) {
				now.d = (now.d + 1) % 2;
				// 이전 위치에서 방향 바꾸어 1칸 이동
				nx = now.x + dx[now.d];
			}
		}
		else if (now.id == 2) {
			ny += dy[now.d];
			// ny가 격자 초과할 때 (0 또는 n+1일 때)
			if (ny == 0 || ny == n + 1) {
				now.d = (now.d + 1) % 2;
				// 이전 위치에서 방향 바꾸어 1칸 이동
				ny = now.y + dy[now.d];
			}
		}
		// 이동하려는 좌표 (ny,nx)에 술래가 있으면 진행 x
		// 방향 전환은 해주고 진행 x 
		runners[i] = now;
		if (Hero.y == ny && Hero.x == nx)continue;

		// 이동하려는 좌표 (ny,nx)에 술래가 없으면 진행 
		now.y = ny;
		now.x = nx;
		runners[i] = now;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			runnersMap[i][j].clear();
		}
	}

	for (int i = 0; i < runners.size(); i++) {
		Info now = runners[i];
		runnersMap[now.y][now.x].push_back(now);
	}
}

void moveHero() {

	// nxn 크기의 벡터에 역방향 좌표가 저장 (0~ nxn-1)
	// 현재 이동 횟수가 move_cnt
	// 다음 지점은 n-move_cnt
	Hero.move_cnt++;
	int y = Hero.y;
	int x = Hero.x;
	int ny, nx, nny, nnx;
	// 움직인 후 바라보는 방향은
	// 현재 좌표 기준, 다음 좌표와 다다음 좌표의 차이를 이용해야한다.
	if (Hero.move_cnt == ((n * n) - 1)) {
		Hero.move_cnt = 0;
		if (Hero.d == 0) {
			Hero.d = 1;
			ny = 1;
			nx = 1;
			nny = y;
			nnx = x;
		}
		else {
			Hero.d = 0;
			ny = sy;
			nx = sx;
			nny = y;
			nnx = x;
		}
	}
	else {
		if (Hero.d == 0) {
			ny = HeroPos[(n * n - 1) - Hero.move_cnt].first;
			nx = HeroPos[(n * n - 1) - Hero.move_cnt].second;
			nny = HeroPos[(n * n - 1) - (Hero.move_cnt + 1)].first;
			nnx = HeroPos[(n * n - 1) - (Hero.move_cnt + 1)].second;
		}
		else {
			ny = HeroPos[Hero.move_cnt].first;
			nx = HeroPos[Hero.move_cnt].second;
			nny = HeroPos[(Hero.move_cnt + 1)].first;
			nnx = HeroPos[(Hero.move_cnt + 1)].second;
		}

	}
	Hero.y = ny;
	Hero.x = nx;

	int dy = nny - ny;
	int dx = nnx - nx;

	// 움직인 후, 방향 구했으니, 이 방향으로 현재 칸 포함 3칸을 확인
	int ty = ny;
	int tx = nx;

	int cntRunners = 0;

	// 현재 칸 추가 및 현재 칸에 존재하는 도망자들 삭제
	if (trees[ty][tx] != 1) {
		cntRunners += runnersMap[ty][tx].size();
		dead_runners += runnersMap[ty][tx].size();
		runnersMap[ty][tx].clear();
	}

	// 이후 2칸 까지 처리하기
	for (int i = 0; i < 2; i++) {
		ty += dy;
		tx += dx;
		//if (ty > n || tx > n || ty < 1 || tx < 1)break;
		if (trees[ty][tx] != 1) {
			cntRunners += runnersMap[ty][tx].size();
			dead_runners += runnersMap[ty][tx].size();
			runnersMap[ty][tx].clear();
		}
	}
	ans += turn * cntRunners;

	// 잡힌 도망자 처리 
	runners.clear();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (runnersMap[i][j].empty())continue;
			for (int q = 0; q < runnersMap[i][j].size(); q++) {
				Info now = runnersMap[i][j][q];
				runners.push_back(now);
			}
		}
	}

}

void func() {
	// 도망자 움직임
	moveRunner();


	// 술래 움직임
	moveHero();
}

int main() {

	input();
	makeHeroPos();
	for (int i = 1; i <= k; i++) {
		turn = i;
		func();

		if (dead_runners == m) {
			break;
		}
	}
	cout << ans;
	return 0;
}