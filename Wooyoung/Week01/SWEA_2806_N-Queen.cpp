#include <iostream>

using namespace std;

int n, cnt;
int col[16];

// ��Ʈ��ŷ ��ǥ����
// 1���� �迭�� ���� ���� ��ġ�� �����Ѵ�
// ex) col[depth]=i;
// �� ���� ���� ��� Ƚ��(��)�� i��° �࿡ ���� ���Ҵٴ� ���̴�.

// 1�� ���� ���� ���� �� ���� 2�� ���� ���� ���� ��
// �ڽ��� �밢���� ���� �࿡���ؼ� ���� �����ִ��� �Ǵ��Ѵ�.
// ���� ���� �ʴٸ� ���� �ΰ� ����Լ��� �ٽ� �����Ͽ� ���� ���� ���� ���� ã�´�.
// �ݺ��Ѵ�.

bool check(int depth) {

	for (int i = 0; i < depth; i++) {
		if (col[depth] == col[i] || (abs(col[depth] - col[i]) == abs(depth - i))) {
			return false;
		}
	}
	return true;

}

void recur(int depth) {

	if (depth == n) {
		cnt++;
		return;
	}

	for (int i = 0; i < n; i++) {
		// ���� depth�� i��°�� ���� ���� ���� �� �ִٸ� ���� ���� ���� ���� ��ͷ� �̵�
		col[depth] = i;
		if (check(depth)) {
			recur(depth + 1);
		}
	}


}


int main() {
	cin >> n;
	recur(0);
	cout << cnt;
	return 0;
}