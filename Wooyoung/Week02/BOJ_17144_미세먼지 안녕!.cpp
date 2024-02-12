#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

int r, c, t;

int dy[4] = { 1,-1,0,0 };
int dx[4] = { 0,0,1,-1 };

int map[51][51];
int spread_cnt[51][51];

// ����û���� ���κ�, �Ʒ��κ� 
int airc_up_y, airc_up_x;
int airc_down_y, airc_down_x;

// ���κ�, �Ʒ��κ� �̵� ���� �迭
int dy_up[4] = { -1,0,1,0 };
int dx_up[4] = { 0,1,0,-1 };
int dy_down[4] = { 1,0,-1,0 };
int dx_down[4] = { 0,1,0,-1 };

bool visited[51][51];

bool isValid(int y, int x) {
	return y >= 0 && x >= 0 && y <= (r - 1) && x <= (c - 1);
}

bool isDust(int y, int x) {
	return map[y][x] >= 1;
}

bool isAirc(int y, int x) {
	return map[y][x] == -1;
}

// 1�ʸ��� ��� ���� ĭ���� ���ÿ� �Ͼ��? 
// -> �ӽ� �ʿ� �� ĭ���� Ȯ��� ������ ī��Ʈ�ϰ�
// ���� �ʿ� ����� �߰��Ѵ�.
// Why? �ϳ� Ȯ�� �� ���ع����� �ٸ� ��� ������ ������ ��ġ�� ����!
void spread() {

	for (int cur_y = 0; cur_y < r; cur_y++) {
		for (int cur_x = 0; cur_x < c; cur_x++) {
			// ���� ĭ�� ������ ���ų�, ����û���Ⱑ ������ ���� x
			if (!isDust(cur_y, cur_x)) continue;
			// ������ �۶߸� �� ī��Ʈ 
			int temp_cnt = 0;
			for (int k = 0; k < 4; k++) {
				int next_y = cur_y + dy[k];
				int next_x = cur_x + dx[k];
				// ��ȿ�� �ε����� �ƴϰų�, ����û���Ⱑ �ִ� ���̶�� ���� x
				if (!isValid(next_y, next_x) || isAirc(next_y, next_x))continue;
				spread_cnt[next_y][next_x] += (map[cur_y][cur_x] / 5);
				temp_cnt++;
			}
			// (�۶߸� �� x ���� ���� ��)�� ���� ���� Ȯ�� ��������� ���ֱ�
			// spread_cnt�� -�� �����Ͽ� �׳� ���ϸ� ���߿� �˾Ƽ� ����!
			spread_cnt[cur_y][cur_x] += (-1) * (temp_cnt) * (map[cur_y][cur_x] / 5);
		}
	}

	// Ȯ�� ����� ���� �ʿ� �߰��ϱ� & spread_cnt �ʱ�ȭ
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			map[i][j] += spread_cnt[i][j];
			spread_cnt[i][j] = 0;
		}
	}

}

// ����û���� �۵�
// ����û������ ���κ� -> �ݽð�, �Ʒ��κ� -> �ð�

void do_clean() {

	// ���κ� ���� ó��
	// ���� (y,x)�� ����û���� ���κ��̶��
	// ���������� �ϳ��� ���ܿ´�. -> ����û���� ���� �ϸ� �� ĭ�� �����̱� ������ ����� �� ����

	// �ٷ� ��ĭ�� ���Կ� ���� 0���� ��
	int up_cur_y = airc_up_y - 1;
	int up_cur_x = airc_up_x;
	int prev_up_cur_y;
	int prev_up_cur_x;
	//map[up_cur_y][up_cur_x] = 0;

	// �ٽ� ���ƿ� �� ���� �ݺ�

	for (int i = 0; i < 4; i++) {
		while (1) {
			prev_up_cur_y = up_cur_y;
			prev_up_cur_x = up_cur_x;

			// ���� ��ġ�� ���� ��ġ�� �����ϰ� ���� ��ġ�� ���� ��ġ�� ���� �����Ѵ�.
			// ��, �ٶ��� �̵������� ������ �����Ͽ� �о�� ����� �ƴ� ��ܿ��� ����� ���
			// ���� ��ġ���� �̵��������� ���� ��ġ�� �������� �� �Ұ����ϴٸ�
			// ���� ��ġ���� �ð���� 90���� ȸ�� �� ��ĭ �̵��� ��ǥ�� ���� ��ġ�� ����
			// ���� ���� ��ġ�� ���� ���� ��ġ�� ������ ������ �� �ٽ� ����


			if ((prev_up_cur_y == 0 && prev_up_cur_x == 0) ||
				(prev_up_cur_y == 0 && prev_up_cur_x == c - 1) ||
				(prev_up_cur_y == airc_up_y && prev_up_cur_x == c - 1)) {

				if (i < 3) {
					up_cur_y += dy_up[i + 1];
					up_cur_x += dx_up[i + 1];
					map[prev_up_cur_y][prev_up_cur_x] = map[up_cur_y][up_cur_x];
					break;

				}

			}
			up_cur_y += dy_up[i];
			up_cur_x += dx_up[i];

			map[prev_up_cur_y][prev_up_cur_x] = map[up_cur_y][up_cur_x];


			if (up_cur_y == airc_up_y && up_cur_x == airc_up_x + 1) {
				map[up_cur_y][up_cur_x] = 0;
				break;
			}
		}
	}

	// �Ʒ��κ� ó��
	// ���� (y,x)�� ����û���� �Ʒ��κ��̶��
	// ���������� �ϳ��� ���ܿ´�. -> ����û���� ���� �ϸ� �� ĭ�� �����̱� ������ ����� �� ����

	int down_cur_y = airc_down_y + 1;
	int down_cur_x = airc_down_x;
	int prev_down_cur_y;
	int prev_down_cur_x;

	// �ٽ� ���ƿ� �� ���� �ݺ�

	for (int i = 0; i < 4; i++) {
		while (1) {
			prev_down_cur_y = down_cur_y;
			prev_down_cur_x = down_cur_x;

			if ((prev_down_cur_y == r - 1 && prev_down_cur_x == 0) ||
				(prev_down_cur_y == r - 1 && prev_down_cur_x == c - 1) ||
				(prev_down_cur_y == airc_down_y && prev_down_cur_x == c - 1)) {

				if (i < 3) {

					down_cur_y += dy_down[i + 1];
					down_cur_x += dx_down[i + 1];
					map[prev_down_cur_y][prev_down_cur_x] = map[down_cur_y][down_cur_x];
				}

				break;

			}
			down_cur_y += dy_down[i];
			down_cur_x += dx_down[i];


			map[prev_down_cur_y][prev_down_cur_x] = map[down_cur_y][down_cur_x];

			if (down_cur_y == airc_down_y && down_cur_x == airc_down_x + 1) {
				map[down_cur_y][down_cur_x] = 0;
				break;
			}
		}
	}


}


int main() {

	cin >> r >> c >> t;
	bool find_airc = false;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> map[i][j];
			if (map[i][j] == -1 && !find_airc) {
				airc_up_y = i;
				airc_up_x = j;
				airc_down_y = i + 1;
				airc_down_x = j;
				find_airc = true;
			}
		}
	}

	for (int i = 0; i < t; i++) {
		spread();
		do_clean();
	}

	int ans = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (map[i][j] > 0) {

				ans += map[i][j];
			}
		}
	}
	cout << ans;
	return 0;
}