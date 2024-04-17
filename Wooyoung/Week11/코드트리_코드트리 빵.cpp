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
// map의 -1은 베이스캠프, 0은 빈칸, 1이상의 수는 플레이어의 편의점 번호
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

	// 격자 내 플레이어가 아무도 없으면 진행 x
	if (players.size() == 1)return;

	// 격자 내 플레이어들의 이동
	for (int i = 1; i < players.size(); i++) {
		bool visited[16][16] = { false, };
		vector<Info>temp;
		int y = players[i].y;
		int x = players[i].x;
		visited[y][x] = true;
		// 현재 플레이어가 이미 목표 편의점에 도달한 경우 진행 x
		if (store[i].closed)continue;
		temp.push_back({ y,x,false });
		queue<vector<Info>>q;
		q.push(temp);
		bool flag = false;
		while (!q.empty()) {
			for (int j = 0; j < 4; j++) {
				vector<Info> now = q.front();
				// 가장 최근 방문한 지점의 좌표
				int y = now[now.size() - 1].y;
				int x = now[now.size() - 1].x;
				//cout << y << " " << x << "\n";
				int ny = y + dy[j];
				int nx = x + dx[j];
				// 좌표 내에, 빈칸 또는 목표 편의점인 경우이면서 
				// 이전에 다른 플레이어가 방문한 베이스 캠프, 편의점이 아닐 때만 가능
				if (!isValid(ny, nx))continue;
				// 또한, 현재 visited 배열에서 현재 플레이어가 방문하지 않은 지점만 가능
				if (visited[ny][nx])continue;
				visited[ny][nx] = true;
				now.push_back({ ny,nx,false });
				q.push(now);
				// 편의점으로 가는 최단경로를 찾았을 때
				if (ny == store[i].y && nx == store[i].x) {
					flag = true;
					// 현재 플레이어 한 칸 이동 후 다음 플레이어 진행
					players[i].y = now[1].y;
					players[i].x = now[1].x;
					//cout << t<<" "<<i << "번 플레이어" << now[1].y << " " << now[1].x << "로 이동\n";
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
		// 베이스캠프 혹은 목표 편의점인 경우 방문 처리
		if (map[y][x] == -1 || map[y][x] == i) {
			closed[y][x] = true;
			if (map[y][x] == i) {
				store[i].closed = true;
			}
		}
	}

	int cnt = 0;
	// 편의점의 방문처리 개수 확인
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

	// 저장된 경우의 수 중 우선순위가 높은 것 1가지로 플레이어의 베이스 캠프 배정
	players.push_back(temp.top());
	closed[temp.top().y][temp.top().x] = true;
}

bool func() {
	// 1. 상좌우하 우선순위로 최단 경로를 선택 후 한칸 이동
	firstMove();
	// 2. 이동한 플레이어의 좌표에 편의점 혹은 베이스 캠프 확인
	if (!secondMove())return false;
	// 3. 격자 밖 t번 사람 베이스 캠프 지정

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