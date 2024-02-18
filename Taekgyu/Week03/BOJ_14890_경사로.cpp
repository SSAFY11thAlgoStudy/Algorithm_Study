#define _NO_CRT_NO_SECURE
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

int N, L; // 맵의 크기, 경사로의 길이
int MAP[110][110];// 입력받는 경사 맵
int Runway[110][110]; // 경사로 설치 맵 배열
int ansCnt; // 정답 카운트
int flag; // 조건을 만족하는지 판단

// 해결방법 : 가로 체크 후 세로 체크
// 가로 체크 시 왼쪽부터 체크 케이스와 오른쪽부터 체크 케이스 나눔
// 왼쪽부터 체크 시 : 오른쪽 부분이 증가면 경사로 놓기( 단, 경사로 길이만큼 평평한가 체크 )
// 오른쪽부터 체크 시 : 왼쪽 부분이 증가면 경사로 놓기( 단, 경사로 길이만큼 평평한가 체크 )
// 
// 마지막 체크사항
// 1. 경사로 배열 맵에서 중첩 확인
// 2. 근접 높이가 2차이 나지 않는지


// 가로 진행 경사로 체크
void runway_ROW() {

	// 가로 길 체크 
	for (int i = 0; i < N; i++)
	{
		flag = 0;

		// 오른쪽에서 왼쪽으로 진행
		for (int j = N - 1; j > 0; j--)
		{
			if (flag == 1) {
				break;
			}
			// 경사로의 길이가 1이상일 때
			// 경사로가 설치되는 지역이 평평한지 확인하는 부분
			if (L > 1) {
				// 왼쪽이 높을 때
				if (MAP[i][j - 1] - MAP[i][j] == 1) {
					for (int k = 1; k < L; k++)
					{
						if (j + k >= N) {
							flag = 1;
							break;
						}
						// 경사로 길이만큼 동일하지 않다면
						if (MAP[i][j] != MAP[i][j + k]) {
							flag = 1;
							break;
						}
					}if (flag == 0) {
						for (int k = 0; k < L; k++)
						{
							Runway[i][j + k]++;
						}
					}
				}
			}

			// 인접한 땅의 높이가 2차이 이상날 때
			if (j >= 1) {
				if (abs(MAP[i][j - 1] - MAP[i][j]) >= 2) {
					flag = 1;
					break;
				}
			}
			// 경사로의 길이가 1일 때
			// 경사로의 길이만큼 평평한지 체크할 필요가 없음
			if (L == 1) {
				if (MAP[i][j - 1] - MAP[i][j] == 1) {
					Runway[i][j]++;
				}
			}
		}

		// 왼쪽에서 오른쪽으로 진행
		for (int j = 0; j < N - 1; j++)
		{
			if (flag == 1) {
				break;
			}

			if (L > 1) {
				// 오른쪽이 높을 때
				if (MAP[i][j] - MAP[i][j + 1] == -1) {
					for (int k = 1; k < L; k++)
					{
						if (j - k < 0) {
							flag = 1;
							break;
						}
						// 경사로 길이만큼 동일하지 않다면
						if (MAP[i][j] != MAP[i][j - k]) {
							flag = 1;
							break;
						}
					}if (flag == 0) {
						for (int k = 0; k < L; k++)
						{
							Runway[i][j - k]++;
						}
					}
				}
			}
			// 인접한 땅의 높이가 2차이 나는지 판단하는 부분은
			// 위 반복문에서 절댓값으로 확인 끝

			// 경사로의 길이가 1일 때
			// 경사로의 길이만큼 평평한지 체크할 필요가 없음
			if (L == 1) {
				if (MAP[i][j] - MAP[i][j + 1] == -1) {
					Runway[i][j]++;
				}
			}
		}

		// 왼쪽시작, 오른쪽시작 판단을 끝낸 후 경사로 배열 확인 
		for (int j = 0; j < N; j++)
		{
			// 위의 조건을 다 만족하지만 경사로가 겹칠 때
			if (Runway[i][j] >= 2) {
				flag = 1;
				break;
			}
		}
		// 위의 조건을 모두 만족한다면 카운트 증가~
		if (flag == 0) {
			ansCnt++;
		}
	}
}


// 세로 진행 경사로 체크
// 가로 진행 설명 참고
void runway_COL() {

	for (int j = 0; j < N; j++)
	{
		flag = 0;

		for (int i = N - 1; i > 0; i--)
		{
			if (flag == 1) {
				break;
			}

			if (L > 1) {
				if (MAP[i - 1][j] - MAP[i][j] == 1) {
					for (int k = 1; k < L; k++)
					{
						if (i + k >= N) {
							flag = 1;
							break;
						}
						if (MAP[i][j] != MAP[i + k][j]) {
							flag = 1;
							break;
						}
					}if (flag == 0) {
						for (int k = 0; k < L; k++)
						{
							Runway[i + k][j]++;
						}
					}
				}
			}

			if (i >= 1) {
				if (abs(MAP[i - 1][j] - MAP[i][j]) >= 2) {
					flag = 1;
					break;
				}
			}

			if (L == 1) {
				if (MAP[i - 1][j] - MAP[i][j] == 1) {
					Runway[i][j]++;
				}
			}
		}

		for (int i = 0; i < N - 1; i++)
		{
			if (flag == 1) {
				break;
			}

			if (L > 1) {

				if (MAP[i][j] - MAP[i + 1][j] == -1) {
					for (int k = 1; k < L; k++)
					{
						if (i - k < 0) {
							flag = 1;
							break;
						}

						if (MAP[i][j] != MAP[i - k][j]) {
							flag = 1;
							break;
						}
					}if (flag == 0) {
						for (int k = 0; k < L; k++)
						{
							Runway[i - k][j]++;
						}
					}
				}
			}

			if (L == 1) {
				if (MAP[i][j] - MAP[i + 1][j] == -1) {
					Runway[i][j]++;
				}
			}
		}

		for (int i = 0; i < N; i++)
		{

			if (Runway[i][j] >= 2) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			ansCnt++;
		}
	}
}

int main() {

	cin >> N >> L;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> MAP[i][j];
		}
	}
	runway_ROW();
	// 가로 진행 판단 후 경사로 배열 초기화
	memset(Runway, 0, sizeof(Runway));
	runway_COL();
	cout << ansCnt;
	return 0;
}