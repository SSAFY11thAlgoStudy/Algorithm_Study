#include <iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;


int dy[4] = { 1,-1,0,0 };
int dx[4] = { 0,0,1,-1 };
int map[21][21];
int n;


// ����� ���� ũ�� 2
// ���� �ڽ��� ũ�� ���� ���� ����⸦ ���� �� �ִ�.
// ���� �ڽ��� ũ��� ������ ������ �ʰ� ������ ���� �ִ�.
// �ڽ��� ũ��� ���� ����� ���� �Ծ�� ũ�Ⱑ 1 �����Ѵ�.
// ex) ũ�Ⱑ 2�� ��, ũ�Ⱑ 1������ ����� 2������ �Ա�
// ex) ũ�Ⱑ 3�� ��, ũ�Ⱑ 2������ ����� 3������ �Ա�

// �׷��ٸ� ������ �Ʊ����� ��ǥ�� �����ϰ�
// ������� ũ�Ⱑ ���� �������� ������ ��
// ���� �� �ִ� ����⸦ �� �Ծ��� ��
// 1. �ڽ��� ũ�⸸ŭ �Ծ��ٸ� ũ�� + 1
// 2. �ڽ��� ũ�⸸ŭ ���� ���ߴٸ� ���� ȣ���ϱ�
// 3. ���� �ʿ� ����Ⱑ ������? ���� ȣ���ϱ�

// ���� �� �ִ� ����Ⱑ 1���� ? -> �� ����� �Ա�
// ���� �� �ִ� ����Ⱑ �������� ?
// -> �Ÿ��� ���� ����� ����� �Ա�
// ���� �Ÿ��� ���� ����� ����Ⱑ ���ٸ�? ���� ��, �׷��� ���ٸ�? ���� ����
// !! �̴� �Է¹��� �� �ε����� ���� ���� ������� ��ǥ�� �����ϴ�

// �׷��ٸ� �� �������� �Ÿ��� ���ϰ� 
// �Ÿ��� ���� ����� ����Ⱑ 1������ �� ����⸦ �԰�
// �Ÿ��� ���� ����� ����Ⱑ ����������� 
// �Է� ��ȣ(�ε���)�� ���� �������� ������ �ȴ�! 


vector<pair<int, int>>fish[7];
int s_y, s_x, s_size = 2;
int cur_dis, cur_eaten;
struct Info {
	int y, x, dis;
};



bool compare(Info a, Info b) {
	// �Ÿ���
	if (a.dis != b.dis) {
		return a.dis < b.dis;
	}
	// �Ÿ��� ���ٸ� ��ǥ ��
	else {
		if (a.y != b.y) {
			return a.y < b.y;
		}
		else {
			return a.x < b.x;
		}
	}
}

bool isValid(int y, int x) {
	return y >= 0 && x >= 0 && y < n&& x < n;
}

// ���� ����� ��ǥ, ũ�� ���
bool func() {
	// ���� ���� �� �ִ� ����� Ž��

	// ����� ��ġ 
	queue<pair<int, int>>q;
	q.push({ s_y,s_x });
	int temp[21][21] = { 0, };
	temp[s_y][s_x] = -1;
	vector<Info>order_fish;

	// �� ���� 1ȸ Ž��
	while (!q.empty()) {
		int cur_y = q.front().first;
		int cur_x = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int next_y = cur_y + dy[i];
			int next_x = cur_x + dx[i];
			// ���� ���̰ų�, �̹� ������ ���̰ų�, ���� ��� ũ�⺸�� ū �����̸� ���� x
			if (!isValid(next_y, next_x) ||
				temp[next_y][next_x] != 0 ||
				map[next_y][next_x] > s_size)continue;

			// ť�� �߰�
			q.push({ next_y,next_x });

			// ������ ���� ����
			if (temp[cur_y][cur_x] == -1)temp[next_y][next_x] = 1;
			else temp[next_y][next_x] = temp[cur_y][cur_x] + 1;

			// ���� �� ���� �� �ִ� ������?
			if (map[next_y][next_x] < s_size && map[next_y][next_x]>0) {
				// ������� ��ǥ�� ���� ������ ���̸� ����
				order_fish.push_back({ next_y,next_x,temp[next_y][next_x] });
			}

		}
	}

	// 1ȸ Ž�� �� ���� �� �ִ� ����⿡ ����
	// �Ÿ��� ����� ��, ���� �����ִ� ��, ���� ���ʿ� �ִ� ������ ����� ����
	sort(order_fish.begin(), order_fish.end(), compare);

	// ���̻� ���� �� �ִ� ����Ⱑ ������ ���� -> ���� ȣ���ϱ�
	if (order_fish.empty())return false;

	// ���� �� �ִ� ����Ⱑ ������ ���� �տ� ����� ����� �԰� �Լ� ����
	// �Լ� ���� �� 
		// ���� ���� ����� ��ġ�� ��� �߰�
		// ��� ���� ��ġ 0���� ��ü
		// ���� ���� ����� �� + 1, 
		// ���� ���� ����� ���� ���� ũ��� ������ Ȯ��
		// ���� �̵��Ÿ� �߰�
	else {
		int goal_y = order_fish[0].y;
		int goal_x = order_fish[0].x;
		int goal_dis = order_fish[0].dis;
		map[s_y][s_x] = 0;
		map[goal_y][goal_x] = 9;
		s_y = goal_y;
		s_x = goal_x;
		cur_dis += goal_dis;
		cur_eaten++;
		if (cur_eaten == s_size) {
			s_size++;
			cur_eaten = 0;
		}
		//cout << goal_y << " " << goal_x << " " << goal_dis << "\n";
		return true;
	}


}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			// ����� �Է� �� ũ�� ���� ��ǥ ����
			if (map[i][j] >= 1 && map[i][j] <= 6) {
				fish[map[i][j]].push_back({ i,j });
			}
			// ��� �Է� �� ��ǥ ����
			else if (map[i][j] == 9) {
				s_y = i;
				s_x = j;
			}
		}
	}

	// ������ �õ�
	for (int i = 0; i < n * n; i++) {
		// ���̻� ���� ����Ⱑ ������ ����
		if (!func())break;
	}

	cout << cur_dis;

	return 0;
}