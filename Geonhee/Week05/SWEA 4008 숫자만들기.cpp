#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int t, n;
int arr[4];
int num[13];
int maxi = -21e8;
int mini = 21e8;

void dfs(int x, int temp, int plus, int sub, int mul, int div) {
    if (x == n) { //수식 다썻으면 최대 값, 최소 값 비교
        maxi = max(maxi, temp);
        mini = min(mini, temp);
        return;
    }
    if (plus) //+ 남아있으면 +해주고 + 갯수-1
        dfs(x + 1, temp + num[x], plus - 1, sub, mul, div);
    if (sub) // - 남아있으면 -해주고 - 갯수 -1
        dfs(x + 1, temp - num[x], plus, sub - 1, mul, div);
    if (mul) // * 남아있으면 *해주고 * 갯수 -1
        dfs(x + 1, temp * num[x], plus, sub, mul - 1, div);
    if (div && num[x] != 0) // / 남아있고 num[x]가 0이 아니라면 /해주고 / 갯수 -1
        dfs(x + 1, (int)temp / num[x], plus, sub, mul, div - 1);


}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++) {
        maxi = -21e8;
        mini = 21e8;
        memset(arr, 0, sizeof(arr));
        memset(num, 0, sizeof(num));
        cin >> n;
        for (int j = 0; j < 4; j++) {
            cin >> arr[j];
        }
        for (int j = 0; j < n; j++) {
            cin >> num[j];
        }
        // 시작인덱스, 계산될 값, +갯수, -갯수, *갯수, /갯수
        dfs(1, num[0], arr[0], arr[1], arr[2], arr[3]);
        cout << "#" << i + 1 << " " << maxi - mini << '\n';
    }

    return 0;
}
