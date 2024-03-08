#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

// 구조체 선언 
// 점수 학생번호 순위 순으로 저장
struct sd
{
	int score;
	int idx;
	int top;
};

// 순위를 결정하기 위해 점수 내림차순
bool compare(sd left, sd right) {
	if (left.score > right.score)return true;
	if (left.score < right.score)return false;
	return false;
}

// 출력을 위해 학생번호 오름차순
bool com(sd left, sd right) {
	if (left.idx < right.idx)return true;
	if (left.idx > right.idx)return false;
	return false;
}

// 0,1,2번 인덱스 = 대회 결과 저장
// 3번 인덱스 = 총 점수 합산 저장
vector<sd>sv[4];

int N;

void input() {
	cin >> N;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int score = 0;
			cin >> score;
			sv[i].push_back({ score,j,0 });
		}
	}

	// 합계를 저장할 인덱스 초기화
	for (int i = 0; i < N; i++)
	{
		sv[3].push_back({ 0,i,0 });
	}

	// 3개 대회 점수의 합을 저장
	for (int j = 0; j < N; j++)
	{
		sv[3][j].score = sv[0][j].score + sv[1][j].score + sv[2][j].score;
	}
}

void func() {

	// 점수가 큰 순서대로 정렬
	for (int i = 0; i < 4; i++)
	{
		sort(sv[i].begin(), sv[i].end(), compare);
	}
	// 점수가 큰 순서대로 순위를 매긴다
	for (int i = 0; i < 4; i++)
	{
		int k = 1;
		int cnt = 0;
		for (int j = 1; j < N; j++)
		{
			if (sv[i][j - 1].score == sv[i][j].score) {
				sv[i][j - 1].top = k;
				sv[i][j].top = k;
				cnt++;
			}
			else {
				if (sv[i][j - 1].top == 0) {
					sv[i][j - 1].top = k;
				}
				k += cnt + 1;
				cnt = 0;
				sv[i][j].top = k;
			}
		}
	}

	// 출력에 맞게 학생 순서대로 다시 정렬
	for (int i = 0; i < 4; i++)
	{
		sort(sv[i].begin(), sv[i].end(), com);
	}
}

int main() {

	input();
	func();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << sv[i][j].top << " ";
		}cout << endl;
	}

	return 0;
}