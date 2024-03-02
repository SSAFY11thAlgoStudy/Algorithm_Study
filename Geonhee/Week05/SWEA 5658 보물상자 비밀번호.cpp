#include <iostream>
#include <algorithm>
#include <set>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

int t;
int main() {
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        set<string, greater<string>> number; //�������� ����
        vector<int> res;
        for (int j = 0; j < n / 4; j++) {
            for (int k = 0; k < 4; k++) {
                //���� s������ ���� �־��ֱ�
                number.insert(s.substr(k * (n / 4), n / 4));
            }
            // ��ĭ �� �о��ֱ� 
            string temp = s.substr(1, s.length() - 1) + s[0];
            s = temp; //�о��� �� s�� �ְ� �ݺ�
        }
        for (auto i : number) { //16������ �ٲ㼭 res�� �־��ֱ�
            res.push_back(stoi(i, nullptr, 16));
        }
        cout << "#" << i + 1 << " " << res[k - 1] << '\n';
    }
    return 0;
}