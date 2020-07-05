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
#define vi deque<int>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define il pair<int,ll>
#define pll pair<ll,ll>
#define _path pair<ll,pair<ll,int> > 
#define vv deque
//#define endl '\n'
#define mp make_pair

using namespace std;

const int MAXN = 100000+5;
const int LOGN = 18;
const int INF = 1e9;


void solve(){
	int k,n,m,o;
	cin >> k >> n >> m >> o;
	int NUM_BL = n/k;
	int outgoing[NUM_BL][k];
	int dp[LOGN][NUM_BL][k][k];// id of block, 2^i, subindex1, subindex2;
	FOR(i,LOGN)FOR(j,NUM_BL)FOR(x,k)FOR(y,k)dp[i][j][x][y] = INF;

	FOR(i,m){
		int a,b,c;
		cin >> a >> b >> c;
		dp[0][a/k][a%k][b%k] = c;
	}
	// compute the full sparse Table dp
	FOR(i,LOGN){
		if(i == 0)continue;
		FOR(j,NUM_BL){
			FOR(x,k){
				FOR(y,k){
					FOR(z,k){
						if(j + (1<<(i-1)) >= NUM_BL){
							dp[i][j][x][y] = INF;
						}
						else dp[i][j][x][y] = min(dp[i][j][x][y],dp[i-1][j][x][z] + dp[i-1][j+(1<<(i-1))][z][y]);
					}
				}
			}
		}
	}
	
	FOR(i,o){
		int a,b;
		cin >> a >> b;
		int f[k];
		FOR(i,k)f[i] = INF;
		f[a%k] = 0;
		a = a/k;
		for(int i = LOGN-1;i >= 0;i--){
			int nxt = a + (1<<i);
			if(nxt <= b/k){
				int g[k];
				FOR(x,k)g[x] = INF;
				FOR(x,k){
					FOR(y,k){
						g[x] = min(g[x],f[y] + dp[i][a][y][x]);
					}
				}
				FOR(x,k)f[x] = g[x];
				a = nxt;
			}
		}
		if(f[b%k] >= INF){
			cout << -1 << endl;
		}else
			cout << f[b%k] << endl;
	}
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
	//cin >> t;
	while(t--){
		solve();
	}
	return 0;
}