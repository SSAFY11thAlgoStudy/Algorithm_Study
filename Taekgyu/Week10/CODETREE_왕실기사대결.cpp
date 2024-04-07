#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

struct Knight
{
    int y;
    int x;
};

// ��纤�� ( ����� ������ ���� )
vector<Knight>kv[30];
// �и��� �ʴ� �����Ͻ� �� ���� ����� cv
vector<Knight>cv[30];
// ü�� ���� ����
vector<int>life[30];
// �ʱ� ü�� ����
vector<int>total_life[30];


int L;
int N;
int Q;
int MAP[40][40];

// ��͸� ���Ҵ� ��� �ľ�
int DAT[30];
// �׾����� üũ
int die[30];
// �зȴ��� üũ
int isPush[30];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

// ������ ������ �� �ִ��� ������?
int noWay = 0;

// ��ͷ� ����
void Push(int push, int dir) {

    for (int i = 0; i < kv[push].size(); i++)
    {
        // ������ ��ĭ �о��
        kv[push][i].y += dy[dir];
        kv[push][i].x += dx[dir];
        // ���̶�� ������
        if (kv[push][i].y >= L || kv[push][i].x >= L || kv[push][i].y < 0 || kv[push][i].x < 0) {
            noWay = 1;
            break;
        }
        // ��ֹ��̸� ������
        if (MAP[kv[push][i].y][kv[push][i].x] == 2) {
            noWay = 1;
            break;
        }
    }

    // ��������
    if (noWay == 1) {
        return;
    }

    // �о��~~!!!
    for (int k = 0; k < kv[push].size(); k++)
    {
        for (int i = 0; i < N; i++)
        {
            // ������ ���� ���� �������� �ʴ´�.
            if (push == i)continue;
            // ��������� �������� �ʴ´�.
            if (die[i] == 1)continue;
            // �̹� �������� ���� �������� �ʴ´�.
            if (DAT[i] == 1)continue;
            for (int j = 0; j < kv[i].size(); j++)
            {
                // �и���簡 �ִٸ�
                if (kv[push][k].y == kv[i][j].y && kv[push][k].x == kv[i][j].x) {
                    DAT[i] = 1;
                    isPush[i] = 1;
                    // �и����� �� ����~
                    Push(i, dir);
                    DAT[i] = 0;
                }
            }
        }
    }
}

void input() {

    cin >> L >> N >> Q;
    // �� �Է�
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < L; j++)
        {
            cin >> MAP[i][j];
        }
    }

    // �� ����� ������ �ް� ü���� �޴´�
    for (int i = 0; i < N; i++)
    {
        int r, c, h, w, k = 0;
        cin >> r >> c >> h >> w >> k;
        for (int u = 0; u < h; u++)
        {
            // �� ����� ���� ����
            for (int j = 0; j < w; j++)
            {
                kv[i].push_back({ r + u - 1,c + j - 1 });
            }
        }
        life[i].push_back(k);
        total_life[i].push_back(k);
    }

    // ��ɸ�ŭ ���ƶ�
    for (int i = 0; i < Q; i++)
    {
        int toOrd, order = 0;
        cin >> toOrd >> order;
        // ����Լ� ���� ����
        // ������� ����

        // ������ �޴� ��簡 �̹� �׾��ٸ� ����
        if (die[toOrd - 1] == 1)continue;

        // ��� ���� �� ���� ���� ��ġ ����
        for (int c = 0; c < N; c++)
        {
            cv[c].clear();
        }
        for (int k = 0; k < N; k++)
        {
            for (int j = 0; j < kv[k].size(); j++)
            {
                cv[k].push_back({ kv[k][j].y, kv[k][j].x });
            }
        }
        noWay = 0;
        Push(toOrd - 1, order);
        memset(DAT, 0, sizeof(DAT));
        // �ᱹ �и��� ������ ���󺹱�
        if (noWay == 1) {

            memset(isPush, 0, sizeof(isPush));
            for (int c = 0; c < N; c++)
            {
                kv[c].clear();
            }

            for (int k = 0; k < N; k++)
            {
                for (int j = 0; j < cv[k].size(); j++)
                {
                    kv[k].push_back({ cv[k][j].y, cv[k][j].x });
                }
            }
        }
        // �зȴٸ� ������ �ְ� ���󺹱� X
        else {

            for (int k = 0; k < N; k++)
            {
                // �ȹи� ����� ���� X
                if (isPush[k] != 1)continue;
                // ���� ���� �������� X
                if (die[k] == 1)continue;
                int dangerCnt = 0;
                for (int j = 0; j < kv[k].size(); j++)
                {
                    if (MAP[kv[k][j].y][kv[k][j].x] == 1) {
                        dangerCnt++;
                    }
                }
                life[k][0] -= dangerCnt;
                if (life[k][0] <= 0)die[k] = 1;
            }
            memset(isPush, 0, sizeof(isPush));
        }
    }
}

int main() {

    input();
    int ans = 0;
    //cout << endl;
    for (int i = 0; i < N; i++)
    {
        // ������ ������ ����� �ʿ䰡 ����
        if (die[i] == 1)continue;
        //cout <<i<<" " << total_life[i][0] - life[i][0] << endl;
        ans += total_life[i][0] - life[i][0];
    }

    cout << ans;
    return 0;
}