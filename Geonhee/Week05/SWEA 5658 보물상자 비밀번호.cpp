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
        set<string, greater<string>> number; //내림차순 정렬
        vector<int> res;
        for (int j = 0; j < n / 4; j++) {
            for (int k = 0; k < 4; k++) {
                //현재 s변마다 숫자 넣어주기
                number.insert(s.substr(k * (n / 4), n / 4));
            }
            // 한칸 씩 밀어주기 
            string temp = s.substr(1, s.length() - 1) + s[0];
            s = temp; //밀어준 거 s에 넣고 반복
        }
        for (auto i : number) { //16진수로 바꿔서 res에 넣어주기
            res.push_back(stoi(i, nullptr, 16));
        }
        cout << "#" << i + 1 << " " << res[k - 1] << '\n';
    }
    return 0;
}