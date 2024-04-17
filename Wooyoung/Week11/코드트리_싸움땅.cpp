#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int n, m, k;
priority_queue<int> map[21][21];
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
struct Player {
	int y, x, d, s, gun_damage;
};
vector<Player>players;
int playersMap[21][21];
int ans[21];
void input() {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int gun;
			cin >> gun;
			if (gun > 0) {
				map[i][j].push(gun);
			}
		}
	}


	int y, x, d, s;
	players.push_back({ 0,0,0,0,0 });
	for (int i = 0; i < m; i++) {
		cin >> y >> x >> d >> s;
		Player input = { y,x,d,s,0 };
		playersMap[y][x] = i + 1;
		players.push_back(input);
	}
}

bool isValid(int y, int x) {
	return y >= 1 && x >= 1 && y <= n && x <= n;
}

void func() {

	// 1�� �÷��̾� ���� �ڽ��� ������ �� ĭ �̵� 
	// ���� ���� ���� ��� ���ݴ�� (���� ���� �ؾ���)
	for (int i = 1; i < players.size(); i++) {
		Player now = players[i];
		int y = now.y;
		int x = now.x;

		int d = now.d;
		int ny = y + dy[d];
		int nx = x + dx[d];
		// 0 -> 2, 2 -> 0, 1 -> 3, 3 -> 1
		// ���� ������ ������ Ȯ�� �� ��ǥ ����
		if (!isValid(ny, nx)) {
			now.d = (d + 2) % 4;
			ny = y + dy[now.d];
			nx = x + dx[now.d];
		}
		now.y = ny;
		now.x = nx;
		// �̵� ������ �÷��̾ ���� ���
		if (playersMap[ny][nx] == 0) {
			// �÷��̾�� ����, ���� �ִ� ���
			if (!map[ny][nx].empty()) {
				// ���� ���� �������� ��
				int strongest_gun = map[ny][nx].top();
				// ���� ���� ���� ���
				if (now.gun_damage == 0) {
					now.gun_damage = strongest_gun;
					map[ny][nx].pop();
				}
				// ���� ���� �ִ� ���
				else {
					// ���� ���� �������� ���� �� ���� ��ü
					if (strongest_gun > now.gun_damage) {
						int temp = now.gun_damage;
						now.gun_damage = strongest_gun;
						map[ny][nx].pop();
						map[ny][nx].push(temp);
					}
				}
			}
			players[i] = now;
			playersMap[y][x] = 0;
			playersMap[ny][nx] = i;
		}

		// �̵� ������ �÷��̾ �ִ� ���
		else {

			int nowNum = i;
			int nextNum = playersMap[ny][nx];
			Player next = players[nextNum];

			// �� �÷��̾��� �ɷ�ġ�� ���ݷ��� �� ��
			int nowSum = now.s + now.gun_damage;
			int nextSum = next.s + next.gun_damage;
			int dif = nowSum - nextSum;

			bool nowWin = false;


			if (dif > 0) {
				nowWin = true;
				ans[nowNum] += dif;
			}
			else if (dif < 0) {
				ans[nextNum] += (-1 * dif);
			}
			else {
				int dif_s = now.s - next.s;
				if (dif_s > 0) {
					nowWin = true;
				}
			}

			// ���� ��ġ 0���� ����
			playersMap[y][x] = 0;

			// ���� �÷��̾ �� ���
			if (!nowWin) {
				// ���� �÷��̾�� ���� �����ϰ� ������ ��������
				if (now.gun_damage > 0) {
					map[ny][nx].push(now.gun_damage);
					now.gun_damage = 0;
				}
				// ���� �÷��̾�� ���� ĭ���� �̵�
				int loser_ny = 0, loser_nx = 0;
				int temp_d = now.d;
				for (int j = 0; j < 4; j++) {
					now.d = (temp_d + j) % 4;
					loser_ny = ny + dy[now.d];
					loser_nx = nx + dx[now.d];
					// ���� �� Ȥ�� �ٸ� �÷��̾� ���� �� 90�� ȸ��
					if (!isValid(loser_ny, loser_nx) || playersMap[loser_ny][loser_nx] > 0)continue;
					// ���� ������ Ȯ��
					break;
				}

				// �ش� ĭ�� ���� �ִٸ�
				if (!map[loser_ny][loser_nx].empty()) {
					// ���� ���� �������� �� ����
					int strongest_gun = map[loser_ny][loser_nx].top();
					now.gun_damage = strongest_gun;
					map[loser_ny][loser_nx].pop();

				}

				// ���� �÷��̾�� ���� ĭ�� ������ �� �� ���� �����ŷ� ��ü
				if (!map[ny][nx].empty()) {
					int strongest_gun = map[ny][nx].top();
					if (strongest_gun > next.gun_damage) {
						int temp = next.gun_damage;
						next.gun_damage = strongest_gun;
						map[ny][nx].pop();
						map[ny][nx].push(temp);
					}
				}
				// ���� �÷��̾� ��ġ �� ��ȣ ����
				now.y = loser_ny;
				now.x = loser_nx;
				playersMap[loser_ny][loser_nx] = nowNum;
			}

			// ���� �÷��̾ �̱� ���
			else {
				// ���� �÷��̾�� ���� �����ϰ� ������ ��������
				if (next.gun_damage > 0) {
					map[ny][nx].push(next.gun_damage);
					next.gun_damage = 0;
				}
				// ���� �÷��̾�� ���� ĭ���� �̵�
				int loser_ny = 0, loser_nx = 0;
				int temp_d = next.d;
				for (int j = 0; j < 4; j++) {
					next.d = (temp_d + j) % 4;
					loser_ny = ny + dy[next.d];
					loser_nx = nx + dx[next.d];
					// ���� ���̸� 90�� ȸ��
					if (!isValid(loser_ny, loser_nx) || playersMap[loser_ny][loser_nx] > 0)continue;
					// ���� ������ Ȯ��
					break;
				}

				// �ش� ĭ�� ���� �ִٸ�
				if (!map[loser_ny][loser_nx].empty()) {
					// ���� ���� �������� �� ����
					int strongest_gun = map[loser_ny][loser_nx].top();
					next.gun_damage = strongest_gun;
					map[loser_ny][loser_nx].pop();

				}

				// ���� �÷��̾�� ���� ĭ�� ������ �� �� ���� �����ŷ� ��ü
				if (!map[ny][nx].empty()) {
					int strongest_gun = map[ny][nx].top();
					if (strongest_gun > now.gun_damage) {
						int temp = now.gun_damage;
						now.gun_damage = strongest_gun;
						map[ny][nx].pop();
						map[ny][nx].push(temp);
					}
				}
				// ���� �÷��̾�� ���� �÷��̾��� ��ġ�� ��ȣ ����
				next.y = loser_ny;
				next.x = loser_nx;
				now.y = ny;
				now.x = nx;
				playersMap[ny][nx] = nowNum;
				playersMap[loser_ny][loser_nx] = nextNum;

			}
			players[nowNum] = now;
			players[nextNum] = next;
		}
	}
}

int main() {

	input();
	for (int i = 0; i < k; i++) {
		func();
	}
	for (int i = 1; i <= m; i++) {
		cout << ans[i] << " ";
	}
	return 0;
}