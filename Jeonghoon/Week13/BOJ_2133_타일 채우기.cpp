#include <iostream>

using namespace std;

long long dp[32];

int main()
{
    int n;
    cin >> n;

    //n이 0이면 0을 출력해야 하므로
    if (n != 0) {
        dp[0] = 1;
        dp[2] = 3;


        for (int i = 4; i <= n; i++) {
            dp[i] = dp[i - 2] * 3;

            for (int j = i - 4; j >= 0; j -= 2) {
                dp[i] += dp[j] * 2;
            }
        }
    }

    cout << dp[n];
    return 0;
}