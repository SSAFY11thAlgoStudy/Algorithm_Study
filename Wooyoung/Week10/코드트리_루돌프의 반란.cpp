#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<climits>
#include<cmath>
#define MAX INT_MAX
using namespace std;

// �� ĭ�� �Ÿ� -> ��Ʈ ����
// �絹���� ������
	// ���� ����� ��Ÿ�� ���� 1ĭ ����
	// Ż������ ���� ��Ÿ���� !
	// 2�� �̻��̶��, y�� ū, y�� ���ٸ� x�� ū ��Ÿ���� 
	// �����¿�, �밢�� ������ 8�������� ���� ����
	// �밢�� 1ĭ �̵����� ����
	// ���� �켱������ ���� ��Ÿ�� ���� 8���� �� ���� ��������� �������� �� ĭ ����
	// (���� �� �� ĭ�� �Ÿ��� ���ؼ� ���� ���� �ؾ���)

// ��Ÿ�� ������
	// 1������ P������ �������!
	// ���� Ȥ�� Ż�� ��Ÿ�� ������ x
	// �絹������ �Ÿ��� ���� ��������� �������� 1ĭ �̵�
	// �ٸ� ��Ÿ, ���� ������ �̵� �Ұ�
	// ������ �� ������ �������� ����
	// ������ �� �ִ� ĭ�� �־ �絹������ ����� ���� ���ϸ� �̵� x!
	// ��Ÿ�� �����¿�� �̵� ! (�絹���� �ٸ�)
	// ���� ������ ���������, ������� ������ �°� �̵�

// �浹
	// ��Ÿ�� �絹���� ���� ĭ�� ������ �浹
	// �絹���� �������� �߻��� ���
		// ��Ÿ�� C��ŭ�� ���� ȹ��, ���ÿ� ��Ÿ�� �絹���� �̵��� �� �������� Cĭ ��ŭ �з�����
	// ��Ÿ�� �������� �߻��� ���
		// ��Ÿ�� D��ŭ�� ���� ȹ��, ���ÿ� ��Ÿ�� �ڽ��� �̵��ؿ� �ݴ� �������� Dĭ ��ŭ �з�����
	// �з����� ���, �浹 �߻� ��� ��������, ��Ȯ�� ���ϴ� ��ġ�� ������!
	// ���� �з��� ��ġ�� ������ ���� ��� ��Ÿ�� Ż��
	// ���� �з��� ĭ�� �ٸ� ��Ÿ�� ���� ��� ��ȣ�ۿ� �߻�

// ��ȣ�ۿ�
	// �絹������ �浹 �Ŀ��� �߻�
	// ��Ÿ�� �浹 �� �����Ϸ��� ĭ�� �ٸ� ��Ÿ�� ������ �� ��Ÿ�� 1ĭ �ش� �������� �з���!
	// �� ���� �ٸ� ��Ÿ�� �� ���� ���, 1ĭ�� �з����� ���� �ݺ�
	// ����, �����ǿ� �з������� ��Ÿ�� ���� ��� �ش� ��Ÿ�� Ż��

// ����
	// ��Ÿ�� �絹������ �浹 �� ����
	// ���簡 k��, k+1��° ����, k+2��°���� �ٽ� �������� ������
	// ������ ��Ÿ�� ��������
	// �絹���� ������ ��Ÿ�� ���� ������� ���� ����

// ����
	// M���� �Ͽ� ���� �絹��, ��Ÿ�� ������� ������ �� ����
	// ���� P���� ��Ÿ�� ��� Ż���Ѵٸ� �� ��� ����
	// �� ���� ������ �� Ż������ ���� ��Ÿ���� +1���� ȹ��

int n, m, p, c, d;
int ry, rx;
int dead_cnt;
// ��,��,��,�� �밢
int dy[8] = { -1,0,1,0,1,1,-1,-1 };
int dx[8] = { 0,1,0,-1,1,-1,-1,1 };
int map[52][52];
struct Info {
	int y, x, score, stun_day;
	bool dead;
};

struct Pos {
	int y, x, dis;
};

struct Cmp {
	bool operator()(Pos a, Pos b) {
		if (a.dis != b.dis) {
			return a.dis > b.dis;
		}
		else if (a.y != b.y) {
			return a.y < b.y;
		}
		else {
			return a.x < b.x;
		}
	}
};

vector<Info>santa;

bool isIn(int y, int x) {
	return y >= 1 && x >= 1 && y <= n && x <= n;
}

