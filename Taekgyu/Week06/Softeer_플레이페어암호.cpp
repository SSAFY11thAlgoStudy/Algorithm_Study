#define _CRT_SECURE_NO_WARNINGS
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

char MAP[5][5];
int DAT[26];
// �� �����Ҷ� �ʿ��� ���� v
vector<char>v;
// �� ���鶧 �ʿ��� ���� cv
vector<char>cv;
// ��ȣȭ�� ���� ������ ��ȣ�� ���� ansv
vector<char>ansv;

string str1;
string str2;

void makeMAP() {
	// ��Ʈ���� ��ҵ��� ���� v�� �����Ѵ�
	// DAT�� Ȱ���Ͽ� �̹� ���Դ� ���ĺ��� continue
	for (int i = 0; i < str2.size(); i++)
	{
		if (DAT[str2[i] - 'A'] == 1)continue;
		v.push_back(str2[i]);
		DAT[str2[i] - 'A'] = 1;
	}
	// �ߺ� ��Ҹ� �����ϰ� �ʿ� �ֱ�
	int flag = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (5 * i + j == v.size()) {
				// ���Ͱ� �� ���ٸ� break
				flag = 1;
				break;
			}
			MAP[i][j] = v[5 * i + j];
		}
		if (flag) {
			break;
		}
	}
	// ������ �κ��� ���� ������ �ʾҴ� ���ĺ� ������� ä���
	int st = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (MAP[i][j] != '\0')continue;
			// DAT���� 0�� ���� ������ �ε��� = ���� ������ ���� ���ĺ�
			// �� �ε��� +'A'�� ���� ���ĺ� ����
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
	// �� �ڵ����� �� ����� �ϼ�
}

void divStr() {

	// str1�� �ɰ� ������ ������
	// �켱 str1�� ���� cv�� ����
	// ���͸� Ȱ���ϴ� ���� : X�Ǵ� Q�� �����ϱ� ���ϴ� (�ε��� �ڵ����� )
	for (int i = 0; i < str1.size(); i++)
	{
		cv.push_back(str1[i]);
	}
	// X�� Q�� �����ϸ� �׸�ŭ ������ ũ�Ⱑ Ŀ���� ���̹Ƿ� �ݺ��� ���� ������ �÷��ش�
	int Size = cv.size();
	int addS = 0;
	// cv���� ��� �ΰ��� �Ǵ��Ͽ� ���� �����
	for (int i = 0; i < Size + addS; i += 2)
	{
		// ����ũ�⸦ ����Ͽ� break
		if (i + 1 == Size + addS)break;
		// �Ѵ� X�϶��� Q ����
		if (cv[i] == 'X' && cv[i + 1] == 'X') {
			cv.insert(cv.begin() + i + 1, 'Q');
			addS++;
		}
		// �ΰ��� ���ĺ��� ������ X ����
		else if (cv[i] == cv[i + 1]) {
			cv.insert(cv.begin() + i + 1, 'X');
			addS++;
		}
	}
	// cv���͸� ������µ� ũ�Ⱑ Ȧ���� �ڿ� X�� �߰��Ͽ� 2���� ������ش�
	// ¦���϶��� �������� �ʴ´�
	if ((Size + addS) % 2 == 1) {
		cv.push_back('X');
	}
	//�̷��� ������� �� ���ʹ� ������ ¦���� ũ�⸦ ������
}

void makeSecret() {

	// ������� �ʰ� cv ���͸� �ΰ��� �ڸ����� �̿�����
	for (int i = 0; i < cv.size(); i += 2)
	{
		// ù��° ���ĺ��� ��ġ�� �ι�° ���ĺ��� ��ġ�� �����Ѵ�
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

		// �� ���ĺ��� ���� �࿡ �ִٸ�~
		if (fY == sY) {
			// ù��° ��� ��ȣȭ�ؼ� ���ϱ�
			if (fX != 4) {
				ansv.push_back(MAP[fY][fX + 1]);
			}
			else {
				ansv.push_back(MAP[fY][0]);
			}
			// �ι�° ��� ��ȣȭ�ؼ� ���ϱ�
			if (sX != 4) {
				ansv.push_back(MAP[sY][sX + 1]);
			}
			else {
				ansv.push_back(MAP[sY][0]);
			}
		}
		// �� ���ĺ��� ���� ���� �ִٸ�~
		else if (fX == sX) {
			// ù��° ��� ��ȣȭ�ؼ� ���ϱ�
			if (fY != 4) {
				ansv.push_back(MAP[fY + 1][fX]);
			}
			else {
				ansv.push_back(MAP[0][fX]);
			}
			// �ι�° ��� ��ȣȭ�ؼ� ���ϱ�
			if (sY != 4) {
				ansv.push_back(MAP[sY + 1][sX]);
			}
			else {
				ansv.push_back(MAP[0][sX]);
			}
		}
		// ���� �ٸ� �� �ٸ� ���� �ִٸ�~
		else {
			//���� X�ప�� �ٲ۰��� �����ϸ� ��
			ansv.push_back(MAP[fY][sX]);
			ansv.push_back(MAP[sY][fX]);
		}
	}
}

int main() {

	//freopen("sample_input.txt", "r", stdin);
	cin >> str1 >> str2;

	//���� �켱 ������
	makeMAP();
	// ��Ʈ���� �ɰ��� ���� ������
	divStr();
	// �ʰ� ���� ���� ��ȣ���� ������
	makeSecret();

	for (int i = 0; i < ansv.size(); i++)
	{
		cout << ansv[i];
	}
	return 0;
}