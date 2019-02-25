/*
SOLUTION: DFS,Fast io
COMPLEXITY: O(n)
*/

#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <stdio.h>
#include <cmath>
#include <queue>
#include <string>
#include <map>
#include <complex>
#include <stack>
#include <set>
#include <fstream>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>
#define ld long double

using namespace std;

const int MOD = 1000000007;
const ll INF = 1000000000000000000;
const int MAXN = 1000001;

#define pil pair<int,ll>

vector<pair<int,ll> > g[MAXN];
ll ans = 0;
int n;

int dfs(int node,int p,ll wt){
	int tot = 1;
	FOR(i,g[node].size()){
		pil child = g[node][i];
		if(child.ff == p)continue;
		tot += dfs(child.ff,node,child.ss);
		
	}

	
	ans += wt*abs(tot - (n-tot));
	return tot;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n;
	//cout << "af" << endl;
	FOR(i,n-1){
		int a,b,c;
		cin >> a >> b >> c;
		a--;b--;
		//cout << a << " " << b << endl;
		g[a].pb(mp(b,c));
		g[b].pb(mp(a,c));
	}
	dfs(0,-1,0);
	cout << ans << endl;
	return 0;
}
