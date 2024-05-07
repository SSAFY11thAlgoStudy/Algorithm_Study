#include<iostream>
#include<unordered_map>
using namespace std;
int t, n;
unordered_map<string, string>par;
unordered_map<string, int>cnt;
void init(string s1, string s2) {
	if (par.count(s1) == 0) {
		par[s1] = s1;
		cnt[s1] = 1;
	}
	if (par.count(s2) == 0) {
		par[s2] = s2;
		cnt[s2] = 1;
	}
}

string find(string tar) {
	if (tar == par[tar])return tar;
	string ret = find(par[tar]);
	par[tar] = ret;
	return ret;
}

void setUnion(string s1, string s2) {
	string t1 = find(s1);
	string t2 = find(s2);
	if (t1 == t2)return;
	par[t2] = t1;
	cnt[t1] += cnt[t2];
}

void func() {
	par.clear();
	cnt.clear();
	cin >> n;

	for (int i = 0; i < n; i++) {
		string s1, s2;
		cin >> s1 >> s2;
		init(s1, s2);
		//if (find(s1) == find(s2))continue;
		setUnion(s1, s2);
		cout << cnt[find(s1)] << "\n";
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) {
		func();
	}
	return 0;
}