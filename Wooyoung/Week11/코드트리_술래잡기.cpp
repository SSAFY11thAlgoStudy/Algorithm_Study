#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

int n, m, h, k;

// �������� ����迭
int dy[2] = { 1,-1 };
int dx[2] = { 1,-1 };

// ������ ����迭
// �������
int dy1[4] = { -1,0,1,-1 };
int dx1[4] = { 0,1,0,-1 };

// �Ͽ����
int dy2[4] = { 1,0,-1,0 };
int dx2[4] = { 0,1,0,-1 };

struct Info {
	int y, x, id, d;
	bool isDead;
};

struct Info2 {
	int y, x, d, move_cnt;
};

// ���Ϳ��� ������ ��ϵ� �����ڵ鸸 �̵�
// �̵� ����� �ʿ� ����

vector<Info>runners;
vector<Info>runnersMap[100][100];
int trees[100][100];
// sd�� 0 -> �߽ɿ��� (1,1)��, sd�� 1 -> (1,1)���� �߽�����
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

	// (1,1)���� �������� ����
	// ù��° ���� �׳� ����
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

		// ���� �����ڴ� ���� x
		if (now.isDead)continue;

		// �������� �Ÿ��� 3 �ʰ��� ��� ���� x
		int dis = abs(now.y - Hero.y) + abs(now.x - Hero.x);
		if (dis > 3)continue;

		// ���� ĭ 
		int ny = now.y;
		int nx = now.x;

		// id�� 1�� ��� �¿�, 2�� ��� ����
		if (now.id == 1) {
			nx += dx[now.d];
			// nx�� ���� �ʰ��� �� (0 �Ǵ� n+1�� ��)
			if (nx == 0 || nx == n + 1) {
				now.d = (now.d + 1) % 2;
				// ���� ��ġ���� ���� �ٲپ� 1ĭ �̵�
				nx = now.x + dx[now.d];
			}
		}
		else if (now.id == 2) {
			ny += dy[now.d];
			// ny�� ���� �ʰ��� �� (0 �Ǵ� n+1�� ��)
			if (ny == 0 || ny == n + 1) {
				now.d = (now.d + 1) % 2;
				// ���� ��ġ���� ���� �ٲپ� 1ĭ �̵�
				ny = now.y + dy[now.d];
			}
		}
		// �̵��Ϸ��� ��ǥ (ny,nx)�� ������ ������ ���� x
		// ���� ��ȯ�� ���ְ� ���� x 
		runners[i] = now;
		if (Hero.y == ny && Hero.x == nx)continue;

		// �̵��Ϸ��� ��ǥ (ny,nx)�� ������ ������ ���� 
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

	// nxn ũ���� ���Ϳ� ������ ��ǥ�� ���� (0~ nxn-1)
	// ���� �̵� Ƚ���� move_cnt
	// ���� ������ n-move_cnt
	Hero.move_cnt++;
	int y = Hero.y;
	int x = Hero.x;
	int ny, nx, nny, nnx;
	// ������ �� �ٶ󺸴� ������
	// ���� ��ǥ ����, ���� ��ǥ�� �ٴ��� ��ǥ�� ���̸� �̿��ؾ��Ѵ�.
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

	// ������ ��, ���� ��������, �� �������� ���� ĭ ���� 3ĭ�� Ȯ��
	int ty = ny;
	int tx = nx;

	int cntRunners = 0;

	// ���� ĭ �߰� �� ���� ĭ�� �����ϴ� �����ڵ� ����
	if (trees[ty][tx] != 1) {
		cntRunners += runnersMap[ty][tx].size();
		dead_runners += runnersMap[ty][tx].size();
		runnersMap[ty][tx].clear();
	}

	// ���� 2ĭ ���� ó���ϱ�
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

	// ���� ������ ó�� 
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
	// ������ ������
	moveRunner();


	// ���� ������
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