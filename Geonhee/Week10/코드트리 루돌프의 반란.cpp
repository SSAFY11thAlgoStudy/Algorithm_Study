#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

int n, m, p, c, d;
int ry, rx;
int map[52][52] = { 0 };
int dy[4] = { -1,0,1,0 }; //0123 �������
int dx[4] = { 0,1,0,-1 };
bool santa_live[32] = { false }; //��Ÿ�� ��� �ִ���
pair<int, int> santa_location[32]; //��ȣ�� ���� ��Ÿ ��ǥ 
int final_score[32];
int stun_santa[1004];

//�����浹 Ȯ�� �� �Ϲ��浹 ó�� 
//c��ŭ �и� y,x��ǥ, �ش� �������� 1�и��� ���� y,x ���� ��Ÿ ��ȣ
void crash(int cy, int cx, int my, int mx, int s_num) {
    //ù��° �浹�� ��Ÿó��
    int idx = map[cy][cx];
    map[cy][cx] = s_num;
    santa_location[s_num] = { cy,cx };

    //�� ���� ����� �浹�� ��Ÿ ó��
    int newy = cy + my;
    int newx = cx + mx;
    //���� �Ѿ�� �ٷ� out
    if (newy > n || newy < 1 || newx > n || newx < 1) {
        santa_live[idx] = false;
        santa_location[idx] = { 0,0 };
        return;
    }
    else {
        //�зȴµ� �� ������ �ٽ� ���
        if (map[newy][newx] > 0) crash(newy, newx, my, mx, idx);
        //�зȴµ� ������� �ְ� ��
        else {
            map[newy][newx] = idx;
            santa_location[idx] = { newy,newx };
            return;
        }
    }
}


//�絹���� ������
//�絹�� �̵�, ��Ÿ�� �浹�ϸ� ��Ÿ �о��ְ� �絹���� ���� �ش��ϴ� ���� �ش� ��Ÿ�� �����ֱ�
//���������� �浹�ϴ� ��쵵 ����
void move_dear(int y, int x, int turn) {
    int santa_num = 0; //����� ��Ÿ ��ȣ
    int mind = 1e9; //����� �Ÿ�
    pair<int, int> same_distance; //����� ��Ÿ ��ǥ 

    //����� �Ÿ� ã��(��Ÿ�� �� ��ŭ)
    for (int i = 1; i <= p; i++) {
        //��Ÿ �׾����� continue
        if (!santa_live[i]) continue;
        //���� �絹���� ��Ÿ[i]�� �Ÿ�
        int nowd = pow((ry - santa_location[i].first), 2) + pow((rx - santa_location[i].second), 2);
        //���ؼ� ����� ��Ÿ ã���ֱ�
        if (mind > nowd) {
            mind = nowd;
            same_distance = { santa_location[i].first,santa_location[i].second };
            santa_num = i;
        }
        //������ y��ǥ,x��ǥ ������ ���ؼ� ��Ÿ ã���ֱ� 
        else if (mind == nowd) {
            if (same_distance.first == santa_location[i].first) {
                if (same_distance.second > santa_location[i].second) continue;
                else {
                    same_distance = { santa_location[i].first,santa_location[i].second };
                    santa_num = i;
                }
            }
            else if (same_distance.first > santa_location[i].first) continue;
            else {
                same_distance = { santa_location[i].first,santa_location[i].second };
                santa_num = i;
            }
        }
    }

    //����� ��Ÿ ã�����Ƿ� �絹�� �̵� ��Ű��

    //����� ��Ÿ�� �����ϸ� ������ ���� ������ ����ִ� ��Ÿ X�̹Ƿ� ��������
    if (santa_num) {
        int tempry = ry, temprx = rx;
        int movey, movex;
        if (ry - same_distance.first < 0) movey = 1;
        else if (ry - same_distance.first > 0)movey = -1;
        else movey = 0;
        if (rx - same_distance.second < 0) movex = 1;
        else if (rx - same_distance.second > 0) movex = -1;
        else movex = 0;
        //�絹�� �̵� �� ���� �絹�� ��ġ 0
        ry += movey;
        rx += movex;
        //map[ry][rx] = -1;
        map[tempry][temprx] = 0;
        //�絹�� �̵� �ߴµ� ��Ÿ�� ���� ���
        if (same_distance.first == ry && same_distance.second == rx) {
            //����
            //��Ÿ �����϶� turn+1���� ũ�� �ٽ� ������ �� ����
            stun_santa[santa_num] = turn + 1;
            int tempy = same_distance.first + movey * c;
            int tempx = same_distance.second + movex * c;
            //���� �Ѿ��
            if (tempy > n || tempy < 1 || tempx > n || tempx < 1) {
                final_score[santa_num] += c;
                santa_live[santa_num] = false; //��Ÿ Ż��
                map[same_distance.first][same_distance.second] = 0; //Ż���� ��Ÿ ��ġ �ʱ�ȭ
                santa_location[santa_num] = { 0,0 }; //Ż���� ��Ÿ ��ġ �ʱ�ȭ
                map[ry][rx] = -1;
                return;
            }
            //���� �°� 0���� ũ�� �����浹 ó��
            if (map[tempy][tempx] > 0) {
                //�����浹 ó��
                //c��ŭ �и� y,x��ǥ, �ش� �������� 1�и��� ���� y,x ���� ��Ÿ ��ȣ
                crash(tempy, tempx, movey, movex, santa_num);

            }
            //�Ϲ��浹
            else {
                map[same_distance.first][same_distance.second] = 0;
                map[tempy][tempx] = santa_num;
                santa_location[santa_num] = { tempy,tempx };
            }
            final_score[santa_num] += c; //�ش��ϴ� ��Ÿ ��ȣ�� c��ŭ ���� �����ֱ�
        }
    }
    //�絹�� ��ǥ �� �־��ֱ�
    map[ry][rx] = -1;
}

