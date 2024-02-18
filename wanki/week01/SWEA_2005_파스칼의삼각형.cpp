#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>

using namespace std;

int N;
int mat[10][10] = { 0 };

//�ʱ�ȭ
void init() {
	memset(mat, 0, sizeof(mat));
}

//�����
void func() {

	//�� �ʱⰪ�� � ���� ���͵� 0,0�� 1�̴�.

	// #. ���� �ʿ���� ����? �Ʒ� ������ �ɰŰ�����...
	mat[0][0] = 1;
	//N�� ���̸� ����
	//1���� �ϴ� ������ 0��ġ�� ���س��� ������
	for (int i = 1; i < N; i++)
	{
		//�ǿ��ʰ��� �� 1�̴�.
		mat[i][0] = 1;
		// 1���� �ϴ� ������ 0��ġ�� ���س��� ������
		//i ���� �ϴ� ���� ��� �����̱⿡ i�� 1�϶� j�� 1���� ä���.
		for (int j = 1; j <= i; j++)
		{
			// ��_i,j =  �� ����(i-1, j) +  �� �»���(i-1, j-1)�̴�.
			// ���� ����
			mat[i][j] = mat[i - 1][j] + mat[i - 1][j - 1];
		}
	}
}

//���
void print() {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < i + 1; j++)
		{
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	freopen("sample_input.txt", "r", stdin);
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++)
	{

		cin >> N;
		init();
		func();
		cout << "#" << tc << endl;
		print();
	}


	return 0;
}