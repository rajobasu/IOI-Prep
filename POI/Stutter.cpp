/*
SOLUTION : basically the standard DP with some memory optimisation
We need to store some specific positions in memory due to two
occurances. We can either do it using a map(which gives TLE),
or a simple lookup array by utilising the fact that each 'j' will
have a unique last value of 'i' and hence it is okay to just 
store the 'j' value. 

*/



//#pragma GCC target ("avx2")

//#pragma GCC optimization ("unroll-loops")

#include <stdio.h>      /* printf */
#include <stdlib.h>     /* qsort */
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
//#include <ext/pb_ds/assoc_container.hpp>
//using namespace __gnu_pbds;


#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long 
#define ld long double
//#define int short
#define vi vector<int>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define pll pair<ll,ll>
#define plll pair<ll,pll>
#define vv vector
#define endl '\n'
#define max(a,b) (a>b?a:b)

using namespace std;

const int MAXN = 15*1005;
int a[MAXN];
int b[MAXN];
int n,m;
int pa[MAXN];
int pb[MAXN];
int c[2][MAXN];




int lookup[MAXN];
signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	scanf("%d %d",&n,&m);
	FOR(i,n)scanf("%d",&a[i]);
	FOR(i,m)scanf("%d",&b[i]);
	FOR(i,n)pa[i] = -1;
	FOR(j,m)pb[j] = -1;
	FOR(i,n)FOR(j,i)if(a[j] == a[i])pa[i] = j;
	FOR(i,m)FOR(j,i)if(b[j] == b[i])pb[i] = j;
	FORE(i,1,n-1){
		c[1][0] = c[0][0];
		FORE(j,1,m-1){
			c[1][j] = max(c[0][j], (j>0?c[1][j-1]:0));
			if(a[i] == b[j]){
			 	if(pa[i] != -1 and pb[j] != -1){
					int prev = 0;
					if(pa[i] >0 and pb[j] > 0)prev = lookup[pb[j]-1];
					c[1][j] = max(c[1][j],(2 + prev));
				}
			}
		}
		FOR(j,m)if(a[i] == b[j])lookup[j-1] = c[0][j-1];
		FOR(j,m)c[0][j] = c[1][j];
	}
	printf("%d\n",c[1][m-1]);
	return 0;
}