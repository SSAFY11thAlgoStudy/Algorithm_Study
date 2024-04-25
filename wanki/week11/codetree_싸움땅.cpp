#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

int n, m, k;
// n�� ������ ũ��,
// m�� �÷��̾��� ��,
// k�� ������ ��
vector<int>map[21][21];
int player_map[21][21] = { 0, };

int score[31];
int dy[] = { -1,0,1,0 }, dx[] = { 0,1,0,-1 };

struct player_info
{
	int y, x, d, s, gun;
};
vector<player_info>player;
void input() {
	int bangbangbang;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> bangbangbang;
			map[i][j].push_back(bangbangbang);
		}
	}
	int x, y, d, s;
	player.push_back({ 0,0,0,0,0 });
	for (int i = 1; i <= m; i++)
	{
		cin >> y >> x >> d >> s;
		player.push_back({ y,x,d,s,0 });
		player_map[y][x] = i;
	}
}

void loser(int num) {
	// ������ ������ �� �ΰ� ����
	map[player[num].y][player[num].x].push_back(player[num].gun);
	sort(map[player[num].y][player[num].x].begin(), map[player[num].y][player[num].x].end(), greater<>());
	player[num].gun = 0;
	int ny = player[num].y + dy[player[num].d];
	int nx = player[num].x + dx[player[num].d];
	if (ny <= 0 || nx <= 0 || ny > n || nx > n || player_map[ny][nx] != 0) {
		player[num].d = (player[num].d + 1) % 4;
		ny = player[num].y + dy[player[num].d];
		nx = player[num].x + dx[player[num].d];
		if (ny <= 0 || nx <= 0 || ny > n || nx > n || player_map[ny][nx] != 0) {
			player[num].d = (player[num].d + 1) % 4;
			ny = player[num].y + dy[player[num].d];
			nx = player[num].x + dx[player[num].d];
			if (ny <= 0 || nx <= 0 || ny > n || nx > n || player_map[ny][nx] != 0) {
				player[num].d = (player[num].d + 1) % 4;
				ny = player[num].y + dy[player[num].d];
				nx = player[num].x + dx[player[num].d];
			}
		}
	}
	player[num].y = ny;
	player[num].x = nx;
	player_map[player[num].y][player[num].x] = num;
	if (map[player[num].y][player[num].x][0] > player[num].gun) {
		map[player[num].y][player[num].x].push_back(player[num].gun);
		player[num].gun = map[player[num].y][player[num].x][0];
		map[player[num].y][player[num].x][0] = 0;
		sort(map[player[num].y][player[num].x].begin(), map[player[num].y][player[num].x].end(), greater<>());
	}
}

void winner(int num) {
	if (map[player[num].y][player[num].x][0] > player[num].gun) {
		map[player[num].y][player[num].x].push_back(player[num].gun);
		player[num].gun = map[player[num].y][player[num].x][0];
		map[player[num].y][player[num].x][0] = 0;
		sort(map[player[num].y][player[num].x].begin(), map[player[num].y][player[num].x].end(), greater<>());
	}
}

void solve(int num) {
	int ny = player[num].y + dy[player[num].d];
	int nx = player[num].x + dx[player[num].d];
	if (ny <= 0 || nx <= 0 || ny > n || nx > n) {
		player[num].d = (player[num].d + 2) % 4;
		ny = player[num].y + dy[player[num].d];
		nx = player[num].x + dx[player[num].d];
	}
	player_map[player[num].y][player[num].x] = 0;
	player[num].y = ny;
	player[num].x = nx;
	//�ٸ� �÷��̾ �ִ°��
	if (player_map[player[num].y][player[num].x] != 0) {
		int fight_num = player_map[player[num].y][player[num].x];
		int player1_ = player[num].s + player[num].gun;
		int player2_ = player[fight_num].s + player[fight_num].gun;
		// ���ݷ��� ���� ���
		if (player1_ == player2_) {
			//���� ���ݷ� ��
			if (player[num].s > player[fight_num].s) {
				loser(fight_num);
				winner(num);
			}
			else if (player[num].s < player[fight_num].s) {
				loser(num);
				winner(fight_num);
			}
		}
		// player1_(�̵��� ���)�� �̱���
		else if (player1_ > player2_) {
			score[num] += player1_ - player2_;
			loser(fight_num);
			winner(num);
		}
		// player2_(���� �ִ� ���)�� �̱���
		else if (player1_ < player2_) {
			score[fight_num] += player2_ - player1_;
			loser(num);
			winner(fight_num);
		}
	}
	player_map[player[num].y][player[num].x] = num;
	if (map[player[num].y][player[num].x][0] > player[num].gun) {
		map[player[num].y][player[num].x].push_back(player[num].gun);
		player[num].gun = map[player[num].y][player[num].x][0];
		map[player[num].y][player[num].x][0] = 0;
		sort(map[player[num].y][player[num].x].begin(), map[player[num].y][player[num].x].end(), greater<>());
	}

}

int main() {
	input();

	for (int i = 0; i < k; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			solve(j);
		}
	}

	for (int i = 1; i <= m; i++)
	{
		cout << score[i] << " ";
	}
	return 0;
}