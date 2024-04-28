#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int n, m;
int dat[32001];
vector<int> student[32001];

void line_up() {
	//���� ���� ���� ���;��ϹǷ� q���
	queue<int> q;
	//�ƹ��� �տ����� ��� ���� �͵��� q�� �־��ֱ�
	for (int i = 1; i <= n; i++) {
		if (!dat[i]) q.push(i);
	}
	for (int i = 0; i < n; i++) {
		//q�� �ִ°� ���
		int now = q.front();
		q.pop();
		cout << now << " ";
		//���� now :{}�� �ִ� �͵鿡 ���ؼ� ����
		for (int x : student[now]) {
			//dat[x]1���ֱ�
			dat[x]--;
			//���� dat[x]�� 0�̶�� ���� �� ������ �ǹǷ� q�� �־��ֱ�
			if (!dat[x]) q.push(x);
		}
	}

}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		//a�������� b�� ���;��ϹǷ� a:{b} �̷��� �־��ְ�
		student[a].push_back(b);
		//b�� �ڿ� ���;���  Ƚ���� dat�迭�� ����
		dat[b]++;
	}
	line_up();
	return 0;
}
//ó������ dat[a]++�ؼ� �־��༭ ������ 1�ΰ͵鿡 ���ؼ�
//q�� �־������
//4 3
//4 2
//3 1
//2 3
//�̷��� 2�� 4���� �ڿ� ���;��ϴµ� q�� ������ 4���� ���� ���� ���� ��µǴ� ��찡 �־
//�ݴ�� �ڿ� ���;��ϴ� �͵鿡 ���ؼ� dat�迭�� Ƚ���� �����ؼ� ������� �����
//�ڿ� ���;��ϴ� �͵鿡 ���ؼ� �����ϸ� a�� ���Դ��� b�� �ѹ��̶� ������
//q�� �߰��� �ȵǹǷ� �ڿ� ���;��ϴ� �͵鿡 ���ؼ� Ƚ���� ���ִ� ���� �´ٰ� �Ǵ�
