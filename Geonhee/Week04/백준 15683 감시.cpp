#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
int map[8][8];
int dx[4] = { 0,1,0,-1 };// ���� ������, ����, ����, �Ʒ���
int dy[4] = { 1,0,-1,0 };
vector<pair<int, int>> arr;
int cnt = 0;
int res = 21e8;//�簢 ���� �ּ� ũ��
void check(int x1, int y1, int d) {
	d %= 4; //���� �����ֱ�
	while (1) {
		int nx = x1 + dx[d];
		int ny = y1 + dy[d];
		x1 = nx;
		y1 = ny;
		if (nx >= n || nx < 0 || ny >= m || ny < 0) break;
		if (map[nx][ny] == 6) break;
		if (map[nx][ny] != 0) continue;
		map[nx][ny] = 7; //CCTV�ɸ��� �� �ٲ��ֱ�
	}
}

void dfs(int st) {
	if (cnt == st) { //cctv������ŭ ��������
		int temp = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] == 0) {
					temp++;
				}
			}
		}
		res = min(temp, res); // �ּҰ� ã���ֱ�
		return;
	}
	int save[9][9];
	int x = arr[st].first;
	int y = arr[st].second;

	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				save[i][j] = map[i][j]; //���� �� ����
			}
		}
		if (map[x][y] == 1) { //1�϶� ������
			check(x, y, k);
		}
		else if (map[x][y] == 2) { //2�϶� ������ ,���� 
			check(x, y, k);
			check(x, y, k + 2);
		}
		else if (map[x][y] == 3) {//3�϶� ������, ����
			check(x, y, k);
			check(x, y, k + 3);
		}
		else if (map[x][y] == 4) { //4�϶� ������,����,����
			check(x, y, k);
			check(x, y, k + 2);
			check(x, y, k + 3);
		}
		else if (map[x][y] == 5) {//5�϶� ������,����,����,�Ʒ���
			check(x, y, k);
			check(x, y, k + 1);
			check(x, y, k + 2);
			check(x, y, k + 3);
		}
		dfs(st + 1); //�������� ����CCTVã�ư���
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				map[i][j] = save[i][j]; //�� �ٽ� ������� ������ֱ�
			}
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] != 0 && map[i][j] != 6) {
				arr.push_back({ i,j }); //CCTV ��ǥ ����
				cnt++;
			}
		}
	}
	dfs(0);
	cout << res;
	return 0;
}