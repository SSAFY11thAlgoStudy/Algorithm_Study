#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;

// N*N격자에서 진행
// 각각의 격자에는 무기들이 존재
// 초기에 플레이어들은 무기가 없는 빈 격자에 위치하며 초기능력치가 있음
// 노란색 배경은 플레이어의 번호
// 빨간색 배경은 초기 능력치
// 총인데 빨간색 배경은 공격력

// 본인이 향하고 있는 방향대로 한칸 전진
// 그게 만약에 맵 밖으로 벗어난다면
// 방향 180 틀어 1칸 전진
// 일단 파악
// 다음 좌표가 맵 밖인지 아닌지
// 맵 밖이라면 방향틀고 하나 전진
// 맵 안이라면 그냥 하나 전진

// 다음 위치에서의 이벤트
// 해당 칸에 총이있는지 확인
// 총이 있는 경우 총을 획득
// 근데 내가 총을 이미 가지고 있다면 
// 더 쎈 총을 얻고 
// 그 총을 그 칸에 버린다.

// 플레이어들이 순서대로 진행하면서
// 같은 칸에서 만나는 경우는 싸운다.
// 각 공격력을 비교하여 더 큰 플레이어가 이긴다
// 이 수치가 같은 경우에는 초기 능력치가 높은 플레이어가 이긴다.
// 이긴 플레이어는 상대 플레이어와의 공격력 차이 만큼 점수를 얻는다.

// 진 플레이어는 가지고 있는 총을 해당 격자에 내려놓고
// 해당 플레이어가 원래 가지고 있던 방향대로 한칸 간다
// 만약 이동하려는 칸에 다른 플레이어가 있는 경우와
// 격자 밖인 경우에는 오른쪽으로 90도씩 회전하여 빈칸이 보이는 순간 이동

// 어떻게 풀것인가?
// 1. 입력받기
// 2. 플레이어 벡터입력
// 3. 권총 벡터 입력
// 4. 맵의 위치에 따라 권총벡터 인덱스 설정
// 5. 순서대로 이동 ( 권총 갈아끼우는 과정 실행 ) -> 플레이어가 권총을 들고 갈때 그 권총을 어떻게 생각할것인가?
// 일단 권총을 집으면 해당 권총 벡터 삭제
// 그리고 권총을 업데이트 하는 과정에서 totalPower에서 Power를 뺀 값이 들고있던 권총에 해당한다.
// 플레이어가 있는 위치 변수를 활용하여 권총 벡터에 추가
// 그럼 권총 벡터가 칸마다 하나 이상 생길 수 있다.
// 그럼 그 칸에 해당하는 권총 개수만큼 돌려라 ( 그 중에 큰 것을 뺀다 )
// 6. fight 함수 만듬 ( 같은 지점에 다른 플레이어가 있을때 )
// 7. 패자는 defeat 함수로 들어감 ( 패자 따로 이동 과정 + 권총 업데이트 )
// 8. 승자는 해당 칸에서 권총 업데이트 진행
// 9. 라운드를 모두 진행하고 점수 출력

struct Player {
	int y;
	int x;
	int dir;
	int Power;
	int totalPower;
	int Score;
};

struct Gun {
	int y;
	int x;
	int Att;
};

vector<Player>player;
vector<Gun>gun;

// 격자크기
int n;
// 플레이어 수
int m;
// 라운드의 수
int k;

int MAP[20][20];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };


void input() {
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int Num = 0;
			cin >> Num;
			if (Num != 0) {
				gun.push_back({ i,j,Num });
			}
		}
	}

	for (int i = 0; i < m; i++)
	{
		int x, y, d, s = 0;
		cin >> x >> y >> d >> s;
		player.push_back({ x - 1,y - 1,d,s,s,0 });
	}

}

void updateGun(int y, int x, int who) {

	// 더 쎈 무기를 얻을 수 있다면 갈아 끼워라
	int gunPower = 0;
	int gunIdx = -1;
	for (int g = 0; g < gun.size(); g++)
	{
		if (y == gun[g].y && x == gun[g].x) {
			if (gunPower < gun[g].Att) {
				gunIdx = g;
				gunPower = gun[g].Att;
			}
		}
	}
	// 갈아끼워라
	if (player[who].totalPower < player[who].Power + gunPower) {
		// 전의 무기 파워 변수
		int beforeAtt = player[who].totalPower - player[who].Power;
		// 전의 무기를 떨궈라
		if (beforeAtt != 0) {
			gun.push_back({ y,x, beforeAtt });
		}
		// 더 쎈 무기를 지워라 (가지고 가라)
		player[who].totalPower = player[who].Power + gunPower;
		gun.erase(gun.begin() + gunIdx, gun.begin() + gunIdx + 1);
	}
}

