#include <iostream>
using namespace std;

int n, m, r, c, d, cnt = 0; // cnt = û���ϴ� ĭ�� ����
int robot[50][50];
bool check[50][50] = { false };
int dx[4] = { -1, 0, 1, 0 };  // d=0��, d=1��,d=2��,d=3��
int dy[4] = { 0, 1, 0, -1 };

int main() {
    cin >> n >> m >> r >> c >> d;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> robot[i][j];
        }
    }

    check[r][c] = true; //r,c�湮 üũ
    cnt = 1; // 1�� û�� �Ϸ�

    while (true) { //�۵� ���� �� ����
        int x = 0; // û���ߴ��� ���ߴ��� �Ǻ�

        for (int k = 0; k < 4; k++) {
            d = (d + 3) % 4; // (0->3), (3->2), (2->1),(1->0)�ݽð� 90�� ȸ��
            int nx = r + dx[d]; // ���⿡ �°� �̵� ��ǥ ������Ʈ
            int ny = c + dy[d];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m || check[nx][ny] || robot[nx][ny] == 1) {
                continue;  // ������ ����� continue
            }

            check[nx][ny] = true; //û�� ĭ ������Ʈ
            cnt++;  //ĭ���� +1
            r = nx; // ������ǥ ������Ʈ 
            c = ny;
            x = 1; // û�� Ȯ�� 
            break;
        }

        if (x == 0) { //û���� ĭ�� ������
            int nx = r - dx[d]; // ���⿡ �°� ���� ��ǥ ������Ʈ
            int ny = c - dy[d];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m || robot[nx][ny] == 1) {
                break; // ���̰ų� ���� �Ѿ�� �ٷ� ����
            }

            r = nx;  //�װ� �ƴ϶�� ����
            c = ny;
        }
    }

    cout << cnt;

    return 0;
}