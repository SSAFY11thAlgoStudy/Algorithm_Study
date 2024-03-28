#include <iostream>
#include <algorithm>
using namespace std;

int n, q;
int arr[50001];

int bs(int x) {
    int st = 0;
    int en = n - 1;
    int mid = 0;
    while (st <= en) {
        mid = (st + en) / 2;
        // x를 찾았으면 인덱스 값 return해주기
        if (x == arr[mid]) return mid;
        // 현재 arr[mid] 값이 더 크다면 en index값  mid값보다 1 줄여주기
        else if (arr[mid] > x) en = mid - 1;
        // 현재 arr[mid]값이 더 작다면 st index값 mid값보다 1 늘려주기
        else st = mid + 1;
    }
    return 0;
}

int main() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    //이분탐색을 위한 정렬
    sort(arr, arr + n);
    for (int i = 0; i < q; i++) {
        int a;
        cin >> a;
        //처음인 경우와 마지막인 경우 중간 값이 될 수 없으므로 0 출력
        if (arr[0] == a || arr[n - 1] == a) {
            cout << 0 << '\n';
            continue;
        }
        else {
            int idx = bs(a);
            //현재 인덱스 보다 작은거에 개수 * 큰거에 개수
            cout << idx * (n - idx - 1) << '\n';
        }
    }
    return 0;
}