#include <iostream>
#include <algorithm>
using namespace std;

int n;
long long solution[5001];
long long res1, res2, res3;
long long temp = 4000000001;

void bs() {
	//i���� ���� ��ų ���̹Ƿ� for���Ἥ �ϳ� �� ����
	//������ �� ���̹Ƿ� n-2����
	for (int i = 0; i < n - 2; i++) {
		//i�� �������� �����ְ� �� �����ź��� �̺� Ž�� ����
		int st = i + 1;
		int ed = n - 1;

		//�ߺ� �ȵǹǷ� ��ȣ ���ֱ�
		while (st < ed) {
			long long a = solution[i] + solution[st] + solution[ed];
			//0�̸� �ٷ� ���̹Ƿ� return
			if (a == 0) {
				res1 = solution[i];
				res2 = solution[st];
				res3 = solution[ed];
				return;
			}
			//temp�� ���� ���� ���� ���񰪺��� ũ�ٸ� ��׵� �������ֱ�
			if (temp > abs(a)) {
				temp = abs(a);
				res1 = solution[i];
				res2 = solution[st];
				res3 = solution[ed];
			}
			//����� ���� ���� 0���� �۰� temp���� ������ ũ�ٸ� 
			//�տ��� �÷��ֱ�
			if (a < 0) st++;
			//����� ���� ���� 0���� ũ�� temp���� ������ ũ�ٸ�
			//������ �ٿ��ֱ�
			else ed--;
		}
	}
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) cin >> solution[i];
	//�̺�Ž���� ���� �������� ����
	sort(solution, solution + n);

	bs();
	cout << res1 << " " << res2 << " " << res3;
}