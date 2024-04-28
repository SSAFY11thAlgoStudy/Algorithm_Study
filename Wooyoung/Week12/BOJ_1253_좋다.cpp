#include <iostream>
#include<algorithm>
#include<vector>
using namespace std;

int n, ans;
vector<int>nums;

void func() {
	// 두개의 포인터를 0,n-1번 인덱스로 두고 시작한다.
	// 현재 i는 left와 right가 가질 수 없다. (다른 두 수의 합으로만 이루어져야 함)
	for (int i = 0; i < n; i++) {
		int now_num = nums[i];
		int left = 0, right = n - 1;
		while (left < right) {
			int sum = nums[left] + nums[right];
			// 현재 합이 더 작은 경우 -> left+1 
			if (sum < now_num) {
				left++;

			}
			// 현재 합이 더 큰 경우 -> right -1
			else if (sum > now_num) {
				right--;
			}
			// 좋은 수인가?
			else {
				if (left != i && right != i) {

					ans++;
					break;
				}
				else {
					if (left == i) {
						left++;
					}
					else {
						right--;
					}
					continue;
				}
			}
		}

	}
}

int main() {
	cin >> n;
	nums.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	sort(nums.begin(), nums.end());
	func();
	cout << ans;
	return 0;
}