#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>

using namespace std;
int N, K, L;
int map[101][101] = { 0 };
int dy[] = { 0,1,0,-1 }, dx[] = { 1,0,-1,0 };// ��, ��, ��, ��
int dr = 0, cnt = 0;
//-1�̸�, +3, �׸��� 3�ʰ��̸� % 4

/*
1. ���� ���� �����̸� �÷� �Ӹ��� ����ĭ�� ��ġ��Ų��.
2. ���� ���̳� �ڱ��ڽ��� ���� �ε����� ������ ������.
3. ���� �̵��� ĭ�� ����� �ִٸ�, �� ĭ�� �ִ� ����� �������� ������ �������� �ʴ´�.
���� �̵��� ĭ�� ����� ���ٸ�, �����̸� �ٿ��� ������ ��ġ�� ĭ�� ����ش�.
��, �����̴� ������ �ʴ´�.
*/
//4.������ �����Ҷ� ���� ���� �������� ��ġ�ϰ� ���� ���̴� 1 �̴�.
//5.���� ó���� �������� ���Ѵ�. L�������� D����������

struct position {
	int y;
	int x;

};
//�Ӹ� ��ġ
position head_pos;
//�� ���� ��ŭ�� �Ӹ��� ������ ��ġ �迭
vector<position>tail_pos;

struct command {
	int straight;
	char dir;
};
command cmd[100];

//������ ��Ҵ��� Ȯ��
bool tailcheck(position pos) {
	for (int i = 0; i < tail_pos.size(); i++)
	{
		if (pos.y == tail_pos[i].y && pos.x == tail_pos[i].x) {
			return true;
		}
	}
	return false;
}

void move() {
	//i�� cmd�� �� ������ �µ��� �����ϱ����� �ε��� ����
	int i = 0;
	//4.������ �����Ҷ� ���� ���� �������� ��ġ�ϰ� ���� ���̴� 1 �̴�.
	tail_pos.push_back(head_pos);
	while (1) {
		//���� ��ġ ���
		head_pos.y += dy[dr];
		head_pos.x += dx[dr];

		//�ð��� ����
		cnt++;

		//2. ���� ���̳� �ڱ��ڽ��� ���� �ε����� ������ ������.
		//�ʹ����� ��Ż�� �Լ�����
		if (head_pos.y < 1 || head_pos.x< 1 || head_pos.y > N || head_pos.x > N)return;

		// �� ���� �߽߰� ����
		if (tailcheck(head_pos)) return;

		//1. ���� ���� �����̸� �÷� �Ӹ��� ����ĭ�� ��ġ��Ų��.
		//�Ӹ� ��ġ �̵�
		tail_pos.push_back(head_pos);

		/* 3. ���� �̵��� ĭ�� ����� �ִٸ�, �� ĭ�� �ִ� ����� �������� ������ �������� �ʴ´�.
			���� �̵��� ĭ�� ����� ���ٸ�, �����̸� �ٿ��� ������ ��ġ�� ĭ�� ����ش�.
			��, �����̴� ������ �ʴ´�.*/
			//����߽߰� ���� ����
		if (map[head_pos.y][head_pos.x] == 1) {
			//����� �Ծ����� ��������
			map[head_pos.y][head_pos.x] = 0;
		}
		//����� ���ٸ� ���̰� �þ�� �ʱ� ������ ������ ���� ��ġ�� ����
		else {
			tail_pos.erase(tail_pos.begin());
		}

		//5.���� ó���� �������� ���Ѵ�. L�������� D����������
		//���� ����
		if (i < L && cmd[i].straight == cnt) {
			if (cmd[i].dir == 'D') { // �ð�
				dr = (dr + 1) % 4;
			}
			else if (cmd[i].dir == 'L') { //�ݽð�
				dr = (dr + 3) % 4;
			}
			i++;
		}
	}
}

void input() {
	cin >> N;
	cin >> K;
	//1,1 ���� ����
	for (int i = 1; i <= K; i++)
	{
		int r, c;
		cin >> r >> c;

		map[r][c] = 1;//��� ��ġ
	}
	cin >> L;

	for (int i = 0; i < L; i++)
	{
		cin >> cmd[i].straight >> cmd[i].dir;
	}
}



int main() {
	//�Է�
	input();

	//���� ��ġ
	head_pos.y = 1;
	head_pos.x = 1;

	//����
	move();

	//���
	cout << cnt;
}