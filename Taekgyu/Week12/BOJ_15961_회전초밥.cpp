#define _CRT_SECURE_NO_WARNINGS
#include<algorithm>
#include<vector>
#include<cstring>
#include<iostream>
using namespace std;
vector<int>sv;

int N;
int d;
int k;
int c;
int eat[3001];
int Max;

// �ϴ� ȸ���ʹ� ���̺��� 
// k���� �̴´�
// ���⼭ �ߺ��� ������ �ߺ�����

// ó���� ��Ʈ�� ���� �ʹ��� �����ٸ�
// ������ +1

// k�� �������߿� ������ �ִٸ� �״��
// k�� �������߿� ������ ���ٸ� +1

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> d >> k >> c;
	for (int i = 0; i < N; i++)
	{
		int kind = 0;
		cin >> kind;
		sv.push_back(kind);
	}

	// 0�ε������� �����ϴ� ó�� ���̽�
	// DAT�� �߰��Ѵ�
	int idx = 0;
	int count = k;
	bool eatCoupon = false;
	// �ߺ� ����
	int uptwo = 0;
	for (int i = 0; i < k; i++)
	{
		eat[sv[i]]++;
	}

	for (int i = 0; i < 3001; i++)
	{
		if (eat[i] >= 2) {
			uptwo += eat[i] - 1;
		}
	}
	if (eat[c] >= 1) {
		eatCoupon = true;
		Max = count - uptwo;
	}
	else {
		Max = count - uptwo + 1;
	}

	// ó�� ���̽����� 
	// ���� ��Ҹ� �����ϰ�
	// ���� ��Ҹ� �߰��ϴ� ������� N�� Ž��
	for (int i = 0; i < N; i++)
	{
		int idx = i + k;
		if (idx >= N) {
			idx = idx - N;
		}
		count = k;
		// �տ� �ִ� �ʹ� DAT����
		// �ڿ� �ִ� �ʹ� DAT�߰��ϱ�

		// �׸��� �ߺ�üũ�Ѵ�
		// DAT�Ǵ��ؼ� 2�̻��ΰ��� ������ k-���� ���� ����
		eat[sv[i]]--;
		// 1���� �ʰ��ϴ� ��� �׸�ŭ�� uptwo�̴�
		if (eat[sv[i]] != 0)uptwo--;
		eat[sv[idx]]++;
		if (eat[sv[idx]] != 1)uptwo++;

		// �ߺ�üũ = �ʹ��� ������ ����
		count -= uptwo;
		// �̺�Ʈ�ʹ��� �������¶��~
		if (eat[c] >= 1) {
			Max = max(Max, count);
		}
		else {
			Max = max(Max, count + 1);
		}
	}
	cout << Max;

	return 0;
}