#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

int N, L, R;
int map[50][50];
int dy[] = { 0,0,1,-1 }, dx[] = { 1,-1,0,0 };
int visit[50][50] = { 0 };

struct  point
{
	int y;
	int x;
};

//�Է�
void input() {
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
		}
	}
}


// ������ Ȯ���Ͽ� ��ġ�� �Լ�
int solve(point st) {
	queue<point>q;
	vector<point>v;
	int sum = 0; //sum�� ���� ������ ������ �α����� ���ϸ鼭 ����
	q.push(st);
	visit[st.y][st.x] = 1;
	while (!q.empty()) {
		point now = q.front();
		q.pop();
		v.push_back({ now.y, now.x });//�ּ��� �ڱ��ڽ��� �ڱ��ڽŰ� ������ �Ѵ�.
		sum += map[now.y][now.x]; 
		for (int i = 0; i < 4; i++)
		{
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			// now�� next���� �α� ���̸� ����
			int checkvalid = abs(map[ny][nx] - map[now.y][now.x]);
			//���� Ȯ��
			if (ny < 0 || nx < 0 || ny >= N || nx >= N)continue;
			// �湮�� ������ Ȯ��
			if (visit[ny][nx] != 0)continue;
			// �� ������ �α� ���̰� L�� �̻�, R�� ���϶��
			if (checkvalid < L || checkvalid > R) continue;
			visit[ny][nx] = 1;
			q.push({ ny, nx });

		}
	}
	//�����̵� ������ ����
	int sizes = v.size();

	// ������ �ڱ��ڽŸ� �ִٸ� 0�� ����
	if (sizes <= 1) return 0;

	//vector�� ����� ������ ������ ��� ���� �־���
	for (point p : v) {
		map[p.y][p.x] = sum / sizes;
	}

	return 1;
}

//�߰� Ȯ���� ���� �Լ�
void print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//��ġ�� ����Ȯ���ϸ鼭 ������ �������� Ȯ��
int func() {
	//visit�� ���� ������ ���� �̹� ����� ���̶�� 
	// ��� ���� �ʵ��� ��
	memset(visit, 0, sizeof(visit));
	//flag�� ���� ������ ����� Ȯ��
	int flag = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visit[i][j] == 1)continue;
			if (solve({ i, j })) flag = 1;
		}
	}
	return flag;
}


int main() {
	input();
	int cnt = 0;

	//������ �ȵɶ� ���� Ȯ��
	while (func()) {
		//print();
		cnt++;
	}
	cout << cnt;
	return 0;
}