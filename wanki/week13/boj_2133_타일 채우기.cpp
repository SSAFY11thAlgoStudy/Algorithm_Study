#include<iostream>

using namespace std;

int N;
int block[31];
//(block[N - 2] * 3) + (block[N - 2] * 2) + (block[N - 4] * 2)... + 2
int main() {
	cin >> N;

	block[0] = 1;
	block[1] = 0;
	block[2] = 3;

	for (int n = 3; n <= N; n++)
	{
		//Ȧ�� ũ���� Ʋ�� ������ ä��� ����
		if (n % 2 == 1) {
			block[n] = 0;
			continue;
		}
		else {
			for (int i = 2; i <= n; i += 2)
			{
				//n�� �ڽź��� ���� n-2�� ũ�⸦ ���� ��������
				//n-2�� Ƚ���� 2���� ��츦 ���� ����� ���� ������.
				if (i == 2) {
					block[n] = block[n - 2] * block[2];
				}
				//�ڽžȿ� �����Ҽ� �ִ� ������ X 2�� ��츦 ������.
				else {
					block[n] += block[n - i] * 2;
				}
			}
		}
	}

	cout << block[N];//N�� ���� ��簪 2
}