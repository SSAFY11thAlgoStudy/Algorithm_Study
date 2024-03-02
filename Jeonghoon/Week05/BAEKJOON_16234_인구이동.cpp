#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<cmath>
#include<unordered_map>
#include<cstring>

using namespace std;

struct Node {
	int y, x;
};

//���ձ��� ���� �� �α��� ����
struct Uni {
	int num;
	int s_pop;
};

int N, L, R;
int map[101][101];
//���� ǥ�ÿ� �迭
int vis[101][101];
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };
//���ռ� Ȯ��
int v_cnt;

//���ձ��� ���� �� �α��� ����
unordered_map<int, Uni> un;

void input() {
	cin >> N >> L >> R;

	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			cin >> map[i][j];
		}
	}
}

void init() {
	un.clear();
	v_cnt = 1;
	memset(vis, 0, sizeof(vis));
}

void bfs(int sp_y, int sp_x) {
	queue<Node> q;
	q.push({ sp_y, sp_x });

	//�������� ����ǥ��
	vis[sp_y][sp_x] = v_cnt;

	//���ձ� �� �÷��ְ� �α��� ����
	un[v_cnt].num++;
	un[v_cnt].s_pop += map[sp_y][sp_x];

	while (!q.empty()){
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++){
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			//�� üũ
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;

			//������ �ִ��� Ȯ��
			if (vis[ny][nx] != 0) continue;

			//�� ������ �α��� ���� ���ϱ�
			int gap = abs(map[now.y][now.x] - map[ny][nx]);

			if ( gap >= L && gap <= R ){
				//�����ΰ� ǥ���ϱ�
				vis[ny][nx] = v_cnt;

				//���ձ� �� �÷��ְ� �α����� ����
				un[v_cnt].num++;
				un[v_cnt].s_pop += map[ny][nx];

				q.push({ ny,nx });
			}
		}
	}
	//���� ���տ� �� ǥ�� ++
	v_cnt++;
}

void find_sp() {

	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			//���վ��� �������� ã�Ƽ� ��Ÿ��
			if (vis[i][j] == 0) {
				bfs(i, j);
			}
		}
	}
}

//�������� ���� ����
void imigrate() {
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){

			if (vis[i][j] != 0) {
				int uni_num = vis[i][j];
				map[i][j] = un[uni_num].s_pop / un[uni_num].num;
			}
		}
	}
}

int main() {

	//freopen("sample.txt", "r", stdin);

	input();
	int cnt = 0;

	while (1) {
		//vis�� 0���� �ʱ�ȭ�ؼ� 
		//������ ǥ���ϱ� ���� 1���� ���
		//�ʱ�ȭ�� -1�� �ϰ� 0���� ����������
		//�������ǿ� +1 ���ص� ��
		v_cnt = 1;

		init();

		//�������� ã�� + bfs
		find_sp();

		//���� ���� ���ռ��� 1���� �����߱� ������
		//bfs�� ������ ī��Ʈ�� N*N+1�̸�
		//������ ���� ���̹Ƿ� ����ϰ� ����
		if (v_cnt == (N * N + 1)) {
			cout << cnt;
			break;
		}

		//�����ϴ� �Լ�
		imigrate();

		//�ϼ� üũ
		cnt++;
	}

	return 0;
}