#include <iostream>
#include <algorithm>
using namespace std;

string message, key;
int dat[26];
char password[26];
string res;
int main() {
    cin >> message >> key;
    //dat�� ������ �Ѿ�� ������ dat�� 1 ���ְ� password�� �߰�
    int cnt = 0;
    for (int i = 0; i < key.length(); i++) {
        if (dat[key[i] - 'A'] == 1) continue;
        dat[key[i] - 'A'] = 1;
        password[cnt] = key[i];
        cnt++;
    }
    //j�� �����Ƿ� �Ѱ��ְ� dat�� 1�� �ƴ϶��(���� ���ĺ��̸�) password�� �߰�
    for (int i = 0; i < 26; i++) {
        if (i == 9) continue;
        if (dat[i] == 1) continue;
        password[cnt] = i + 'A';
        cnt++;
    }

    for (int i = 0; i < message.length(); i += 2) {
        //Ȧ�� �� ���� �غôµ� X �߰��ǰ� i-=1�ϸ� ������ ���ڿ� �߰��ȵ�
        // ������ ���� �� ��
        if (i == message.length() - 1) {
            res += message[i];
            res += 'X';
        }
        //������ ���ڰ� �ƴ� ��
        else {
            //�α��ڰ� ���� ��
            if (message[i] == message[i + 1]) {
                //XX��� XQ��
                if (message[i] == 'X') {
                    res += 'X';
                    res += 'Q';
                }
                //�װ� �ƴ϶�� ���̿� X�־��ֱ�
                else {
                    res += message[i];
                    res += 'X';
                }
                //�ְ� i�� -1 ������� X�� ��ü�Ǵ°� �ƴ϶� �߰��� �ִ°Ŷ�
                i -= 1;
            }
            //�α��ڰ� �ٸ��� ���ϰ� res�� �߰�
            else {
                res += message[i];
                res += message[i + 1];
            }
        }
    }
    for (int i = 0; i < res.length(); i += 2) {
        int temp1 = 0, temp2 = 0;
        for (int j = 0; j < 25; j++) {
            if (password[j] == res[i]) temp1 = j;
            if (password[j] == res[i + 1]) temp2 = j;
        }
        //�� ������ ���� ��
        if ((temp1 / 5) == (temp2 / 5)) {
            if ((temp1 + 1) / 5 != (temp1 / 5)) { //temp1�� 1���� ���� ��� �޶����� ���� �� (9 -> 5)
                res[i] = password[temp1 - 4];
            }
            else {
                res[i] = password[temp1 + 1];
            }
            if ((temp2 + 1) / 5 != (temp2 / 5)) {
                res[i + 1] = password[temp2 - 4];
            }
            else {
                res[i + 1] = password[temp2 + 1];
            }
        }
        //������ ������ ���� ��
        else if ((temp1 % 5) == (temp2 % 5)) {
            if ((temp1 + 5) / 5 == 5) { // 25 �Ѿ ��(20->0)
                res[i] = password[temp1 - 20];
            }
            else {
                res[i] = password[temp1 + 5];
            }
            if ((temp2 + 5) / 5 == 5) {
                res[i + 1] = password[temp2 - 20];
            }
            else {
                res[i + 1] = password[temp2 + 5];
            }
        }
        //���� ��,���� ���� ���� ���
        else {
            res[i] = password[(temp1 / 5) * 5 + (temp2 % 5)]; //temp1�� �� �����ְ� temp2�� �� �� �����ֱ�
            res[i + 1] = password[(temp2 / 5) * 5 + (temp1 % 5)];
        }
    }
    cout << res;
    return 0;
}
