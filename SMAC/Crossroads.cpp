/*
SOLUTION: fix a column span and do a 2ptr on the rows.
COMPLEXITY: O(n^3)
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
#define ii pair<ll,ll>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>


using namespace std;

const int MOD = 1000000007;
const ll INF = 100000000000000000;
const int MAXN = 200001;

int main(){
	int h,w;ll budget;
	cin >>w >> h >> budget;

	ll mat[h][w];
	FOR(i,h)FOR(j,w)cin >> mat[i][j];
	ll pref_hor[h][w];
	ll sum_ver[w];
	FOR(i,w){
		ll tot = 0;
		FOR(j,h){
			tot += mat[j][i];
		}
		sum_ver[i] = tot;
	}

	FOR(i,h){

		FOR(j,w){
			if(j == 0)pref_hor[i][j] = mat[i][j];
			else pref_hor[i][j] = pref_hor[i][j-1]+mat[i][j];
		}
	}

	ll mx = 0;
	ll best = 0;
	FOR(right,w){
		FOR(left,right+1){
			// from left to right is fixed. Now do a 2-ptr on vertical portion
			ll tot = 0;
			FORE(i,left,right)tot+=sum_ver[i];
			if(tot > budget)continue;
			ll covered = (right-left+1)*h;
			int UPTR = -1;
			int LPTR = 0;
			while(LPTR < h and UPTR < h-1){
				while(UPTR < h-1 and (tot+pref_hor[UPTR+1][w-1]+(left>0?pref_hor[UPTR+1][left-1]:0) - pref_hor[UPTR+1][right]) <= budget){
					tot += pref_hor[UPTR+1][w-1]+(left>0?pref_hor[UPTR+1][left-1]:0) - pref_hor[UPTR+1][right];
					UPTR++;
				}
				if(UPTR>=LPTR){
					ll c2overed = (UPTR-LPTR+1)*(w - (right-left+1));
					mx = max(mx,c2overed + covered);
				}
				//cout << tot << " : " << left << " " << right << endl;
				//mx = max(mx,tot);
				
				tot -= pref_hor[LPTR][w-1]+(left>0?pref_hor[LPTR][left-1]:0) - pref_hor[LPTR][right];
				LPTR++;
			}
		}
	}
	cout << mx << endl;


	return 0;
}