void defeat(int idx) {
	// 진 플레이어 처리
	// 권총을 그 칸에 떨구고
	int beforeAtt = player[idx].totalPower - player[idx].Power;
	if (beforeAtt != 0) {
		player[idx].totalPower -= beforeAtt;
		gun.push_back({ player[idx].y, player[idx].x, beforeAtt });
	}

	int go = 1;
	while (go == 1) {
		// 다음 위치가 벽이 아니면서 빈칸이면 go를 0로 만들어서
		// while 문을 빠져나오자

		// 해당 방향으로 한칸이동한 위치를 구한다.
		int ny = player[idx].y + dy[player[idx].dir];
		int nx = player[idx].x + dx[player[idx].dir];

		int whoexist = 0;
		for (int i = 0; i < m; i++)
		{
			// 자기자신은 생각하지 않는다.
			if (idx == i)continue;
			if (ny == player[i].y && nx == player[i].x) {
				whoexist = 1;
			}
		}
		// 빈칸이면!!! 방향만 딱 저장하고 while문 탈출
		if (ny < n && nx < n && ny >= 0 && nx >= 0 && whoexist == 0) {
			go = 0;
			continue;
		}
		// 벽이거나 플레이어가 있으면 90도 회전
		player[idx].dir = (player[idx].dir + 1) % 4;
	}
	// 바뀐 방향에 맞게 이동
	player[idx].y += dy[player[idx].dir];
	player[idx].x += dx[player[idx].dir];
	// 패자의 권총 업데이트
	updateGun(player[idx].y, player[idx].x, idx);
}

void fight(int fr, int se) {

	// 누가 이겼는지 판단하라
	// fr이 이긴경우
	if (player[fr].totalPower > player[se].totalPower) {
		// fr은 점수를 가져간다.
		player[fr].Score += player[fr].totalPower - player[se].totalPower;
		// se는 졌다
		defeat(se);
		// 승자는 그 칸에서 권총 업데이트 진행
		updateGun(player[fr].y, player[fr].x, fr);
	}

	// se가 이긴경우
	else if (player[se].totalPower > player[fr].totalPower) {
		// se은 점수를 가져간다.
		player[se].Score += player[se].totalPower - player[fr].totalPower;
		// fr은 졌다
		defeat(fr);
		// 승자는 그 칸에서 권총 업데이트 진행
		updateGun(player[se].y, player[se].x, se);
	}

	// fr과 se가 값이 같으면 원래 Power로 승부결정
	// 대신 점수는 얻을 수 없음
	else {
		// fr이 원래 Power가 높은 경우
		if (player[fr].Power > player[se].Power) {
			defeat(se);
			updateGun(player[fr].y, player[fr].x, fr);
		}
		// se가 원래 Power가 높은 경우
		else {
			defeat(fr);
			updateGun(player[se].y, player[se].x, se);
		}
	}
}

void move() {

	// 플레이어들이 순서대로 진행한다
	for (int i = 0; i < m; i++)
	{

		// 해당 위치에서 한칸 다음 위치를 구해라
		int ny = player[i].y + dy[player[i].dir];
		int nx = player[i].x + dx[player[i].dir];

		// 그 위치가 맵 밖이면 거꾸로~ ( 방향벡터 거꾸로 하고 한칸 진행 )
		if (ny >= n || nx >= n || ny < 0 || nx < 0) {
			player[i].dir = (player[i].dir + 2) % 4;
			ny = player[i].y + dy[player[i].dir];
			nx = player[i].x + dx[player[i].dir];
		}
		// 그 위치로 이동
		player[i].y = ny;
		player[i].x = nx;

		// 그 위치에 다른플레이어가 있으면 fight
		int fightflag = 0;
		for (int j = 0; j < m; j++)
		{
			if (i == j)continue;
			if (ny == player[j].y && nx == player[j].x) {
				fightflag = 1;
				fight(i, j);
			}
		}

		if (fightflag == 0) {
			// 권총 업데이트
			updateGun(ny, nx, i);
		}
	}
}

int main() {

	input();
	for (int i = 0; i < k; i++)
	{
		move();
	}
	for (int i = 0; i < m; i++)
	{
		cout << player[i].Score << " ";
	}
	return 0;
}