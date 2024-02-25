#include <iostream>
#include <queue>
using namespace std;
int n;
int baby_shark = 2; //�Ʊ� ��� ũ��
int map[21][21];
int dx[4] = { -1,0,1,0 }; //���� �� -> ���� -> �Ʒ� -> ������
int dy[4] = { 0,-1,0,1 };
int res = 0; // ���� �ð�
int cnt = 0; // ����� ���� Ƚ�� 
pair<int, int> now; //���� �Ʊ� ��� ��ġ
bool possible = false; //����� �Ծ��� ��

void eat() {
    queue<pair<pair<int, int>, int>> q;
    q.push({ now,0 }); //���� �Ʊ� ��� ��ġ�� ������ �ð� �־��ֱ�
    bool check[21][21] = { false };
    check[now.first][now.second] = true; //���� ��ġ �湮Ȯ��
    int temp = 0; //�Ѹ��� �Ծ��� �� �ɸ� �ð�

    while (!q.empty()) {
        int x = q.front().first.first;
        int y = q.front().first.second;
        int nowtime = q.front().second; //������� �ð�
        //���� ���� ���� �԰� ������ �Ե��� 
        if (map[x][y] > 0 && map[x][y] < baby_shark && temp == nowtime) {
            if (now.first > x || (now.first == x && now.second > y)) {
                now = { x,y }; //����� ���� �Ʊ� ��� ��ġ ����
                continue;
            }
        }
        q.pop();
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx < n && nx >= 0 && ny < n && ny >= 0 && !check[nx][ny]) {
                if (map[nx][ny] <= baby_shark) {
                    if (map[nx][ny] > 0 && map[nx][ny] < baby_shark && !possible) {
                        possible = true; //�� ���� �ܲ�
                        now = { nx,ny }; // ����� ���� ��ġ�� ����
                        temp = nowtime + 1; // ���� �ð� +1
                        res += temp; // ���� �ð��� �����ֱ�
                    }
                    else { //����� ���Ծ��� �� 
                        q.push({ {nx,ny},nowtime + 1 });
                        check[nx][ny] = true;
                    }
                }
            }
        }
    }

}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (map[i][j] == 9) {
                map[i][j] = 0;
                now = { i,j };
            }
        }
    }
    while (true) {
        eat();
        if (possible) { //�Ծ��� ��
            possible = false;
            cnt++; // ����� ���� Ƚ�� ����
            map[now.first][now.second] = 0; // ���� ����� �ڸ� 0
            if (cnt == baby_shark) { //����� ���� Ƚ���� ũ��� ������
                baby_shark += 1; // �Ʊ� ��� ũ�� Ű���ֱ�
                cnt = 0; //����� ���� Ƚ�� �ʱ�ȭ
            }
        }
        else { //���� �� ���� ��
            break; //���� ��� Help
        }
    }
    cout << res;
    return 0;
}