#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;

int MAP[4][8]; // 태엽 저장 맵
int K; // 회전을 진행하는 횟수
int circle; // 시작태엽 위치 입력
int dir; // 시작 태엽의 회전방향 입력
int DAT[4]; // 4개 태엽의 회전방향 기록
string line; // 태엽 gear 값
int sum;

// DAT 설정 // 방향 설정
// 시작 태엽 위치 : st
// 시작 방향 변수 : dir
void func() {
	int st = circle - 1;

	// 인접한 태엽이 회전하는지 판단하고 DAT에 회전방향 저장

	// --------- 오른쪽으로 판단할 때 ----------------
	// 현재 자신의 태엽이 회전이 있고
	// 자신의 태엽의 2번 인덱스와
	// 오른쪽 태엽의 6번 인덱스가 다른지 확인

	// --------- 왼쪽으로 판단할 때 ----------------
	// 현재 자신의 태엽이 회전이 있고
	// 자신의 태엽의 6번 인덱스와
	// 왼쪽 태엽의 2번 인덱스가 다른지 확인

	// 시작이 첫번째 태엽일 경우 1-2-3-4 순서
	if (st == 0) {
		DAT[st] = dir;
		for (int i = 0; i < 3; i++)
		{
			if (MAP[i][2] != MAP[i + 1][6] && DAT[i] != 0) {
				dir = -DAT[i];
				DAT[i + 1] = dir;
			}
			else {
				DAT[i + 1] = 0;
			}
		}
	}
	// 시작이 네번째 태엽일 경우 4-3-2-1 순서
	else if (st == 3) {
		DAT[st] = dir;
		for (int i = 3; i > 0; i--)
		{
			if (MAP[i][6] != MAP[i - 1][2] && DAT[i] != 0) {
				dir = -DAT[i];
				DAT[i - 1] = dir;
			}
			else {
				DAT[i - 1] = 0;
			}
		}
	}
	// 시작이 중간 태엽일 경우 반복문 두개로 모두 파악
	else if (st >= 1 && st < 3) {
		DAT[st] = dir;
		// 시작 태엽 기준 왼쪽 판단
		for (int i = st; i > 0; i--)
		{
			if (MAP[i][6] != MAP[i - 1][2] && DAT[i] != 0) {
				dir = -DAT[i];
				DAT[i - 1] = dir;
			}
			else {
				DAT[i - 1] = 0;
			}
		}
		// 시작 태엽 기준 오른쪽 판단
		for (int i = st; i < 3; i++)
		{
			if (MAP[i][2] != MAP[i + 1][6] && DAT[i] != 0) {
				dir = -DAT[i];
				DAT[i + 1] = dir;
			}
			else {
				DAT[i + 1] = 0;
			}
		}
	}
}

// 완성된 DAT 방향 배열을 통한 태엽 회전 실행
void solution() {

	// 첫번째 태엽부터 마지막 태엽까지 반복문
	for (int i = 0; i < 4; i++)
	{
		// 회전하지 않는 태엽이면 넘어가~
		if (DAT[i] == 0) {
			continue;
		}
		//시계방향으로 회전하면
		if (DAT[i] == 1) {
			int temp = MAP[i][7];
			for (int j = 7; j > 0; j--)
			{
				MAP[i][j] = MAP[i][j - 1];
			}
			MAP[i][0] = temp;
		}
		// 반시계방향으로 회전하면
		else if (DAT[i] == -1) {
			int temp = MAP[i][0];
			for (int j = 0; j < 7; j++)
			{
				MAP[i][j] = MAP[i][j + 1];
			}
			MAP[i][7] = temp;
		}
	}
}

int main() {
	for (int i = 0; i < 4; i++)
	{
		cin >> line;
		for (int j = 0; j < 8; j++)
		{
			int a = line[j] - '0';
			MAP[i][j] = a;
		}
	}
	cin >> K;
	// 총 K번 회전 진행
	for (int i = 0; i < K; i++)
	{
		cin >> circle >> dir;
		func();
		solution();
	}
	// K번 회전한 후 각 태엽의 점수 합산
	if (MAP[0][0] == 1) {
		sum += 1;
	}
	if (MAP[1][0] == 1) {
		sum += 2;
	}
	if (MAP[2][0] == 1) {
		sum += 4;
	}
	if (MAP[3][0] == 1) {
		sum += 8;
	}
	cout << sum;
	return 0;
}