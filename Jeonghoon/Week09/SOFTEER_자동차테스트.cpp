#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int n, q;
vector<int> v;
bool vis[1000000001];

void input() {

	cin >> n >> q;

	//�Է¹��� ���� ���Ϳ� ����
	//�Է¹��� ���� ǥ��
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		v.push_back(temp);
		vis[temp] = true;
	}

	//����
	sort(v.begin(), v.end());
}

void bs(int tar) {
	//�̺� Ž��
	//���� �ε��� 1
	//�� �ε��� �Է¹��� ������ �ε���
	int sp = 1;
	int ep = n - 1;

	while (1) {

		int r = (sp + ep) / 2;

		if (tar == v[r]) {
			//Ÿ�� ���ڸ� ã����
			//�� ���ڱ��� ���� �� ���� * ������ �� ����
			cout << (n - r - 1) * r << "\n";
			break;
		}
		else if (tar > v[r]) {
			sp = r;
		}
		else {
			ep = r;
		}
	}
}

int main() {

	input();

	for (int i = 0; i < q; i++) {

		//Ÿ�� ���� �ϳ��� �ޱ�
		int temp;
		cin >> temp;

		// �� �����̰ų� �������̸� ����� ���� 0�� �̹Ƿ� 0���
		if (temp == v[0] || temp == v[n - 1]) {
			cout << 0 << "\n";
		}
		//�Է� ���� ���� ���ڵ� 0���� ���
		else if (vis[temp] == false) {
			cout << 0 << "\n";
		}
		//�ִ� ���ڸ� �̺�Ž��
		else {
			bs(temp);
		}
	}

	return 0;
}