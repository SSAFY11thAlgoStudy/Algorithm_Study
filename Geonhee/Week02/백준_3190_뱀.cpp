#include <iostream>
#include <queue>
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };
using namespace std;
int main() {
    int n, k;
    int bam[102][102] = { 0 };
    bool check[102][102] = { false };
    cin >> n >> k;
    int a, b;
    for (int i = 0; i < k; i++) {
        cin >> a >> b;
        bam[a - 1][b - 1] = 1;  //(1,1)���� �����ε� (0,0)���ͷ� �������� �ٲ��ַ���
    }
    int cnt = 0; // ��������ð�
    char c;

    int d = 0; // ���⺯ȯ����
    int x = 0, y = 0; // ���� ��ǥ
    queue<pair<int, int>> q;
    q.push({ x,y });// ���� ��ǥ �� ť�� �ֱ�
    int l;
    cin >> l;
    int t1;
    for (int i = 0; i < l; i++) {
        cin >> t1 >> c;

        while (cnt < t1 || i == l - 1) { //cnt < t1 : ���� ���� �̵��ؾ��� �ð��� ���� �ִ� ���
            // i == l-1 : t1�� �Ѿ�� ���� �ȳ������� ���� ���� �� ���� �̵��ؾ��ϹǷ� 
            cnt++;
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx < n && nx >= 0 && ny < n && ny >= 0 && !check[nx][ny]) { // ���� ���� ����
                if (bam[nx][ny] == 1) { //����� ������
                    bam[nx][ny] = 0;  // ��� �Ծ��ְ�
                    q.push({ nx,ny });  // �� ��ǥ �߰�
                    check[nx][ny] = true; //�� �ڸ� true
                }
                else { //��� ������
                    q.push({ nx,ny });
                    check[nx][ny] = true; // ���ڸ� true
                    check[q.front().first][q.front().second] = false; //���� ��ǥ false
                    q.pop(); //���� ��ǥ pop
                }
            }
            else { //���� ���� ���� �������ϸ� ������ ���� ��
                cout << cnt;
                return 0;
            }
            x = nx; //x,y��ǥ ������Ʈ
            y = ny;
            if (cnt == t1) { //�ð��� ���ٸ�
                if (c == 'D') {  // ������ ����
                    d = (d + 1) % 4; //(0,1) -> (1,0) -> (0,-1) -> (-1,0)
                }
                else { //���� ����
                    d = (d + 3) % 4; // (0,1) -> (-1,0) -> (0,-1) -> (1,0)
                }
            }
        }
    }
    return 0;
}