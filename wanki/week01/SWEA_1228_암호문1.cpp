#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>

using namespace std;

vector<int> v;

int main() {
	int T = 10;

	//freopen("sample_input.txt", "r", stdin);
	//�׽�Ʈ ���̽�
	for (int tc = 1; tc <= T; tc++)
	{
		//���Ͱ��� �ʱ�ȭ�� ���� �׽�Ʈ ���̽� ������ ����
		v.clear();

		// ���� ��ȣ���� ���� N ( 10 �� N �� 20 �� ����)
		int N;
		cin >> N;

		//���� ��ȣ�� N�� �Է�
		for (int i = 0; i < N; i++)
		{
			int passward;
			cin >> passward;
			v.push_back(passward);
		}

		//��ɾ��� ���� ( 5 �� N �� 10 �� ����)
		cin >> N;
		//��ɾ�
		for (int i = 0; i < N; i++)
		{
			// I(���� ��ɾ�), x = idx : ������ ��ġ, y = M : �Է��� ���� 
			char I;
			int idx, M;

			cin >> I >> idx >> M;

			// M���� ������ ��ȣ�� �Է�
			for (int j = 0; j < M; j++)
			{
				int passward; // s
				cin >> passward;

				//v��� ���� �迭�� v.begin�������� ������ ��ġidx
				//�׸��� ��ȣ���� ������ŭ �ε����� �ڷ� �ѱ�� ���� j
				//������ ��ȣ�� passward
				v.insert(v.begin() + idx + j, passward);
			}

		}

		//��º�
		cout << "#" << tc << " ";
		for (int i = 0; i < 10; i++)
		{
			cout << v[i] << " ";
		}
		cout << endl;
	}
}