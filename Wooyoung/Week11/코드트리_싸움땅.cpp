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

	// 1번 플레이어 부터 자신의 방향대로 한 칸 이동 
	// 만약 격자 밖인 경우 정반대로 (방향 갱신 해야함)
	for (int i = 1; i < players.size(); i++) {
		Player now = players[i];
		int y = now.y;
		int x = now.x;

		int d = now.d;
		int ny = y + dy[d];
		int nx = x + dx[d];
		// 0 -> 2, 2 -> 0, 1 -> 3, 3 -> 1
		// 격자 밖인지 안인지 확인 후 좌표 설정
		if (!isValid(ny, nx)) {
			now.d = (d + 2) % 4;
			ny = y + dy[now.d];
			nx = x + dx[now.d];
		}
		now.y = ny;
		now.x = nx;
		// 이동 지점에 플레이어가 없는 경우
		if (playersMap[ny][nx] == 0) {
			// 플레이어는 없고, 총이 있는 경우
			if (!map[ny][nx].empty()) {
				// 가장 높은 데미지의 총
				int strongest_gun = map[ny][nx].top();
				// 보유 총이 없는 경우
				if (now.gun_damage == 0) {
					now.gun_damage = strongest_gun;
					map[ny][nx].pop();
				}
				// 보유 총이 있는 경우
				else {
					// 가장 높은 데미지의 총이 더 세면 교체
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

		// 이동 지점에 플레이어가 있는 경우
		else {

			int nowNum = i;
			int nextNum = playersMap[ny][nx];
			Player next = players[nextNum];

			// 두 플레이어의 능력치와 공격력의 합 비교
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

			// 원래 위치 0으로 변경
			playersMap[y][x] = 0;

			// 현재 플레이어가 진 경우
			if (!nowWin) {
				// 현재 플레이어는 총을 보유하고 있으면 내려놓기
				if (now.gun_damage > 0) {
					map[ny][nx].push(now.gun_damage);
					now.gun_damage = 0;
				}
				// 현재 플레이어는 다음 칸으로 이동
				int loser_ny = 0, loser_nx = 0;
				int temp_d = now.d;
				for (int j = 0; j < 4; j++) {
					now.d = (temp_d + j) % 4;
					loser_ny = ny + dy[now.d];
					loser_nx = nx + dx[now.d];
					// 격자 밖 혹은 다른 플레이어 존재 시 90도 회전
					if (!isValid(loser_ny, loser_nx) || playersMap[loser_ny][loser_nx] > 0)continue;
					// 문제 없으면 확정
					break;
				}

				// 해당 칸에 총이 있다면
				if (!map[loser_ny][loser_nx].empty()) {
					// 가장 높은 데미지의 총 갖기
					int strongest_gun = map[loser_ny][loser_nx].top();
					now.gun_damage = strongest_gun;
					map[loser_ny][loser_nx].pop();

				}

				// 기존 플레이어는 현재 칸에 떨어진 총 중 가장 높은거로 교체
				if (!map[ny][nx].empty()) {
					int strongest_gun = map[ny][nx].top();
					if (strongest_gun > next.gun_damage) {
						int temp = next.gun_damage;
						next.gun_damage = strongest_gun;
						map[ny][nx].pop();
						map[ny][nx].push(temp);
					}
				}
				// 현재 플레이어 위치 및 번호 갱신
				now.y = loser_ny;
				now.x = loser_nx;
				playersMap[loser_ny][loser_nx] = nowNum;
			}

			// 현재 플레이어가 이긴 경우
			else {
				// 기존 플레이어는 총을 보유하고 있으면 내려놓기
				if (next.gun_damage > 0) {
					map[ny][nx].push(next.gun_damage);
					next.gun_damage = 0;
				}
				// 현재 플레이어는 다음 칸으로 이동
				int loser_ny = 0, loser_nx = 0;
				int temp_d = next.d;
				for (int j = 0; j < 4; j++) {
					next.d = (temp_d + j) % 4;
					loser_ny = ny + dy[next.d];
					loser_nx = nx + dx[next.d];
					// 격자 밖이면 90도 회전
					if (!isValid(loser_ny, loser_nx) || playersMap[loser_ny][loser_nx] > 0)continue;
					// 문제 없으면 확정
					break;
				}

				// 해당 칸에 총이 있다면
				if (!map[loser_ny][loser_nx].empty()) {
					// 가장 높은 데미지의 총 갖기
					int strongest_gun = map[loser_ny][loser_nx].top();
					next.gun_damage = strongest_gun;
					map[loser_ny][loser_nx].pop();

				}

				// 기존 플레이어는 현재 칸에 떨어진 총 중 가장 높은거로 교체
				if (!map[ny][nx].empty()) {
					int strongest_gun = map[ny][nx].top();
					if (strongest_gun > now.gun_damage) {
						int temp = now.gun_damage;
						now.gun_damage = strongest_gun;
						map[ny][nx].pop();
						map[ny][nx].push(temp);
					}
				}
				// 현재 플레이어와 기존 플레이어의 위치와 번호 갱신
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