//��Ÿ�� ������
void move_santa(int turn) {
    for (int i = 1; i <= p; i++) {
        //��Ÿ �׾��ų� ���� �����̸� continue
        if (!santa_live[i]) continue;
        if (stun_santa[i] >= turn) continue;
        //i��° ��Ÿ ��ġ
        int tempsy = santa_location[i].first;
        int tempsx = santa_location[i].second;

        //��Ÿ ������ �� �ִ����� 4���⿡ ���� �ּ� �� ���ϱ�
        int mindis = pow((tempsy - ry), 2) + pow((tempsx - rx), 2);
        int flag = -1;

        for (int k = 0; k < 4; k++) {
            int ny = tempsy + dy[k];
            int nx = tempsx + dx[k];
            //���� �Ѿ�ų� �ٸ� ��Ÿ�� ������ continue
            if (ny > n || ny < 1 || nx > n || nx < 1 || map[ny][nx] > 0) continue;
            int dis = pow((ny - ry), 2) + pow((nx - rx), 2);
            //�Ÿ� �ּ� �� �� 
            if (mindis > dis) { //�켱������ ���� ��ȣ�� ���ֱ�
                mindis = dis;
                flag = k; //���� �־��ֱ�
            }
        }
        //������ �� ������
        if (flag != -1) {
            //�����̱�
            tempsy += dy[flag];
            tempsx += dx[flag];

            //�������µ� �絹���� �浹�� ���
            if (tempsy == ry && tempsx == rx) {

                stun_santa[i] = turn + 1;
                //�ݴ�������� d��ŭ �з�����
                int tempcy = tempsy + (-dy[flag] * d);
                int tempcx = tempsx + (-dx[flag] * d);

                //d��1�̸� ������ ���ڸ� �״�� �̹Ƿ� ������ �����ش�.
                if (d == 1) {
                    final_score[i] += d;
                }

                else {
                    //�浹�ؼ� �зȴµ� ������ �Ѿ ���
                    if (tempcy > n || tempcy < 1 || tempcx > n || tempcx < 1) {
                        final_score[i] += d;
                        santa_live[i] = false;
                        map[santa_location[i].first][santa_location[i].second] = 0;
                        santa_location[i] = { 0,0 };
                        continue;
                    }
                    else {
                        //���� �浹
                        if (map[tempcy][tempcx] > 0) {
                            map[santa_location[i].first][santa_location[i].second] = 0;
                            crash(tempcy, tempcx, -dy[flag], -dx[flag], i);

                        }
                        //�Ϲ� �浹
                        else {
                            map[tempcy][tempcx] = i; //���ο� ��ǥ�� ��Ÿ ��ȣ �ֱ�
                            map[santa_location[i].first][santa_location[i].second] = 0; //�� ����ǥ 0
                            santa_location[i] = { tempcy,tempcx }; //��Ÿ ��ġ ������Ʈ
                        }
                    }
                    //�浹�� ��Ÿi������ d��ŭ ���� �����ֱ�
                    final_score[i] += d;
                }
            }
            //�浹 X
            else {
                map[santa_location[i].first][santa_location[i].second] = 0;
                map[tempsy][tempsx] = i;
                santa_location[i] = { tempsy,tempsx };
            }
        }
    }
}

int main() {
    cin >> n >> m >> p >> c >> d;
    cin >> ry >> rx;
    map[ry][rx] = -1;
    for (int i = 1; i <= p; i++) {
        int num, y, x;
        cin >> num >> y >> x;
        map[y][x] = num;
        santa_location[num] = { y,x };
        santa_live[num] = true;
    }
    for (int i = 1; i <= m; i++) {
        move_dear(ry, rx, i);

        move_santa(i);

        bool flag = false;
        //��� ���� ��Ÿ�� 1���� �߰�
        //��� ���� ��Ÿ�� �ִ��� Ȯ��
        for (int i = 1; i <= p; i++) {
            if (santa_live[i]) {
                flag = true;
                final_score[i] += 1;
            }
        }
        //�Ѹ� �Ȼ���ִٸ� ���� ���� 
        if (!flag) break;
    }
    for (int i = 1; i <= p; i++) {
        cout << final_score[i] << " ";
    }
}