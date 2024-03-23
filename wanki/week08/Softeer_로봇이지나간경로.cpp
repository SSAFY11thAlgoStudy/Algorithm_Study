#include<iostream>
#include<vector>
#include<string>

using namespace std;

int H, W, min_path = 21e8;
int dy[] = { -1, 0, 1, 0 }, dx[] = { 0, 1, 0, -1 };
char arr[26][26];
string path;
vector<pair<int, int>> v;

void input() {
	cin >> H >> W;
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= W; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == '#') v.push_back({ i,j });
		}
	}
}

//��� ���� �ٳబ���� Ȯ��
bool check(int visit[26][26]) {
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= W; j++) {
			if (arr[i][j] == '#' && !visit[i][j]) return false;
		}
	}
	return true;
}

void go(int y, int x, int d, string cmd, int visit[26][26]) {
	if (check(visit)) {
		if (min_path > cmd.size()) {
			path = cmd;
			min_path = cmd.size();
		}
		return;
	}

	//4���� Ž��
	for (int i = 0; i < 4; i++) {
		d = (d + 1) % 4;
		string temp = "";
		if (i == 0) temp = "R";
		if (i == 1) temp = "RR";
		if (i == 2) temp = "L";

		//A�϶� 2ĭ ������ ���⿡ �Ÿ�1, 2�� Ȯ��
		int ny = y + (dy[d] * 2);
		int nx = x + (dx[d] * 2);
		int my = y + dy[d];
		int mx = x + dx[d];
		//�� Ȯ��
		if (ny <= 0 || nx <= 0 || ny > H || nx > W) continue;
		//�̹� �湮�߰ų�, "."��ġ �Ͻ� �ٸ� �������� ����.
		if (visit[ny][nx] || visit[my][mx] || arr[ny][nx] == '.' || arr[my][mx] == '.') continue;
		//�湮 üũ
		visit[ny][nx] = 1;
		visit[my][mx] = 1;
		go(ny, nx, d, cmd + temp + "A", visit);
		//�湮�Ѱ��� �ٽ� ���� ����
		visit[ny][nx] = 0;
		visit[my][mx] = 0;
	}
}

int main(int argc, char** argv)
{
	int startY, startX;
	char dir;
	input();
	for (auto var : v) {
		for (int i = 0; i < 4; i++) {
			int visit[26][26] = { 0 };
			visit[var.first][var.second] = 1;
			int temp = min_path;
			go(var.first, var.second, i, "", visit);
			if (min_path < temp) {
				if (i == 0) dir = '^';
				if (i == 1) dir = '>';
				if (i == 2) dir = 'v';
				if (i == 3) dir = '<';
				startY = var.first;
				startX = var.second;
			}
		}
	}
	cout << startY << " " << startX << "\n" << dir << "\n" << path;
}