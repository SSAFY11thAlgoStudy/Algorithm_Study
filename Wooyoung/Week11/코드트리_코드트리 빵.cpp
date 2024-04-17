#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#define MAX INT_MAX
using namespace std;
int n, m;
int map[16][16];
bool closed[16][16];
int dy[4] = { -1,0,0,1 };
int dx[4] = { 0,-1,1,0 };
int t;
struct Info {
	int y, x;
	bool closed;
};

struct Cmp {
	bool operator()(Info a, Info b) {
		if (a.y != b.y) {
			return a.y > b.y;
		}
		else {
			return a.x > b.x;
		}
	}
};

Info store[31];
vector<Info>players;
// map�� -1�� ���̽�ķ��, 0�� ��ĭ, 1�̻��� ���� �÷��̾��� ������ ��ȣ
void input() {

	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1)map[i][j] = -1;
		}
	}
	for (int i = 1; i <= m; i++) {
		int y, x;
		cin >> y >> x;
		store[i].y = y;
		store[i].x = x;
		store[i].closed = false;
		map[y][x] = i;
	}
	players.push_back({ 0,0,false });
}

bool isValid(int y, int x) {
	return y >= 1 && x >= 1 && y <= n && x <= n && !closed[y][x];
}

void firstMove() {

	// ���� �� �÷��̾ �ƹ��� ������ ���� x
	if (players.size() == 1)return;

	// ���� �� �÷��̾���� �̵�
	for (int i = 1; i < players.size(); i++) {
		bool visited[16][16] = { false, };
		vector<Info>temp;
		int y = players[i].y;
		int x = players[i].x;
		visited[y][x] = true;
		// ���� �÷��̾ �̹� ��ǥ �������� ������ ��� ���� x
		if (store[i].closed)continue;
		temp.push_back({ y,x,false });
		queue<vector<Info>>q;
		q.push(temp);
		bool flag = false;
		while (!q.empty()) {
			for (int j = 0; j < 4; j++) {
				vector<Info> now = q.front();
				// ���� �ֱ� �湮�� ������ ��ǥ
				int y = now[now.size() - 1].y;
				int x = now[now.size() - 1].x;
				//cout << y << " " << x << "\n";
				int ny = y + dy[j];
				int nx = x + dx[j];
				// ��ǥ ����, ��ĭ �Ǵ� ��ǥ �������� ����̸鼭 
				// ������ �ٸ� �÷��̾ �湮�� ���̽� ķ��, �������� �ƴ� ���� ����
				if (!isValid(ny, nx))continue;
				// ����, ���� visited �迭���� ���� �÷��̾ �湮���� ���� ������ ����
				if (visited[ny][nx])continue;
				visited[ny][nx] = true;
				now.push_back({ ny,nx,false });
				q.push(now);
				// ���������� ���� �ִܰ�θ� ã���� ��
				if (ny == store[i].y && nx == store[i].x) {
					flag = true;
					// ���� �÷��̾� �� ĭ �̵� �� ���� �÷��̾� ����
					players[i].y = now[1].y;
					players[i].x = now[1].x;
					//cout << t<<" "<<i << "�� �÷��̾�" << now[1].y << " " << now[1].x << "�� �̵�\n";
					break;
				}
			}
			if (flag)break;
			q.pop();
		}
	}

}

bool secondMove() {

	if (players.size() == 1)return true;
	for (int i = 1; i < players.size(); i++) {
		Info now = players[i];
		int y = now.y;
		int x = now.x;
		// ���̽�ķ�� Ȥ�� ��ǥ �������� ��� �湮 ó��
		if (map[y][x] == -1 || map[y][x] == i) {
			closed[y][x] = true;
			if (map[y][x] == i) {
				store[i].closed = true;
			}
		}
	}

	int cnt = 0;
	// �������� �湮ó�� ���� Ȯ��
	for (int i = 1; i <= m; i++) {
		if (store[i].closed)cnt++;
	}
	if (cnt == m)return false;
	return true;
}

void thirdMove() {
	if (t > m)return;
	int num = t;
	int sy = store[num].y;
	int sx = store[num].x;
	queue<pair<int, int>>q;
	q.push({ sy,sx });
	bool visited[16][16] = { false, };
	bool flag = false;
	priority_queue<Info, vector<Info>, Cmp>temp;
	visited[sy][sx] = true;
	int dist = MAX;
	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (!isValid(ny, nx))continue;
			if (visited[ny][nx])continue;
			if (map[ny][nx] == -1) {
				int dis = abs(sy - ny) + abs(sx - nx);
				if (dist >= dis) {
					dist = dis;
					temp.push({ ny,nx,false });
				}
				else {
					flag = true;
				}
			}
			visited[ny][nx] = true;
			q.push({ ny,nx });
		}
		if (flag)break;
	}

	// ����� ����� �� �� �켱������ ���� �� 1������ �÷��̾��� ���̽� ķ�� ����
	players.push_back(temp.top());
	closed[temp.top().y][temp.top().x] = true;
}

bool func() {
	// 1. ���¿��� �켱������ �ִ� ��θ� ���� �� ��ĭ �̵�
	firstMove();
	// 2. �̵��� �÷��̾��� ��ǥ�� ������ Ȥ�� ���̽� ķ�� Ȯ��
	if (!secondMove())return false;
	// 3. ���� �� t�� ��� ���̽� ķ�� ����

	thirdMove();
	return true;
}

int main() {
	input();
	while (1) {
		t++;
		if (!func())break;
	}
	cout << t;
	return 0;
}