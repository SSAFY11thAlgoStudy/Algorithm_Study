#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<cstring>


using namespace std;

int N, M;
//������ ���ǵ��� ���� �� vector�� ����ϴ� ���� ���غ���
vector<int> v;
char I;
//
int nx, ny;

void input() {
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int num;
		cin >> num;
		v.push_back(num);
	}
}

void solve() {


}

int main() {
	//freopen("sample.txt", "r", stdin);

	for (int tc = 1; tc <= 10; tc++)
	{
		//���� �ʱ�ȭ
		v.clear();

		input();

		cin >> M;

		//�Է��� ���� ����
		int num = 0;

		for (int i = 0; i < M; i++)
		{
			cin >> I >> nx >> ny;

			//ó�� �� �� �ڿ� �����ؼ� ���
			//�ٸ� ����� ������ �����ѵ� ������ �ȳ�
			int cnt = 0;

			for (int j = 0; j < ny; j++)
			{
				// ���� ���� �ް�
				cin >> num;

				//���� ���Ϳ� �ֱ�
				v.insert(v.begin() + nx + cnt, num);

				//���� ���� �� �ڿ� �;��ϴϱ� ++
				cnt++;
			}
		}

		cout << "#" << tc << " ";

		for (int i = 0; i < 10; i++)
		{
			cout << v[i] << " ";
		}
		cout << "\n";
	}

	return 0;
}