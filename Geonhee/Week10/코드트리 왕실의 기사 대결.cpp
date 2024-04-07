#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct fight {
    int r, c, h, w, k, health;
    bool live;
};

int l, n, q;
int map[41][41]; //��ֹ� �� ��
int knight[41][41]; //���� ��ġ ��
int dy[4] = { -1,0,1,0 }; //�������
int dx[4] = { 0,1,0,-1 };
vector<fight> v;
vector<int> crash;

void command(int idx, int d) {
    if (!v[idx].live) return; //��������� �ٷ� return
    bool visited[41][41] = { false }; //�湮 �迭 �̹� üũ�� �Ŵ� �� ���ʿ� ������
    queue<pair<int, int>> q;
    //���� idx�� �ش��ϴ� ����� ��ǥ ���� q�� �־��ֱ�
    for (int i = v[idx].r; i < v[idx].r + v[idx].h; i++) {
        for (int j = v[idx].c; j < v[idx].c + v[idx].w; j++) {
            q.push({ i,j });
            visited[i][j] = true;
        }
    }
    //�� �ִ��� �Ǵ�
    int flag = 1;
    while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        int ny = y + dy[d];
        int nx = x + dx[d];
        //���� �ȿ� �ְ� d�������� �̵��Ѱ� ���� �ƴϰ�
        if (ny <= l && ny >= 1 && nx <= l && nx >= 1 && map[ny][nx] != 2) {
            //�湮���� �ʾҴµ�
            if (!visited[ny][nx]) {
                //�ٸ� ��� ���
                if (knight[ny][nx] > 0) {
                    int nidx = knight[ny][nx];
                    crash.push_back(nidx);
                    //�ٸ� ��翡 ���ؼ��� ���� �ִ��� �����ؾ��ϹǷ� q�� �־��ְ� �湮üũ
                    for (int i = v[nidx].r; i < v[nidx].r + v[nidx].h; i++) {
                        for (int j = v[nidx].c; j < v[nidx].c + v[nidx].w; j++) {
                            q.push({ i,j });
                            visited[i][j] = true;
                        }
                    }
                }
            }
        }
        //���̶��
        else {
            flag = 0;
            crash.clear(); //�� �Ǵ��ϱ����� ���� �ִ°� ���������
            break;
        }
    }
    //���̶�� �ٷ� �̵��� �� ������ ������ ��
    if (!flag) return;
    //��� �̵��Ѱ� �־��ְ� ���� �ʿ� �Ű��ֱ� ����
    int knight_save[41][41] = { 0 };
    //��ɹ��� ��� �̵���Ű��
    for (int i = v[idx].r; i < v[idx].r + v[idx].h; i++) {
        for (int j = v[idx].c; j < v[idx].c + v[idx].w; j++) {
            knight[i][j] = 0; //�̵������Ƿ� 0���� �ʱ�ȭ ���ֱ�
            //knight[i + dy[d]][j + dx[d]] = idx + 1; //��� �ش�������� �̵������ֱ�
            knight_save[i + dy[d]][j + dx[d]] = idx;
        }
    }
    //idx�� �ش��ϴ� ��� ��ǥ ������Ʈ
    v[idx].r += dy[d];
    v[idx].c += dx[d];


    //�и� ��� ���� �°� �̵���Ű��
    for (int i = 0; i < crash.size(); i++) {
        int nidx = crash[i];
        for (int j = v[nidx].r; j < v[nidx].r + v[nidx].h; j++) {
            for (int t = v[nidx].c; t < v[nidx].c + v[nidx].w; t++) {
                //knight[i + dy[d]][j + dx[d]] = nidx+1;
                knight[j][t] = 0; //��� �̵������Ƿ� 0���� �ʱ�ȭ ���ֱ�
                knight_save[j + dy[d]][t + dx[d]] = nidx;
            }
        }
        //nidx�� �ش��ϴ� ��� ��ǥ ������Ʈ
        v[nidx].r += dy[d];
        v[nidx].c += dx[d];
    }
    for (int i = 1; i <= l; i++) {
        for (int j = 1; j <= l; j++) {
            //��� �̵��Ѱ� �ִ� �Ÿ� ���� ��� �ʿ� �־������
            if (knight_save[i][j]) knight[i][j] = knight_save[i][j];
        }
    }
}

void damage() {
    //�и� ��� ���� �°� ������ �����
    for (int i = 0; i < crash.size(); i++) {
        int idx = crash[i];
        for (int j = v[idx].r; j < v[idx].r + v[idx].h; j++) {
            for (int t = v[idx].c; t < v[idx].c + v[idx].w; t++) {
                //��ֹ��� ��������
                if (map[j][t] == 1) {
                    //�Ǵ� -1����ϰ� ������ ������ +1 ���ֱ�
                    v[idx].k -= 1;
                    v[idx].health += 1;
                    //ü�� �������� �ٷ� ��� ������� �ϱ�
                    if (v[idx].k <= 0) {
                        v[idx].live = false;
                        for (int a = v[idx].r; a < v[idx].r + v[idx].h; a++) {
                            for (int b = v[idx].c; b < v[idx].c + v[idx].w; b++) {
                                knight[a][b] = 0;
                            }
                        }
                    }
                }
            }
        }

    }
}

int main() {
    cin >> l >> n >> q;
    for (int i = 1; i <= l; i++) {
        for (int j = 1; j <= l; j++) {
            cin >> map[i][j];
        }
    }
    //-1����µ� �����Ƽ� v[0]�� ä���ִ� �ɷ� �ٲ�
    v.push_back({ 0,0,0,0,0,0,true });
    for (int i = 1; i <= n; i++) {
        int r, c, h, w, k;
        cin >> r >> c >> h >> w >> k;
        v.push_back({ r,c,h,w,k,0,true });
        for (int y = r; y < r + h; y++) {
            for (int x = c; x < c + w; x++) {
                knight[y][x] = i;
            }
        }
    }
    for (int i = 1; i <= q; i++) {
        int x, d;
        cin >> x >> d;
        command(x, d);
        damage(); //�� �а� ���� ������ �ֱ�
        crash.clear();//���� ���� ���� clear���ֱ�
    }
    int res = 0;
    //������ ������ �������� �ջ�
    for (int i = 1; i <= n; i++) {
        if (v[i].live) res += v[i].health;
    }
    cout << res;
    return 0;
}