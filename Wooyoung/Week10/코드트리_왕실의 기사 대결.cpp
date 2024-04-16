#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
using namespace std;

int L, N, Q;
int map[41][41];
bool trap[41][41];
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
long long ans;
struct Info {
	int r, c, h, w, k, damage;
	bool isDead;
};
unordered_map<int, Info>knightsInfo;
bool isValid(int y, int x) {
	return y >= 1 && x >= 1 && y <= L && x <= L && map[y][x] != -1;
}

bool isInteraction(int y, int x, int num) {
	return map[y][x] != num && map[y][x] >= 1 && map[y][x] <= N;
}

bool isTrap(int y, int x) {
	return trap[y][x];
}

// �̵� �� ���ΰ�?
bool isValidAll(Info knight, int dir) {
	int sy = knight.r;
	int sx = knight.c;
	int ey = sy + knight.h;
	int ex = sx + knight.w;
	for (int y = sy; y < ey; y++) {
		for (int x = sx; x < ex; x++) {
			int ny = y + dy[dir];
			int nx = x + dx[dir];
			if (!isValid(ny, nx))return false;
		}
	}
	return true;
}

unordered_set<int> findKnights(int num, int dir) {
	unordered_set<int> temp;
	Info knight = knightsInfo[num];
	int sy = knight.r;
	int sx = knight.c;
	int ey = sy + knight.h;
	int ex = sx + knight.w;
	for (int y = sy; y < ey; y++) {
		for (int x = sx; x < ex; x++) {
			int ny = y + dy[dir];
			int nx = x + dx[dir];
			if (!isValid(ny, nx))continue;
			if (!isInteraction(ny, nx, num))continue;
			temp.insert(map[ny][nx]);
		}
	}
	return temp;
}

bool canPushAll(Info knight, int num, int dir) {
	bool check = true;
	// ���� ��簡 �̵� �����ϴٸ�
	// ���� ��� �ֺ� ���� ���� �� ��ͷ� �̵� ���� ���� Ȯ��
	if (isValidAll(knight, dir)) {
		unordered_set<int> around_knights = findKnights(num, dir);
		for (auto i : around_knights) {
			Info now_knight = knightsInfo[i];
			if (now_knight.isDead)continue;
			// check = canPushAll �ع����� �ȵ�
			// ��� ������ �з��� �ϱ� ������
			// ���� check�� ���� check ��� �����ϰ� true��
			// ��� ��͸� ������ �� true�� ��츸 �о����
			check = check && canPushAll(now_knight, i, dir);
		}
	}
	else {
		check = false;
	}
	return check;
}

void eraseKnight(Info knight, int num) {
	int sy = knight.r;
	int sx = knight.c;
	int ey = sy + knight.h;
	int ex = sx + knight.w;
	for (int y = sy; y < ey; y++) {
		for (int x = sx; x < ex; x++) {
			map[y][x] = 0;
		}
	}
	knightsInfo[num].isDead = true;
}

void onHit(int num, int dir) {
	if (knightsInfo[num].isDead)return;
	Info knight = knightsInfo[num];
	int sy = knight.r;
	int sx = knight.c;
	int ey = sy + knight.h;
	int ex = sx + knight.w;
	for (int y = sy; y < ey; y++) {
		for (int x = sx; x < ex; x++) {
			if (trap[y][x]) {
				knightsInfo[num].damage++;
			}
		}
	}
	if (knightsInfo[num].k <= knightsInfo[num].damage) {
		eraseKnight(knight, num);
	}
}

void move(int num, int dir) {
	Info knight = knightsInfo[num];
	int sy = knight.r;
	int sx = knight.c;
	int ey = sy + knight.h;
	int ex = sx + knight.w;
	for (int y = sy; y < ey; y++) {
		for (int x = sx; x < ex; x++) {
			map[y][x] = 0;
		}
	}
	knightsInfo[num].r += dy[dir];
	knightsInfo[num].c += dx[dir];
	knight = knightsInfo[num];
	sy = knight.r;
	sx = knight.c;
	ey = sy + knight.h;
	ex = sx + knight.w;

	for (int y = sy; y < ey; y++) {
		for (int x = sx; x < ex; x++) {
			map[y][x] = num;
		}
	}
}

void push(int num, int dir, int depth) {
	unordered_set<int>around_knights = findKnights(num, dir);
	for (auto i : around_knights) {
		// �ֺ��� ��ͷ� ã�ƺ����� ����
		//Info knight = knightsInfo[i];
		push(i, dir, depth + 1);
	}
	move(num, dir);
	if (depth != 0) {
		onHit(num, dir);
	}
}

int main() {

	cin >> L >> N >> Q;
	for (int i = 1; i <= L; i++) {
		for (int j = 1; j <= L; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) {
				// ������ ���� �迭�� ����(���� ��ǥ�� ��ġ�� ����)
				trap[i][j] = true;
				map[i][j] = 0;
			}
			else if (map[i][j] == 2) {
				// ���� -1�� ���� (2�� ����� ��ǥ�� ��ġ�°� ����)
				map[i][j] = -1;
			}
		}
	}
	for (int i = 1; i <= N; i++) {
		int r, c, h, w, k;
		cin >> r >> c >> h >> w >> k;
		// ����� �ʱ� ���� ����
		knightsInfo[i] = { r,c,h,w,k,0,false };
		for (int y = r; y < r + h; y++) {
			for (int x = c; x < c + w; x++) {
				map[y][x] = i;
			}
		}
	}

	for (int i = 0; i < Q; i++) {
		int num, d;
		cin >> num >> d;
		if (knightsInfo[num].isDead)continue;
		// ��� ��縦 �м� �ִ°�?
		if (canPushAll(knightsInfo[num], num, d)) {
			push(num, d, 0);
		}
		//for (int j = 1; j <= L; j++) {
		//	for (int q = 1; q <= L; q++) {
		//		cout << map[j][q] << " ";
		//	}
		//		cout << "\n";
		//	}
		//cout << "\n";
		//cout << "���� ���� " << ans << "\n";
	}
	for (int i = 1; i <= N; i++) {
		if (!knightsInfo[i].isDead)ans += knightsInfo[i].damage;
	}
	cout << ans;
	return 0;

}
