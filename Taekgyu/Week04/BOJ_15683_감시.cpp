#define _NO_CRT_NO_SECURE
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;

struct CCTV
{
	int y;
	int x;
	int kind;
};
vector<CCTV>cam;

int N, M;
int cnt;
int Min = 21e8;
int MAP[9][9];
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
int flag = 0;

void fill(int y, int x, int kind, int dir) {
	int nowy = y;
	int nowx = x;
	int nowDr = dir;
	if (kind == 1) {
		while (true) {
			int ny = y + dy[nowDr];
			int nx = x + dx[nowDr];

			if (ny >= N || nx >= M || ny < 0 || nx < 0) break;
			else if (MAP[ny][nx] == 6) break;
			else if (MAP[ny][nx] == 0) MAP[ny][nx] = -1;
			y = ny;
			x = nx;
		}
	}
	else if (kind == 2) {
		while (true) {
			int ny = y + dy[nowDr];
			int nx = x + dx[nowDr];
			if (ny >= N || nx >= M || ny < 0 || nx < 0) break;
			else if (MAP[ny][nx] == 6) break;
			else if (MAP[ny][nx] == 0) MAP[ny][nx] = -1;
			y = ny;
			x = nx;
		}
		y = nowy;
		x = nowx;
		while (true) {
			int ny = y + dy[(nowDr + 2) % 4];
			int nx = x + dx[(nowDr + 2) % 4];
			if (ny >= N || nx >= M || ny < 0 || nx < 0) break;
			else if (MAP[ny][nx] == 6) break;
			else if (MAP[ny][nx] == 0) MAP[ny][nx] = -1;
			y = ny;
			x = nx;
		}
	}

	else if (kind == 3) {
		while (true) {
			int ny = y + dy[nowDr];
			int nx = x + dx[nowDr];
			if (ny >= N || nx >= M || ny < 0 || nx < 0)break;
			else if (MAP[ny][nx] == 6)break;
			else if (MAP[ny][nx] == 0)MAP[ny][nx] = -1;
			y = ny;
			x = nx;
		}
		y = nowy;
		x = nowx;
		while (true) {
			int ny = y + dy[(nowDr + 1) % 4];
			int nx = x + dx[(nowDr + 1) % 4];
			if (ny >= N || nx >= M || ny < 0 || nx < 0)break;
			else if (MAP[ny][nx] == 6)break;
			else if (MAP[ny][nx] == 0)MAP[ny][nx] = -1;
			y = ny;
			x = nx;
		}
	}

	else if (kind == 4) {
		while (true) {
			int ny = y + dy[nowDr];
			int nx = x + dx[nowDr];
			if (ny >= N || nx >= M || ny < 0 || nx < 0)break;
			else if (MAP[ny][nx] == 6)break;
			else if (MAP[ny][nx] == 0)MAP[ny][nx] = -1;
			y = ny;
			x = nx;
		}
		y = nowy;
		x = nowx;
		while (true) {
			int ny = y + dy[(nowDr + 1) % 4];
			int nx = x + dx[(nowDr + 1) % 4];
			if (ny >= N || nx >= M || ny < 0 || nx < 0)break;
			else if (MAP[ny][nx] == 6)break;
			else if (MAP[ny][nx] == 0)MAP[ny][nx] = -1;
			y = ny;
			x = nx;
		}
		y = nowy;
		x = nowx;
		while (true) {
			int ny = y + dy[(nowDr + 2) % 4];
			int nx = x + dx[(nowDr + 2) % 4];
			if (ny >= N || nx >= M || ny < 0 || nx < 0)break;
			else if (MAP[ny][nx] == 6)break;
			else if (MAP[ny][nx] == 0)MAP[ny][nx] = -1;
			y = ny;
			x = nx;
		}
	}
	else if (kind == 5) {
		for (int i = 0; i < 4; i++)
		{
			y = nowy;
			x = nowx;
			while (true) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny >= N || nx >= M || ny < 0 || nx < 0)break;
				else if (MAP[ny][nx] == 6)break;
				else if (MAP[ny][nx] == 0)MAP[ny][nx] = -1;
				y = ny;
				x = nx;
			}
		}
	}
}

void dfs(int now) {
	if (now == cam.size()) {
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (MAP[i][j] == 0) {
					cnt++;
				}
			}
		}

		if (Min >= cnt) {
			Min = cnt;
		}
		cnt = 0;
		return;
	}

	int y = cam[now].y;
	int x = cam[now].x;
	int kind = cam[now].kind;
	int copyMAP[9][9];

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			copyMAP[i][j] = MAP[i][j];
		}
	}

	for (int i = 0; i < 4; i++)
	{
		fill(y, x, kind, i);
		dfs(now + 1);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				MAP[i][j] = copyMAP[i][j];
			}
		}

	}
}

int main() {

	//freopen("sample_input.txt", "r", stdin);
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> MAP[i][j];
			if (MAP[i][j] != 0 && MAP[i][j] != 6) {
				cam.push_back({ i,j,MAP[i][j] });
			}
		}
	}
	dfs(0);
	cout << Min;
	return 0;
}