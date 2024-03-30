#include<iostream>
#include<deque>
#include<cmath>
#include<algorithm>
// Ʈ�� ���� h
// ���� ���� �� ��� ���� k
// ���� ���� �ð� r
// h�� �� ���� ���� ���� ? 2�� h����
// ���� ��ȣ 0, ���� ������ ���� ������ ������ �������� ��ȣ�� ? 2�� h���� -1 ~ 2�� (h+1)���� -2
// h=10�� ��, ��ü ������ ���� 1=3, 2=7, 3=15, -> 2^(h+1) - 1 = 2048-1, 2100���� ������ ����

using namespace std;
int h, k, r, ans, day;
int end_left, end_right;
struct Info {
    int num;
    bool odd;
};

deque<Info>workers[2100];

void input() {
    cin >> h >> k >> r;
    end_left = pow(2, h) - 1;
    end_right = pow(2, h + 1) - 2;
    for (int i = end_left; i <= end_right; i++) {
        int num;
        for (int j = 0; j < k; j++) {
            cin >> num;
            if (i % 2 == 0) {
                workers[i].push_back({ num,false });
            }
            else {
                workers[i].push_back({ num,true });
            }
        }
    }
}

// �� �� ��Ʈ���� ����, ������ ��ͷ� Ž��
// ���� ������ �ø� �� ���� �� ��簡 ó���ϴ� ����� �Ųٷ� ����
// ��簡 ó���ؾ��� ������ ������ ó�� �� �ؿ� �������� ���� �������� ������ �ø����� ����

void func(int root) {
    if (root > end_right)return;
    if (!workers[root].empty()) {
        // �μ���
        if (root == 0) {
            int start = 0;
            bool check = false;
            if (day % 2 == 0) {
                for (int i = 0; i < workers[0].size(); i++) {
                    if (!workers[0][i].odd) {
                        start = i;
                        check = true;
                        break;
                    }
                }
            }
            else {
                for (int i = 0; i < workers[0].size(); i++) {
                    if (workers[0][i].odd) {
                        start = i;
                        check = true;
                        break;
                    }
                }
            }
            // ó���� Ȧ��,¦���� ° ������ ���� ���� ó��
            if (check) {

                Info finish = workers[0][start];
                ans += finish.num;
                workers[0].erase(workers[0].begin() + start);
            }
        }
        // ���
        else if (root < end_left) {
            int start = 0;
            bool check = false;
            if (day % 2 == 0) {
                for (int i = 0; i < workers[root].size(); i++) {
                    if (!workers[root][i].odd) {
                        start = i;
                        check = true;
                        break;
                    }
                }
            }
            else {
                for (int i = 0; i < workers[root].size(); i++) {
                    if (workers[root][i].odd) {
                        start = i;
                        check = true;
                        break;
                    }
                }
            }
            if (check) {

                Info work = workers[root][start];
                // ��� ���� ������ ������ ���
                if (root % 2 == 0) {
                    work.odd = false;
                    workers[(root - 1) / 2].push_back(work);
                }
                else {
                    work.odd = true;
                    workers[(root) / 2].push_back(work);
                }
                workers[root].erase(workers[root].begin() + start);
            }
        }
        // ���� ����
        else {
            Info work = workers[root][0];
            if (root % 2 == 0) {
                workers[(root - 1) / 2].push_back(work);
            }
            else {
                workers[root / 2].push_back(work);
            }
            workers[root].pop_front();
        }
    }
    func(root + 1);
    return;
}

bool Isempty() {
    for (int i = 0; i <= end_right; i++) {
        if (!workers[i].empty())return false;
    }

    return true;
}

int main(int argc, char** argv)
{
    input();
    for (int i = 0; i < r; i++) {
        day++;
        func(0);
    }
    cout << ans;
    return 0;
}