#include <iostream>
using namespace std;
int arr[11][11] = { 0 }; //n�� 1~10�����̹Ƿ� 11�� �ʱ�ȭ
int t, n;
void print(int tc) {
	arr[0][0] = 1;  // ù��° ���� �׻� 1
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j || j == 0) // ��Ģ�� ã�ƺ��� i==j�ε��� j==0�ε��� �׻� 1�̹Ƿ�
				arr[i][j] = 1;
			else {
				arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
			} // ���� ���� �밢�� + ���� ������ �밢�� ���� ��
		}
	}
	cout << "#" << tc + 1 << '\n';
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) { //�ʿ� ���� ���� ���� ��Ű�� ���ؼ� i����
			if (arr[i][j] != 0) //0�� �ƴϸ� !
				cout << arr[i][j] << " ";
		}
		cout << '\n';
	}
}
int main() {
	cin >> t;
	for (int i = 0; i < t; i++) { //t���� �׽�Ʈ���̽� 
		cin >> n;
		print(i);  // ����ϰ� ����ϴ� �Լ�
	}

	return 0;
}