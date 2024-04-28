#include <iostream>
#include<algorithm>
#include<vector>
using namespace std;

int n, ans;
vector<int>nums;

void func() {
	// �ΰ��� �����͸� 0,n-1�� �ε����� �ΰ� �����Ѵ�.
	// ���� i�� left�� right�� ���� �� ����. (�ٸ� �� ���� �����θ� �̷������ ��)
	for (int i = 0; i < n; i++) {
		int now_num = nums[i];
		int left = 0, right = n - 1;
		while (left < right) {
			int sum = nums[left] + nums[right];
			// ���� ���� �� ���� ��� -> left+1 
			if (sum < now_num) {
				left++;

			}
			// ���� ���� �� ū ��� -> right -1
			else if (sum > now_num) {
				right--;
			}
			// ���� ���ΰ�?
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