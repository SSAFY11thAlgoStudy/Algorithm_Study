#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, k, l, t, y, x;
char c;
int map[101][101];
bool visited[101][101];
queue<pair<int, char>>dir_changes;
queue<pair<int, char>>tails;
// ���� �Ӹ��� �ϳ� �÷� ����ĭ���� �̵��Ѵ�.
// ����ĭ�� ����� �Դ´�? -> �ƹ� �̻� ���� (������ +1)
// ����ĭ�� ����� �ȸԴ´�? -> ������ �ڸ���. (���� ĭ�� ����, ������ �״��)
// ���� ���� ���� �ִ� �κ��� visited�� true��
// ���� ����� �ȸ����� ������ false��

bool isEnd(int cur_y, int cur_x) {
	return cur_y < 0 || cur_y == n || cur_x < 0 || cur_x == n || visited[cur_y][cur_x];
}

void move(int start_y, int start_x) {



	// ù ���� �̵� ����
	int cur_dir_y = 0;
	int cur_dir_x = 1;

	queue<pair<int, int>>q;
	q.push({ start_y, start_x });
	tails.push({ start_y,start_x });
	visited[start_y][start_x] = true;

	while (!q.empty()) {

		int cur_y = q.front().first;
		int cur_x = q.front().second;

		//cout << cur_y <<" "<< cur_x << "\n";
		q.pop();

		int next_y = cur_y + cur_dir_y;
		int next_x = cur_x + cur_dir_x;

		// ����ĭ�� ���� ���̰ų� ���̸� ����
		if (isEnd(next_y, next_x)) {
			cout << map[cur_y][cur_x] + 1;
			return;
		}

		q.push({ next_y,next_x });
		tails.push({ next_y,next_x });

		int cur_tail_y = tails.front().first;
		int cur_tail_x = tails.front().second;

		// ���� ĭ�� ����� ������? -> ���� �κ� false��
		if (map[next_y][next_x] != -1) {
			visited[cur_tail_y][cur_tail_x] = false;
			if (!tails.empty()) {

				tails.pop();
			}
		}

		// ���� ĭ�� ��(���� �ð����� ���� ����ð�)�� ���� ���� ��ȯ�� �ð��̶��
		map[next_y][next_x] = map[cur_y][cur_x] + 1;
		visited[next_y][next_x] = true;

		// ���� ���� ��ȯ�� �ؾ��ϴ°� Ȯ�� �� ����
		if (!dir_changes.empty()) {

			int cur_dir_change_time = dir_changes.front().first;
			int cur_dir_change_rotation = dir_changes.front().second;
			if (map[next_y][next_x] == cur_dir_change_time) {
				dir_changes.pop();
				// �����̸�?
				// (0,1) -> (-1,0) -> (0,-1) -> (1,0)
				if (cur_dir_change_rotation == 'L') {
					if (cur_dir_y == 0) {
						cur_dir_y = (-1) * (cur_dir_x);
						cur_dir_x = 0;
					}

					else if (cur_dir_x == 0) {
						cur_dir_x = cur_dir_y;
						cur_dir_y = 0;
					}

				}


				// �������̸�?
				// (0,1) -> (1,0) -> (0,-1) -> (-1,0)
				else if (cur_dir_change_rotation == 'D') {
					if (cur_dir_y == 0) {
						cur_dir_y = cur_dir_x;
						cur_dir_x = 0;
					}

					else if (cur_dir_x == 0) {
						cur_dir_x = (-1) * cur_dir_y;
						cur_dir_y = 0;
					}
				}
			}
		}


	}
}

int main() {
	cin >> n;
	cin >> k;

	for (int i = 0; i < k; i++) {
		cin >> y >> x;
		// ����� �ִ� ���� -1
		map[y - 1][x - 1] = -1;
	}

	cin >> l;

	for (int i = 0; i < l; i++) {
		cin >> t >> c;
		dir_changes.push({ t,c });
	}

	move(0, 0);


	return 0;
}