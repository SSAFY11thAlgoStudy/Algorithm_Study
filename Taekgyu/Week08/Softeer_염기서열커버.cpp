#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;

// 처음에 이 문제를 보았을때 입력순서대로 초염기서열을 제작
// 하지만 반례 케이스 존재
// 따라서 완탐으로 품
// 근데 시간초과남
// 따라서, 안좋은 방법이지만
// 위에서 아래로, 아래서 위로, 중간에서 나가면서, 중간으로 들어오며 초염기서열을 제작
// 근데 우연치않게 정답나옴;;
vector<string>sv;
int N, M;
char MAP[15][20];
int visited[15];
string set;
int Min = 21e8;

void input() {

	cin >> N >> M;
	// 초기에 벡터에 M길이만큼의 와일드 카드로 초기화 한다
	for (int i = 0; i < M; i++)
	{
		set = set + ".";
	}
	sv.push_back(set);
	// 입력받은 염기서열 MAP에 저장
	for (int i = 0; i < N; i++)
	{
		string str1;
		cin >> str1;
		for (int j = 0; j < M; j++)
		{
			MAP[i][j] = str1[j];
		}
	}
}


void makeSV(string str) {

	// 들어온 문자열값을 확인한다
	// 들어온 문자열중에 알파벳이 몇개 있는지 저장한다 An
	int An = 0;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] != '.') {
			An++;
		}
	}

	// 기존 서열과 비교하였을때 해당 서열로 들어갈수 있다면 갱신
	// 아니라면 새롭게 벡터에 추가한다.
	int flag = 0;
	for (int i = 0; i < sv.size(); i++)
	{
		// An개수를 충족시키는지 확인
		int AnCnt = 0;
		for (int j = 0; j < M; j++) {
			// 비교하고자 하는 서열이 와일드카드이거나
			// 염기의 종류가 같다면 AnCnt 증가
			if (str[j] != '.') {
				if (sv[i][j] == '.' || sv[i][j] == str[j]) {
					AnCnt++;
				}
			}
		}
		// 조건을 충족한다면
		if (An == AnCnt) {
			flag = 1;
			//기존 sv스트링값과 str값의 알파벳을 합친값으로 갱신한다.
			for (int k = 0; k < M; k++)
			{
				if (sv[i][k] == '.' && str[k] != '.') {
					sv[i][k] = str[k];
				}
			}
			break;
		}
	}
	// 기존에 있는 스트링에 들어갈수 없는 경우
	// 벡터에 스트링을 새롭게 추가한다
	if (flag == 0) {
		sv.push_back(str);
	}
}

int main() {
	//freopen("sample_input.txt", "r", stdin);
	input();

	for (int i = 0; i < N; i++)
	{
		// 위에서 아래로 초염기서열을 만들자
		if (i == 0) {
			for (int j = 0; j < N; j++)
			{
				string str = "";
				for (int k = 0; k < M; k++)
				{
					str += MAP[j][k];
				}
				// MAP의 한줄마다 서열을 만들어 makeSV 함수로 들어간다.
				makeSV(str);
			}
			// 다 만들고 나면 벡터의 최소 사이즈를 저장한다.
			int a = sv.size();
			Min = min(Min, a);
			sv.clear();
		}
		// 아래서 위로 초염기서열을 만들자
		else if (i == N - 1) {
			for (int j = N - 1; j >= 0; j--)
			{
				string str = "";
				for (int k = 0; k < M; k++)
				{
					str += MAP[j][k];
				}
				makeSV(str);
			}
			int a = sv.size();
			Min = min(Min, a);
			sv.clear();
		}
		// 중간부터 초염기서열을 만들자
		else {
			for (int j = i; j < N; j++)
			{
				string str = "";
				for (int k = 0; k < M; k++)
				{
					str += MAP[j][k];
				}
				makeSV(str);
			}
			for (int j = i - 1; j >= 0; j--)
			{
				string str = "";
				for (int k = 0; k < M; k++)
				{
					str += MAP[j][k];
				}
				makeSV(str);
			}
			int a = sv.size();
			Min = min(Min, a);
			sv.clear();


			for (int j = i - 1; j >= 0; j--)
			{
				string str = "";
				for (int k = 0; k < M; k++)
				{
					str += MAP[j][k];
				}
				makeSV(str);
			}
			for (int j = i; j < N; j++)
			{
				string str = "";
				for (int k = 0; k < M; k++)
				{
					str += MAP[j][k];
				}
				makeSV(str);
			}
			a = sv.size();
			Min = min(Min, a);
			sv.clear();


			for (int j = 0; j <= i; j++)
			{
				string str = "";
				for (int k = 0; k < M; k++)
				{
					str += MAP[j][k];
				}
				makeSV(str);
			}
			for (int j = N - 1; j > i; j--)
			{
				string str = "";
				for (int k = 0; k < M; k++)
				{
					str += MAP[j][k];
				}
				makeSV(str);
			}
			a = sv.size();
			Min = min(Min, a);
			sv.clear();
		}
	}
	cout << Min;
	return 0;
}