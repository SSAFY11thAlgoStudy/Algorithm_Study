#include <iostream>

using namespace std;

int n, cnt;
int col[16];

// 백트래킹 대표문제
// 1차원 배열에 퀸을 놓을 위치를 저장한다
// ex) col[depth]=i;
// 위 뜻은 현재 재귀 횟수(열)의 i번째 행에 퀸을 놓았다는 뜻이다.

// 1번 열에 퀸을 놓고 그 다음 2번 열에 퀸을 놓을 때
// 자신의 대각선과 현재 행에대해서 퀸이 놓여있는지 판단한다.
// 놓여 있지 않다면 퀸을 두고 재귀함수를 다시 진행하여 다음 열에 놓을 퀸을 찾는다.
// 반복한다.

bool check(int depth) {

	for (int i = 0; i < depth; i++) {
		if (col[depth] == col[i] || (abs(col[depth] - col[i]) == abs(depth - i))) {
			return false;
		}
	}
	return true;

}

void recur(int depth) {

	if (depth == n) {
		cnt++;
		return;
	}

	for (int i = 0; i < n; i++) {
		// 현재 depth의 i번째에 퀸을 놓고 놓을 수 있다면 다음 퀸을 놓기 위해 재귀로 이동
		col[depth] = i;
		if (check(depth)) {
			recur(depth + 1);
		}
	}


}


int main() {
	cin >> n;
	recur(0);
	cout << cnt;
	return 0;
}