#include <iostream>
using namespace std;

int map[101][101];
int n, l;
int res = 0;

void row(int x, int y, int cnt) {  // cnt : ���θ� ���� �� �ֳ� ���� �Ǵ��� ���� ����
    int cur = map[x][y]; // ���� ��ǥ
    int next = map[x][y + 1]; // ���� ��ǥ
    if (y + 1 == n) { // y+1��ǥ�� n�̸� ���� �� �ǳʿ� ���̹Ƿ� res++
        res++;
        return;
    }
    if (cur == next) {  // ���� ��ǥ�� ���� ��ǥ�� ���ٸ�
        row(x, y + 1, cnt + 1); // �׳� �Ѿ�� ��
    }
    else if (cur + 1 == next) { // ���� ��ǥ���� ���� ��ǥ�� 1 �� ũ�ٸ�
        if (cnt >= l) // ���θ� ���� �� ������
            row(x, y + 1, 1); // ������ǥ�� ���� ���θ� �����Ƿ� cnt�� 1�� �ʱ�ȭ
        return;
    }
    else if (cur == next + 1) { // ���� ��ǥ�� ���� ��ǥ���� 1 ũ�ٸ�
        if (y + l < n) { // ������ ����� �ʴ´ٸ�
            for (int i = y + 1; i < y + 1 + l; i++) { // ������ǥ���� l�������� ��ǥ�� ���ƾ� ���θ� ���� �� �����Ƿ�
                if (next != map[x][i]) return; // �ٸ��ٸ� ���� ���ϹǷ� return
            }
            row(x, y + l, 0); // ������ �����ϸ� l�� ���� ������ǥ�� ���� ���θ� ���� ���������Ƿ� cnt�� 0���� �ʱ�ȭ
        }
    }
}

void col(int x, int y, int cnt) {
    int cur = map[x][y];
    int next = map[x + 1][y];
    if (x + 1 == n) {
        res++;
        return;
    }
    if (cur == next) {
        col(x + 1, y, cnt + 1);
    }
    else if (cur + 1 == next) {
        if (cnt >= l)
            col(x + 1, y, 1);
        return;
    }
    else if (cur == next + 1) {
        if (x + l < n) {
            for (int i = x + 1; i < x + 1 + l; i++) {
                if (next != map[i][y]) return;
            }
            col(x + l, y, 0);
        }
    }
}

int main() {
    cin >> n >> l;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        row(i, 0, 1); // �� �Ǵܽ� x��ǥ ���� y��ǥ �̵� cnt�� 1�� �԰� ����
        col(0, i, 1); // �� �Ǵܽ� y��ǥ ���� x��ǥ �̵� cnt�� 1�� �԰� ����
    }
    cout << res;
    return 0;
}