#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

int L, N, Q;
//����, �� ��
int map[42][42];
//��� ��ġ ��
int kmap[42][42];
//�������� ���� Ȯ���ϴ� �÷���
int flag;

//��� ����
struct Knight {
    int y, x;
    int h, w;
    int k;
};

//�������
struct Command {
    int num, dir;
};

vector<Knight> k;
vector<Command> c;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };

//�׾����� ��Ҵ��� Ȯ��
bool isdie[31];
// ���� �޾Ҵ��� Ȯ��
bool isattacked[31];
int damage[31];

void input() {

    cin >> L >> N >> Q;

    for (int i = 0; i <= L + 1; i++) {
        for (int j = 0; j <= L + 1; j++) {

            if (i == 0 || j == 0 || i == L + 1 || j == L + 1) {
                map[i][j] = 2;
            }
            else {
                cin >> map[i][j];
            }
        }
    }

    k.push_back({});
    for (int i = 1; i <= N; i++) {
        int t1, t2, t3, t4, t5;
        cin >> t1 >> t2 >> t3 >> t4 >> t5;
        k.push_back({ t1,t2,t3,t4,t5 });

        for (int r = t1; r < t1 + t3; r++) {
            for (int c = t2; c < t2 + t4; c++) {
                kmap[r][c] = i;
            }
        }
    }

    c.push_back({});
    for (int i = 1; i <= Q; i++) {
        int t1, t2;
        cin >> t1 >> t2;
        c.push_back({ t1,t2 });
    }
}

void movek(int sy, int sx, int dir) {

    //�̵��� ��ǥ
    int ny = sy + dy[dir];
    int nx = sx + dx[dir];

    //��ɹ��� ��� ����
    int height = k[kmap[sy][sx]].h;
    int width = k[kmap[sy][sx]].w;
    int num = kmap[sy][sx];

    //��� ������ŭ �̵�
    for (int i = ny; i < ny + k[kmap[sy][sx]].h; i++) {
        for (int j = nx; j < nx + k[kmap[sy][sx]].w; j++) {
            if (kmap[i][j] != 0 && kmap[i][j] != kmap[sy][sx]) {
                //�����̵�
                movek(k[kmap[i][j]].y, k[kmap[i][j]].x, dir);
            }
        }
    }

    //���� �ڸ��� 0����
    for (int r = sy; r < sy + height; r++) {
        for (int c = sx; c < sx + width; c++) {
            kmap[r][c] = 0;
        }
    }

    //���� �̵��� �ڸ��� ���� �ֱ�
    for (int r = ny; r < ny + height; r++) {
        for (int c = nx; c < nx + width; c++) {
            kmap[r][c] = num;
        }
    }

    //��ǥ ����
    k[num].y = ny;
    k[num].x = nx;
}

void movepos(int sy, int sx, int dir) {

    //�̵��� ��ǥ
    int ny = sy + dy[dir];
    int nx = sx + dx[dir];

    //������ŭ Ȯ��
    for (int i = ny; i < ny + k[kmap[sy][sx]].h; i++) {
        for (int j = nx; j < nx + k[kmap[sy][sx]].w; j++) {
            //���̸� �÷��� 1
            if (map[i][j] == 2) {
                flag = 1;
                return;
            }

            //�ٸ� ��簡 �ִٸ� �����̵� ���� Ȯ��
            if (kmap[i][j] != 0 && kmap[i][j] != kmap[sy][sx]) {
                movepos(k[kmap[i][j]].y, k[kmap[i][j]].x, dir);
                //���� ���� ��� ǥ��
                isattacked[kmap[i][j]] = true;
            }
        }
    }

    if (flag == 1) return;
}

void checktrap() {

    for (int i = 1; i <= N; i++) {
        int trap = 0;

        //���� ���� ����鸸 ���� üũ
        if (isattacked[i] == true) {
            for (int r = k[i].y; r < k[i].y + k[i].h; r++) {
                for (int c = k[i].x; c < k[i].x + k[i].w; c++) {
                    if (map[r][c] == 1) {
                        trap++;
                    }
                }
            }

            //ü�� - ���� ��
            k[i].k -= trap;

            // �������� ü�º��� ũ�� ����
            if (k[i].k <= 0) {
                isdie[i] = true;
                //�� ��� ��ġ �����
                for (int r = k[i].y; r < k[i].y + k[i].h; r++) {
                    for (int c = k[i].x; c < k[i].x + k[i].w; c++) {
                        kmap[r][c] = 0;
                    }
                }

            }
            else {
                damage[i] += trap;
            }
        }
    }
}

void solve() {

    for (int i = 1; i <= Q; i++) {

        //�ʱ�ȭ
        flag = 0;
        for (int i = 0; i <= N; i++) {
            isattacked[i] = false;
        }

        //������� ����� ����
        if (isdie[c[i].num] == true) continue;

        //���������ϴ� ��� ��ȣ
        int k_ind = c[i].num;

        //��ɴ�� �� �� �ִ��� üũ
        movepos(k[k_ind].y, k[k_ind].x, c[i].dir);
        isattacked[k_ind] = false;

        if (flag == 1)continue;

        //��ɴ�� �� �� ������ �����̱�
        movek(k[k_ind].y, k[k_ind].x, c[i].dir);

        //������ �ڿ� ü���� ���� ���� üũ
        checktrap();

    }
}

int main() {

    //freopen("sample.txt", "r", stdin);

    input();
    solve();

    int result = 0;
    for (int i = 1; i <= N; i++) {
        if (isdie[i] == false) {
            result += damage[i];
        }
    }
    cout << result;

    return 0;
}