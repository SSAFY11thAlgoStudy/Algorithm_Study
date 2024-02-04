#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <cctype>
#include <sstream>

using namespace std;

int T;
int N;
// 범위 여유롭게 20으로 잡아주기
int path[20];
int visited[20];
// 경우의 수
int cnt;

//초기화 함수
void init() {
	cnt = 0;
	memset(visited, 0, sizeof(visited));
	memset(path, 0, sizeof(path));
}

//대각선 공격 여부 확인
// ex1) path[3]=0, path[0]=3 인 경우 ( 오른쪽 위 진행 대각선 / ) 
// ex2) path[0]=0, path[3]=3 인 경우 ( 오른쪽 아래 진행 대각선 )

// 절댓값(path 인덱스 row값을 뺸 값) = 절댓값(퀸이 위치한 col값의 차)
bool isAttackQueen(int row) {

	for (int i = 0; i < row; i++)
	{
		if (abs(path[row] - path[i]) == abs(row - i)) {
			return true;
		}
	}
	return false;
}

//재귀 함수
// path는 row 입장
// visited는 col 입장
void func(int row) {
	if (row == N) {
		cnt++;
		return;
	}

	for (int col = 0; col < N; col++)
	{
		// path[0]=0이면
		// (0,0)에 퀸이 존재한다고 가정
		path[row] = col;

		// 해당 col 제외
		if (visited[col] == 1 || isAttackQueen(row))continue;

		// visited[0] = 1(yes)
		// 0번째 col에는 퀸이 존재한다.
		visited[col] = 1;
		// 행 이동
		func(row + 1);
		visited[col] = 0;
		path[row] = 0;
	}
}


int main() {

	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N;
		init();
		// N이 1인 경우는 재귀 함수 돌지 않고 바로 1 출력
		if (N == 1) {
			cout << "#" << tc << " " << N << endl;
		}
		//아닌 경우는 재귀함수 호출
		else {
			func(0);
			cout << "#" << tc << " " << cnt << endl;
		}
	}
	return 0;
}