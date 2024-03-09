#define _CRT_SECURE_NO_WARNINGS
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

char MAP[5][5];
int DAT[26];
// 맵 제작할때 필요한 벡터 v
vector<char>v;
// 쌍 만들때 필요한 벡터 cv
vector<char>cv;
// 암호화된 쌍을 저장할 암호문 벡터 ansv
vector<char>ansv;

string str1;
string str2;

void makeMAP() {
	// 스트링의 요소들을 벡터 v에 저장한다
	// DAT를 활용하여 이미 나왔던 알파벳은 continue
	for (int i = 0; i < str2.size(); i++)
	{
		if (DAT[str2[i] - 'A'] == 1)continue;
		v.push_back(str2[i]);
		DAT[str2[i] - 'A'] = 1;
	}
	// 중복 요소를 제외하고 맵에 넣기
	int flag = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (5 * i + j == v.size()) {
				// 벡터가 다 들어갔다면 break
				flag = 1;
				break;
			}
			MAP[i][j] = v[5 * i + j];
		}
		if (flag) {
			break;
		}
	}
	// 나머지 부분을 아직 나오지 않았던 알파벳 순서대로 채운다
	int st = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (MAP[i][j] != '\0')continue;
			// DAT에서 0의 값을 가지는 인덱스 = 아직 나오지 않은 알파벳
			// 그 인덱스 +'A'를 통해 알파벳 삽입
			for (int k = st; k < 26; k++)
			{
				if (k == 9)continue;
				if (DAT[k] == 0) {
					MAP[i][j] = k + 'A';
					st = k + 1;
					break;
				}
			}
		}
	}
	// 위 코딩까지 맵 만들기 완성
}

void divStr() {

	// str1을 쪼개 쌍으로 만들자
	// 우선 str1을 벡터 cv에 넣자
	// 벡터를 활용하는 이유 : X또는 Q를 삽입하기 편리하다 (인덱스 자동정렬 )
	for (int i = 0; i < str1.size(); i++)
	{
		cv.push_back(str1[i]);
	}
	// X나 Q를 삽입하면 그만큼 벡터의 크기가 커지는 것이므로 반복문 종료 조건을 늘려준다
	int Size = cv.size();
	int addS = 0;
	// cv벡터 요소 두개씩 판단하여 쌍을 만든다
	for (int i = 0; i < Size + addS; i += 2)
	{
		// 벡터크기를 고려하여 break
		if (i + 1 == Size + addS)break;
		// 둘다 X일때는 Q 삽입
		if (cv[i] == 'X' && cv[i + 1] == 'X') {
			cv.insert(cv.begin() + i + 1, 'Q');
			addS++;
		}
		// 두개의 알파벳이 같으면 X 삽입
		else if (cv[i] == cv[i + 1]) {
			cv.insert(cv.begin() + i + 1, 'X');
			addS++;
		}
	}
	// cv벡터를 만들었는데 크기가 홀수면 뒤에 X를 추가하여 2개씩 만들어준다
	// 짝수일때는 진행하지 않는다
	if ((Size + addS) % 2 == 1) {
		cv.push_back('X');
	}
	//이렇게 만들어진 쌍 벡터는 무조건 짝수의 크기를 가진다
}

void makeSecret() {

	// 만들어진 맵과 cv 벡터를 두개씩 자른것을 이용하자
	for (int i = 0; i < cv.size(); i += 2)
	{
		// 첫번째 알파벳의 위치와 두번째 알파벳의 위치를 저장한다
		int fX, fY = 0;
		int sX, sY = 0;
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				if (cv[i] == MAP[j][k]) {
					fX = k;
					fY = j;
				}
				if (cv[i + 1] == MAP[j][k]) {
					sX = k;
					sY = j;
				}
			}
		}

		// 두 알파벳이 같은 행에 있다면~
		if (fY == sY) {
			// 첫번째 요소 암호화해서 더하기
			if (fX != 4) {
				ansv.push_back(MAP[fY][fX + 1]);
			}
			else {
				ansv.push_back(MAP[fY][0]);
			}
			// 두번째 요소 암호화해서 더하기
			if (sX != 4) {
				ansv.push_back(MAP[sY][sX + 1]);
			}
			else {
				ansv.push_back(MAP[sY][0]);
			}
		}
		// 두 알파벳이 같은 열에 있다면~
		else if (fX == sX) {
			// 첫번째 요소 암호화해서 더하기
			if (fY != 4) {
				ansv.push_back(MAP[fY + 1][fX]);
			}
			else {
				ansv.push_back(MAP[0][fX]);
			}
			// 두번째 요소 암호화해서 더하기
			if (sY != 4) {
				ansv.push_back(MAP[sY + 1][sX]);
			}
			else {
				ansv.push_back(MAP[0][sX]);
			}
		}
		// 서로 다른 행 다른 열에 있다면~
		else {
			//서로 X축값을 바꾼값을 저장하면 됨
			ansv.push_back(MAP[fY][sX]);
			ansv.push_back(MAP[sY][fX]);
		}
	}
}

int main() {

	//freopen("sample_input.txt", "r", stdin);
	cin >> str1 >> str2;

	//맵을 우선 만들자
	makeMAP();
	// 스트링을 쪼개서 쌍을 만들자
	divStr();
	// 맵과 쌍을 통해 암호문을 만들자
	makeSecret();

	for (int i = 0; i < ansv.size(); i++)
	{
		cout << ansv[i];
	}
	return 0;
}