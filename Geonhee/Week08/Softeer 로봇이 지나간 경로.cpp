#include <iostream>
#include <algorithm>
using namespace std;

int h, w;
char map[26][26];
bool visited[26][26] = { false };
int a, b;
string dir = "v<^>";
int dy[4] = { 1,0,-1,0 };
int dx[4] = { 0,-1,0,1 };
int d;

void find() {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            //���� ��ǥ ��ó #�� ���� �־��� ���� 
            int temp = 0;
            for (int k = 0; k < 4; k++) {
                int ny = i + dy[k];
                int nx = j + dx[k];
                //4�������� ���� #�� ���� �����ֱ�
                if (ny < h && ny >= 0 && nx < w && nx >= 0) {
                    if (map[i][j] == '#' && map[ny][nx] == '#') {
                        temp++;
                    }
                }
            }
            //1�̸� ��� ������ �� �� ����
            if (temp == 1) {
                a = i;
                b = j;
                //��� ������ �������� ó�� �κ��� �ٶ󺸴� ���� �����ֱ�
                for (int k = 0; k < 4; k++) {
                    int ny = i + dy[k];
                    int nx = j + dx[k];
                    //���� �ȿ� �ְ�
                    if (ny < h && ny >= 0 && nx < w && nx >= 0) {
                        // ���� �� ��ó 4������ ���� # ������ ó�� ����
                        if (map[i][j] == '#' && map[ny][nx] == '#') d = k;
                    }
                }
                //ã������ return
                return;
            }
        }
    }
}

void command(int y, int x) {
    //�̵��� ĭ�� #�� ���̹Ƿ� �ٷ� �湮 üũ
    visited[y][x] = true;
    //2ĭ�����ؾ��ϹǷ� ��ĭ �� �����ֱ�
    y += dy[d];
    x += dx[d];
    //���� �����Ƿ� A���
    cout << "A";
    //��ĭ �� ������ ĭ�� �湮 üũ
    visited[y][x] = true;

    //4���⿡ ���ؼ� ���� �ٲ���ϴ��� üũ
    for (int k = 0; k < 4; k++) {
        int ny = y + dy[k];
        int nx = x + dx[k];

        if (ny < h && ny >= 0 && nx < w && nx >= 0) {
            if (map[ny][nx] == '#' && !visited[ny][nx]) {
                //(d=1,< => d=0,v), L ,k = 0
                //(d=0,v => d=3,>), L , k = 3
                //(d=3,> => d=2,^), L , k = 2 
                if (d - k == 1 || d - k == -3) cout << "L";
                //(d=2,^ => d=3,>), R , k = 3
                //(d=3,> => d=0,v), R , k = 0
                //(d=0,v => d=1,<), R , k = 1
                else if (d - k == -1 || d - k == 3) cout << "R";
                //�ٲ� ������ k�� ����
                d = k;
                return command(ny, nx);
            }
        }
    }
}

int main() {
    cin >> h >> w;
    for (int i = 0; i < h; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < s.length(); j++) {
            map[i][j] = s[j];
        }
    }
    find();
    cout << a + 1 << " " << b + 1 << '\n';
    cout << dir[d] << '\n';
    //��� ���� �湮 üũ
    visited[a][b] = true;
    //��� ���� �湮 üũ �����Ƿ� ���� ���� ��ǥ���� ����
    command(a + dy[d], b + dx[d]);
    return 0;
}