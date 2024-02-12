#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>

using namespace std;

vector<int> v;

int main() {
	int T = 10;

	//freopen("sample_input.txt", "r", stdin);
	//테스트 케이스
	for (int tc = 1; tc <= T; tc++)
	{
		//백터공간 초기화를 통한 테스트 케이스 오류를 방지
		v.clear();

		// 원본 암호문의 길이 N ( 10 ≤ N ≤ 20 의 정수)
		int N;
		cin >> N;

		//원본 암호문 N개 입력
		for (int i = 0; i < N; i++)
		{
			int passward;
			cin >> passward;
			v.push_back(passward);
		}

		//명령어의 개수 ( 5 ≤ N ≤ 10 의 정수)
		cin >> N;
		//명령어
		for (int i = 0; i < N; i++)
		{
			// I(삽입 명령어), x = idx : 삽입할 위치, y = M : 입력할 개수 
			char I;
			int idx, M;

			cin >> I >> idx >> M;

			// M개의 삽입할 암호문 입력
			for (int j = 0; j < M; j++)
			{
				int passward; // s
				cin >> passward;

				//v라는 백터 배열에 v.begin시작점에 삽입할 위치idx
				//그리고 암호문의 갯수만큼 인덱스를 뒤로 넘기기 위한 j
				//삽입할 암호문 passward
				v.insert(v.begin() + idx + j, passward);
			}

		}

		//출력부
		cout << "#" << tc << " ";
		for (int i = 0; i < 10; i++)
		{
			cout << v[i] << " ";
		}
		cout << endl;
	}
}