#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

int map[10][10];
int T, N;


int main() {
    //freopen("sample_input.txt", "r", stdin);
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cin >> N;
        memset(map, 0, sizeof(map));
        map[0][0] = 1;
        for (int i = 1; i < N; i++) {
            for (int j = 0; j <= i; j++) {
                if (j == 0 || j == i) {
                    map[i][j] = 1;
                }
                else {
                    map[i][j] = map[i - 1][j - 1] + map[i - 1][j];
                }
            }
        }
        cout << "#" << i << "\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (map[i][j] != 0) {
                    cout << map[i][j] << " ";
                }
            }
            cout << "\n";
        }

    }



    return 0;
}