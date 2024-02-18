#include <iostream>
#include <string>
#include <queue>

using namespace std;

int n, m;
int r, c, d;

// map�� ���� 0�̸� û�ҵ��� ���� �� ĭ
// map�� ���� 1�̸� ���� �ִ� ĭ
int map[51][51];

// d = 0 -> ���� (-1,0)
// d = 1 -> ���� (0,1)
// d = 2 -> ���� (1,0)
// d = 3 -> ���� (0,-1)


// �� �� �� �� ������ ���� (d ���� �ε�����)
// �׷��ٸ� ������ �ٶ󺸴� ��� ������ ?
// d = 0 �̸� dy, dx�� �ε����� 2 ���� ����
// d = 1 �̸� dy, dx�� �ε����� 3 ���� ����
// d = 2 �̸� dy, dx�� �ε����� 0 ���� ����
// d = 3 �̸� dy, dx�� �ε����� 1 ���� ����

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

int ans;

struct Info {
	int y, x, dir;
};

bool isValid(int y, int x) {
	return x >= 0 && y >= 0 && y <= n - 1 && x <= m - 1 && (map[y][x] != 1);
}

bool isCleaned(int y, int x) {
	return (map[y][x] == 0);
}

void bfs(int start_y, int start_x, int start_dir) {

	// ���� ĭ�� û�ҵ��� ���� �� ���� ���
	// ���� 2�� ����
	// -> 0�� ��츸 �湮���� ���� �� ������ �Ǵ� ����
	// �湮 üũ�� visited �迭 ��� x
	if (map[start_y][start_x] == 0) {
		map[start_y][start_x] = 2;
		ans++;
	}

	queue<Info>q;
	q.push({ start_y,start_x,start_dir });
	while (!q.empty()) {
		int cur_y = q.front().y;
		int cur_x = q.front().x;
		int cur_dir = q.front().dir;
		//cout << cur_y << " " << cur_x << " "<< cur_dir<<"\n";
		q.pop();

		if (map[cur_y][cur_x] == 0) {
			map[cur_y][cur_x] = 2;
			ans++;
		}


		// ���� ĭ�� �ֺ� 4ĭ���� û���� �� �ִ� �� ĭ�� ���� ��� Ȯ��
		bool check_clean = false;

		for (int i = 0; i < 4; i++) {
			int next_y = cur_y + dy[i];
			int next_x = cur_x + dx[i];
			if (!isValid(next_y, next_x) || !isCleaned(next_y, next_x))continue;

			check_clean = true;

		}
		// ���� �ֺ� 4ĭ ��� û�� �Ұ��� ��� ����
		if (!check_clean) {

			// ������ ������ �����ΰ�?
			// dy[cur_dir], dx[cur_dir]�� ���� �ٶ󺸴� ���⿡ ���� �� ĭ ����

			// cur_dir�� 0, 1 �̸� + 2
			// cur_dir�� 2, 3 �̸� - 2

			int next_dir = 0;

			if (cur_dir < 2) {
				next_dir = cur_dir + 2;
			}
			else {
				next_dir = cur_dir - 2;
			}

			int next_y = cur_y + dy[next_dir];
			int next_x = cur_x + dx[next_dir];

			// ���� �Ұ��� ? -> (�̰� ���� ������ �� �˾����� �װ� �ƴ�)
			// ������ ���� �� ��쿡�� (���� �ƴϰ� �׳� �̹� û���� �����̸� �� ��ҷ� �ٽ� �̵�)
			if (isValid(next_y, next_x)) {
				q.push({ next_y, next_x, cur_dir });
			}

		}

		// ���� �ֺ� 4ĭ �� û�� ����
		else {
			// �ٶ󺸴� ������ �ݽð�� 90�� ȸ��
			// 0->3->2->1->0..
			// 360�� ȸ���� �ϸ� ���߿� �����ϸ� �װ����� �̵�

			int next_dir = cur_dir;
			for (int i = 0; i < 4; i++) {

				// ��, ��, �� (1, 2, 3)�� �ε��� -1�ϸ� ����
				if (next_dir > 0) {
					next_dir -= 1;
				}

				// ��(0) �� �ִ��� 3���� �̵�
				else {
					next_dir = 3;
				}

				// �ٶ󺸴� ���� ȸ�� �� ���� ĭ�� ��ǥ
				int next_y = cur_y + dy[next_dir];
				int next_x = cur_x + dx[next_dir];

				// ���� �� ��ǥ�� ��ȿ�ϰ�  �� ĭ�̶�� ���� 
				if (isValid(next_y, next_x) && isCleaned(next_y, next_x)) {
					q.push({ next_y, next_x, next_dir });
					break;
				}
			}

		}

	}
}

int main() {

	cin >> n >> m;
	cin >> r >> c >> d;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	bfs(r, c, d);
	cout << ans;

	return 0;
}