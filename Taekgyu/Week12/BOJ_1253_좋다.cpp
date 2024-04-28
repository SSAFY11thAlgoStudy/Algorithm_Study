#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;

int N;
vector<long long>v;
int ans;
int SumNum;

bool tp(int st, int en, int tIdx) {

	while (st <= en) {

		// Ÿ���� �����ϰ� �����Ѵ�
		if (st == tIdx || en == tIdx) {
			if (st == tIdx)st++;
			if (en == tIdx)en--;
		}

		// �������� �������� ��ġ�� ������
		// ���� + �� ���� Ÿ���̶�� true  
		if (st != en && v[st] + v[en] == SumNum) {
			return true;
		}

		// ���� Ÿ�ٺ��� ũ�ٸ� ���� ���ܿ���
		if (v[st] + v[en] > SumNum) {
			en = en - 1;
		}
		// ���� Ÿ�ٺ��� �۴ٸ� ������ �б�
		else {
			st = st + 1;
		}
	}
	return false;
}

int main() {

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		long long Num = 0;
		cin >> Num;
		v.push_back(Num);
	}
	// ���ڵ� �������� ����
	sort(v.begin(), v.end());

	for (int i = 0; i < N; i++)
	{
		// ���� �ϳ��� ���Ѵ�
		// �� ���ڰ� �μ��� ������ �̷�������� �Ǵ�
		SumNum = v[i];
		// �� ������ 
		if (tp(0, N - 1, i)) {
			ans++;
		}
	}
	cout << ans;

	return 0;
}