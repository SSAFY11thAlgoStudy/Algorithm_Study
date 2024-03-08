#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>

using namespace std;
int N;
int map[101][101];
int dy[] = { -1,0,1,0 }, dx[] = { 0,1,0,-1 };

struct point {
	int y;
	int x;
};
vector<point>warmhole[11];

void init() {
	for (int i = 5; i < 11; i++)
	{
		warmhole[i].clear();
	}
}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
			//ø˙ »¶¿˙¿Â
			if (map[i][j] > 5) {
				warmhole[map[i][j]].push_back({ i,j });
			}
		}
	}
}
int simulation(point st, int dir) {
	point now = st;
	int cnt = 0;
	while (1) {
		now.y += dy[dir];
		now.x += dx[dir];



		// ∫Æ¿ª ∏∏≥µ¿ª ∂ß
		if (now.y < 0 || now.x < 0 || now.y >= N || now.x >= N) {
			cnt++;
			dir = (dir + 2) % 4;
			continue;
		}

		// Ω√¿€¡°¿Ã≥™ ∫Ì∑¢»¶¿ª ∏∏≥µ¿ª∂ß 
		if ((now.y == st.y && now.x == st.x) || map[now.y][now.x] == -1) {
			return cnt;
		}

		// ∫Ûƒ≠¿ª ∏∏≥µ¿ª ∂ß
		if (map[now.y][now.x] == 0)continue;

		// ∫Ì∑∞¿ª ∏∏≥µ¿ª∂ß
		if (map[now.y][now.x] <= 5) {
			int block = map[now.y][now.x];
			cnt++;
			switch (block)
			{
			case 1: {
				if (dir == 2) dir = 1;
				else if (dir == 3) dir = 0;
				else dir = (dir + 2) % 4;
				break;
			}
			case 2: {
				if (dir == 0) dir = 1;
				else if (dir == 3) dir = 2;
				else dir = (dir + 2) % 4;
				break;
			}
			case 3: {
				if (dir == 0) dir = 3;
				else if (dir == 1) dir = 2;
				else dir = (dir + 2) % 4;
				break;
			}
			case 4: {
				if (dir == 2) dir = 3;
				else if (dir == 1) dir = 0;
				else dir = (dir + 2) % 4;
				break;
			}
			case 5: {
				dir = (dir + 2) % 4;
				break;
			}
			}
		}
		// ø˙»¶¿ª ∏∏≥µ¿ªãö 
		else {
			int block = map[now.y][now.x];
			if (warmhole[block][0].y == now.y && warmhole[block][0].x == now.x) {
				now.y = warmhole[block][1].y;
				now.x = warmhole[block][1].x;
			}
			else {
				now.y = warmhole[block][0].y;
				now.x = warmhole[block][0].x;
			}
		}

	}


}

int solve() {
	int maxi = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[i][j] != 0)continue;
			for (int d = 0; d < 4; d++)
			{
				int ret = simulation({ i,j }, d);
				maxi = max(maxi, ret);
			}
		}
	}
	return maxi;
}

int main() {
	//freopen("sample_input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		init();
		input();
		int result = solve();

		cout << "#" << tc << " " << result << "\n";
	}

	return 0;
}