#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int n, m, h, k;
int map[101][101];
int cmap[101][101];
struct Player {
	int y, x, dir;
};

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };

vector<Player>p;
Player c;

bool iscatched[10001];

void input() {
	cin >> n >> m >> h >> k;

	p.push_back({});
	for (int i = 1; i <= m; i++) {
		int t1, t2, t3;
		cin >> t1 >> t2 >> t3;
		p.push_back({ t1, t2, t3 });
	}

	for (int i = 0; i < h; i++) {
		int t1, t2;
		cin >> t1 >> t2;
		map[t1][t2] = 2;
	}

	cmap[n / 2 + 1][n / 2 + 1] = 1;
	c = { n / 2 + 1, n / 2 + 1, 0 };
}

void pmove() {

	for (int i = 1; i <= m; i++) {

		if (iscatched[i] == true) continue;

		int dist = abs(p[i].x - c.x) + abs(p[i].y - c.y);
		if (dist > 3) continue;

		int ny = p[i].y + dy[p[i].dir];
		int nx = p[i].x + dx[p[i].dir];

		if (ny < 1 || nx < 1 || ny > n || nx >n) {
			p[i].dir = (p[i].dir + 2) % 4;
			ny = p[i].y + dy[p[i].dir];
			nx = p[i].x + dx[p[i].dir];
		}

		if (cmap[ny][nx] == 1) continue;

		p[i].x = nx;
		p[i].y = ny;
	}
}

void print() {
	int pmap[6][6] = { 0, };

	for (int i = 1; i <= m; i++) {
		if (iscatched[i] == true) continue;
		pmap[p[i].y][p[i].x] = i;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << pmap[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

int m_cnt;
int mm;
int m_max = 1;
int flag;

void movec() {
	if (flag == 0) {
		int ny = c.y + dy[c.dir];
		int nx = c.x + dx[c.dir];

		mm++;
		if (mm == m_max) {
			m_cnt++;
			mm = 0;
			c.dir = (c.dir + 1) % 4;
		}

		if (m_cnt == 2) {
			m_max++;
			m_cnt = 0;
		}

		cmap[c.y][c.x] = 0;
		c.x = nx;
		c.y = ny;
		cmap[c.y][c.x] = 1;
		if (nx == 1 && ny == 1) {
			mm = 0;
			m_cnt = -1;
			flag = 1;
			c.dir = (c.dir + 2) % 4;
			m_max--;
		}
	}
	else {
		int ny = c.y + dy[c.dir];
		int nx = c.x + dx[c.dir];

		cmap[c.y][c.x] = 0;
		c.x = nx;
		c.y = ny;
		cmap[c.y][c.x] = 1;
		if (nx == (n / 2 + 1) && ny == (n / 2 + 1)) {
			mm = 0;
			m_cnt = 0;
			flag = 0;
			c.dir = (c.dir + 2) % 4;
			return;
		}

		mm++;
		if (mm == m_max) {
			m_cnt++;
			mm = 0;
			c.dir = (c.dir + 3) % 4;
		}

		if (m_cnt == 2) {
			m_max--;
			m_cnt = 0;
		}
	}
}

int result;

void search(int turn) {
	int cnt = 0;
	for (int i = 0; i < 3; i++) {
		int ny = c.y + dy[c.dir] * i;
		int nx = c.x + dx[c.dir] * i;

		if (ny < 1 || nx < 1 || ny > n || nx >n) continue;

		if (map[ny][nx] == 2) continue;

		for (int j = 1; j <= m; j++) {
			if (iscatched[j] == true) continue;

			if (ny == p[j].y && nx == p[j].x) {
				iscatched[j] = true;
				cnt++;
			}
		}
	}
	result = result + cnt * turn;
}

void solve() {

	for (int i = 1; i <= k; i++) {
		pmove();
		//print();
		movec();
		search(i);
	}
}

int main() {

	//freopen("sample.txt", "r", stdin);

	input();
	solve();
	cout << result;

	return 0;
}