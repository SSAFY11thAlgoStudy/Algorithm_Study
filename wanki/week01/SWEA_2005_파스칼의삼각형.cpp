#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>

using namespace std;

int N;
int mat[10][10] = { 0 };

//초기화
void init() {
	memset(mat, 0, sizeof(mat));
}

//연산부
void func() {

	//맨 초기값은 어떤 수가 들어와도 0,0은 1이다.

	// #. 굳이 필요없을 지도? 아래 넣으면 될거같은데...
	mat[0][0] = 1;
	//N의 높이를 가짐
	//1부터 하는 이유는 0위치는 정해놓고 시작함
	for (int i = 1; i < N; i++)
	{
		//맨왼쪽같은 늘 1이다.
		mat[i][0] = 1;
		// 1부터 하는 이유는 0위치는 정해놓고 시작함
		//i 까지 하는 이유 계단 형식이기에 i가 1일때 j는 1까지 채운다.
		for (int j = 1; j <= i; j++)
		{
			// 나_i,j =  내 상측(i-1, j) +  내 좌상측(i-1, j-1)이다.
			// ㄱ자 연산
			mat[i][j] = mat[i - 1][j] + mat[i - 1][j - 1];
		}
	}
}

//출력
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