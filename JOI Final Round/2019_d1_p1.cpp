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

const int MAXN = 3000;
const int MAXK = 100+10;

string s[MAXN];
ll tolow[MAXN][MAXN];
ll tori[MAXN][MAXN];

int main(){
	int n,m;
	cin >> n >> m;
	FOR(i,n){
		cin >> s[i];
	}
	FOR(j,m){
		tolow[n-1][j] = s[n-1][j] == 'I';
		for(int i = n-2;i>=0;i--){
			tolow[i][j] = tolow[i+1][j] + (s[i][j] == 'I');
		}
	}
	FOR(i,n){
		tori[i][m-1] = s[i][m-1] == 'O';
		for(int j = m-2;j>=0;j--){
			tori[i][j] = tori[i][j+1] + (s[i][j] == 'O');
		}
	}
	ll ans = 0;
	FOR(i,n){
		FOR(j,m){
			if(s[i][j] == 'J')ans += tori[i][j]*tolow[i][j];
		}
	}
	cout << ans << endl;
	return 0;
}