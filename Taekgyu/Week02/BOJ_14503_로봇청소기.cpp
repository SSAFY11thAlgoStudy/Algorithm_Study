#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>

using namespace std;

struct pos {
	int y;
	int x;
};

int N, M;
int r, c;
int d;
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
int MAP[50][50];
int No;
int go;
int cnt;
int flag;

// ���� �ٶ󺸴� ����
int nowDir;
// ���� ��ġ
pos now = { 0 };
// ���� ���� ��ġ
pos Turn = { 0 };

void init() {
	memset(MAP, 0, sizeof(MAP));
	flag = 0;
}

void solution(pos st) {

	// û���� �� 8�� ǥ��
	if (MAP[st.y][st.x] != 8) {
		MAP[st.y][st.x] = 8;
		//cout << "cnt����";
		cnt++;
	}
	//�� ���⿡ û���� ���� �ִ��� Ȯ���ϴ� ���� No
	No = 0;
	for (int i = 0; i < 4; i++)
	{
		pos next = { 0 };
		next.y = st.y + dy[i];
		next.x = st.x + dx[i];

		// û�Ҹ� �߰ų� ���̸� ����
		if (MAP[next.y][next.x] == 8 || MAP[next.y][next.x] == 1) {
			No++;
		}
	}
	// û�ҵ��� ���� ��ĭ�� ���� ���
	if (No == 4) {
		int SelectBack = 0;
		// ���� ���� ����
		if (nowDir == 0)SelectBack = 2;
		if (nowDir == 1)SelectBack = 3;
		if (nowDir == 2)SelectBack = 0;
		if (nowDir == 3)SelectBack = 1;

		pos Back = { 0 };
		Back.y = st.y + dy[SelectBack];
		Back.x = st.x + dx[SelectBack];

		// ���� ���� �� ���̸� ������~
		if (MAP[Back.y][Back.x] == 1) {
			flag = 1;
			return;
		}

		// ���� ���� �� û���Ѱ��̸� �ϴ� ����
		if (MAP[Back.y][Back.x] == 8) {
			now.y = Back.y;
			now.x = Back.x;
			solution(now);
		}
	}
	//û�ҵ��� ���� ��ĭ�� �ִ� ���
	else {
		int TurnDir = nowDir;
		// �ݽð� ���� 0 -> 3 -> 2 -> 1
		// ���� 0�϶��� 3���� ȸ��
		if (TurnDir == 0) {
			TurnDir = 3;
		}
		// 0�� �ƴҶ��� -1
		else {
			TurnDir--;
		}
		TurnDir = TurnDir % 4;
		Turn.y = st.y + dy[TurnDir];
		Turn.x = st.x + dx[TurnDir];

		// û�� ���� �� ã�������� ���ƶ�~
		while (true) {
			if (flag == 1) {
				return;
			}
			// û�Ұ� �ȵ� ���̶�� ����~
			if (MAP[Turn.y][Turn.x] == 0) {
				now.y = Turn.y;
				now.x = Turn.x;
				nowDir = TurnDir;
				solution(now);
			}

			if (TurnDir == 0) {
				TurnDir = 3;
			}
			else {
				TurnDir--;
			}
			TurnDir = TurnDir % 4;
			nowDir = TurnDir;
			Turn.y = st.y + dy[TurnDir];
			Turn.x = st.x + dx[TurnDir];

		}
	}
}


int main()
{

	//freopen("sample_input.txt", "r", stdin);

	cin >> N >> M;
	cin >> r >> c >> d;

	init();

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			// 0�� ��� û�� X
			// 1�� ��� ��
			cin >> MAP[i][j];
		}
	}
	// ���� ���� ����
	nowDir = d;
	solution({ r,c });
	cout << cnt;
	return 0;
}

// �ùķ��̼� �ڵ�
// �������� �϶���� �ϸ� Ǯ����.
// �ݽð� ������ �������ؼ� ����迭 �򰥸��� ����