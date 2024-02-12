#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <cctype>

using namespace std;

int T, N;
//T: �׽�Ʈ���̽� ���� N:�Ľ�Į�ﰢ�� ũ��
int arr[10][11] = { 0, };
//size�� 10 * 11�� ������ ���� : 0�� �̷���� col�� �� ���ʿ� �߰�

void init() {
	//�ʱ�ȭ
	memset(arr, 0, sizeof(arr));
}

void solution() {
	//�� ���� 1�� ����
	arr[0][1] = 1;
	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j < N + 1; j++) //col�� �ϳ� �߰��Ͽ����� +1
		{
			// �ڽ��� ���� �»�� ���� ��
			arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
		}
	}
}

int main() {

	cin >> T;

	//���
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N;
		init();
		solution();
		cout << "#" << tc << endl;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N + 1; j++)
			{
				if (arr[i][j] != 0) {
					cout << arr[i][j] << " ";
				}
			}cout << endl;
		}
	}

	return 0;
}