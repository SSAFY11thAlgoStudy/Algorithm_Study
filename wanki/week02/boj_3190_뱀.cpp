#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>

using namespace std;
int N, K, L;
int map[101][101] = { 0 };
int dy[] = { 0,1,0,-1 }, dx[] = { 1,0,-1,0 };// 우, 하, 좌, 상
int dr = 0, cnt = 0;
//-1이면, +3, 그리고 3초과이면 % 4

/*
1. 먼저 뱀은 몸길이를 늘려 머리를 다음칸에 위치시킨다.
2. 만약 벽이나 자기자신의 몸과 부딪히면 게임이 끝난다.
3. 만약 이동한 칸에 사과가 있다면, 그 칸에 있던 사과가 없어지고 꼬리는 움직이지 않는다.
만약 이동한 칸에 사과가 없다면, 몸길이를 줄여서 꼬리가 위치한 칸을 비워준다.
즉, 몸길이는 변하지 않는다.
*/
//4.게임이 시작할때 뱀은 맨위 맨좌측에 위치하고 뱀의 길이는 1 이다.
//5.뱀은 처음에 오른쪽을 향한다. L왼쪽으로 D오른쪽으로

struct position {
	int y;
	int x;

};
//머리 위치
position head_pos;
//뱀 길이 만큼의 머리가 지나온 위치 배열
vector<position>tail_pos;

struct command {
	int straight;
	char dir;
};
command cmd[100];

//꼬리에 닿았는지 확인
bool tailcheck(position pos) {
	for (int i = 0; i < tail_pos.size(); i++)
	{
		if (pos.y == tail_pos[i].y && pos.x == tail_pos[i].x) {
			return true;
		}
	}
	return false;
}

void move() {
	//i는 cmd에 들어간 순서에 맞도록 실행하기위한 인덱스 변수
	int i = 0;
	//4.게임이 시작할때 뱀은 맨위 맨좌측에 위치하고 뱀의 길이는 1 이다.
	tail_pos.push_back(head_pos);
	while (1) {
		//다음 위치 계산
		head_pos.y += dy[dr];
		head_pos.x += dx[dr];

		//시간초 증가
		cnt++;

		//2. 만약 벽이나 자기자신의 몸과 부딪히면 게임이 끝난다.
		//맵밖으로 이탈시 함수종료
		if (head_pos.y < 1 || head_pos.x< 1 || head_pos.y > N || head_pos.x > N)return;

		// 내 꼬리 발견시 종료
		if (tailcheck(head_pos)) return;

		//1. 먼저 뱀은 몸길이를 늘려 머리를 다음칸에 위치시킨다.
		//머리 위치 이동
		tail_pos.push_back(head_pos);

		/* 3. 만약 이동한 칸에 사과가 있다면, 그 칸에 있던 사과가 없어지고 꼬리는 움직이지 않는다.
			만약 이동한 칸에 사과가 없다면, 몸길이를 줄여서 꼬리가 위치한 칸을 비워준다.
			즉, 몸길이는 변하지 않는다.*/
			//사과발견시 길이 증가
		if (map[head_pos.y][head_pos.x] == 1) {
			//사과를 먹었으면 제거해줌
			map[head_pos.y][head_pos.x] = 0;
		}
		//사과가 없다면 길이가 늘어나지 않기 때문에 마지막 꼬리 위치를 없앰
		else {
			tail_pos.erase(tail_pos.begin());
		}

		//5.뱀은 처음에 오른쪽을 향한다. L왼쪽으로 D오른쪽으로
		//방향 조정
		if (i < L && cmd[i].straight == cnt) {
			if (cmd[i].dir == 'D') { // 시계
				dr = (dr + 1) % 4;
			}
			else if (cmd[i].dir == 'L') { //반시계
				dr = (dr + 3) % 4;
			}
			i++;
		}
	}
}

void input() {
	cin >> N;
	cin >> K;
	//1,1 부터 시작
	for (int i = 1; i <= K; i++)
	{
		int r, c;
		cin >> r >> c;

		map[r][c] = 1;//사과 배치
	}
	cin >> L;

	for (int i = 0; i < L; i++)
	{
		cin >> cmd[i].straight >> cmd[i].dir;
	}
}



int main() {
	//입력
	input();

	//시작 위치
	head_pos.y = 1;
	head_pos.x = 1;

	//구현
	move();

	//출력
	cout << cnt;
}