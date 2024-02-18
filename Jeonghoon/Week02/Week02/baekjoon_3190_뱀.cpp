#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;

int map[101][101];
int N, K, L;

//�ð��� ���� ������ �ٲ�� Ŀ��尡 �����Ƿ� �̸� 
//�ð��� �ε����� ����� �迭�� ����
char dat[10001];

//���� �Ӹ��� �ð��� ���� ������ ��� ����
//map�� �ð��� ������ ������ �Ƚᵵ �Ǳ���
int snake[101][101];

//�ð� ������ ����
int cnt;

void input() {
	cin >> N >> K;

	for (int i = 0; i < K; i++) {
		int y, x;
		cin >> y >> x;
		//����� �ʿ� 1�� ǥ��
		//�̰� �ٸ��� (ex: -1)�� �ϸ� snake �迭 �Ƚᵵ ��
		map[y][x] = 1;
	}

	cin >> L;

	for (int i = 0; i < L; i++)
	{
		int S;
		cin >> S;
		char D;
		cin >> D;
		dat[S] = D;
	}
}

void solve(int y, int x) {

	//ó�� ��ġ�� 0�ʿ� �ִ°��̹Ƿ� 0���� �ΰ� ���� 
	snake[y][x] = 0;

	//������ ���ϴ� ����
	//0 = ������, 1 = �Ʒ�, 2 = ���� 3 = ��
	int flag = 0;

	//�ʱ� ���� ����
	int slen = 1;

	while (1) {

		//1����Ŭ���� 1�ʾ� �����ϹǷ�
		cnt++;

		//������ �������� �̵�
		//�̷��� �������� �׳� ����迭 ������....
		if (flag == 0) {
			x += 1;
		}
		else if (flag == 1) {
			y += 1;
		}
		else if (flag == 2) {
			x -= 1;
		}
		else if (flag == 3) {
			y -= 1;
		}

		//����� �Ծ��� �� �� �ڸ��� 0���� �ٲٰ� ���� ����
		if (map[y][x] == 1) {
			map[y][x] = 0;
			slen++;
		}

		//�ڱ� ���� �Ӹ��� ���� ���
		//���ο� y,x�� �̹� ������ ��� �װ��� ������ ����� �ð��� ��������
		//�̶� ���� �ð��� �װ��� ������ ���� ���̰�
		//���� ���̺��� �۴ٸ�
		//���� ���� �Ϻΰ� �� ���� �ִ� ����
		//�׷��� ������ game over
		//�� �κ� ���� ������ ���׿�.....
		if (snake[y][x] != 0) {
			if ((cnt - snake[y][x]) <= slen) {
				break;
			}
		}

		//��ο� �ð� �Է�
		snake[y][x] = cnt;

		//���� ������ die
		if (y<1 || y>N || x<1 || x>N) {
			break;
		}

		//���� ��ȯ
		if (dat[cnt] == 'D') {
			flag = (flag + 1) % 4;
		}

		if (dat[cnt] == 'L') {
			//ó���� -1�� ���������� ������ ������ ��� 
			//�۵��� �ȵɰ� ���Ƽ� �̷��� ǥ��
			flag = (flag + 3) % 4;
		}
	}
}

int main() {
	freopen("sample.txt", "r", stdin);

	input();
	solve(1, 1);

	cout << cnt;

	return 0;
}