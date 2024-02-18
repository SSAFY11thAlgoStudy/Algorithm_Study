#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;

int map[101][101];
int N, K, L;

//시간에 따라 방향이 바뀌는 커멘드가 있으므로 이를 
//시간을 인덱스로 사용해 배열에 넣음
char dat[10001];

//뱀의 머리가 시간에 따라 움직인 경로 저장
//map에 시간을 저장해 버리고 안써도 되긴함
int snake[101][101];

//시간 측정용 변수
int cnt;

void input() {
	cin >> N >> K;

	for (int i = 0; i < K; i++) {
		int y, x;
		cin >> y >> x;
		//사과는 맵에 1로 표시
		//이걸 다르게 (ex: -1)로 하면 snake 배열 안써도 됨
		map[y][x] = 1;
	}

	cin >> L;

	for (int i = 0; i < L; i++)
	{
		int S;
		cin >> S;
		char D;
		cin >> D;
		dat[S] = D;
	}
}

void solve(int y, int x) {

	//처음 위치는 0초에 있는것이므로 0으로 두고 시작 
	snake[y][x] = 0;

	//방향을 정하는 변수
	//0 = 오른쪽, 1 = 아래, 2 = 왼쪽 3 = 위
	int flag = 0;

	//초기 뱀의 길이
	int slen = 1;

	while (1) {

		//1사이클마다 1초씩 증가하므로
		cnt++;

		//정해진 방향으로 이동
		//이렇게 하지말고 그냥 방향배열 쓰세요....
		if (flag == 0) {
			x += 1;
		}
		else if (flag == 1) {
			y += 1;
		}
		else if (flag == 2) {
			x -= 1;
		}
		else if (flag == 3) {
			y -= 1;
		}

		//사과를 먹었을 때 그 자리를 0으로 바꾸고 길이 증가
		if (map[y][x] == 1) {
			map[y][x] = 0;
			slen++;
		}

		//자기 몸과 머리가 만난 경우
		//새로운 y,x를 이미 지나온 경우 그곳을 지났을 당시의 시간이 남아있음
		//이때 현재 시간과 그곳을 지났을 때의 차이가
		//몸의 길이보다 작다면
		//아직 몸의 일부가 그 곳에 있는 것임
		//그렇게 때문에 game over
		//이 부분 질문 많을것 같네요.....
		if (snake[y][x] != 0) {
			if ((cnt - snake[y][x]) <= slen) {
				break;
			}
		}

		//경로에 시간 입력
		snake[y][x] = cnt;

		//벽에 박으면 die
		if (y<1 || y>N || x<1 || x>N) {
			break;
		}

		//방향 전환
		if (dat[cnt] == 'D') {
			flag = (flag + 1) % 4;
		}

		if (dat[cnt] == 'L') {
			//처음에 -1로 구현했으나 음수로 내려갈 경우 
			//작동이 안될거 같아서 이렇게 표현
			flag = (flag + 3) % 4;
		}
	}
}

int main() {
	freopen("sample.txt", "r", stdin);

	input();
	solve(1, 1);

	cout << cnt;

	return 0;
}