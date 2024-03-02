#include<iostream>
#include<queue>
#include<vector>

using namespace std;

int N;
int map[21][21];
int dy[] = { -1,0,0,1 }, dx[] = { 0, -1,1,0 }; // 상 좌 우 화
int times = 0, cnt = 0;
int sizes = 2;
struct point {
	int y;
	int x;
	int dist = 0;
};
point baby_shark;

struct cmp {
	//거리가 가까운 것부터
	// 만약 같다면 위쪽에있는 거부터 그리고 왼쪽
	bool operator() (point a, point b) {
		if (a.dist == b.dist) {
			if (a.y == b.y) {
				return a.x > b.x;
			}
			return a.y > b.y;
		}
		return a.dist > b.dist;
	}
};

//공간의 상태는 0, 1, 2, 3, 4, 5, 6, 9로 이루어져 있다
//0: 빈 칸
//1, 2, 3, 4, 5, 6 : 칸에 있는 물고기의 크기
//9 : 아기 상어의 위치
void input() {
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 9) {
				baby_shark = { i,j };
				map[i][j] = 0;
			}
		}
	}
}

int bfs() {
	// 사이즈가 더 큰곳으 지나갈수 없으나 거리에 따르므로 정렬을 함
	priority_queue<point, vector<point>, cmp>pq;
	int visit[21][21] = { 0 };
	pq.push(baby_shark);

	while (!pq.empty()) {
		point now = pq.top();
		pq.pop();

		if (map[now.y][now.x] < sizes && map[now.y][now.x] != 0) {
			times += now.dist; // 물고기를 먹은 후에 times 값 증가
			baby_shark = { now.y, now.x }; // 아기상어 위치 변환
			cnt++; // 물고기먹은 횟수
			map[now.y][now.x] = 0; //먹은 물고기 없애줌
			return 1;
		}
		for (int i = 0; i < 4; i++)
		{
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			//범위 지정
			if (ny < 0 || nx < 0 || ny >= N || nx >= N)continue;
			//사이즈가 같으면 통과가능
			if (visit[ny][nx] >= 1 || map[ny][nx] > sizes) continue;
			// 거리
			visit[ny][nx] = 1 + visit[now.y][now.x];
			pq.push({ ny,nx, visit[ny][nx] });
		}
	}
	return 0;
}



int main() {
	input();
	// 먹을 물고기가 없을때 까지
	while (bfs()) {
		//물고기를 먹은 횟수가 사이즈와 같다면 size up
		if (cnt == sizes) {
			sizes++;
			//먹이를 먹은 횟수초기화
			cnt = 0;
		}
	}
	cout << times;
	return 0;
}