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
#include <fstream>
#include <complex>
#include <stack>
#include <set>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define vv vector
#define ff first
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 
#define ld long double
#define pld pair<ld,ld>
#define iii pair<ii,int>

using namespace std;

const int INF = 1e9;
const int MAXN = 400+5;
const int MAXK = 100+10;
// 0 = red, 1 = green, 2 = blue;
int dp[2][MAXN][MAXN][3]; // [index][redused][blueused][color of last cell] = min cost (blue used can be inferred)
int prefixSum[MAXN][3];


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

   	int n;
   	string s;
   	FOR(i,2)FOR(j,MAXN)FOR(k,MAXN)FOR(l,3)dp[i][j][k][l] = INF;
   	cin >> n;
   	cin >> s;
   	vi r,g,b;
   	FOR(i,n){
   		switch(s[i]){
   			case 'R':r.pb(i);break;
   			case 'G':g.pb(i);break;
   			case 'Y':b.pb(i);break;
   		}
   		if(i == 0){
   			prefixSum[i][0] = s[i] == 'R';
   			prefixSum[i][1] = s[i] == 'G';
   			prefixSum[i][2] = s[i] == 'Y';
   		}else{
   			prefixSum[i][0] = (s[i] == 'R') + prefixSum[i-1][0];
   			prefixSum[i][1] = (s[i] == 'G') + prefixSum[i-1][1];
   			prefixSum[i][2] = (s[i] == 'Y') + prefixSum[i-1][2];
   		}
   	}


   	FOR(i,n){
   		FOR(j,MAXN)FOR(k,MAXN)FOR(l,3){
   			dp[0][j][k][l] = dp[1][j][k][l];
   			dp[1][j][k][l] = INF;
   		}
   		FOR(rr,r.size()+1){
   			FOR(gg,g.size()+1){
   				int bb = (i+1) - (rr+gg);
   				if(min(bb,min(rr,gg)) < 0 or bb > b.size())continue;
   				//cout << rr << " " << gg << " " << bb << endl;
   				
   				// try making this a red color cell;
   				if(rr > 0){
   					int cst = 0;
	   				if(i == 0){
	   					cst = 0;
	   				}else{
	   					cst = min(dp[0][rr-1][gg][1],dp[0][rr-1][gg][2]);
	   				}

	   				int ctr = r[rr-1];
	   				ctr -= min(rr-1,prefixSum[r[rr-1]][0]);
	   				ctr -= min(gg,prefixSum[r[rr-1]][1]);
	   				ctr -= min(bb,prefixSum[r[rr-1]][2]);
	   				dp[1][rr][gg][0] = min(dp[1][rr][gg][0],ctr + cst);
	   			}
	   			// try for green
	   			if(gg > 0){
   					int cst = 0;
	   				if(i == 0){
	   					cst = 0;
	   				}else{
	   					cst = min(dp[0][rr][gg-1][0],dp[0][rr][gg-1][2]);
	   				}
	   				
	   				int ctr = g[gg-1];
	   				ctr -= min(rr,prefixSum[g[gg-1]][0]);
	   				ctr -= min(gg-1,prefixSum[g[gg-1]][1]);
	   				ctr -= min(bb,prefixSum[g[gg-1]][2]);
	   				dp[1][rr][gg][1] = min(dp[1][rr][gg][1],ctr + cst);
	   			}
	   			// try for blue
	   			if(bb > 0){
   					int cst = 0;
	   				if(i == 0){
	   					cst = 0;
	   				}else{
	   					cst = min(dp[0][rr][gg][0],dp[0][rr][gg][1]);
	   				}
	   				int ctr = b[bb-1];
	   				ctr -= min(rr,prefixSum[b[bb-1]][0]);
	   				ctr -= min(gg,prefixSum[b[bb-1]][1]);
	   				ctr -= min(bb-1,prefixSum[b[bb-1]][2]);
	   				dp[1][rr][gg][2] = min(dp[1][rr][gg][2],ctr + cst);
	   			}
   			}
   		}
   	}
   	int ans = INF;
   	FOR(k,3)ans = min(dp[1][r.size()][g.size()][k],ans);
   	if(ans >= INF){
   		cout << -1 << endl;
   	}else{
   		cout << ans << endl;
   	}

    return 0;
}