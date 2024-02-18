#include <iostream>
#include <vector>
using namespace std;

int n;
int dragon[101][101];
int dx[4] = { 0, -1, 0, 1 }; // 0,1,2,3�� �°� ���� �迭 ����
int dy[4] = { 1, 0, -1, 0 };
void curve(int x, int y, int d, int g) {
    vector<int> v; // ���� ���� ���� �����ϱ� ���� ����
    v.push_back(d);
    dragon[x][y] = 1; // ������ = 1
    x += dx[d];  //d���� ��ŭ �������ְ�
    y += dy[d];
    dragon[x][y] = 1; // ���� = 1

    for (int i = 0; i < g; i++) { // g���븸ŭ ���ƾ��ϹǷ�
        for (int j = v.size() - 1; j >= 0; j--) { // 1->2->3->2 => 3->0->3->2 �� �� ���� ���� ������ �� +1��
            int dir = (v[j] + 1) % 4;          // ���� ���� �巡�� Ŀ�� ������
            x += dx[dir];
            y += dy[dir];
            dragon[x][y] = 1;
            v.push_back(dir); // ���� ���븦 ���� ���� �� �־��ֱ� 
        }
    }
}
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y, d, g;
        cin >> y >> x >> d >> g; //x,y�� ���ؼ� y���� �Է� ����
        curve(x, y, d, g);
    }
    int res = 0;
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < 101; j++) {
            if (dragon[i][j] == 1 && dragon[i][j + 1] == 1 && dragon[i + 1][j] == 1 && dragon[i + 1][j + 1] == 1) {
                res++; // �� ������ ��� 1(�巡�� Ŀ���� �Ϻ�)�̸� res++
            }
        }
    }
    cout << res;
    return 0;
}