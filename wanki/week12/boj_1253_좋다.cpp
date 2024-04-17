#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int arr[2000];

int N, result = 0;

void input() {
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> arr[i];
    sort(arr, arr + N);
}


int main() {
    input();
    for (int i = 0; i < N; i++) {
        int left = 0, right = N - 1, sum;
        while (left < right) {
            sum = arr[left] + arr[right];
            if (sum == arr[i]) {
                if (left != i && right != i) {
                    result++;
                    break;
                }
                else if (left == i) left++;
                else if (right == i) right--;
            }
            else if (sum < arr[i]) left++;
            else right--;
        }
    }
    cout << result;
    return 0;
}