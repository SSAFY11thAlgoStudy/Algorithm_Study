#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int n;
string s;
vector<int> num;
vector<char> oper_str;
int res = -987654321;
// ������ ó���ϱ� ���� �Լ�
int oper(char a, int b, int c) {
    if (a == '+') return b + c;
    if (a == '-') return b - c;
    if (a == '*') return b * c;
}

void go(int cnt, int x) {
    //��� ���ڸ� �� ��� ������
    if (cnt == num.size() - 1) {
        // �ִ� �� ��
        res = max(res, x);
        return;
    }
    // �ε��� +1 ���ְ� ���� ���� ���� �� ���
    go(cnt + 1, oper(oper_str[cnt], x, num[cnt + 1]));
    // 3�� ���� �� �ڿ� �ΰ��� ���� �����ϴ� ��츦 ó�� �ϴ� ���
    // +2���� �� ��ü ���� ���� �������� �۰ų� ���ƾ���
    if (cnt + 2 <= num.size() - 1) {
        // 3���� �ڿ� 2�� ���ڸ� ���� ��� �ϰ�
        int temp = oper(oper_str[cnt + 1], num[cnt + 1], num[cnt + 2]);
        // �ε��� +2 ���ְ� ���� �̾��
        go(cnt + 2, oper(oper_str[cnt], x, temp));
    }
    return;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> s;
    // ���ڿ� �����ȣ ���� ������ �޾��ֱ�
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) num.push_back(s[i] - '0');
        else oper_str.push_back(s[i]);
    }
    //�ʱ� �� ���ʷ� Ž��
    go(0, num[0]);
    cout << res << '\n';
    return 0;
}