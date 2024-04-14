#include<iostream>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
//2^H�� ��� ��,
//K�� ��庰�� ������ ���� ����, 
//R������ ����Ǵ� ����
//���������� �Ⱓ���� �Ϸ�� ������ȣ�� ���� ���
int result = 0;
int H, K, R;
queue<int>v[2049];

void input() {
    int num;
    cin >> H >> K >> R;
    for (int i = pow(2, H); i < pow(2, H + 1); i++) {
        for (int j = 0; j < K; j++)
        {
            cin >> num;
            v[i].push(num);
        }
    }
}

void solve() {
    int today = 1;//���� ��¥


    while (today <= R) {
        if (!v[1].empty()) {
            result += v[1].front();
            v[1].pop();
        }
        if (today % 2 != 1) { //¦����
            for (int i = 2; i < pow(2, H + 1); i++) {
                if (i % 2 != 0 || v[i].empty())continue;//���� ���
                v[i / 2].push(v[i].front());
                v[i].pop();
            }
        }
        else { //Ȧ����
            for (int i = 2; i < pow(2, H + 1); i++) {
                if (i % 2 == 0 || v[i].empty())continue;//������ ���
                v[(i - 1) / 2].push(v[i].front());
                v[i].pop();
            }
        }

        today++;
    }


}

int main(int argc, char** argv)
{
    input();
    solve();


    cout << result;
    return 0;
}