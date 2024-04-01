#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

int h, k, r;
queue<int> all[2049];
queue<int> left_e[2049], right_e[2049];
int res = 0;

int main() {
    cin >> h >> k >> r;
    //��ü ���� �� 
    int person = pow(2, h + 1);
    //���� ���� ��
    int junior = pow(2, h);
    //���� �����鸸 k���� ������ ������ ������ ����
    for (int i = 0; i < junior; i++) {
        for (int j = 0; j < k; j++) {
            int a;
            cin >> a;
            //���� ���� index�� �°� push
            all[junior + i].push(a);
        }
    }
    //���� ����Ǵ� �� ��ŭ
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j < person; j++) {
            //���� �������� ������ ������
            if (j >= junior) {
                //�� ������ ������ continue
                if (!all[j].size()) continue;
                //���� ��尡 ������ ���� �����̸�
                if (j % 2 == 1)
                    //index / 2�� �θ����� index
                    right_e[j / 2].push(all[j].front());
                //���� ��尡 ���� ���� �����̸�
                else if (j % 2 == 0)
                    left_e[j / 2].push(all[j].front());
                //�ش� ���� ó�� �����Ƿ� pop
                all[j].pop();
            }
            //Ȧ�� �� �ϋ�
            else if (i % 2 == 1) {
                //���ʿ� ������ ������ ��
                if (left_e[j].size()) {
                    //���� ��尡 �μ��� �̶�� ������ �����ֱ�
                    if (j == 1) res += left_e[j].front();
                    //���� ��尡 ������ ���� �����̸�
                    else if (j % 2 == 1)
                        right_e[j / 2].push(left_e[j].front());
                    //���� ��尡 ���� ���� �����̸�
                    else if (j % 2 == 0)
                        left_e[j / 2].push(left_e[j].front());
                    //�ش� ���� ó�� �����Ƿ� pop
                    left_e[j].pop();
                }
            }
            //¦�� �� �϶�
            else if (i % 2 == 0) {
                //�����ʿ� ������ ������ ��
                if (right_e[j].size()) {
                    //�μ��� �̶�� ������ �����ֱ�
                    if (j == 1) res += right_e[j].front();
                    //���� ��尡 ������ ���� �����̸�
                    else if (j % 2 == 1)
                        right_e[j / 2].push(right_e[j].front());
                    //���� ��尡 ���� ���� �����̸�
                    else if (j % 2 == 0)
                        left_e[j / 2].push(right_e[j].front());
                    //�ش� ���� ó�� �����Ƿ� pop
                    right_e[j].pop();
                }
            }
        }
    }
    cout << res << '\n';
    return 0;
}