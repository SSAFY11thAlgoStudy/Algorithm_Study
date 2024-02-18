#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <cctype>

using namespace std;

int T, N;
//T: 테스트케이스 개수 N:파스칼삼각형 크기
int arr[10][11] = { 0, };
//size를 10 * 11로 설정한 이유 : 0로 이루어진 col을 맨 왼쪽에 추가

void init() {
	//초기화
	memset(arr, 0, sizeof(arr));
}

void solution() {
	//맨 윗줄 1로 설정
	arr[0][1] = 1;
	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j < N + 1; j++) //col을 하나 추가하였으니 +1
		{
			// 자신의 값은 좌상과 상값의 합
			arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
		}
	}
}

int main() {

	cin >> T;

	//출력
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