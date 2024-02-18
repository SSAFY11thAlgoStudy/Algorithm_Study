#include<iostream>
#include<cstring>
using namespace std;

int N, L;
int map[100][100] = { 0 };



int solve() {
    int cnt = 0;

    // ���� ����
    for (int x = 0; x < N; x++) {
        int flag = 1;

        //�ɼ��� ���ؿ��� ��Ÿ�� ������ ���� �����ʱ�ȭ�� ��ȯ
        int stairs[100] = { 0 };
        for (int y = 0; y < N - 1; y++) {
            //�̹� �۸��� ������ ��ŵ
            if (flag == 0) break;

            // �� ��ġ�� ������ ������ �н�
            if (map[y][x] == map[y + 1][x]) continue;

            // ������ �� ��ġ���� ���� ���
            else if (map[y][x] > map[y + 1][x]) {
                for (int l = 1; l <= L; l++) {
                    //�ʹ��� ����� Ȯ���ϴ� ���
                    //���� ��ġ��(L��)�� ����ġ���� +1 ũ�Ⱑ �ƴ� ���
                    //����� ��ġ���� �� ���
                    if (y + l >= N || !(map[y][x] - 1 == map[y + l][x]) || stairs[y + l] == 1) {
                        flag = 0;
                        break;
                    }
                    stairs[y + l] = 1;
                }
            }

            // ������ �� ��ġ���� Ŭ ���
            else if (map[y][x] < map[y + 1][x]) {
                for (int l = 0; l < L; l++) {
                    //�ʹ��� ����� Ȯ���ϴ� ���
                    //���� ��ġ��(L��)�� ����ġ���� -1 ũ�Ⱑ �ƴ� ���
                    //����� ��ġ���� �� ���
                    if (y - l < 0 || !(map[y + 1][x] - 1 == map[y - l][x]) || stairs[y - l] == 1) {
                        flag = 0;
                        break;
                    }
                    stairs[y - l] = 1;
                }
            }
        }
        if (flag == 1) cnt++;
    }

    // ���� ����
    for (int y = 0; y < N; y++) {
        int flag = 1;
        int stairs[100] = { 0 };
        for (int x = 0; x < N - 1; x++) {

            //�̹� �۸��� ������ ��ŵ
            if (flag == 0) break;

            // �� ��ġ�� ������ ������ �н�
            if (map[y][x] == map[y][x + 1]) continue;

            // ������ �� ��ġ���� ���� ���
            else if (map[y][x] > map[y][x + 1]) {
                for (int l = 1; l <= L; l++) {
                    //�ʹ��� ����� Ȯ���ϴ� ���
                    //���� ��ġ��(L��)�� ����ġ���� +1 ũ�Ⱑ �ƴ� ���
                    //����� ��ġ���� �� ���
                    if (x + l >= N || !(map[y][x] - 1 == map[y][x + l]) || stairs[x + l] == 1) {
                        flag = 0;
                        break;
                    }
                    stairs[x + l] = 1;
                }
            }

            // ������ �� ��ġ���� Ŭ ���
            else if (map[y][x] < map[y][x + 1]) {
                for (int l = 0; l < L; l++) {
                    //�ʹ��� ����� Ȯ���ϴ� ���
                    //���� ��ġ��(L��)�� ����ġ���� -1 ũ�Ⱑ �ƴ� ���
                    //����� ��ġ���� �� ���
                    if (x - l < 0 || !(map[y][x + 1] - 1 == map[y][x - l]) || stairs[x - l] == 1) {
                        flag = 0;
                        break;
                    }
                    stairs[x - l] = 1;
                }
            }
        }
        if (flag == 1) cnt++;
    }

    return cnt;
}

void input() {
    cin >> N >> L;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> map[i][j];
        }
    }
}

int main() {
    input();
    cout << solve();
    return 0;
}