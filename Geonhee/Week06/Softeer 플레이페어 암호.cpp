#include <iostream>
#include <algorithm>
using namespace std;

string message, key;
int dat[26];
char password[26];
string res;
int main() {
    cin >> message >> key;
    //dat에 있으면 넘어가고 없으면 dat에 1 해주고 password에 추가
    int cnt = 0;
    for (int i = 0; i < key.length(); i++) {
        if (dat[key[i] - 'A'] == 1) continue;
        dat[key[i] - 'A'] = 1;
        password[cnt] = key[i];
        cnt++;
    }
    //j는 없으므로 넘겨주고 dat가 1이 아니라면(없는 알파벳이면) password에 추가
    for (int i = 0; i < 26; i++) {
        if (i == 9) continue;
        if (dat[i] == 1) continue;
        password[cnt] = i + 'A';
        cnt++;
    }

    for (int i = 0; i < message.length(); i += 2) {
        //홀수 일 때로 해봤는데 X 추가되고 i-=1하면 마지막 글자에 추가안됨
        // 마지막 글자 일 때
        if (i == message.length() - 1) {
            res += message[i];
            res += 'X';
        }
        //마지막 글자가 아닐 때
        else {
            //두글자가 같을 때
            if (message[i] == message[i + 1]) {
                //XX라면 XQ로
                if (message[i] == 'X') {
                    res += 'X';
                    res += 'Q';
                }
                //그게 아니라면 사이에 X넣어주기
                else {
                    res += message[i];
                    res += 'X';
                }
                //넣고 i값 -1 해줘야함 X로 대체되는게 아니라 중간에 넣는거라
                i -= 1;
            }
            //두글자가 다르면 편하게 res에 추가
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
        //몫 같으면 같은 행
        if ((temp1 / 5) == (temp2 / 5)) {
            if ((temp1 + 1) / 5 != (temp1 / 5)) { //temp1에 1더한 값이 몫과 달라지면 다음 행 (9 -> 5)
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
        //나머지 같으면 같은 열
        else if ((temp1 % 5) == (temp2 % 5)) {
            if ((temp1 + 5) / 5 == 5) { // 25 넘어갈 때(20->0)
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
        //같은 행,같은 열에 없는 경우
        else {
            res[i] = password[(temp1 / 5) * 5 + (temp2 % 5)]; //temp1의 행 맞춰주고 temp2의 열 값 더해주기
            res[i + 1] = password[(temp2 / 5) * 5 + (temp1 % 5)];
        }
    }
    cout << res;
    return 0;
}
