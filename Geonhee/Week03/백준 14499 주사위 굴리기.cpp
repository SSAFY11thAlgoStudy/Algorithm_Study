#include <iostream>
using namespace std;

int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };
int dice[7] = { 0 };
int n, m, x, y, k;
int map[21][21];
int command[1001]; //��ɾ� ���� �迭


void rolling() {
	for (int i = 0; i < k; i++) {
		int dir = command[i]; // ��ɾ�
		bool check = true;  // ���� �������� �Ǻ��ϱ� ���� ��
		int nx = x + dx[dir - 1]; // dir = 3 (1,0), dir = 2 (-1,0), dir = 1 (0,-1), dir = 0 (0,1)
		int ny = y + dy[dir - 1]; // ���� ���͵� �Ϻη� dir�� ������ �°� ���������
		if (nx >= n || nx < 0 || ny >= m || ny < 0) { // ������ �����
			check = false; // false
		}
		if (!check) continue; //false�� �ƹ��͵� ���ؾ� �ϹǷ� continue
		x = nx; // true�̸� ���� ���̹Ƿ� x,y��ǥ ������Ʈ
		y = ny;

		if (dir == 4) { // 4�̸� �������� 
			int temp = dice[1]; // 2 => 6 => 5 => 1
			dice[1] = dice[5];  // 1    2    6    5
			dice[5] = dice[6];  // 5    1    2    6
			dice[6] = dice[2];  // 6    5    1    2
			dice[2] = temp;
		}
		else if (dir == 3) { // 3�̸� ��������
			int temp = dice[1]; // 2 => 1 => 5 => 6
			dice[1] = dice[2];  // 1    5    6    2
			dice[2] = dice[6];  // 5    6    2    1
			dice[6] = dice[5];  // 6    2    1    5
			dice[5] = temp;
		}
		else if (dir == 2) { // 2�̸� ��������
			int temp = dice[1];  // 4 1 3  => 1 3 6  => 3 6 4 =>  6 4 1
			dice[1] = dice[4];   //   6         4         1         3
			dice[4] = dice[6];
			dice[6] = dice[3];
			dice[3] = temp;
		}
		else if (dir == 1) { // 1�̸� ��������
			int temp = dice[1];  // 4 1 3  => 6 4 1  => 3 6 4 =>  1 3 6
			dice[1] = dice[3];   //   6         3         1         4
			dice[3] = dice[6];
			dice[6] = dice[4];
			dice[4] = temp;
		}
		if (map[x][y] == 0) { // 0�϶�
			map[x][y] = dice[6]; // ĭ�� �ֻ��� �ٴڸ� �� ������Ʈ
		}
		else {  // 0�� �ƴҶ�
			dice[6] = map[x][y]; // �ֻ��� �ٴڸ� �� ĭ�� ������ ������Ʈ �ϰ�
			map[x][y] = 0;       // ĭ�� ���� 0���� ������Ʈ
		}
		cout << dice[1] << '\n';  // ���� ���� �� ��� 

	}

}

int main() {
	cin >> n >> m >> x >> y >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < k; i++) {
		cin >> command[i];
	}
	rolling();
	return 0;
}