#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<cstring>


using namespace std;

int N, M;
//문제의 조건들을 봤을 때 vector를 사용하는 것이 편해보임
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
		//벡터 초기화
		v.clear();

		input();

		cin >> M;

		//입력을 받을 변수
		int num = 0;

		for (int i = 0; i < M; i++)
		{
			cin >> I >> nx >> ny;

			//처음 들어간 수 뒤에 들어가야해서 사용
			//다른 방법이 있을것 같긴한데 생각이 안남
			int cnt = 0;

			for (int j = 0; j < ny; j++)
			{
				// 넣을 숫자 받고
				cin >> num;

				//기존 벡터에 넣기
				v.insert(v.begin() + nx + cnt, num);

				//다음 수는 그 뒤에 와야하니깐 ++
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