#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int T;

//���� ģ���� ������ �迭
unordered_set<string>fr[200001];
//��ü �ο��� ������ map
unordered_map<string, int> mem;

int main() {

	//freopen("sample.txt", "r", stdin);
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int cnt = 0;
	cin >> T;
	for (int i = 0; i < T; i++) {

		//���ɸ��� �ʱ�ȭ
		for (int i = 0; i < cnt; i++) {
			fr[i].clear();
		}
		mem.clear();

		int N;
		cin >> N;
		cnt = 0;

		for (int i = 0; i < N; i++) {
			string m1, m2;
			cin >> m1 >> m2;

			//�� �ɹ� ��ü ��Ͽ� �ֱ�
			mem.insert({ m1,cnt });
			cnt++;
			mem.insert({ m2,cnt });
			cnt++;

			//�� �ɹ��� ��ȣ ã��
			auto it1 = mem.find(m1);
			int m1_ind = it1->second;

			auto it2 = mem.find(m2);
			int m2_ind = it2->second;

			//���� �ֱ�
			fr[m1_ind].insert(m1);
			fr[m2_ind].insert(m2);

			//������ �ջ�� ģ�� ��� �ֱ�
			for (string i : fr[m1_ind]) {
				fr[m2_ind].insert(i);
			}

			//�ջ������ �޻�� ��� �ֱ�
			for (string i : fr[m2_ind]) {
				fr[m1_ind].insert(i);
			}

			cout << fr[m2_ind].size() << "\n";
		}
	}

	return 0;
}