void interaction(int y, int x, int num, int dir, int kind) {
	// ���� �� �������� ƨ���� ���ƿ��� ��Ÿ ��ȣ num
	// ������ �� ������ �ִ� ��Ÿ ��ȣ now_num
	// �� ���� (y,x)
	int now_num = map[y][x];
	map[y][x] = num;
	santa[num].y = y;
	santa[num].x = x;
	int ny = y;
	int nx = x;
	if (kind == 1) {
		ny -= dy[dir];
		nx -= dx[dir];
	}
	else {
		ny += dy[dir];
		nx += dx[dir];
	}
	if (!isIn(ny, nx)) {
		santa[now_num].dead = true;
		return;
	}
	else {
		if (map[ny][nx] > 0) {
			interaction(ny, nx, now_num, dir, kind);
		}
		else {
			map[ny][nx] = now_num;
			santa[now_num].y = ny;
			santa[now_num].x = nx;
			return;
		}
	}
}

bool func() {

	// �絹�� �̵�
	priority_queue<Pos, vector<Pos>, Cmp>rudol_dis;
	for (int i = 1; i <= p; i++) {
		Info now_santa = santa[i];
		if (now_santa.dead)continue;
		int dis = pow(ry - now_santa.y, 2) + pow(rx - now_santa.x, 2);
		rudol_dis.push({ now_santa.y,now_santa.x,dis });
	}

	// 8���⿡ ���� �̵� �� ���� �Ÿ��� ��������� ���� ã��
	if (rudol_dis.empty())return false;
	Pos selectedSanta = rudol_dis.top();
	int dis = MAX;
	int rdir = 0;
	int final_ry = 0;
	int final_rx = 0;
	for (int i = 0; i < 8; i++) {
		int temp_y = ry + dy[i];
		int temp_x = rx + dx[i];
		if (!isIn(temp_y, temp_x))continue;
		int temp_dis = pow(temp_y - selectedSanta.y, 2) + pow(temp_x - selectedSanta.x, 2);
		if (dis > temp_dis) {
			final_ry = temp_y;
			final_rx = temp_x;
			dis = temp_dis;
			rdir = i;
		}
	}

	// �絹�� �̵� �� ��Ÿ�� �ִ��� Ȯ��
	map[ry][rx] = 0;
	// ������
	if (map[final_ry][final_rx] > 0) {
		// ƨ�ܳ��� ��Ÿ�� ����
		int santa_y = final_ry + c * dy[rdir];
		int santa_x = final_rx + c * dx[rdir];
		int santa_num = map[final_ry][final_rx];
		// C ȹ��� ����
		santa[santa_num].score += c;
		santa[santa_num].stun_day = 2;
		// ����� ���̸� �ƿ�
		if (!isIn(santa_y, santa_x)) {
			santa[santa_num].dead = true;
			dead_cnt++;
			if (dead_cnt == p) {
				return false;
			}
		}

		// ����� ���̸�
		else {
			// �ڿ� ��Ÿ ��ȣ�ۿ� Ȯ��
			if (map[santa_y][santa_x] > 0) {
				// �� ��Ÿ ��ȣ ����
				int temp_santa_num = map[santa_y][santa_x];
				// ���� ��Ÿ ����
				map[santa_y][santa_x] = santa_num;
				santa[santa_num].y = santa_y;
				santa[santa_num].x = santa_x;
				// �� ���� ������ Ȯ���Ͽ� �����ۿ�
				int nny = santa_y + dy[rdir];
				int nnx = santa_x + dx[rdir];
				// ���� ������ ��ܶ�� ��� ó�� �� ���� x
				if (!isIn(nny, nnx)) {
					santa[temp_santa_num].dead = true;
					dead_cnt++;
					if (dead_cnt == p) {
						return false;
					}
				}
				// ��Ÿ�� �ڿ� �� �־��ٸ�?
				if (map[nny][nnx] > 0) {
					// ��ȣ�ۿ� �ǽ�
					interaction(nny, nnx, temp_santa_num, rdir, 2);
				}
				// ������ ��ĭ �ڷ� ���� 
				else {
					map[nny][nnx] = temp_santa_num;
					santa[temp_santa_num].y = nny;
					santa[temp_santa_num].x = nnx;
				}
			}
			// ��Ÿ�� ���� ������ �ٸ� ��Ÿ ������ �׳� ����
			else {
				map[santa_y][santa_x] = santa_num;
				santa[santa_num].y = santa_y;
				santa[santa_num].x = santa_x;
			}
		}

	}
	// �ش� ���� �絹�� �̵�
	ry = final_ry;
	rx = final_rx;
	map[ry][rx] = -1;


	// ��Ÿ �̵�
	for (int i = 1; i <= p; i++) {
		Info now_santa = santa[i];
		// �׾��ų� ������ ��Ÿ�� �н�
		if (now_santa.dead || now_santa.stun_day > 0)continue;
		int sy = now_santa.y;
		int sx = now_santa.x;
		int sdis = pow(sy - ry, 2) + pow(sx - rx, 2);
		int tempdis = MAX;
		int to_y = 0, to_x = 0;
		int sdir = 0;
		bool can_move = false;
		for (int j = 0; j < 4; j++) {
			int ny = sy + dy[j];
			int nx = sx + dx[j];
			// ������ �� �Ǵ� ��Ÿ�� �̹� �ִ� ���
			if (!isIn(ny, nx) || map[ny][nx] > 0)continue;
			int ndis = pow(ny - ry, 2) + pow(nx - rx, 2);
			// �������� ��������� �ʴ� ���
			if (sdis <= ndis)continue;
			if (tempdis > ndis) {
				// ������� ������ ���� �迭 ����
				// ���� ������ ���� ����� ���
				// ���� ���ϹǷ� ������� ������ ���� �����Ǿ�����
				to_y = ny;
				to_x = nx;
				sdir = j;
				tempdis = ndis;
				can_move = true;
			}
		}
		// ������ �� ���ų�, ������� �� ���ٸ� �̵� x
		if (!can_move)continue;

		// �̵�
		map[sy][sx] = 0;
		// �絹���� �ִٸ�?
		if (map[to_y][to_x] == -1) {
			// D ȹ�� �� ����
			santa[i].score += d;
			santa[i].stun_day = 2;
			// (to_y,to_x) �������� D��ŭ �з���
			int ny = to_y - d * dy[sdir];
			int nx = to_x - d * dx[sdir];
			// ����߳�?
			if (!isIn(ny, nx)) {

				santa[i].dead = true;
				dead_cnt++;
				if (dead_cnt == p) {
					return false;
				}
				map[sy][sx] = 0;
				continue;
			}
			// ��Ҵٸ�?
			// ���� ��Ÿ�� �� ���� ������?
			if (map[ny][nx] > 0) {

				// �� ��Ÿ ��ȣ ����
				int temp_santa_num = map[ny][nx];
				// ���� ��Ÿ ����
				map[sy][sx] = 0;
				map[ny][nx] = i;
				santa[i].y = ny;
				santa[i].x = nx;
				// �� ���� ������ Ȯ���Ͽ� �����ۿ�
				int nny = ny - dy[sdir];
				int nnx = nx - dx[sdir];
				// ���� ������ ��ܶ�� ��� ó�� �� ���� x
				if (!isIn(nny, nnx)) {
					santa[temp_santa_num].dead = true;
					dead_cnt++;
					if (dead_cnt == p) {
						return false;
					}
					continue;
				}
				// ��Ÿ�� �ڿ� �� �־��ٸ�?
				if (map[nny][nnx] > 0) {
					// ��ȣ�ۿ� �ǽ�
					interaction(nny, nnx, temp_santa_num, sdir, 1);
				}
				// ������ ��ĭ �ڷ� ���� 
				else {
					map[nny][nnx] = temp_santa_num;
					santa[temp_santa_num].y = nny;
					santa[temp_santa_num].x = nnx;
				}

			}
			// ��Ÿ�� ������ �׳� ����
			else {
				map[sy][sx] = 0;
				map[ny][nx] = i;
				santa[i].y = ny;
				santa[i].x = nx;
			}
		}
		// �絹���� ���ٸ� �׳� �̵�
		else {
			map[sy][sx] = 0;
			map[to_y][to_x] = i;
			santa[i].y = to_y;
			santa[i].x = to_x;
		}

	}

	return true;
}

int main() {

	cin >> n >> m >> p >> c >> d;
	santa.resize(p + 1);
	cin >> ry >> rx;
	map[ry][rx] = -1;
	for (int i = 0; i < p; i++) {
		int num, py, px;
		cin >> num >> py >> px;
		santa[num] = { py,px,0,0,false };
		map[py][px] = num;
	}

	for (int i = 0; i < m; i++) {
		for (int j = 1; j <= p; j++) {
			if (santa[j].stun_day > 0) {
				santa[j].stun_day--;
			}
		}
		if (!func()) {
			break;
		}
		for (int j = 1; j <= p; j++) {
			if (!santa[j].dead) {
				santa[j].score++;
			}
		}
	}
	for (int i = 1; i <= p; i++) {
		cout << santa[i].score << " ";
	}

	return 0;
}