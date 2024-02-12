#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <cctype>
#include <sstream>

using namespace std;

int T;
int N;
// ���� �����Ӱ� 20���� ����ֱ�
int path[20];
int visited[20];
// ����� ��
int cnt;

//�ʱ�ȭ �Լ�
void init() {
	cnt = 0;
	memset(visited, 0, sizeof(visited));
	memset(path, 0, sizeof(path));
}

//�밢�� ���� ���� Ȯ��
// ex1) path[3]=0, path[0]=3 �� ��� ( ������ �� ���� �밢�� / ) 
// ex2) path[0]=0, path[3]=3 �� ��� ( ������ �Ʒ� ���� �밢�� )

// ����(path �ε��� row���� �A ��) = ����(���� ��ġ�� col���� ��)
bool isAttackQueen(int row) {

	for (int i = 0; i < row; i++)
	{
		if (abs(path[row] - path[i]) == abs(row - i)) {
			return true;
		}
	}
	return false;
}

//��� �Լ�
// path�� row ����
// visited�� col ����
void func(int row) {
	if (row == N) {
		cnt++;
		return;
	}

	for (int col = 0; col < N; col++)
	{
		// path[0]=0�̸�
		// (0,0)�� ���� �����Ѵٰ� ����
		path[row] = col;

		// �ش� col ����
		if (visited[col] == 1 || isAttackQueen(row))continue;

		// visited[0] = 1(yes)
		// 0��° col���� ���� �����Ѵ�.
		visited[col] = 1;
		// �� �̵�
		func(row + 1);
		visited[col] = 0;
		path[row] = 0;
	}
}


int main() {

	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N;
		init();
		// N�� 1�� ���� ��� �Լ� ���� �ʰ� �ٷ� 1 ���
		if (N == 1) {
			cout << "#" << tc << " " << N << endl;
		}
		//�ƴ� ���� ����Լ� ȣ��
		else {
			func(0);
			cout << "#" << tc << " " << cnt << endl;
		}
	}
	return 0;
}