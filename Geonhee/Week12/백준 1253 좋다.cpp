#include<iostream>
#include <algorithm>
using namespace std;

long long n;
long long num[2001];
long long cnt;

bool bs(long long tar, int idx) {
	long long st = 0;
	long long en = n - 1;
	long long mid = 0;

	while (st < en) {
		mid = num[st] + num[en];
		//�� ���� �հ� � ���� ������
		if (mid == tar) {
			//idx�� ��� �޶�� true�� return
			// ex) 0,0,0,3�̸� �ȵ� 
			if (st != idx && en != idx) return true;
			//st�� ���ٸ� st�� 1Ű���
			else if (st == idx) st += 1;
			//ed�� ���ٸ� en�� 1���̱�
			else en -= 1;
		}
		//� ������ ũ�� �� ���� ������ Ž���ϱ� ���� en�� -1
		else if (mid > tar) en -= 1;
		//� �� ���� ������ �� ū ������ Ž���ϱ� ���� st�� +1
		else st += 1;
	}
	//ã�� ���ϰ� �����ٸ� false return
	return false;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> num[i];
	}
	//�̺�Ž���� ���� ����
	sort(num, num + n);
	//num[i]���� Ȯ�� �ε����� ��ġ�� �ȵǹǷ� i�� ����
	for (int i = 0; i < n; i++) {
		bool check = bs(num[i], i);
		//���� �������� ���� ������ �����ֱ�
		if (check)cnt++;

	}
	cout << cnt;
	return 0;
}