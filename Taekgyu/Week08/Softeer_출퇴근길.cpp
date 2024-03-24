#define _CRT_SECURE_NO_WARININGS
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

int n, m;
int S, T;
vector<int>v[200001];
vector<int>cv[200001];
// 갈 필요가 없는 마을을 고른다
int SDAT1[100001];
int SDAT2[100001];
int TDAT1[100001];
int TDAT2[100001];
int ansCnt;

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int to, from;
        cin >> to >> from;
        v[to].push_back(from);
        cv[from].push_back(to);
    }
    cin >> S >> T;
}

void ftoT(int now) {

    if (SDAT1[now] == 1) {
        return;
    }
    SDAT1[now] = 1;
    for (int i = 0; i < v[now].size(); i++)
    {
        ftoT(v[now][i]);
    }
}

void stoT(int now) {

    if (SDAT2[now] == 1) {
        return;
    }
    SDAT2[now] = 1;
    for (int i = 0; i < cv[now].size(); i++)
    {
        stoT(cv[now][i]);
    }
}

void ftoS(int now) {

    if (TDAT1[now] == 1) {
        return;
    }
    TDAT1[now] = 1;
    for (int i = 0; i < v[now].size(); i++)
    {
        ftoS(v[now][i]);
    }
}

void stoS(int now) {

    if (TDAT2[now] == 1) {
        return;
    }
    TDAT2[now] = 1;
    for (int i = 0; i < cv[now].size(); i++)
    {
        stoS(cv[now][i]);
    }
}

int main() {
    //freopen("sample_input.txt", "r", stdin);

    input();
    SDAT1[T] = 1;
    ftoT(S);
    stoT(S);

    TDAT1[S] = 1;

    ftoS(T);
    stoS(T);

    for (int i = 1; i <= n; i++)
    {
        if (i == S || i == T)continue;
        int Num = SDAT1[i] + SDAT2[i] + TDAT1[i] + TDAT2[i];
        if (Num == 4) {
            ansCnt++;
        }
    }
    cout << ansCnt;

    return 0;
}