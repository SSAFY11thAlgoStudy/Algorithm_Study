#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

struct hole
{
	int y;
	int x;
};
struct wall
{
	int input;
	int output;
};

vector<wall>w[6];
vector<hole> h[11];

int T;
int N;
int MAP[100][100];
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
int Maxans = -21e8;

void init() {
	Maxans = -21e8;
	memset(h, 0, sizeof(h));
	memset(MAP, 0, sizeof(MAP));
}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> MAP[i][j];

			if (MAP[i][j] >= 6 && MAP[i][j] <= 10) {
				h[MAP[i][j]].push_back({ i,j });
			}
		}
	}
}

int simulation(int sy, int sx, int dir) {

	int score = 0;
	int starty = sy;
	int startx = sx;
	int nowdir = dir;

	while (true) {
		int ny = starty + dy[nowdir];
		int nx = startx + dx[nowdir];

		// 벽을 만났을 때 => 방향 변경 및 점수 추가
		if (ny >= N || nx >= N || ny < 0 || nx < 0) {
			nowdir = (nowdir + 2) % 4;
			starty = ny;
			startx = nx;
			score++;
		}
		else {

			starty = ny;
			startx = nx;
			// 블록에 닿았을 때
			if (MAP[ny][nx] >= 1 && MAP[ny][nx] <= 5) {
				int flag = 0;
				// 여기가 왜 6인지 진짜 아직도 이해가 안됨 씨 벌
				for (int i = 1; i <= 6; i++)
				{
					if (flag == 1) {
						score++;
						break;
					}
					for (int j = 0; j < 4; j++)
					{
						if (MAP[ny][nx] == i) {
							if (nowdir == w[i][j].input) {
								nowdir = w[i][j].output;
								flag = 1;
								break;
							}
						}
					}
				}
			}

			// 홀에 빠졌을 때
			if (MAP[ny][nx] >= 6 && MAP[ny][nx] <= 10) {

				int flag = 0;
				for (int i = 6; i <= 10; i++)
				{
					if (flag == 1)break;
					for (int j = 0; j < 2; j++)
					{
						if (h[i][j].y == ny && h[i][j].x == nx) {
							starty = h[i][(j + 1) % 2].y;
							startx = h[i][(j + 1) % 2].x;
							flag = 1;
							break;
						}

					}
				}
			}

			// 블랙홀에 갔을 때
			if (MAP[ny][nx] == -1) {
				break;
			}
			// 시작 지점으로 돌아왔을 때
			if (ny == sy && nx == sx) {
				break;
			}
		}
	}
	return score;
}

void bfs() {
	// 맵에서 0일때 출발 할 수 있다 
	// 출발 할 수 있는 칸의 개수 * 방향 4가지
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (MAP[i][j] == 0) {
				for (int d = 0; d < 4; d++)
				{
					int ans = simulation(i, j, d);
					Maxans = max(Maxans, ans);
				}
			}
		}
	}
}

int main() {
	freopen("sample_input.txt", "r", stdin);
	cin >> T;
	// 벽 설정
	w[1].push_back({ 3,0 });
	w[1].push_back({ 2,1 });
	w[1].push_back({ 1,3 });
	w[1].push_back({ 0,2 });
	w[2].push_back({ 0,1 });
	w[2].push_back({ 3,2 });
	w[2].push_back({ 1,3 });
	w[2].push_back({ 2,0 });
	w[3].push_back({ 1,2 });
	w[3].push_back({ 0,3 });
	w[3].push_back({ 2,0 });
	w[3].push_back({ 3,1 });
	w[4].push_back({ 2,3 });
	w[4].push_back({ 1,0 });
	w[4].push_back({ 0,2 });
	w[4].push_back({ 3,1 });
	w[5].push_back({ 0,2 });
	w[5].push_back({ 1,3 });
	w[5].push_back({ 2,0 });
	w[5].push_back({ 3,1 });

	for (int tc = 1; tc <= T; tc++)
	{
		init();
		input();
		bfs();
		cout << "#" << tc << " " << Maxans << endl;
	}
	return 0;
}