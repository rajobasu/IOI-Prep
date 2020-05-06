/*
SOLUTION : Easy DP
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <deque>
#include <iomanip>
#include <cmath>
#include <set>
#include <stack>
#include <map>
#include <unordered_map>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long 
//#define int long long
#define ld long double
#define vi vector<int>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define vv vector
#define endl '\n'

using namespace std;

const int MAXN = 200*1000 + 5;

vi g[MAXN];
int res;
int dfs(int node,int p=-1){
	int mx = 0;
	int mx2 = 0;
	for(auto e : g[node]){
		if(e == p)continue;
		int val = dfs(e,node);
		if(val >=mx){
			mx2 = mx;
			mx = val;
		}else mx2 = max(mx2,val);
	}
	int sz = g[node].size();
	int newVal = mx+mx2+sz-2 + (mx2 == 0);
	res = max(res,newVal);
	return mx + sz-2 + (mx == 0);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	FOR(i,n-1){
		int a,b;
		cin >> a >> b;a--;b--;
		//a = 0;b = i+1;
		g[a].pb(b);
		g[b].pb(a);
	}
	dfs(0);
	cout << res << endl;
	return 0;
}