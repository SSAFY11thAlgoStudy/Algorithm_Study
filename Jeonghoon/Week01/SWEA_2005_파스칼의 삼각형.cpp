#include<iostream>
#include<cstring>

using namespace std;

int N;

//값 저장할 배열
int dat[10][10];

//초기화 0으로
void init() {
	memset(dat, 0, sizeof(dat));
}

void solve(int level)
{
	//N번 반복해야 하므로 level이 N이되면 리턴
	if (level == N) {
		return;
	}


	for (int i = 0; i < N; i++) {
		//(level,0) 의 경우 (level-1,0) 과 같이 1이므로 같은 값 넣어주기
		if (i == 0) {
			dat[level][i] = dat[level - 1][i];
		}

		//이외에는 (level-1, i-1) + (level-1,i) = (level,i)이므로
		else {
			dat[level][i] = dat[level - 1][i] + dat[level - 1][i - 1];
		}
	}

	//다음 단계로 이동
	solve(level + 1);
}

int main() {

	int T = 0;
	cin >> T;

	for (int tc = 1; tc <= T; tc++)
	{
		init();

		//항상 (0,0)은 1이므로
		dat[0][0] = 1;

		cin >> N;

		//첫 줄은 1로 처리했으므로 level 1부터 시작
		solve(1);

		cout << "#" << tc << " " << endl;

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (dat[i][j] == 0) {
					continue;
				}
				cout << dat[i][j] << " ";
			}
			cout << endl;
		}

	}

	return 0;
}