#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <deque>
#include <iomanip>
#include <list>
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
#define vi vector<ll>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define il pair<ll,ll>
#define vv vector
#define endl '\n'

using namespace std;

const int MAXN = 1001;
char grid[MAXN][MAXN];

void solve(){
	int n,m,a,b;
	cin >> n >> m >> a >> b;
	FOR(i,n){
		string s;
		cin >> s;
		FOR(j,m)grid[i][j] = s[j];
	}
	vv<ii> all;
	ii first = {-1,-1};
	FOR(i,a){
		string s;
		cin >> s;
		FOR(j,b){
			if(s[j] == 'x'){
				if(first.ff == -1)first = {i,j};
				all.pb({i,j});
			}
		}
	}
	// got all the input
	FOR(i,n){
		FOR(j,m){
			if(grid[i][j] == 'x'){
				// try and delete everything: 
				for(auto e : all){
					int x = i + e.ff - first.ff;
					int y = j + e.ss - first.ss;
					if(x >= n or y >= m or x < 0 or y < 0 or grid[x][y] != 'x'){
						cout << "NIE" << endl;
						return;
					}else{
						grid[x][y] = '.';
					}
				}
			}
		}
	}
	cout << "TAK" << endl;
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int q;
	cin >> q;
	while(q--)solve();
	return 0;
}