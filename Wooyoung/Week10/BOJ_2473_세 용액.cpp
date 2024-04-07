#include<iostream>
#include<algorithm>
#include<vector>
#include<climits>
#include<queue>
#define MAX LLONG_MAX
using namespace std;

int n;
vector<int>nums;
priority_queue<int, vector<int>, greater<>>ans;
long long sum = MAX;

void func(int idx) {

	int now_num = nums[idx];
	int start = 0, end = n - 1;
	if (idx == 0) {
		start = 1;
	}
	else if (idx == n - 1) {
		end = n - 2;
	}
	// long long (nums[start] + nums[end] + now_num)을 해버리면 안됨!
	while (start < end) {
		long long temp_sum = (long long)nums[start] + nums[end] + now_num;
		if (abs(sum) > abs(temp_sum)) {
			sum = temp_sum;
			while (!ans.empty()) {
				ans.pop();
			}
			ans.push(nums[start]);
			ans.push(nums[end]);
			ans.push(now_num);
		}
		if (temp_sum < 0) {
			start++;
			if (start == idx)start++;
		}
		else {
			end--;
			if (end == idx)end--;
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

	for (int i = 0; i < n; i++) {
		func(i);
	}

	while (!ans.empty()) {
		cout << ans.top() << " ";
		ans.pop();
	}

	return 0;
}